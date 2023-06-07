#include "Mouse.h"

//EVENT FUNCTIONS

Mouse::Event::Event() noexcept
	:posX(0), posY(0),type(Mouse::Event::Type::Invalid),button(Mouse::Button::None)
{
}

Mouse::Event::Event(int posX, int posY, Type type, Button button) noexcept
	:posX(posX), posY(posY), type(type), button(button)
{
}

Mouse::Event::Type Mouse::Event::GetType() const noexcept
{
	return type;
}

Mouse::Button Mouse::Event::GetButton() const noexcept
{
	return button;
}

int Mouse::Event::GetPosX() const noexcept
{
	return posX;
}

int Mouse::Event::GetPosY() const noexcept
{
	return posY;
}

inline Mouse::Button operator|(Mouse::Button a, Mouse::Button b)
{
	return (Mouse::Button)((int)a | (int)b);
}

inline Mouse::Button operator&(Mouse::Button a, Mouse::Button b)
{
	return (Mouse::Button)((int)a & (int)b);
}

inline Mouse::Button operator~(Mouse::Button a)
{
	return (Mouse::Button)(~(int)a);
}

bool Mouse::IsQueueEmpty() const noexcept
{
	return mouseEvents.empty();
}

Mouse::Event Mouse::Read() noexcept
{
	if (!IsQueueEmpty()) 
	{
		Event event = mouseEvents.front();
		mouseEvents.pop();
		return event;
	}
	else
	{
		return Event();
	}
}

// MOUSE FUNCTIONS

Mouse::Mouse() noexcept
{
	POINT pos;
	GetCursorPos(&pos);
	posX = pos.x;
	posY = pos.y;
}

int Mouse::GetPosX() const noexcept
{
	return posX;
}

int Mouse::GetPosY() const noexcept
{
	return posY;
}

bool Mouse::IsButtonPressed(Button button) const noexcept
{
	return (bool)(buttonsPressed & button);
}


void Mouse::ClearButtonsStates() noexcept
{
	buttonsPressed = Button::None;
}

void Mouse::OnMoved(int posX, int posY) noexcept
{
	mouseEvents.push(Event(posX, posY, Event::Type::MouseMove));
	TrimQueue(mouseEvents);
	this->posX = posX;
	this->posY = posY;
}

void Mouse::OnPressed(int posX, int posY,Button button) noexcept
{
	mouseEvents.push(Event(posX, posY, Event::Type::Pressed, button));
	TrimQueue(mouseEvents);
	buttonsPressed = buttonsPressed | button;

	this->posX = posX;
	this->posY = posY;
}
void Mouse::OnReleased(int posX, int posY, Button button) noexcept
{
	mouseEvents.push(Event(posX, posY, Event::Type::Released, button));
	TrimQueue(mouseEvents);
	buttonsPressed = ~(~buttonsPressed | button);

	this->posX = posX;
	this->posY = posY;
}

void Mouse::OnWheelMoved(int posX, int posY, bool isUp) noexcept
{
	mouseEvents.push(
		Event(posX, posY,
			isUp ? Mouse::Event::Type::WheelUp : Mouse::Event::Type::WheelDown,
			Mouse::Button::Middle
		)
	);
	TrimQueue(mouseEvents);

	this->posX = posX;
	this->posY = posY;
}

void Mouse::TrimQueue(std::queue<Event>& queue) noexcept
{
	while (queue.size() > QUEUE_SIZE)
		queue.pop();
}
