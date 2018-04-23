//
// Created by jeff2310 on 4/23/18.
//

#include "PhongShading.h"

namespace VkRenderer {
    PhongVariables normalPhongVariable = PhongVariables(0.1f, 0.6f, 0.3f, 128, Vector(0.5f, 0.5, 0.5),
                                                        Color(1.0f, 1.0f, 1.0f));

    Color PhongFragment(VirtualDevice &device, const Vector &fragPos, const Vector &eyePos, const Vector &normal,
                        const Color &objectColor, PhongVariables variables) {

        Color fragColor;
        Color baseColor = variables.lightColor * objectColor;
        Vector norm = normal.normalize();

        Vector lightDir = (variables.lightPos - fragPos).normalize();
        Vector viewDir = (eyePos - fragPos).normalize();
        Vector reflectDir = reflect(lightDir, norm).normalize();

        float ambient = variables.ambient;

        float diffuse = variables.diffuse * max(normal.dot(lightDir), 0.0f);

        float specular = variables.specular * powf(max(viewDir.dot(reflectDir), 0.0f), variables.shiniess);
        //float specular = 0.0f;
        // cout<<viewDir.dot(reflectDir)<<endl;

        fragColor = baseColor * (specular);
        return fragColor;
    }
}