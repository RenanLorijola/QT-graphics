#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{}

OpenGLWidget::~OpenGLWidget()
{
    destroyVBOs();
    destroyShaders();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);

    qDebug("OpenGL Version: %s",glGetString(GL_VERSION));
    qDebug("GLSL Version: %s",glGetString(GL_SHADING_LANGUAGE_VERSION));

    connect(&timer, &QTimer::timeout, this, &OpenGLWidget::animate);
    timer.start(0);

    elapsedTime.start();

    createShaders();
    createVBOs();
}

void OpenGLWidget::resizeGL(int w, int h){}

void OpenGLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    GLint locScaling{glGetUniformLocation(shaderProgram, "scaling")};
    GLint locTranslation{glGetUniformLocation(shaderProgram, "translation")};
    GLint locColor{glGetUniformLocation(shaderProgram, "color")};
    GLint locSolidColor{glGetUniformLocation(shaderProgram, "solidColor")};

    //Target
    glUniform4f(locTranslation, 0.8f, targetPosY, 0, 0);
    glUniform1f(locScaling, 0.2f);

    glBindVertexArray(vaoTriangle);
    glDrawElements(GL_TRIANGLES, indicesTriangle.size(), GL_UNSIGNED_INT, 0);

    //Player
    glBindVertexArray(vaoSquare);
    glUniform4f(locTranslation, -0.8f, playerPosY, 0, 0);
    glUniform1f(locScaling,0.2f);
    glDrawElements(GL_TRIANGLES, indicesSquare.size(), GL_UNSIGNED_INT, 0);

    if(blinkScreenTime > 0){
        glClearColor(1,1,1,1);
    } else {
        glClearColor(0,0,0,1);
    }

    glBindVertexArray(vaoRectangle);

    //Projectile
    if(shooting){
        glUniform1i(locSolidColor, 1);
        glUniform4f(locTranslation, projectilePos[0], projectilePos[1], 0, 0);
        glUniform4f(locColor, projectilePos[0], projectilePos[1], 0, 0);
        if(shootingCounter % 5 == 0){
            glUniform1f(locScaling,0.08f);
        } else {
            glUniform1f(locScaling,0.02f);
        }
        glDrawElements(GL_TRIANGLES, indicesRectangle.size(), GL_UNSIGNED_INT, 0);
    }
    glUniform1i(locSolidColor, 0);

    //Ammo
    glUniform1f(locScaling,0.01f);
    if(shootingCounter % 5){
        for(int i = shootingCounter % 5; i < 5; i ++){
            glUniform4f(locTranslation, -0.9f + 0.05f*(i-1), 0.9f, 0, 0);
            glDrawElements(GL_TRIANGLES, indicesRectangle.size(), GL_UNSIGNED_INT, 0);
        }
    }
    glUniform1f(locScaling, 0.04f);
    glUniform4f(locTranslation, -0.67f, 0.9f, 0, 0);
    glDrawElements(GL_TRIANGLES, indicesRectangle.size(), GL_UNSIGNED_INT, 0);
}

