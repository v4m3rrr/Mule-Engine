#include "Keyboard.h"

Keyboard::Event::Event()
	:state(Type::Invaild),key(0)
{
}

Keyboard::Event::Event(Type state, unsigned char key) noexcept
	:state(state),key(key)
{
}

Keyboard::Event::Type Keyboard::Event::GetState() const noexcept
{
	return state;
}

unsigned char Keyboard::Event::GetKey() const noexcept
{
	return key;
}

bool Keyboard::IsKeyPressed(unsigned int vKey) const noexcept
{
	return vKeystates.test(vKey);
}

void Keyboard::Flush() noexcept
{
	vKeys = std::queue<Event>();
	chars = std::queue<wchar_t>();
}

bool Keyboard::AreKeysEmpty() const noexcept
{
	return vKeys.empty();
}

Keyboard::Event Keyboard::ReadKey() noexcept
{
	if (!AreKeysEmpty()) 
	{
		Event key = vKeys.front();
		vKeys.pop();
		return key;
	}
	else
	{
		return Event();
	}
}

void Keyboard::FlushKeys() noexcept
{
	vKeys = std::queue<Event>();
}

bool Keyboard::AreCharsEmpty() const noexcept
{
	return chars.empty();
}

wchar_t Keyboard::ReadChar() noexcept
{
	if (!AreCharsEmpty())
	{
		wchar_t c = chars.front();
		chars.pop();
		return c;
	}
	else
	{
		return 0;
	}
}

void Keyboard::FlushChars() noexcept
{
	chars = std::queue<wchar_t>();
}

void Keyboard::EnableAutoRepeat() noexcept
{
	enableAutoRepeat = true;
}

void Keyboard::DisableAutoRepeat() noexcept
{
	enableAutoRepeat = false;
}

bool Keyboard::IsAutoRepeatEnabled() const noexcept
{
	return enableAutoRepeat;
}

void Keyboard::ClearKeyStates() noexcept
{
	vKeystates.reset();
}

void Keyboard::OnKeyPressed(unsigned int vKey)noexcept
{
	vKeystates[vKey] = true;
	vKeys.push(Event(Event::Type::Pressed, vKey));
	TrimQueue(vKeys);
}

void Keyboard::OnKeyReleased(unsigned int vKey)noexcept
{
	vKeystates[vKey] = false;
	vKeys.push(Event(Event::Type::Released, vKey));
	TrimQueue(vKeys);
}

void Keyboard::OnChar(unsigned int vKey) noexcept
{
	chars.push(vKey);
	TrimQueue(chars);
}

template<typename T>
void Keyboard::TrimQueue(std::queue<T>& queue) noexcept
{
	while (queue.size() > QUEUE_SIZE)
		queue.pop();
}
