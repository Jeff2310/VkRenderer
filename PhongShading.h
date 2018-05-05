//
// Created by jeff2310 on 4/23/18.
//

#ifndef VKSOFTWARERENDER_PHONGSHADING_H
#define VKSOFTWARERENDER_PHONGSHADING_H

#include "MathUtility.h"
#include "VirtualDevice.h"
#include "Primitives.h"

namespace VkRenderer {

    // the uniform variables


    void PhongVertex(Vertex *v);

    Color PhongFragment(VirtualDevice &device, const Vertex &frag, PhongConstants variables);
}
#endif //VKSOFTWARERENDER_PHONGSHADING_H
