//
// Created by Engin Manap on 10.02.2016.
//

#ifndef UBERGAME_GLHELPER_H
#define UBERGAME_GLHELPER_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

#include <string>
#include <algorithm>
#include <vector>

#include <fstream>
#include <streambuf>
#include <iostream>

class GLHelper {
    GLuint gpuProgram;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    GLint transformMatrixLocation;
    GLint cameraMatrixLocation;

    float aspect;

    glm::mat4 model_matrix;//FIXME this is a left over?

    glm::mat4 cameraTransform;

public:
    GLHelper();
    ~GLHelper();

    GLuint createShader(GLenum, const std::string &);
    GLuint createProgram(const std::vector<GLuint> &);
    GLuint initializeProgram();

    void bufferVertexData(const GLfloat* vertexData, const GLfloat* colorData, const GLuint vertexSize,
                          const GLuint* elementData, const GLuint elementSize,
                          GLuint& vao, GLuint& vbo, GLuint& ebo);

    void setCamera(const glm::vec3&, const glm::vec3&, const glm::vec3&);

    void clearFrame(){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
;    }
    void render(const GLuint, const GLuint, const glm::mat4&);
    void reshape(int height, int width);
};

#endif //UBERGAME_GLHELPER_H
