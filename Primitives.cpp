//
// Created by jeff2310 on 4/25/18.
//

#include "Primitives.h"
#include "ShaderVariables.h"

namespace VkRenderer {
    Vertex interp(const Vertex &v1, const Vertex &v2, float t) {
        Vertex _v;
        _v.pos = interp(v1.pos, v2.pos, t);
        _v.texCoord.u = interp(v1.texCoord.u, v2.texCoord.u, t);
        _v.texCoord.v = interp(v1.texCoord.v, v2.texCoord.v, t);
        _v.color.r = interp(v1.color.r, v2.color.r, t);
        _v.color.g = interp(v1.color.g, v2.color.g, t);
        _v.color.b = interp(v1.color.b, v2.color.b, t);
        _v.color.w = interp(v1.color.w, v2.color.w, t);
        _v.normal = interp(v1.normal, v2.normal, t);

        _v.shaderVariables = PhongVariables::variablesInterp(v1.shaderVariables, v2.shaderVariables, t);
        return _v;
    }
}