#include"Camera.hpp"
#include"Globals.hpp"
#include<glm/gtc/matrix_transform.hpp>


Camera::Camera(const glm::vec2& point)
{
	init(point);
}


void Camera::init(const glm::vec2& point)
{

	view = glm::mat4();
	position = glm::vec3(point.x,point.y, 1.0f);

	view = glm::lookAt(position, glm::vec3(position.x, position.y, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

}


void Camera::update(const glm::vec2& point)
{
	position = glm::vec3(point.x-(Globals::WIDTH/2.0f),point.y-(Globals::HEIGHT/2.0f),.1f);
	
	//Clamps the position of the camera according to the map size
	position = glm::clamp(position,glm::vec3(0.0f,0.0f,.1f),glm::vec3(mapSize,.1f));
	view = glm::lookAt(position,glm::vec3(position.x,position.y,0.0f),glm::vec3(0.0f,1.0f,0.0f));
}


void Camera::setMapSize(const glm::vec2& _mapSize)
{
	this->mapSize = _mapSize;
}
