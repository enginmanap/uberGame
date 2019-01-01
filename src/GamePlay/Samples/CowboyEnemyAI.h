//
// Created by engin on 31.12.2018.
//

#ifndef LIMONENGINE_COWBOYENEMYAI_H
#define LIMONENGINE_COWBOYENEMYAI_H


#include "../../AI/ActorInterface.h"
#include <random>

/**
 * Cowboy Enemy can be doing one of these:
 * 1) Scripted loop
 * 2) idling until player detection
 * 3) walking to player if player is close
 * 4) hitting player with melee if player is hitting close
 * 5) running to player if player is at medium distance
 * 6) Shooting player
 * 7) kneeling to shoot
 * 8) kneel shooting
 * 9) standing up
 *
 * kneeling is to be selected by random, only if player is medium distance and visible
 */

class CowboyEnemyAI : public ActorInterface {
    static ActorRegister<CowboyEnemyAI> reg;

    enum class State {
        DEAD,
        IDLE,
        WALKING,
        RUNNING,
        SHOOTING,
        MELEE,
        KNEELING_DOWN,
        STANDING_UP,
        KNEEL_SHOOTING,
        KNEEL_IDLE,
        HIT,
        SCRIPTED
    };

    enum class Gun {
        PISTOL,
        RIFLE,
        SHOTGUN
    };

    State currentState = State::IDLE;
    State transitionState = State::IDLE;
    State beforeState = State::IDLE;//Shooting and Hit uses to return

    Gun currentGun = Gun::RIFLE;
    Gun transitionGun = Gun::RIFLE;

    std::string currentAnimationName;

    std::vector<glm::vec3> routeToRequest;

    long routeGetTime = 0;
    bool currentAnimationFinished;

    const float DETECTION_DISTANCE = 100;//too little because of testing
    const float MELEE_DISTANCE = 15;
    const float RUN_DISTANCE = 25;

    long lastSetupTime;
    long lastShootTime = 0;
    int shootingStage = 0;
    glm::vec3 lastWalkDirection = glm::vec3(0,0,0);
    bool routeRequested = false;


    /********* Parameters to expose as setting *************/
    float shootChance = 0.85f;
    float kneelDownChance = 0.005f;
    float kneelStayChance = 0.0025f;
    long minShootTimeWait = 1000;
    uint32_t hitPoints = 100;
    float walkSpeed = 0.1;
    float runSpeed = 0.14;

    /********* Parameters to expose as setting *************/
    std::uniform_real_distribution<float> randomFloats;
    std::default_random_engine generator;

public:
    CowboyEnemyAI(uint32_t id, LimonAPI *limonAPI) : ActorInterface(id, limonAPI) {
        randomFloats = std::uniform_real_distribution<float>(0.0f, 1.0f); // generates random floats between 0.0 and 1.0
    };

    void play(long time, ActorInterface::ActorInformation &information) override;

    bool interaction(std::vector<LimonAPI::ParameterRequest> &interactionInformation) override;

    std::vector<LimonAPI::ParameterRequest> getParameters() const override;

    void setParameters(std::vector<LimonAPI::ParameterRequest> parameters) override;


    std::string getName() const override {
        return "Cowboy Enemy";
    }

    void transitionToMelee(const ActorInformation &information);

    void transitionToWalk(const ActorInformation &information);

    void transitionToRun(const ActorInformation &information);

    void transitionToKneel(const ActorInformation &information);

    void transitionToKneelIdle(const ActorInformation &information);

    void transitionToKneelShoot(const ActorInformation &information);

    void transitionToStandUp(const ActorInformation &information);

    void transitionToShoot(const ActorInformation &information);

    void transitionToIdle(const ActorInformation &information);

    void turnFaceToPlayer(const ActorInformation &information) const;

    void transitionToHit();

    void transitionToDead();
};


extern "C" void registerActors(std::map<std::string, ActorInterface*(*)(uint32_t, LimonAPI*)>*);



#endif //LIMONENGINE_COWBOYENEMYAI_H