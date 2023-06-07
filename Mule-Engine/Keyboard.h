#pragma once
#include "MuleWin.h"

#include <queue>
#include <bitset>

class Keyboard
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			Pressed,
			Released,
			Invaild
		};
	public:
		Event();
		Event(Type state, unsigned char key) noexcept;
		Type GetState() const noexcept;
		unsigned char GetKey() const noexcept;
	private:
		Type state;
		unsigned char key;
	};
public:
	Keyboard() noexcept = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;
	~Keyboard() noexcept = default;
public:
	bool IsKeyPressed(unsigned int vKey)const noexcept;
	void Flush() noexcept;
	//Keys
	bool AreKeysEmpty() const noexcept;
	Event ReadKey() noexcept;
	void FlushKeys() noexcept;
	//Chars
	bool AreCharsEmpty() const noexcept;
	wchar_t ReadChar() noexcept;
	void FlushChars() noexcept;
	//autorepeat control
	void EnableAutoRepeat() noexcept;
	void DisableAutoRepeat() noexcept;
	bool IsAutoRepeatEnabled() const noexcept;
private:
	void ClearKeyStates() noexcept;

	void OnKeyPressed(unsigned int vKey)noexcept;
	void OnKeyReleased(unsigned int vKey)noexcept;
	void OnChar(unsigned int vKey)noexcept;
	
	template<typename T>
	static void TrimQueue(std::queue<T>& queue)noexcept;
private:
	static constexpr size_t V_KEYS_SIZE = 256U;
	static constexpr size_t QUEUE_SIZE = 16u;

	std::bitset<V_KEYS_SIZE> vKeystates; //TRUE - PRESSED ; FALSE - RELEASED
	std::queue<Event> vKeys;
	std::queue<wchar_t> chars;

	bool enableAutoRepeat = false;
};