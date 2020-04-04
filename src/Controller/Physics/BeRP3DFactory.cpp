#include "BeRP3DFactory.hpp"

BeAbstractBody *BeRP3DFactory::CreateBody(BeReact::BeCollisionWorld *world, std::string shape) {
    switch (shape){
        case "Box": return new BeBoxBody();
        case "Height": return new BeHeightBody();
        default:
            std::cout << "No shape specified or incorrect shape specified." << std::endl;
            break;
    }
}