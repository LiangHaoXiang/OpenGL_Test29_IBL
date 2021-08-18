//
//  Camera.cpp
//  OpenGL_Test7_Light
//
//  Created by Haoxiang Liang on 2021/7/10.
//

#include "Camera.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

//各函数具体实现

Camera::Camera(vec3 position, vec3 up, float yaw, float pitch): Front(vec3(0,0,-1)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch): Front(vec3(0,0,-1)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = vec3(posX, posY, posZ);
    WorldUp = vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

mat4 Camera::GetViewMatrix(){
    return lookAt(Position, Position + Front, WorldUp);
}

void Camera::ProcessKeyboard(Camera_Movement dir, float deltaTime){
    float velocity = MovementSpeed * deltaTime;
    switch (dir) {
        case FORWARD:
            Position += Front * velocity;
            break;
        case BACKWARD:
            Position -= Front * velocity;
            break;
        case LEFT:
            Position -= Right * velocity;
            break;
        case RIGHT:
            Position += Right * velocity;
            break;
        default:
            break;
    }
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        Pitch = glm::min(89.0f, Pitch);
        Pitch = glm::max(-89.0f, Pitch);
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    Zoom = glm::min(80.0f, Zoom);
    Zoom = glm::max(1.0f, Zoom);
}

void Camera::updateCameraVectors(){
    vec3 front;
    front.x = cos(radians(Yaw)) * cos(radians(Pitch));
    front.y = sin(radians(Pitch));
    front.z = sin(radians(Yaw)) * cos(radians(Pitch));
    Front = normalize(front);
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Right = normalize(cross(Front, WorldUp));
    Up = normalize(cross(Right, Front));
}

