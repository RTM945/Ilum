#pragma once

#include "Core/Engine/Eventing/Event.hpp"
#include "Core/Engine/PCH.hpp"
#include "Core/Engine/Subsystem.hpp"
#include "Monitor.hpp"

struct SDL_Window;
union SDL_Event;

namespace Ilum
{
class Window : public TSubsystem<Window>
{
  public:
	Window(Context *context = nullptr);

	~Window();

	virtual void onTick(float delta_time) override;

	uint32_t getWidth() const;

	uint32_t getHeight() const;

	uint32_t getPositionX() const;

	uint32_t getPositionY() const;

	const std::string getTitle() const;

	void *getWindowHandle() const;

	void *getSDLHandle() const;

	void setSize(uint32_t width, uint32_t height);

	void setPosition(uint32_t x, uint32_t y);

	void setTitle(const std::string &title);

	void setIcon(const std::string &filepath);

	void minimize();

	void maximize();

	void fullscreen();

	void fullscreenBorderless();

	bool shouldClose();

	void show();

	void hide();

	void focus();

	bool isHidden() const;

	bool isFocused() const;

	bool isShown() const;

	bool isMinimized() const;

	bool isMaximized() const;

	bool isFullscreen() const;

	bool isFullscreenBorderless() const;

  private:
	SDL_Window *m_window = nullptr;
	std::vector<Monitor> m_monitors;
	bool        m_close  = false;

  public:
	Event<const SDL_Event &>  Event_SDL;
	Event<uint32_t, uint32_t> Event_Resize;
	Event<uint32_t, uint32_t> Event_Move;
	Event<>                   Event_Minimize;
	Event<>                   Event_Maximize;
	Event<>                   Event_GainFocus;
	Event<>                   Event_LostFocus;
	Event<>                   Event_Close;
};
}        // namespace Ilum