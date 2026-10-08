#include "movableitem.h"

MovableItem::MovableItem(
    Atlas atlas,
    Rectangle hitbox
) : atlas{atlas}, hitbox{hitbox} {
    this->center = Vector2{hitbox.x + (hitbox.width / 2.0f), hitbox.y + (hitbox.height / 2.0f)};
}