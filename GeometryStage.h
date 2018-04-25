//
// Created by jeff2310 on 4/19/18.
//

#ifndef VKSOFTWARERENDER_GEOMETRYSTAGE_H
#define VKSOFTWARERENDER_GEOMETRYSTAGE_H

#include "VirtualDevice.h"
#include "Primitives.h"

namespace VkRenderer {

    void homogenize(Vector *v);

    void toViewport(VirtualDevice &device, Vector *v);

    void RenderTriangle(VirtualDevice &device, const Triangle &t);
}

#endif //VKSOFTWARERENDER_GEOMETRYSTAGE_H
