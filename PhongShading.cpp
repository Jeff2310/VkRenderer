//
// Created by jeff2310 on 4/23/18.
//

#include "MathUtility.h"
#include "PhongShading.h"
#include "ShaderVariables.h"

namespace VkRenderer {

    PhongConstants normalPhongVariable = PhongConstants(0.1f, 0.6f, 0.3f, 128, Vector(0.5f, 0.5, 0.5),
                                                        Color(1.0f, 1.0f, 1.0f));

    void PhongVertex(Vertex *v) {

        Transform &transform = Transform::currentTransform;
        Matrix model = Transform::currentTransform.getModel();
        // mat3(transpose(inverse(model)))
        Matrix normalTransform = model.transpose() * model.inverse();
        normalTransform.value[3][0] = normalTransform.value[3][1] = normalTransform.value[3][2] = 0.0f;
        normalTransform.value[3][3] = 1.0f;

        v->shaderVariables.fragPos = transform.toWorld(v->pos);

        transform.toScreen(&v->pos);
        v->normal = normalTransform * v->normal;
        // texCoord...,etc here

    }

    Color PhongFragment(const Vertex &frag, const Vector &eyePos, PhongConstants variables) {

        Color fragColor;
        Color baseColor = variables.lightColor * frag.color;
        Vector norm = frag.normal.normalize();

        Vector lightDir = (variables.lightPos - frag.shaderVariables.fragPos).normalize();
        Vector viewDir = (eyePos - frag.shaderVariables.fragPos).normalize();
        Vector reflectDir = reflect(lightDir, norm).normalize();

        float ambient = variables.ambient;

        float diffuse = variables.diffuse * max(norm.dot(lightDir), 0.0f);

        float specular = variables.specular * powf(max(viewDir.dot(reflectDir), 0.0f), variables.shiniess);
        //float specular = 0.0f;
        // cout<<viewDir.dot(reflectDir)<<endl;

        fragColor = baseColor * (0.0f + specular);
        return fragColor;
    }
}