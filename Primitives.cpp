//
// Created by jeff2310 on 4/25/18.
//

#include "Primitives.h"
#include "ShaderVariables.h"

namespace VkRenderer {
    Vertex interp(const Vertex &v1, const Vertex &v2, float t) {
        Vertex _v;
        float perspective_inv;
        _v.pos = interp(v1.pos, v2.pos, t);
        perspective_inv = _v.pos.w;
        _v.texCoord.u = interp(v1.texCoord.u, v2.texCoord.u, t) * perspective_inv;
        _v.texCoord.v = interp(v1.texCoord.v, v2.texCoord.v, t) * perspective_inv;
        _v.color = interp(v1.color, v2.color, t) * perspective_inv;
        _v.normal = interp(v1.normal, v2.normal, t); // TODO: normal interpolate needed

        _v.shaderVariables = PhongVariables::variablesInterp(v1.shaderVariables, v2.shaderVariables, t,
                                                             perspective_inv);
        return _v;
    }
}