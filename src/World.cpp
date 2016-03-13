//
// Created by Engin Manap on 13.02.2016.
//


#include "World.h"
#include "SkyBox.h"

World::World(GLHelper *glHelper) {

    // physics init
    broadphase = new btDbvtBroadphase();

    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);

    solver = new btSequentialImpulseConstraintSolver;

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -10, 0));
    debugDrawer = new BulletDebugDrawer(glHelper);
    dynamicsWorld->setDebugDrawer(debugDrawer);
    dynamicsWorld->getDebugDrawer()->setDebugMode(dynamicsWorld->getDebugDrawer()->DBG_MAX_DEBUG_DRAW_MODE);
    //dynamicsWorld->getDebugDrawer()->setDebugMode(dynamicsWorld->getDebugDrawer()->DBG_NoDebug);

    // end of physics init


    this->glHelper = glHelper;

    rigidBodies.push_back(camera.getRigidBody());
    dynamicsWorld->addRigidBody(camera.getRigidBody());

    Model *crate = new Model(glHelper);
    crate->addScale(glm::vec3(250.0f,1.0f,250.0f));
    crate->addTranslate(glm::vec3(-125.0f, 0.0f, 125.0f));
    crate->getWorldTransform();
    objects.push_back(crate);
    rigidBodies.push_back(crate->getRigidBody());
    dynamicsWorld->addRigidBody(crate->getRigidBody());

    crate = new Model(glHelper,1);
    crate->addTranslate(glm::vec3(2.0f, 25.0f, -3.0f));
    crate->getWorldTransform();
    objects.push_back(crate);
    rigidBodies.push_back(crate->getRigidBody());
    dynamicsWorld->addRigidBody(crate->getRigidBody());

    crate = new Model(glHelper,1);
    crate->addTranslate(glm::vec3(-2.0f, 23.0f, -3.0f));
    crate->getWorldTransform();
    objects.push_back(crate);
    rigidBodies.push_back(crate->getRigidBody());
    dynamicsWorld->addRigidBody(crate->getRigidBody());

    crate = new Model(glHelper,1);
    crate->addTranslate(glm::vec3(2.0f, 23.0f, -3.0f));
    crate->getWorldTransform();
    objects.push_back(crate);
    rigidBodies.push_back(crate->getRigidBody());
    dynamicsWorld->addRigidBody(crate->getRigidBody());

    crate = new Model(glHelper,1);
    crate->addTranslate(glm::vec3(3.25f, 2.0f, -3.0f));
    crate->getWorldTransform();
    objects.push_back(crate);
    rigidBodies.push_back(crate->getRigidBody());
    dynamicsWorld->addRigidBody(crate->getRigidBody());

    sky = new SkyBox(glHelper,
                            std::string("D:user_files/engin/Documents/engin/UberGame/Data/Textures/Skyboxes/ThickCloudsWater/ThickCloudsWaterUp2048.png"),
                            std::string("D:/user_files/engin/Documents/engin/UberGame/Data/Textures/Skyboxes/ThickCloudsWater/ThickCloudsWaterDown2048.png"),
                            std::string("D:/user_files/engin/Documents/engin/UberGame/Data/Textures/Skyboxes/ThickCloudsWater/ThickCloudsWaterRight2048.png"),
                            std::string("D:/user_files/engin/Documents/engin/UberGame/Data/Textures/Skyboxes/ThickCloudsWater/ThickCloudsWaterLeft2048.png"),
                            std::string("D:/user_files/engin/Documents/engin/UberGame/Data/Textures/Skyboxes/ThickCloudsWater/ThickCloudsWaterBack2048.png"),
                            std::string("D:/user_files/engin/Documents/engin/UberGame/Data/Textures/Skyboxes/ThickCloudsWater/ThickCloudsWaterFront2048.png")
    );


}

void World::play(Uint32 simulationTimeFrame, InputHandler& inputHandler) {
    // Step simulation
    dynamicsWorld->stepSimulation(simulationTimeFrame/1000.0f);
    camera.updateTransfromFromPhysics(dynamicsWorld);
    objects[0]->updateTransformFromPhysics();
    objects[1]->updateTransformFromPhysics();
    objects[2]->updateTransformFromPhysics();
    objects[3]->updateTransformFromPhysics();
    objects[4]->updateTransformFromPhysics();
    //end of physics step

    btCollisionWorld::ClosestRayResultCallback RayCallback(btVector3(0,0,0), btVector3(0,25,-3));

// Perform raycast
    dynamicsWorld->rayTest(btVector3(0,20,0), btVector3(0,0,-3), RayCallback);

    if(RayCallback.hasHit()) {
        /*
        End = RayCallback.m_hitPointWorld;
        Normal = RayCallback.m_hitNormalWorld;
*/
        // Do some clever stuff here
    }

    float xLook, yLook;
    if(inputHandler.getMouseChange(xLook, yLook)){
        camera.rotate(xLook,yLook);
    }
    Camera::moveDirections direction = Camera::moveDirections::NONE;
    //ignore if both are pressed.
    if (inputHandler.getInputStatus(inputHandler.MOVE_FORWARD) !=  inputHandler.getInputStatus(inputHandler.MOVE_BACKWARD)) {
        if (inputHandler.getInputStatus(inputHandler.MOVE_FORWARD)) {
            direction = camera.FORWARD;
        } else {
            direction = camera.BACKWARD;
        }
    }
    if (inputHandler.getInputStatus(inputHandler.MOVE_LEFT) != inputHandler.getInputStatus(inputHandler.MOVE_RIGHT)) {
        if (inputHandler.getInputStatus(inputHandler.MOVE_LEFT)) {
            if (direction == camera.FORWARD) {
                direction = camera.LEFT_FORWARD;
            } else if (direction == camera.BACKWARD){
                direction = camera.LEFT_BACKWARD;
            } else {
                direction = camera.LEFT;
            }
        } else
        if (direction == camera.FORWARD) {
            direction = camera.RIGHT_FORWARD;
        } else if (direction == camera.BACKWARD){
            direction = camera.RIGHT_BACKWARD;
        } else {
            direction = camera.RIGHT;
        }
    }
    if (direction!= camera.NONE){
        camera.move(direction);
    }

}

void World::render() {
    glHelper->setCamera(camera.getCameraMatrix());
    for (std::vector<Renderable *>::iterator it = objects.begin(); it != objects.end(); ++it) {
        (*it)->render();
    }
    dynamicsWorld->debugDrawWorld();
    sky->render();
    //debugDrawer->drawLine(btVector3(0,0,-3),btVector3(0,250,-3),btVector3(1,1,1));
}

World::~World() {
    for (std::vector<Renderable *>::iterator it = objects.begin(); it != objects.end(); ++it) {
        delete (*it);
    }
    delete sky;
    for(std::vector<btRigidBody*>::iterator it = rigidBodies.begin(); it!= rigidBodies.end(); ++it){
        dynamicsWorld->removeRigidBody((*it));
    }

    delete dynamicsWorld;
    delete solver;
    delete collisionConfiguration;
    delete dispatcher;
    delete broadphase;

}