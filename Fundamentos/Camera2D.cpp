#include "Camera2D.h"

Camera2D::Camera2D() : position(0,0),
cameraMatrix(1.0f),
scale(1.0f),
needsMatrixUpdate(true),
orthoMatrix(1.0f),
screenWidth(500), screenHeight(500)
{
}

Camera2D::~Camera2D()
{
}

void Camera2D::init(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
}

void Camera2D::update()
{
	/*if (needsMatrixUpdate) {
		glm::vec3 translate(-position.x + screenWidth / 2, -position.y + screenHeight / 2, 0.0f);
		cameraMatrix = glm::translate(orthoMatrix, translate);

		glm::vec3 scale(scale, scale, 0.0f);
		cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * cameraMatrix;
		needsMatrixUpdate = false;
	}*/
}