void OpenGLWidget::createShaders(){
    makeCurrent();
    destroyShaders();
    QFile vs(":/shaders/vshader1.glsl");
    QFile fs(":/shaders/fshader1.glsl");
    if(!vs.open(QFile::ReadOnly | QFile::Text)) return;//inserir mensagem de erro
    if(!fs.open(QFile::ReadOnly | QFile::Text)) return;//inserir mensagem de erro
    auto byteArrayVs{vs.readAll()};
    auto byteArrayFs{fs.readAll()};
    const char *c_strVs{byteArrayVs};
    const char *c_strFs{byteArrayFs};
    vs.close();
    fs.close();
    GLuint vertexShader{glCreateShader(GL_VERTEX_SHADER)};
    glShaderSource(vertexShader, 1, &c_strVs,0);
    glCompileShader(vertexShader);
    GLint isCompiled{0};
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS, &isCompiled);

    if(isCompiled == GL_FALSE){
        GLint maxLength{0};
        glGetShaderiv(vertexShader,GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader,maxLength,&maxLength,&infoLog[0]);
        qDebug("%s",&infoLog[0]);
        glDeleteShader(vertexShader);
        return;
    }

    GLuint fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)};
    glShaderSource(fragmentShader,1,&c_strFs,0);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&isCompiled);

    if(isCompiled == GL_FALSE){
        GLint maxLength{0};
        glGetShaderiv(fragmentShader,GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader,maxLength,&maxLength,&infoLog[0]);
        qDebug("%s",&infoLog[0]);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    GLint isLinked{0};
    glGetProgramiv(shaderProgram,GL_LINK_STATUS, &isLinked);

    if(isLinked == GL_FALSE){
        GLint maxLength{0};
        glGetProgramiv(shaderProgram,GL_INFO_LOG_LENGTH,&maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(shaderProgram,maxLength,&maxLength, &infoLog[0]);
        qDebug("%s",&infoLog[0]);
        glDeleteProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    glDetachShader(shaderProgram,vertexShader);
    glDetachShader(shaderProgram,fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void OpenGLWidget::destroyShaders() {
    makeCurrent();
    glDeleteProgram(shaderProgram);
}

void OpenGLWidget::createVBOs() {


    makeCurrent();
    destroyVBOs();

    // Square
    verticesSquare.resize(4);
    colorsSquare.resize(4);
    indicesSquare.resize(6);
    verticesSquare[0] = QVector4D(-0.5, -0.5 , 0, 1);
    verticesSquare[1] = QVector4D( 0.5, -0.5 , 0, 1);
    verticesSquare[2] = QVector4D( 0.5, 0.5 , 0, 1);
    verticesSquare[3] = QVector4D(-0.5, 0.5 , 0, 1);

    colorsSquare[0] = QVector4D(0, 1, 0, 1);
    colorsSquare[1] = QVector4D(0, 1, 0, 1);
    colorsSquare[2] = QVector4D(0, 1, 0, 1);
    colorsSquare[3] = QVector4D(0, 1, 0, 1);

    indicesSquare[0] = 0; indicesSquare[1] = 1; indicesSquare[2] = 2;
    indicesSquare[3] = 2; indicesSquare[4] = 3; indicesSquare[5] = 0;

    glGenVertexArrays(1,&vaoSquare);
    glBindVertexArray(vaoSquare);

    glGenBuffers(1,&vboSquareVertices);
    glBindBuffer(GL_ARRAY_BUFFER,vboSquareVertices);
    glBufferData(GL_ARRAY_BUFFER, verticesSquare.size()*sizeof(QVector4D),verticesSquare.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers (1, &vboSquareColors);
    glBindBuffer (GL_ARRAY_BUFFER,vboSquareColors);
    glBufferData (GL_ARRAY_BUFFER,colorsSquare.size()*sizeof(QVector4D),colorsSquare.data(), GL_STATIC_DRAW);
    glVertexAttribPointer (1, 4, GL_FLOAT , GL_FALSE , 0, nullptr);
    glEnableVertexAttribArray (1);

    glGenBuffers (1, &eboSquareIndices);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboSquareIndices);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indicesSquare.size() * sizeof (GLuint), indicesSquare.data(), GL_STATIC_DRAW);

    //Triangle
    verticesTriangle.resize(3);
    colorsTriangle.resize(3);
    indicesTriangle.resize(3);

    float widthTriangle{1.0f};
    float heightTriangle{1.0f};

    verticesTriangle[0] = QVector4D(widthTriangle/2, 0, 0, 1);
    verticesTriangle[1] = QVector4D(-widthTriangle/2, heightTriangle/2, 0, 1);
    verticesTriangle[2] = QVector4D(widthTriangle/2, heightTriangle, 0, 1);

    colorsTriangle[0] = QVector4D(0, 0, 1, 1); // Red
    colorsTriangle[1] = QVector4D(0, 0, 1, 1); // Green
    colorsTriangle[2] = QVector4D(0, 0, 1, 1); // Blue

    indicesTriangle[0] = 0; indicesTriangle[1] = 1; indicesTriangle[2] = 2;

    glGenVertexArrays(1,&vaoTriangle);
    glBindVertexArray(vaoTriangle);

    glGenBuffers(1,&vboTriangleVertices);
    glBindBuffer(GL_ARRAY_BUFFER,vboTriangleVertices);
    glBufferData(GL_ARRAY_BUFFER, verticesTriangle.size()*sizeof(QVector4D),verticesTriangle.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers (1, &vboTriangleColors);
    glBindBuffer (GL_ARRAY_BUFFER,vboTriangleColors);
    glBufferData (GL_ARRAY_BUFFER,colorsTriangle.size()*sizeof(QVector4D),colorsTriangle.data(), GL_STATIC_DRAW);
    glVertexAttribPointer (1, 4, GL_FLOAT , GL_FALSE , 0, nullptr);
    glEnableVertexAttribArray (1);

    glGenBuffers (1, &eboSquareIndices);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboSquareIndices);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indicesTriangle.size() * sizeof (GLuint), indicesTriangle.data(), GL_STATIC_DRAW);


    //Rectangle
    verticesRectangle.resize(4);
    colorsRectangle.resize(4);
    indicesRectangle.resize(6);
    verticesRectangle[0] = QVector4D(-0.7, -0.3, 0, 1);
    verticesRectangle[1] = QVector4D(0.7, -0.3, 0, 1);
    verticesRectangle[2] = QVector4D(0.7, 0.3, 0, 1);
    verticesRectangle[3] = QVector4D(-0.7, 0.3, 0, 1);

    colorsRectangle[0] = QVector4D(1, 0, 0, 1);
    colorsRectangle[1] = QVector4D(1, 0, 0, 1);
    colorsRectangle[2] = QVector4D(1, 0, 0, 1);
    colorsRectangle[3] = QVector4D(1, 0, 0, 1);

    indicesRectangle[0] = 0; indicesRectangle[1] = 1; indicesRectangle[2] = 2;
    indicesRectangle[3] = 2; indicesRectangle[4] = 3; indicesRectangle[5] = 0;

    glGenVertexArrays(1,&vaoRectangle);
    glBindVertexArray(vaoRectangle);

    glGenBuffers(1,&vboRectangleVertices);
    glBindBuffer(GL_ARRAY_BUFFER,vboRectangleVertices);
    glBufferData(GL_ARRAY_BUFFER, verticesRectangle.size()*sizeof(QVector4D),verticesRectangle.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers (1, &vboRectangleColors);
    glBindBuffer (GL_ARRAY_BUFFER,vboRectangleColors);
    glBufferData (GL_ARRAY_BUFFER,colorsRectangle.size()*sizeof(QVector4D),colorsRectangle.data(), GL_STATIC_DRAW);
    glVertexAttribPointer (1, 4, GL_FLOAT , GL_FALSE , 0, nullptr);
    glEnableVertexAttribArray (1);

    glGenBuffers (1, &eboRectangleIndices);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboRectangleIndices);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indicesRectangle.size() * sizeof (GLuint), indicesRectangle.data(), GL_STATIC_DRAW);
}

void OpenGLWidget::destroyVBOs() {
    makeCurrent ();
    glDeleteBuffers(1, &vboSquareVertices);
    glDeleteBuffers (1, &vboSquareColors);
    glDeleteBuffers (1, &eboSquareIndices);
    glDeleteVertexArrays (1, &vaoSquare);
    vboSquareVertices=0;
    eboSquareIndices=0;
    vboSquareColors=0;
    vaoSquare=0;
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Up:
            playerPosYOffset = 2.0f;
            break;
        case Qt::Key_Down:
            playerPosYOffset = -2.0f;
            break;
        case Qt::Key_W:
            playerPosYOffset = 2.0f;
            break;
        case Qt::Key_S:
            playerPosYOffset = -2.0f;
            break;
        case Qt::Key_Space:
            if(!shooting){
                shooting = true;
                projectilePos[0] = -0.6;
                projectilePos[1] = playerPosY;
            }
            break;
        case Qt::Key_Escape:
            QApplication::quit();
            break;
    }
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_Up:
            playerPosYOffset = 0.0f;
            break;
        case Qt::Key_Down:
            playerPosYOffset = 0.0f;
            break;
        case Qt::Key_W:
            playerPosYOffset = 0.0f;
            break;
        case Qt::Key_S:
            playerPosYOffset = 0.0f;
            break;
    }
}

