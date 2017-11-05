//
// Created by engin on 5.11.2017.
//

#ifndef UBERGAME_OPTIONS_H
#define UBERGAME_OPTIONS_H

#include <glm/glm.hpp>

class Options {
private:
    glm::vec3 moveSpeed = glm::vec3(5, 0, 5);
    float jumpFactor = 3.0f;
    float lookAroundSpeed = -2.5f;
    int screenHeight = 768;
    int screenWidth = 1024;
public:
    int getScreenHeight() const {
        return screenHeight;
    }

    void setScreenHeight(int height) {
        Options::screenHeight = height;
    }

    int getScreenWidth() const {
        return screenWidth;
    }

    void setScreenWidth(int width) {
        Options::screenWidth = width;
    }

    const glm::vec3 &getMoveSpeed() const {
        return moveSpeed;
    }

    float getJumpFactor() const {
        return jumpFactor;
    }

    float getLookAroundSpeed() const {
        return lookAroundSpeed;
    }

    void setMoveSpeed(const glm::vec3 &moveSpeed) {
        Options::moveSpeed = moveSpeed;
    }

    void setJumpFactor(float jumpFactor) {
        Options::jumpFactor = jumpFactor;
    }

    void setLookAroundSpeed(float lookAroundSpeed) {
        Options::lookAroundSpeed = lookAroundSpeed;
    }

};


#endif //UBERGAME_OPTIONS_H