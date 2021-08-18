//
//  Camera.hpp
//  OpenGL_Test7_Light
//
//  Created by Haoxiang Liang on 2021/7/10.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = 0.0f;
const float PITCH = 0.0f;
const float SPEED = 3.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 60.0f;

class Camera {
public:
    vec3 Position;          //摄像机在世界空间中的位置
    vec3 Front;             //摄像机面向的世界坐标点
    vec3 Up;                //摄像机上向量
    vec3 Right;             //摄像机右向量
    vec3 WorldUp;           //摄像机在世界空间中，世界空间的y轴方向向量

    float Yaw;              //偏航角，在xoz平面中 与x轴的夹角，相当于一条与x轴平行的射线 往z轴正负方向偏来偏去
    float Pitch;            //俯仰角，在xoy平面中 与x轴的夹角，相当于一条与x轴平行的射线 往y轴正负方向偏来偏去
    
    float MovementSpeed;    //移动速度
    float MouseSensitivity; //鼠标灵敏度
    float Zoom;             //视野，用于缩放

    //构造函数声明
    Camera(vec3 position = vec3(0,0,0), vec3 up = vec3(0,1,0), float yaw = YAW, float pitch = PITCH);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    //函数声明
    mat4 GetViewMatrix();
    void ProcessKeyboard(Camera_Movement dir, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    
private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};

#endif /* Camera_hpp */

