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
    glClearColor(1,1,1,1);
    setUpdateBehavior(QOpenGLWidget::PartialUpdate);

    qDebug("OpenGL Version: %s",glGetString(GL_VERSION));
    qDebug("GLSL Version: %s",glGetString(GL_SHADING_LANGUAGE_VERSION));

    createShaders();
    createVBOs();
}

void OpenGLWidget::resizeGL(int w, int h){}

void OpenGLWidget::drawBlueSquare(){
    makeCurrent();

    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 0, 0, 1, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoSquare);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void OpenGLWidget::drawGraySquare(){
    makeCurrent();

    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 0.68, 0.68, 0.68, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoSquare);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void OpenGLWidget::drawGreenTriangle(){
    makeCurrent();

    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 0, 1, 0, 1);

    glBindVertexArray(vaoTriangle);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void OpenGLWidget::drawGrayTriangle(){
    makeCurrent();

    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 0.86, 0.86, 0.86, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoTriangle);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void OpenGLWidget::drawSunCircle(){
    makeCurrent();

    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 1, 1, 0, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoCircle);
    glDrawArrays(GL_TRIANGLE_FAN, 0, steps);
}

void OpenGLWidget::drawMoonCircle(){
    makeCurrent();

    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 0.98, 0.95, 0.84, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoCircle);
    glDrawArrays(GL_TRIANGLE_FAN, 0, steps);
}

void OpenGLWidget::drawPinkHeart(){
    makeCurrent();
    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 1, 0, 1, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoHeart);
    glDrawArrays(GL_TRIANGLE_FAN, 0, steps);
};

void OpenGLWidget::drawGrayHeart(){
    makeCurrent();
    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 0.52, 0.52, 0.52, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoHeart);
    glDrawArrays(GL_TRIANGLE_FAN, 0, steps);
};

void OpenGLWidget::drawBrownRectangle(){
    makeCurrent();
    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 0.44, 0.3, 0.215, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoRectangle);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void OpenGLWidget::drawGrayRectangle(){
    makeCurrent();
    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 0.32, 0.32, 0.32, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoRectangle);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
};

void OpenGLWidget::drawGreenOctagon(){
    makeCurrent();
    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 0.5, 1, 0, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoOctagon);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
};

void OpenGLWidget::drawGrayOctagon(){
    makeCurrent();
    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 0.25, 0.25, 0.25, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoOctagon);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
};

void OpenGLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    if(DayNight){
        drawGraySquare();
        drawMoonCircle();
        drawGrayTriangle();
        drawGrayHeart();
        drawGrayRectangle();
        drawGrayOctagon();
    }
    else {
        drawSunCircle();
        drawBlueSquare();
        drawGreenTriangle();
        drawPinkHeart();
        drawBrownRectangle();
        drawGreenOctagon();
    }

}

