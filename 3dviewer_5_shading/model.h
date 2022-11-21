#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <QVector4D>
#include <QVector3D>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMatrix4x4>
#include <material.h>

class Model
{
public:
    Model();
    ~Model() = default;

    std::vector<QVector4D> vertices;
    std::vector<unsigned> indices;
    std::vector<QVector3D> normals;

    unsigned numVertices{0};
    unsigned numFaces{0};

    unsigned vao{0};
    unsigned vboVertices{0};
    unsigned eboIndices{0};
    unsigned vboNormals{0};


    void readOFFFile(const QString &);

    void computeBBox();
    void rescaleModelMatrix();
    QVector3D centroidBB, minBB, maxBB;
    float diagonalBB{0.0f};
    QMatrix4x4 modelMatrix;

    int currentShader{0};

    std::vector<QString> vertexShaderFileName   = {":/shaders/vzdepth.glsl",
                                                   ":/shaders/vnormal.glsl",
                                                   ":/shaders/vflat.glsl",
                                                   ":/shaders/vgouraud.glsl",
                                                   ":/shaders/vphong.glsl"};

    std::vector<QString> fragmentShaderFileName = {":/shaders/fzdepth.glsl",
                                                   ":/shaders/fnormal.glsl",
                                                   ":/shaders/fflat.glsl",
                                                   ":/shaders/fgouraud.glsl",
                                                   ":/shaders/fphong.glsl"};
    std::vector<unsigned> shaderProgram;

    Material material;
    void createNormals();

};

#endif // MODEL_H
