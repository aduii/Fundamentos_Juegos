#pragma once
#include <unordered_map>
//bajar clase de matrices para la traslacion
class InputManager
{
private:
	std::unordered_map<unsigned int, bool>keys;
public:
	InputManager();
	~InputManager();
	void setMouseCoords(float x, float y);
	void pressKey(unsigned int keyCode);
	void releaseKey(unsigned int keyCode);
	bool isKeyPressed(unsigned int keyCode);
};

