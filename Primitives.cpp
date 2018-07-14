//
// Created by jeff2310 on 4/25/18.
//

#include <iostream>
#include "Primitives.h"
#include "ShaderVariables.h"

namespace VkRenderer {

    Mesh::Mesh() : vertices(), faces() {}

    Mesh::Mesh(const Mesh &m) : vertices(m.vertices), faces(m.faces) {}

    int Mesh::count() {
        int _count = (int) vertices.size() - 2;
        if (_count < 0) return 0;
        return _count;
    }

    void Mesh::addVertex(const Vertex &v) {
        vertices.push_back(v);
    }

    void Mesh::build() {
        int faceCount = (int) vertices.size() / 3;
        for (int i = 0; i < faceCount; i++) {
            Triangle triangle{vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]};
            faces.push_back(triangle);
        }
    }

    Mesh createCube(float length, const Color *colors) {
        /* [0,0]: -1, -1, -1;  [0,1]:  1, -1, -1;  [0,2]:  1,  1, -1;  [0,3]: -1,  1, -1; (back)
         * [1,0]: -1, -1,  1;  [1,1]:  1, -1,  1;  [1,2]:  1,  1,  1;  [1,3]: -1,  1,  1; (front)
         * [2,0]: -1, -1,  1;  [2,1]: -1, -1, -1;  [2,2]: -1,  1, -1;  [2,3]: -1,  1,  1; (left)
         * [3,0]:  1, -1,  1;  [3,1]:  1, -1, -1;  [3,2]:  1,  1, -1;  [3,3]:  1,  1,  1; (right)
         * [4,0]: -1, -1,  1;  [4,1]:  1, -1,  1;  [4,2]:  1, -1, -1;  [4,3]: -1, -1, -1; (bottom)
         * [5,0]: -1,  1,  1;  [5,1]:  1,  1,  1;  [5,2]:  1,  1, -1;  [5,3]: -1,  1, -1; (up)
         */
        Mesh cube;
        length /= 2;

        Vector normal;

        normal = Vector(0.0f, 0.0f, -1.0f);
        cube.addVertex(Vertex(Vector(length, -length, -length), TextureCoordinate(0.0f, 0.0f), colors[0], normal,
                              PhongVariables(Vector(length, -length, -length))));
        cube.addVertex(Vertex(Vector(-length, -length, -length), TextureCoordinate(1.0f, 0.0f), colors[0], normal,
                              PhongVariables(Vector(-length, -length, -length))));
        cube.addVertex(Vertex(Vector(-length, length, -length), TextureCoordinate(1.0f, 1.0f), colors[0], normal,
                              PhongVariables(Vector(-length, length, -length))));
        cube.addVertex(Vertex(Vector(length, -length, -length), TextureCoordinate(0.0f, 0.0f), colors[0], normal,
                              PhongVariables(Vector(length, -length, -length))));
        cube.addVertex(Vertex(Vector(-length, length, -length), TextureCoordinate(1.0f, 1.0f), colors[0], normal,
                              PhongVariables(Vector(-length, length, -length))));
        cube.addVertex(Vertex(Vector(length, length, -length), TextureCoordinate(0.0f, 1.0f), colors[0], normal,
                              PhongVariables(Vector(length, length, -length))));
        normal = Vector(0.0f, 0.0f, 1.0f);
        cube.addVertex(Vertex(Vector(-length, -length, length), TextureCoordinate(0.0f, 0.0f), colors[1], normal,
                              PhongVariables(Vector(-length, -length, length))));
        cube.addVertex(Vertex(Vector(length, -length, length), TextureCoordinate(1.0f, 0.0f), colors[1], normal,
                              PhongVariables(Vector(length, -length, length))));
        cube.addVertex(Vertex(Vector(length, length, length), TextureCoordinate(1.0f, 1.0f), colors[1], normal,
                              PhongVariables(Vector(length, length, length))));
        cube.addVertex(Vertex(Vector(-length, -length, length), TextureCoordinate(0.0f, 0.0f), colors[1], normal,
                              PhongVariables(Vector(-length, -length, length))));
        cube.addVertex(Vertex(Vector(-length, length, length), TextureCoordinate(0.0f, 1.0f), colors[1], normal,
                              PhongVariables(Vector(-length, length, length))));
        cube.addVertex(Vertex(Vector(length, length, length), TextureCoordinate(1.0f, 1.0f), colors[1], normal,
                              PhongVariables(Vector(length, length, length))));

        normal = Vector(-1.0f, 0.0f, 0.0f);
        cube.addVertex(Vertex(Vector(-length, -length, -length), TextureCoordinate(0.0f, 0.0f), colors[2], normal,
                              PhongVariables(Vector(-length, -length, -length))));
        cube.addVertex(Vertex(Vector(-length, -length, length), TextureCoordinate(1.0f, 0.0f), colors[2], normal,
                              PhongVariables(Vector(-length, -length, length))));
        cube.addVertex(Vertex(Vector(-length, length, length), TextureCoordinate(1.0f, 1.0f), colors[2], normal,
                              PhongVariables(Vector(-length, length, length))));
        cube.addVertex(Vertex(Vector(-length, -length, -length), TextureCoordinate(0.0f, 0.0f), colors[2], normal,
                              PhongVariables(Vector(-length, -length, -length))));
        cube.addVertex(Vertex(Vector(-length, length, length), TextureCoordinate(1.0f, 1.0f), colors[2], normal,
                              PhongVariables(Vector(-length, length, length))));
        cube.addVertex(Vertex(Vector(-length, length, -length), TextureCoordinate(0.0f, 1.0f), colors[2], normal,
                              PhongVariables(Vector(-length, length, -length))));
        normal = Vector(1.0f, 0.0f, 0.0f);
        cube.addVertex(Vertex(Vector(length, -length, length), TextureCoordinate(0.0f, 0.0f), colors[3], normal,
                              PhongVariables(Vector(length, -length, length))));
        cube.addVertex(Vertex(Vector(length, -length, -length), TextureCoordinate(1.0f, 0.0f), colors[3], normal,
                              PhongVariables(Vector(length, -length, -length))));
        cube.addVertex(Vertex(Vector(length, length, -length), TextureCoordinate(1.0f, 1.0f), colors[3], normal,
                              PhongVariables(Vector(length, length, -length))));
        cube.addVertex(Vertex(Vector(length, -length, length), TextureCoordinate(0.0f, 0.0f), colors[3], normal,
                              PhongVariables(Vector(length, -length, length))));
        cube.addVertex(Vertex(Vector(length, length, -length), TextureCoordinate(1.0f, 1.0f), colors[3], normal,
                              PhongVariables(Vector(length, length, -length))));
        cube.addVertex(Vertex(Vector(length, length, length), TextureCoordinate(0.0f, 1.0f), colors[3], normal,
                              PhongVariables(Vector(length, length, length))));

        normal = Vector(0.0f, -1.0f, 0.0f);
        cube.addVertex(Vertex(Vector(-length, -length, -length), TextureCoordinate(0.0f, 0.0f), colors[4], normal,
                              PhongVariables(Vector(-length, -length, -length))));
        cube.addVertex(Vertex(Vector(length, -length, -length), TextureCoordinate(1.0f, 0.0f), colors[4], normal,
                              PhongVariables(Vector(length, -length, -length))));
        cube.addVertex(Vertex(Vector(length, -length, length), TextureCoordinate(1.0f, 1.0f), colors[4], normal,
                              PhongVariables(Vector(length, -length, length))));
        cube.addVertex(Vertex(Vector(-length, -length, -length), TextureCoordinate(0.0f, 0.0f), colors[4], normal,
                              PhongVariables(Vector(-length, -length, -length))));
        cube.addVertex(Vertex(Vector(length, -length, length), TextureCoordinate(1.0f, 1.0f), colors[4], normal,
                              PhongVariables(Vector(length, -length, length))));
        cube.addVertex(Vertex(Vector(-length, -length, length), TextureCoordinate(0.0f, 1.0f), colors[4], normal,
                              PhongVariables(Vector(-length, -length, length))));
        normal = Vector(0.0f, 1.0f, 0.0f);
        cube.addVertex(Vertex(Vector(-length, length, length), TextureCoordinate(0.0f, 0.0f), colors[5], normal,
                              PhongVariables(Vector(-length, length, length))));
        cube.addVertex(Vertex(Vector(length, length, length), TextureCoordinate(1.0f, 0.0f), colors[5], normal,
                              PhongVariables(Vector(length, length, length))));
        cube.addVertex(Vertex(Vector(length, length, -length), TextureCoordinate(1.0f, 1.0f), colors[5], normal,
                              PhongVariables(Vector(length, length, -length))));
        cube.addVertex(Vertex(Vector(-length, length, length), TextureCoordinate(0.0f, 0.0f), colors[5], normal,
                              PhongVariables(Vector(-length, length, length))));
        cube.addVertex(Vertex(Vector(length, length, -length), TextureCoordinate(1.0f, 1.0f), colors[5], normal,
                              PhongVariables(Vector(length, length, -length))));
        cube.addVertex(Vertex(Vector(-length, length, -length), TextureCoordinate(0.0f, 1.0f), colors[5], normal,
                              PhongVariables(Vector(-length, length, -length))));

        cube.build();
        return cube;
    }

    Mesh createSphere(float radius, float angle_step) {
        Mesh sphere;
        int count = (int) lround(360.0f / angle_step);
        angle_step = 2.0f * 3.1415926f / count;

        float theta = 0.0f, phi;
        float theta_next, phi_next;
        Vector pos11, pos12, pos21, pos22;
        TextureCoordinate tex11, tex12, tex21, tex22;

        Color color(0.6, 0.24, 0.3);

        // phi and theta are exchanged here
        while (theta < 2.0f * 3.1415926f) {
            theta_next = theta + angle_step;
            if (theta_next >= 2.0f * 3.1415926f) break;
            phi = -0.5f * 3.1415926f;
            while (phi < 0.5f * 3.1415926f) {
                phi_next = phi + angle_step;
                if (phi_next >= 0.5f * 3.1415926f) break;

                pos11 = Vector(cosf(phi) * cosf(theta), sinf(phi), cosf(phi) * sinf(theta)) * radius;
                pos12 = Vector(cosf(phi) * cosf(theta_next), sinf(phi), cosf(phi) * sinf(theta_next)) * radius;
                pos21 = Vector(cosf(phi_next) * cosf(theta), sinf(phi_next), cosf(phi_next) * sinf(theta)) * radius;
                pos22 = Vector(cosf(phi_next) * cosf(theta_next), sinf(phi_next), cosf(phi_next) * sinf(theta_next)) *
                        radius;
                tex11 = TextureCoordinate(theta, phi);
                tex12 = TextureCoordinate(theta_next, phi);
                tex21 = TextureCoordinate(theta, phi_next);
                tex22 = TextureCoordinate(theta_next, phi_next);

                sphere.addVertex(
                        Vertex(
                                pos11,
                                tex11,
                                color,
                                pos11,
                                PhongVariables(pos11)
                        )
                );

                sphere.addVertex(
                        Vertex(
                                pos12,
                                tex12,
                                color,
                                pos12,
                                PhongVariables(pos12)
                        )
                );

                sphere.addVertex(
                        Vertex(
                                pos22,
                                tex22,
                                color,
                                pos22,
                                PhongVariables(pos22)
                        )
                );

                sphere.addVertex(
                        Vertex(
                                pos11,
                                tex11,
                                color,
                                pos11,
                                PhongVariables(pos11)
                        )
                );

                sphere.addVertex(
                        Vertex(
                                pos22,
                                tex22,
                                color,
                                pos22,
                                PhongVariables(pos22)
                        )
                );

                sphere.addVertex(
                        Vertex(
                                pos21,
                                tex21,
                                color,
                                pos21,
                                PhongVariables(pos21)
                        )
                );


                //phi +=45.0f;
                phi = phi_next;
            }
            theta = theta_next;
        }

        sphere.build();
        return sphere;
    }

    Vertex interp(const Vertex &v1, const Vertex &v2, float t) {
        Vertex _v;
        _v.pos = interp(v1.pos, v2.pos, t);
        float z_inv = _v.pos.w;
        float t2;
        float z1 = 1 / v1.pos.w, z2 = 1 / v2.pos.w;
        if (z1 < z2 + 0.0001f && z1 > z2 - 0.0001f)
            t2 = t;
        else
            t2 = (1 / z_inv - 1 / v1.pos.w) / (1 / v2.pos.w - 1 / v1.pos.w);
        //t2 = t;
//        printf("%.3f <> %.3f \n", t, t2);
        _v.texCoord.u = interp(v1.texCoord.u, v2.texCoord.u, t2);
        _v.texCoord.v = interp(v1.texCoord.v, v2.texCoord.v, t2);
        _v.color = interp(v1.color, v2.color, t2);
        _v.normal = interp(v1.normal, v2.normal, t2); // TODO: normal interpolate needed

        _v.shaderVariables = PhongVariables::variablesInterp(v1.shaderVariables, v2.shaderVariables,
                                                             t);
        return _v;
    }
}