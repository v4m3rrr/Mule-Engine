#pragma once
#include "MuleWin.h"

#include <queue>

class Mouse
{
	friend class Window;
public:
	//Doesnt operate with XButtons
	enum class Button
	{
		None = 0b0,
		Left = 0b1,
		Middle = 0b10,
		Right = 0b100
	};
public:
	class Event
	{
	public:
		enum class Type
		{
			Pressed,
			Released,
			MouseMove,
			WheelUp,
			WheelDown,
			Invalid
		};
	public:
		Event() noexcept;
		Event(int posX, int posY, Type type, Button button = Button::None) noexcept;

		Type GetType() const noexcept;
		Button GetButton() const noexcept;
		int GetPosX() const noexcept;
		int GetPosY() const noexcept;
	private:
		Type type;
		Button button;

		int posX, posY;
	};
public:
	Mouse() noexcept;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	~Mouse() noexcept = default;
public:
	int GetPosX() const noexcept;
	int GetPosY() const noexcept;
	bool IsButtonPressed(Button button) const noexcept;

	bool IsQueueEmpty() const noexcept;
	Event Read() noexcept;
private:
	void ClearButtonsStates() noexcept;

	void OnMoved(int posX, int posY) noexcept;
	void OnPressed(int posX, int posY, Button button) noexcept;
	void OnReleased(int posX, int posY, Button button) noexcept;
	void OnWheelMoved(int posX, int posY, bool isUp) noexcept;

	static void TrimQueue(std::queue<Event>& queue) noexcept;
private:
	int posX;
	int posY;

	Button buttonsPressed = Button::None;

	static constexpr size_t QUEUE_SIZE = 16u;
	std::queue<Event> mouseEvents;
};

inline Mouse::Button operator|(Mouse::Button a, Mouse::Button b);
inline Mouse::Button operator&(Mouse::Button a, Mouse::Button b);
inline Mouse::Button operator~(Mouse::Button a);