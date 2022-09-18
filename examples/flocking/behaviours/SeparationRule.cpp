#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"

Vector2 SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    //Try to avoid boids too close
    Vector2 separatingForce = Vector2::zero();

    float desiredDistance = desiredMinimalDistance;

    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
    if (!neighborhood.empty()) {
        Vector2 position = boid->transform.position;

        for(Boid* neighbor : neighborhood) {
            if (Vector2(position - neighbor->transform.position).getMagnitude() < desiredDistance) {
                float separatingForceComponent = 1 - Vector2(position - neighbor->transform.position).getMagnitude() / desiredDistance;
                separatingForce += Vector2::normalized(Vector2(position - neighbor->transform.position)) * separatingForceComponent;
            }
        }
    }

    float distance = separatingForce.getMagnitude();

    if (distance < 0.01) {
        distance = 0.01;
    }

    separatingForce /= distance;

    return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
    ImGui::SetCurrentContext(world->engine->imGuiContext);
    bool valusHasChanged = false;

    if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
        valusHasChanged = true;
    }

    return valusHasChanged;
}