void OpenGLWidget::toggleDayNight(bool changeDayNight){
    makeCurrent();
    if(changeDayNight)
        glClearColor(0,0,0,1);
    else
        glClearColor(1,1,1,1);

    DayNight=changeDayNight;
    update();
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

    float windowXDivByY = 1.5;


    //Square
    std::vector<QVector4D> verticesSquare;
    std::vector<GLuint> indicesSquare;

    verticesSquare.resize(4);
    indicesSquare.resize(6); //2*3

    float posXSquare{-0.5f};
    float posYSquare{-0.5f};
    float offsetSquare{0.3f};

    verticesSquare[0] = QVector4D(posXSquare - offsetSquare/windowXDivByY, posYSquare - offsetSquare , 0, 1);
    verticesSquare[1] = QVector4D(posXSquare + offsetSquare/windowXDivByY, posYSquare - offsetSquare , 0, 1);
    verticesSquare[2] = QVector4D(posXSquare + offsetSquare/windowXDivByY, posYSquare + offsetSquare , 0, 1);
    verticesSquare[3] = QVector4D(posXSquare - offsetSquare/windowXDivByY, posYSquare + offsetSquare , 0, 1);

    indicesSquare[0] = 0; indicesSquare[1] = 1; indicesSquare[2] = 2;
    indicesSquare[3] = 2; indicesSquare[4] = 3; indicesSquare[5] = 0;

    glGenVertexArrays(1,&vaoSquare);
    glBindVertexArray(vaoSquare);

    glGenBuffers(1,&vboVerticesSquare);
    glBindBuffer(GL_ARRAY_BUFFER,vboVerticesSquare);
    glBufferData(GL_ARRAY_BUFFER, verticesSquare.size()*sizeof(QVector4D),verticesSquare.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers (1, &eboIndicesSquare);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndicesSquare);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indicesSquare.size() * sizeof (GLuint), indicesSquare.data(), GL_STATIC_DRAW);


    //Triangle
    std::vector<QVector4D> verticesTriangle;
    std::vector<GLuint> indicesTriangle;

    verticesTriangle.resize(3);
    indicesTriangle.resize(3);

    float posXTriangle{-0.77f};
    float posYTriangle{-0.2f};
    float widthTriangle{0.8f};
    float heightTriangle{0.3f};

    verticesTriangle[0] = QVector4D(posXTriangle, posYTriangle, 0, 1);
    verticesTriangle[1] = QVector4D(posXTriangle + (widthTriangle/2)/windowXDivByY, posYTriangle + heightTriangle, 0, 1);
    verticesTriangle[2] = QVector4D(posXTriangle + widthTriangle/windowXDivByY, posYTriangle, 0, 1);

    indicesTriangle[0] = 0; indicesTriangle[1] = 1; indicesTriangle[2] = 2;

    glGenVertexArrays(1,&vaoTriangle);
    glBindVertexArray(vaoTriangle);

    glGenBuffers(1,&vboVerticesTriangle);
    glBindBuffer(GL_ARRAY_BUFFER,vboVerticesTriangle);
    glBufferData(GL_ARRAY_BUFFER, verticesTriangle.size()*sizeof(QVector4D),verticesTriangle.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers (1, &eboIndicesTriangle);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndicesTriangle);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indicesTriangle.size() * sizeof (GLuint), indicesTriangle.data(), GL_STATIC_DRAW);


    //Rectangle
    std::vector<QVector4D> verticesRectangle;
    std::vector<GLuint> indicesRectangle;

    verticesRectangle.resize(4);
    indicesRectangle.resize(6);

    float posXRectangle{0.6f};
    float posYRectangle{-0.5f};
    float offsetXRectangle{0.09f};
    float offsetYRectangle{0.3f};

    verticesRectangle[0] = QVector4D(posXRectangle - offsetXRectangle/windowXDivByY, posYRectangle - offsetYRectangle , 0, 1);
    verticesRectangle[1] = QVector4D(posXRectangle + offsetXRectangle/windowXDivByY, posYRectangle - offsetYRectangle , 0, 1);
    verticesRectangle[2] = QVector4D(posXRectangle + offsetXRectangle/windowXDivByY, posYRectangle + offsetYRectangle , 0, 1);
    verticesRectangle[3] = QVector4D(posXRectangle - offsetXRectangle/windowXDivByY, posYRectangle + offsetYRectangle , 0, 1);

    indicesRectangle[0] = 0; indicesRectangle[1] = 1; indicesRectangle[2] = 2;
    indicesRectangle[3] = 2; indicesRectangle[4] = 3; indicesRectangle[5] = 0;

    glGenVertexArrays(1,&vaoRectangle);
    glBindVertexArray(vaoRectangle);

    glGenBuffers(1,&vboVerticesRectangle);
    glBindBuffer(GL_ARRAY_BUFFER,vboVerticesRectangle);
    glBufferData(GL_ARRAY_BUFFER, verticesRectangle.size()*sizeof(QVector4D),verticesRectangle.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers (1, &eboIndicesRectangle);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndicesRectangle);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indicesRectangle.size() * sizeof (GLuint), indicesRectangle.data(), GL_STATIC_DRAW);


    //Circle
    glGenVertexArrays(1,&vaoCircle);
    glBindVertexArray(vaoCircle);

    std::vector<QVector4D> verticesCircle;
    verticesCircle.resize(steps);
    for(unsigned int i{0}; i < steps; i++){
        float os[2] = {0.6, 0.7};
        float r[2] = {0.15, 0.15};
        verticesCircle[i] = QVector4D(os[0] + r[0]*sin(qDegreesToRadians(i))/windowXDivByY, os[1] + r[1]*cos(qDegreesToRadians(i)), 0, 1);
    }

    glGenBuffers(1, &vboVerticesCircle);
    glBindBuffer(GL_ARRAY_BUFFER, vboVerticesCircle);
    glBufferData(GL_ARRAY_BUFFER, verticesCircle.size()*sizeof(QVector4D), verticesCircle.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);


    //Heart
    glGenVertexArrays(1, &vaoHeart);
    glBindVertexArray(vaoHeart);

    std::vector<QVector4D> verticesHeart;
    verticesHeart.resize(steps);
    for(unsigned int i{0}; i < steps; i++){
        double t = qDegreesToRadians(i);
        float d[2] = {-0.5, -0.5};
        verticesHeart[i] = QVector4D(d[0] + 0.08*sin(t) * sin(t) * sin(t)/windowXDivByY, d[1] + 0.065*cos(t)-0.025*cos(2*t)-0.01*cos(3*t)-0.005*cos(4*t), 0, 1);
    }

    glGenBuffers(1, &vboVerticesHeart);
    glBindBuffer(GL_ARRAY_BUFFER, vboVerticesHeart);
    glBufferData(GL_ARRAY_BUFFER, verticesHeart.size()*sizeof(QVector4D), verticesHeart.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    //Octagon
    std::vector<QVector4D> verticesOctagon;
    std::vector<GLuint> indicesOctagon;

    verticesOctagon.resize(9);
    indicesOctagon.resize(8);

    float posXOctagon{0.435f};
    float posYOctagon{0.0f};
    float heightOctagon{0.3f};
    float widthOctagon{0.5f};

//    verticesOctagon[0] = QVector4D(posXOctagon, posYOctagon - (heightOctagon/2.0), 0, 1);
//    verticesOctagon[1] = QVector4D(posXOctagon + (widthOctagon/6.0)/windowXDivByY, posYOctagon - (heightOctagon/6.0) , 0, 1);
//    verticesOctagon[2] = QVector4D(posXOctagon + (widthOctagon/2.0)/windowXDivByY, posYOctagon , 0, 1);
//    verticesOctagon[3] = QVector4D(posXOctagon + (widthOctagon*5.0/6.0)/windowXDivByY, posYOctagon - (heightOctagon/6.0) , 0, 1);
//    verticesOctagon[4] = QVector4D(posXOctagon + widthOctagon/windowXDivByY, posYOctagon - (heightOctagon/2.0) , 0, 1);
//    verticesOctagon[5] = QVector4D(posXOctagon + (widthOctagon*5.0/6.0)/windowXDivByY, posYOctagon - (heightOctagon*5.0/6.0) , 0, 1);
//    verticesOctagon[6] = QVector4D(posXOctagon + (widthOctagon/2.0)/windowXDivByY, posYOctagon - heightOctagon , 0, 1);
//    verticesOctagon[7] = QVector4D(posXOctagon + (widthOctagon/6.0)/windowXDivByY, posYOctagon - (heightOctagon*5.0/6.0) , 0, 1);
    verticesOctagon[0] = QVector4D(posXOctagon, posYOctagon - (heightOctagon/2.0), 0, 1);
    verticesOctagon[1] = QVector4D(posXOctagon + (widthOctagon/6.0)/windowXDivByY, posYOctagon - (heightOctagon/6.0) , 0, 1);
    verticesOctagon[2] = QVector4D(posXOctagon + (widthOctagon/2.0)/windowXDivByY, posYOctagon , 0, 1);
    verticesOctagon[3] = QVector4D(posXOctagon + (widthOctagon*5.0/6.0)/windowXDivByY, posYOctagon - (heightOctagon/6.0) , 0, 1);
    verticesOctagon[4] = QVector4D(posXOctagon + widthOctagon/windowXDivByY, posYOctagon - (heightOctagon/2.0) , 0, 1);
    verticesOctagon[5] = QVector4D(posXOctagon + (widthOctagon*5.0/6.0)/windowXDivByY, posYOctagon - (heightOctagon*5.0/6.0) , 0, 1);
    verticesOctagon[6] = QVector4D(posXOctagon + (widthOctagon/2.0)/windowXDivByY, posYOctagon - heightOctagon , 0, 1);
    verticesOctagon[7] = QVector4D(posXOctagon + (widthOctagon/6.0)/windowXDivByY, posYOctagon - (heightOctagon*5.0/6.0) , 0, 1);
    verticesOctagon[8] = QVector4D(posXOctagon, posYOctagon - (heightOctagon/2.0), 0, 1);
//    indicesOctagon[0] = 0; indicesOctagon[1] = 1; indicesOctagon[2] = 2;
//    indicesOctagon[3] = 3; indicesOctagon[4] = 4; indicesOctagon[5] = 5;
//    indicesOctagon[6] = 6; indicesOctagon[7] = 7; indicesOctagon[8] = 8;
//    indicesOctagon[6] = 2; indicesOctagon[7] = 9; indicesOctagon[8] = 3;
//    indicesOctagon[9] = 3; indicesOctagon[10] = 9; indicesOctagon[11] = 4;
//    indicesOctagon[12] = 4; indicesOctagon[13] = 9; indicesOctagon[14] = 5;
//    indicesOctagon[15] = 5; indicesOctagon[16] = 9; indicesOctagon[17] = 6;
//    indicesOctagon[18] = 6; indicesOctagon[19] = 9; indicesOctagon[20] = 7;
//    indicesOctagon[21] = 7; indicesOctagon[22] = 9; indicesOctagon[23] = 8;

    glGenVertexArrays(1,&vaoOctagon);
    glBindVertexArray(vaoOctagon);

    glGenBuffers(1,&vboVerticesOctagon);
    glBindBuffer(GL_ARRAY_BUFFER,vboVerticesOctagon);
    glBufferData(GL_ARRAY_BUFFER, verticesOctagon.size()*sizeof(QVector4D),verticesOctagon.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);

//    glGenBuffers (1, &eboIndicesOctagon);
//    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndicesOctagon);
//    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indicesOctagon.size() * sizeof (GLuint), indicesOctagon.data(), GL_STATIC_DRAW);
}

void OpenGLWidget::destroyVBOs() {
    makeCurrent ();
    glDeleteBuffers (1, &vboVerticesSquare);
    glDeleteBuffers (1, &vboVerticesCircle);
    glDeleteBuffers (1, &vboVerticesHeart);
    glDeleteBuffers (1, &eboIndicesSquare);
    glDeleteVertexArrays (1, &vaoHeart);
    glDeleteVertexArrays (1, &vaoSquare);
    glDeleteVertexArrays (1, &vaoCircle);
    vboVerticesSquare=0;
    vboVerticesCircle=0;
    vboVerticesHeart=0;
    eboIndicesSquare=0;
    vaoHeart=0;
    vaoSquare=0;
    vaoCircle=0;
}

void OpenGLWidget::keyPressEvent(QKeyEvent
*event)
{
    switch(event->key()){
    case Qt::Key_Escape:
        QApplication::quit();
        break;//desnecessario
    }
}
