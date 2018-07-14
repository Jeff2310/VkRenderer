//
// Created by jeff2310 on 4/23/18.
//

#include <iostream>
#include "MathUtility.h"
#include "PhongShading.h"
#include "ShaderVariables.h"
#include "TextureLoader/Texture.h"

namespace VkRenderer {

    PhongConstants normalPhongConstants = PhongConstants(0.2f, 0.6f, 0.5f, 16, Vector(1.0f, 1.0f, 1.0f),
                                                         Color(1.0f, 1.0f, 1.0f));

    void PhongVertex(Vertex *v) {
        Transform &transform = Transform::currentTransform;
        Matrix model = Transform::currentTransform.getModel();
        // mat3(transpose(inverse(model)))
        Matrix normalTransform = model.inverse().transpose();

        v->shaderVariables.fragPos = transform.toWorld(v->pos);

        transform.toScreen(&v->pos);
        v->normal = normalTransform * v->normal;
        // texCoord...,etc here

    }

    Color PhongFragment(VirtualDevice &device, const Vertex &frag, PhongConstants variables) {
        Color fragColor;

        Color objectColor;

        if (device.drawMode & DRAW_TEXTURE) {
            // sampling from texture;
            float u = frag.texCoord.u, v = frag.texCoord.v;
            device.currentTexture->projection(&u, &v);
            unsigned char colors[4];
            device.currentTexture->sample(u, v, colors);
            objectColor = Color((float) colors[0] / 255.0f, (float) colors[1] / 255.0f, (float) colors[2] / 255.0f,
                                (float) colors[3] / 255.0f);
        } else {
            objectColor = frag.color;
        }

        Color baseColor = variables.lightColor * objectColor;
        Vector norm = frag.normal.normalize();

        Vector lightDir = (variables.lightPos - frag.shaderVariables.fragPos).normalize();
        // no view and reflect in blinn-phong model
//        Vector viewDir = (device.camera->pos() - frag.shaderVariables.fragPos).normalize();
//        Vector reflectDir = reflect(lightDir, norm);
        Vector halfDir = (norm + lightDir).normalize();

        float ambient = variables.ambient;

        float diffuse = variables.diffuse * max(norm.dot(lightDir), 0.0f);
        // phong
//        float specular = variables.specular * powf(max(viewDir.dot(reflectDir), 0.0f), variables.shiniess);
        // blinn-phong
        float specular = variables.specular * powf(max(norm.dot(halfDir), 0.0f), variables.shiniess);

        fragColor = baseColor * (ambient + diffuse + specular);
        return fragColor;
    }
}