//
// Created by becky on 26/02/2020.
//

#include "BcFloat.hpp"

BcFloat::BcFloat(bcFloat8 source) {
    bcFloat = source;
}

BcFloat::operator btScalar () {
    return btScalar();
}

bcFloat8 BcFloat::operator+(bcFloat8 target) {
    return this->bcFloat + target;
}

bcFloat8 BcFloat::operator-(bcFloat8 target) {
    return this->bcFloat - target;
}

bcFloat8 BcFloat::operator*(bcFloat8 target) {
    return this->bcFloat * target;
}