void OpenGLWidget::animate(){
    float elTime{elapsedTime.restart()/1000.0f};

    //target
    targetPosY += targetPosYOffset*elTime;
    if(targetPosYOffset > 0 && targetPosY > 0.8f){
            targetPosY = 0.8f;
            targetPosYOffset = -targetPosYOffset;
    } else if(targetPosY < -0.8f){
        targetPosY = -0.8f;
        targetPosYOffset = -targetPosYOffset;
    }

    //player
    playerPosY += playerPosYOffset*elTime;
    if(playerPosY > 0.8f){
        playerPosY = 0.8f;
    } else if(playerPosY < -0.8f){
        playerPosY = -0.8f;
    }

    if(blinkScreenTime > 0){
        blinkScreenTime -= elTime;
    }

    boolean isMegaBullet = shootingCounter % 5 == 0;
    float deltaColision = isMegaBullet ? 0.16f : 0.08f;
    float bulletSpeed = isMegaBullet ? 3.5f : 2.5f;
    float bulletXColision = isMegaBullet ? 0.65f : 0.7f;



    //projectile
    if(shooting){
         yBulletSpeed += isMegaBullet ? 0 : gravityAcc*elTime;

        projectilePos[0] += bulletSpeed*elTime;
        projectilePos[1] -= yBulletSpeed*elTime;
        if(projectilePos[0] > bulletXColision && std::fabs(projectilePos[1] - targetPosY) < deltaColision){
             allyHits++;
             emit updateHitsLabel(QString("Hits: %1").arg(allyHits));
             blinkScreenTime = 0.1f;
             shootingCounter++;
             shooting = false;
             yBulletSpeed = 0;
        } else if(projectilePos[0] > 1.0f || projectilePos[1] < -1.0f){
             shootingCounter++;
             shooting = false;
             yBulletSpeed = 0;
        }
    } else {
        yBulletSpeed = 0;
    }

    update();
}
