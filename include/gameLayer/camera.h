#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtx/transform.hpp>


int getViewDirectionRotation(glm::vec3 vec);

struct Camera
{
	Camera() = default;
	Camera(float aspectRatio, float fovRadians)
		:aspectRatio(aspectRatio),
		fovRadians(fovRadians)
	{
	}

	glm::vec3 up = {0.f,1.f,0.f};

	float aspectRatio = 1;
	float fovRadians = glm::radians(70.f);

	float closePlane = 0.01f;
	float farPlane = 420.f;


	glm::vec3 position = {0,0,2};
	glm::vec3 viewDirection = {0,0,-1};

	glm::mat4x4 getProjectionMatrix();
	glm::mat4x4 getViewMatrix();

	int getViewDirectionRotation()
	{
		return ::getViewDirectionRotation(viewDirection);
	}

	void rotateCamera(const glm::vec2 delta);
	float yaw = 0.f;
	float pitch = 0.f;

	void moveFPS(glm::vec3 direction);
	void rotateFPS(glm::ivec2 mousePos, float speed, bool shouldMove);
	glm::ivec2 lastMousePos = {};

	glm::mat4x4 lastFrameViewProjMatrix = getProjectionMatrix() * getViewMatrix();

	bool operator==(const Camera& other)
	{
		return
			(up == other.up)
			&& (aspectRatio == other.aspectRatio)
			&& (fovRadians == other.fovRadians)
			&& (closePlane == other.closePlane)
			&& (farPlane == other.farPlane)
			&& (position == other.position)
			&& (viewDirection == other.viewDirection)
			;
	};

	bool operator!=(const Camera& other)
	{
		return !(*this == other);
	};


};


glm::mat4 lookAtSafe(glm::vec3 const &eye, glm::vec3 const &center, glm::vec3 const &upVec);
