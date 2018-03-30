#include "AI.hpp"
#include <chrono>
#include <ctime>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

std::vector<Agent> g_agents;
std::vector<Target> g_targets;

// Initialize environment
Environment::Environment()
{
    std::srand(std::time(nullptr));
    std::function<int()> rand = [=]() {
        int floor = 0, ceiling = 1000;  // Range of the random number
        return floor + std::rand() / (RAND_MAX / ceiling + floor);
    };

    for (int i = 0; i < 5; ++i) {
        g_agents.push_back(Agent(Point<int>(rand(), rand()), i));
        for (int j = 0; j < 5; ++j) {
            g_targets.push_back(Target(Point<int>(rand(), rand()), i));
        }
    }
}

void Environment::render()
{
    /**
     * Parse the locations and ids of each agent and target, then
     * update them one by one by calling the front signals
     */
    this->clearScreen();
    // Render targets first so they are on top
    for (auto it = g_targets.begin(); it != g_targets.end(); ++it) {
        if (!it->killed)
            emit renderTarget(it->location, it->id);  // Render if it has not been killed/collected
    }
    for (auto it = g_agents.begin(); it != g_agents.end(); ++it) {
        emit renderAgent(it->location, it->id);
    }
}

void Environment::play()
{
    auto it = g_agents.begin();
    while (it->moveRight()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        this->render();
    }
    while (it->moveDown()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        this->render();
    }
    while (it->moveLeft()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        this->render();
    }
    while (it->moveUp()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        this->render();
    }
}

bool Agent::moveRight()
{
    if ((this->location.x() + 10) <= 1000) {
        this->location.addX(10);
        return true;
    } else
        return false;
}

bool Agent::moveLeft()
{
    if ((this->location.x() - 10) >= 0) {
        this->location.addX(-10);
        return true;
    } else
        return false;
}

bool Agent::moveDown()
{
    if ((this->location.y() + 10) <= 1000) {
        this->location.addY(10);
        return true;
    } else
        return false;
}

bool Agent::moveUp()
{
    if ((this->location.y() - 10) >= 0) {
        this->location.addY(-10);
        return true;
    } else
        return false;
}
