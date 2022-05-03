#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera2D
{
private:
	glm::vec2 position;
	bool needsMatrixUpdate;
	glm::mat4 cameraMatrix;
	glm::mat4 orthoMatrix;
	float scale;
	int screenWidth;
	int screenHeight;

public:
	Camera2D();
	~Camera2D();
	void init(int screenWidth, int screenHeight);
	void update();
	void setPosition(const glm::vec2& newPosition) {
		position = newPosition;
		needsMatrixUpdate = true;
	}
	void setScale(float newScale) {
		scale = newScale;
	}
	glm::mat4 getCameraMatrix() {
		return cameraMatrix;
	}
	glm::vec2 getPosition() {
		return position;
	}
	float getScale() {
		return scale;
	}
};

