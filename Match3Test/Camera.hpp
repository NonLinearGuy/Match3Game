#ifndef INC_CAMERA_H
#define INC_CAMERA_H

#include<glm/glm.hpp>
#include<memory>


class Camera
{
	glm::mat4 view;
	glm::vec3 position;
	glm::vec2 mapSize;

public:

	Camera(const glm::vec2& point);


	void init(const glm::vec2& point);

	void update(const glm::vec2&);

	inline glm::mat4 getView()
	{
		return view;
	}


	void setMapSize(const glm::vec2& mapSize);


	inline glm::vec2 getPosition()
	{
		return glm::vec2(position.x,position.y);
	}

};


#endif
