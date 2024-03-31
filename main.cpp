#include "openglwindow.h"
#include <QGuiApplication>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QtMath>
#include <QSurfaceFormat>
#include "Triangulation.h"
#include "Point3D.h"
#include "Reader.h"


//! [1]
class TriangleWindow : public OpenGLWindow
{
public:
    using OpenGLWindow::OpenGLWindow;

    void initialize() override;
    void render() override;

private:
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;

    QOpenGLShaderProgram* m_program = nullptr;
    int m_frame = 0;
};
//! [1]

//! [2]
int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);
    format.setDepthBufferSize(32); // Changes for depth

    TriangleWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();

    window.setAnimating(true);

    return app.exec();
}
//! [2]


//! [3]
static const char* vertexShaderSource =
"attribute highp vec4 posAttr;\n"
"attribute lowp vec4 colAttr;\n"
"varying lowp vec4 col;\n"
"uniform highp mat4 matrix;\n"
"void main() {\n"
"   col = colAttr;\n"
"   gl_Position = matrix * posAttr;\n"
"}\n";

static const char* fragmentShaderSource =
"varying lowp vec4 col;\n"
"void main() {\n"
"   gl_FragColor = col;\n"
"}\n";

//! [3]

//! [4]
void TriangleWindow::initialize()
{
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = m_program->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = m_program->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);

    // Changes for depth
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}
//! [4]

//! [5]
void TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -3);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 1, 0, 0);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 0, 1);


    m_program->setUniformValue(m_matrixUniform, matrix);


    Triangulation triangulation;
    Reader r;
    r.readFile(triangulation);

    vector<Point3D>& points = triangulation.uniquePoints();
    vector<Triangle>& triangles = triangulation.triangles();

    static const int verticesPerTriangle = 3;
    static const int coordinatesPerVertex = 3;
    static const int totalVertices = verticesPerTriangle * triangles.size();
    static const int totalCoordinates = totalVertices * coordinatesPerVertex;

    GLfloat* vertices = new GLfloat[totalCoordinates];
    int indexIteartion = 0;

    // Iteration for number of triangles
    for (const Triangle& triangle : triangles)
    {
        vertices[indexIteartion++] = points[triangle.v1()].x();
        vertices[indexIteartion++] = points[triangle.v1()].y();
        vertices[indexIteartion++] = points[triangle.v1()].z();

        vertices[indexIteartion++] = points[triangle.v2()].x();
        vertices[indexIteartion++] = points[triangle.v2()].y();
        vertices[indexIteartion++] = points[triangle.v2()].z();

        vertices[indexIteartion++] = points[triangle.v3()].x();
        vertices[indexIteartion++] = points[triangle.v3()].y();
        vertices[indexIteartion++] = points[triangle.v3()].z();  
    }

    GLfloat* colors = new GLfloat[totalCoordinates];

    for (int i = 0; i < totalCoordinates; i += 3) 
    {
        colors[i] = 0.5f;
        colors[i + 1] = 0.0f;
        colors[i + 2] = 0.0f;
    }

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_TRIANGLES, 0, totalCoordinates / 3);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);

    m_program->release();

    ++m_frame;
}
//! [5]
