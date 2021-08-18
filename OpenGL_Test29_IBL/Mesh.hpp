//
//  Mesh.hpp
//  OpenGL_Test10_MyModel
//
//  Created by Haoxiang Liang on 2021/7/26.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

using namespace std;
using namespace glm;

struct Vertex {
    vec3 Position;
    vec3 Normal;
    vec3 TexCoords;
    vec3 Tangent;
    vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    string type;
    string path;    //用于比较纹理是否加载过
};

class Mesh {
    public:
        /*  网格数据  */
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;
        /*  函数  */
        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        void Draw(Shader shader);
    private:
        /*  渲染数据  */
        unsigned int VAO, VBO, EBO;
        /*  函数  */
        void setupMesh();
};  

#endif /* Mesh_hpp */
