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

void OpenGLWidget::drawSolidSquare(){
    makeCurrent();

    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 1, 0, 0, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoSquare);
    //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_LINE_LOOP, 0, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    //glDrawArrays(GL_POINTS, 0, 4);
}

void OpenGLWidget::drawColorSquare(){
    glUseProgram(shaderProgram);
    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 0);
    glBindVertexArray(vaoSquare);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void OpenGLWidget::drawCircle(){
    makeCurrent();

    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 1, 1, 0, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoCircle);
    glDrawArrays(GL_TRIANGLE_FAN, 0, steps);
}

void OpenGLWidget::drawHeart(){
    makeCurrent();
    glUseProgram(shaderProgram);

    auto locColor{glGetUniformLocation(shaderProgram, "vColor")};
    glUniform4f(locColor, 1, 0, 1, 1);

    auto locSolidColor{glGetUniformLocation(shaderProgram, "solid_color")};
    glUniform1i(locSolidColor, 1);

    glBindVertexArray(vaoHeart);
    glDrawArrays(GL_TRIANGLE_FAN, 0, steps);
};

void OpenGLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    if(DayNight)
        drawSolidSquare();
    else
        drawColorSquare();
    drawCircle();
    drawHeart();
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

    std::vector<QVector4D> vertices;
    std::vector<QVector4D> colors;
    std::vector<GLuint> indices;

    vertices.resize(4);
    colors.resize(4);
    indices.resize(6); //2*3

    float posx{0.3f};
    float posy{0.3f};
    float offset{0.2f};

    vertices[0] = QVector4D(posx - offset, posy - offset , 0, 1);
    vertices[1] = QVector4D(posx + offset, posy - offset , 0, 1);
    vertices[2] = QVector4D(posx + offset, posy + offset , 0, 1);
    vertices[3] = QVector4D(posx - offset, posy + offset , 0, 1);

    // Create colors for the vertices
    colors[0] = QVector4D(1, 0, 0, 1); // Red
    colors[1] = QVector4D(0, 1, 0, 1); // Green
    colors[2] = QVector4D(0, 0, 1, 1); // Blue
    colors[3] = QVector4D(1, 1, 0, 1); // Yellow

    // Topology of the mesh ( square )
    indices[0] = 0; indices[1] = 1; indices[2] = 2;
    indices[3] = 2; indices[4] = 3; indices[5] = 0;

    glGenVertexArrays(1,&vaoSquare);
    glBindVertexArray(vaoSquare);

    glGenBuffers(1,&vboVerticesSquare);
    glBindBuffer(GL_ARRAY_BUFFER,vboVerticesSquare);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(QVector4D),vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers (1, &vboColorsSquare);
    glBindBuffer (GL_ARRAY_BUFFER,vboColorsSquare);
    glBufferData (GL_ARRAY_BUFFER,colors.size()*sizeof(QVector4D),colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer (1, 4, GL_FLOAT , GL_FALSE , 0, nullptr);
    glEnableVertexAttribArray (1);

    glGenBuffers (1, &eboIndicesSquare);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndicesSquare);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indices.size() * sizeof (GLuint), indices.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1,&vaoCircle);
    glBindVertexArray(vaoCircle);

    std::vector<QVector4D> verticesCircle;
    verticesCircle.resize(steps);
    for(unsigned int i{0}; i < steps; i++){
        float os[2] = {-0.5, 0.5};
        float r[2] = {0.1, 0.08};
        verticesCircle[i] = QVector4D(os[0] + r[0]*sin(qDegreesToRadians(i)), os[1] + r[1]*cos(qDegreesToRadians(i)), 0, 1);
    }

    glGenBuffers(1, &vboVerticesCircle);
    glBindBuffer(GL_ARRAY_BUFFER, vboVerticesCircle);
    glBufferData(GL_ARRAY_BUFFER, verticesCircle.size()*sizeof(QVector4D), verticesCircle.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);


    glGenVertexArrays(1, &vaoHeart);
    glBindVertexArray(vaoHeart);

    std::vector<QVector4D> verticesHeart;
    verticesHeart.resize(steps);
    for(unsigned int i{0}; i < steps; i++){
        double t = qDegreesToRadians(i);
        float d[2] = {-0.5, -0.5};
        verticesHeart[i] = QVector4D(d[0] + 0.16*sin(t) * sin(t) * sin(t), d[1] + 0.13*cos(t)-0.05*cos(2*t)-0.02*cos(3*t)-0.01*cos(4*t), 0, 1);
    }

    glGenBuffers(1, &vboVerticesHeart);
    glBindBuffer(GL_ARRAY_BUFFER, vboVerticesHeart);
    glBufferData(GL_ARRAY_BUFFER, verticesHeart.size()*sizeof(QVector4D), verticesHeart.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
}

void OpenGLWidget::destroyVBOs() {
    makeCurrent ();
    glDeleteBuffers(1, &vboColorsSquare);
    glDeleteBuffers (1, &vboVerticesSquare);
    glDeleteBuffers (1, &vboVerticesCircle);
    glDeleteBuffers (1, &vboVerticesHeart);
    glDeleteBuffers (1, &eboIndicesSquare);
    glDeleteVertexArrays (1, &vaoHeart);
    glDeleteVertexArrays (1, &vaoSquare);
    glDeleteVertexArrays (1, &vaoCircle);
    vboColorsSquare=0;
    vboVerticesSquare=0;
    vboVerticesCircle=0;
    vboVerticesHeart=0;
    eboIndicesSquare=0;
    vaoHeart=0;
    vaoSquare=0;
    vaoCircle=0;
}

void OpenGLWidget::changeDiagonal() {
    makeCurrent();
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndicesSquare);
    // glMappBuffer-> mac
    auto idx{static_cast<GLuint*>(glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER , 0,
    indices.size()*sizeof(GL_UNSIGNED_INT),GL_MAP_WRITE_BIT))};
    idx[0] = 0; idx[1] = 1; idx[2] = 3;
    idx[3] = 1; idx[4] = 2; idx[5] = 3;
    glUnmapBuffer (GL_ELEMENT_ARRAY_BUFFER) ;
    update();
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
