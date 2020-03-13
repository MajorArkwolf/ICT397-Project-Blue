#include "Transform.hpp"

Transform::Transform(){
    orientation = Quaternion(0,0,0,0);
    position = Vector3(0,0,0);
    
}


Transform::Transform(Vector3 position, Quaternion orientation) {
    orientation = orientation;
    position = position;

    auto *pos = new rp3d::Vector3( position.GetX(),
                                            position.GetY(),
                                            position.GetZ());

    auto *direction = new rp3d::Quaternion( orientation.GetX(),
                                                        orientation.GetY(),
                                                        orientation.GetZ(),
                                                        orientation.GetW());
    transform = new rp3d::Transform(pos, direction);
}

