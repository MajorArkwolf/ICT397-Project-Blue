#include "BeMaterial.hpp"

BeMaterial::BeMaterial(BeMaterial target) {
    material = rp3d::Material(target.GetMaterial());
}
