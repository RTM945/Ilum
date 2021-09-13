#include "Core/Engine/PCH.hpp"

#include "Instance.hpp"

namespace Ilum
{
inline const std::vector<const char *> get_instance_extension_supported(const std::vector<const char *> &extensions)
{
	uint32_t extension_count = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

	std::vector<VkExtensionProperties> device_extensions(extension_count);
	vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, device_extensions.data());

	std::vector<const char *> result;

	for (const auto &extension : extensions)
	{
		bool found = false;
		for (const auto &device_extension : device_extensions)
		{
			if (strcmp(extension, device_extension.extensionName) == 0)
			{
				result.emplace_back(extension);
				found = true;
				VK_INFO("Found instance extension: {}", extension);
				break;
			}
		}
		if (!found)
		{
			VK_ERROR("Instance extension {} is not supported", extension);
		}
	}

	return result;
}

inline bool check_layer_supported(const char *layer_name)
{
	uint32_t layer_count;
	vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

	std::vector<VkLayerProperties> layers(layer_count);
	vkEnumerateInstanceLayerProperties(&layer_count, layers.data());

	for (const auto &layer : layers)
	{
		if (strcmp(layer.layerName, layer_name) == 0)
		{
			return true;
		}
	}

	return false;
}

Instance::Instance()
{
	// Initialize volk context
	volkInitialize();

	// Config application info
	VkApplicationInfo app_info{VK_STRUCTURE_TYPE_APPLICATION_INFO};

	uint32_t                       sdk_version                = VK_HEADER_VERSION_COMPLETE;
	uint32_t                       api_version                = 0;
	PFN_vkEnumerateInstanceVersion enumerate_instance_version = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion"));

	if (enumerate_instance_version)
	{
		enumerate_instance_version(&api_version);
	}
	else
	{
		api_version = VK_VERSION_1_0;
	}

	if (sdk_version > api_version)
	{
		std::string sdk_version_str = std::to_string(VK_VERSION_MAJOR(sdk_version)) + "." + std::to_string(VK_VERSION_MINOR(sdk_version)) + "." + std::to_string(VK_VERSION_PATCH(sdk_version));
		std::string api_version_str = std::to_string(VK_VERSION_MAJOR(api_version)) + "." + std::to_string(VK_VERSION_MINOR(api_version)) + "." + std::to_string(VK_VERSION_PATCH(api_version));
		VK_WARN("Using Vulkan {}, please upgrade your graphics driver to support Vulkan {}", api_version_str, sdk_version_str);
	}

	app_info.pApplicationName   = "IlumEngine";
	app_info.pEngineName        = "IlumEngine";
	app_info.engineVersion      = VK_MAKE_VERSION(0, 0, 1);
	app_info.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
	app_info.apiVersion         = std::min(sdk_version, api_version);

	// Check out extensions support
	std::vector<const char *> extensions_support = get_instance_extension_supported(m_extensions);

	// Config instance info
	VkInstanceCreateInfo create_info{VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
	create_info.pApplicationInfo        = &app_info;
	create_info.enabledExtensionCount   = static_cast<uint32_t>(extensions_support.size());
	create_info.ppEnabledExtensionNames = extensions_support.data();
	create_info.enabledLayerCount       = 0;

	// Validation features
	VkValidationFeaturesEXT validation_features{VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT};
	validation_features.enabledValidationFeatureCount = static_cast<uint32_t>(m_validation_extensions.size());
	validation_features.pEnabledValidationFeatures    = m_validation_extensions.data();

	// Enable validation layers
	if (m_debug_enable)
	{
		// Enable validation layer
		if (check_layer_supported(m_validation_layers.front()))
		{
			create_info.enabledLayerCount   = static_cast<uint32_t>(m_validation_layers.size());
			create_info.ppEnabledLayerNames = m_validation_layers.data();
			create_info.pNext               = &validation_features;
		}
		else
		{
			VK_ERROR("Validation layer was required, but not avaliable, disabling debugging");
			m_debug_enable = false;
		}
	}

	// Create instance
	if (!VK_CHECK(vkCreateInstance(&create_info, nullptr, &m_handle)))
	{
		return;
	}
	else
	{
		// Config to volk
		volkLoadInstance(m_handle);
	}

	// Initialize instance extension functions
	Vulkan::FunctionEXT::initialzize(m_handle);

	// Enable debugger
	if (m_debug_enable)
	{
		Vulkan::Debugger::initialize(m_handle);
	}
}

Instance::~Instance()
{
	if (m_debug_enable)
	{
		Vulkan::Debugger::shutdown(m_handle);
	}

	vkDestroyInstance(m_handle, nullptr);
}

bool Instance::isDebugEnable() const
{
	return m_debug_enable;
}
}        // namespace Ilum