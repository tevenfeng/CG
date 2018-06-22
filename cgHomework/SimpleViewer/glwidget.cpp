#include "glwidget.h"
#include <QMouseEvent>

//--------------------ADS-----------------------//
//static const char *myVertexShaderSource =
//"in vec4 vPosition;\n"
//"in vec3 normal;\n"
//"uniform mat4 projMatrix;\n"
//"uniform mat4 mvMatrix;\n"
//"uniform mat3 normalMatrix;\n"
//"uniform vec3 lightPos;\n"
//"out vec4 veryingColor;\n"
//"void main(){\n"
//"    gl_Position = projMatrix * mvMatrix * vPosition;\n"
//"    vec4 diffuseColor= vec4(0.5, 0.4, 0.8, 1.0);\n"
//"    vec4 ambientColor= vec4(0.1, 0.1, 0.1, 0.0);\n"
//"    vec4 specularColor= vec4(1.0, 1.0, 1.0, 0.0);\n"
//"    vec3 N = normalize(normalMatrix * normal);\n"
//"    vec3 L = normalize(lightPos - vPosition.xyz); \n"
//"    vec3 r = normalize(reflect(-L,N)); \n"
//"    veryingColor=ambientColor+dot(N,L)*diffuseColor+specularColor*pow(dot(r,N),128.0);\n"
//"}\n"
//;
//static const char *myFragmentShaderSource =
//"in vec4 veryingColor;\n"
//"out vec4 fColor;\n"
//"void main(){\n"
//"    fColor = veryingColor;\n"
//"}\n";

//----------------phong--------------------//
static const char *myVertexShaderSource =
"in vec4 vPosition;\n"
"in vec3 normal;\n"
"uniform mat4 projMatrix;\n"
"uniform mat4 mvMatrix;\n"
"uniform mat3 normalMatrix;\n"
"uniform vec3 lightPos;\n"
"out vec3 N;\n"
"out vec3 L;\n"
"void main(){\n"
"    gl_Position = projMatrix * mvMatrix * vPosition;\n"
"    N = normalize(normalMatrix * normal);\n"
"    L = normalize(lightPos - vPosition.xyz); \n"
"}\n"
;
static const char *myFragmentShaderSource =
"in vec3 N;\n"
"in vec3 L;\n"
"out vec4 fColor;\n"
"void main(){\n"
"    vec4 diffuseColor= vec4(0.5, 0.4, 0.8, 1.0);\n"
"    vec4 ambientColor= vec4(0.1, 0.1, 0.1, 0.0);\n"
"    vec4 specularColor= vec4(1.0, 1.0, 1.0, 0.0);\n"
"    vec3 r = normalize(reflect(-L,N)); \n"
"    fColor = ambientColor+dot(N,L)*diffuseColor+specularColor*pow(dot(r,N),128.0);\n"
"}\n";

GLWidget::GLWidget(QWidget *parent)
	: QOpenGLWidget(parent), indexBuffer(QOpenGLBuffer::IndexBuffer)
{

}
GLWidget::~GLWidget() {}

QSize GLWidget::minimumSizeHint() const
{
	return QSize(500, 500);
}

void GLWidget::initializeGL()
{
	this->objLoader = ObjLoader();
	this->objLoader.loadObj("sphere_withNormal.obj");

	initializeOpenGLFunctions();
	int m_transparent = 0;
	glClearColor(0.8, 0.8, 0.8, 1);

	m_program = new QOpenGLShaderProgram;
	m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, myVertexShaderSource);
	m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, myFragmentShaderSource);
	m_program->bindAttributeLocation("vertex", 0);
	m_program->bindAttributeLocation("normal", 1);
	m_program->link();

	m_program->bind();
	m_projMatrixLoc = m_program->uniformLocation("projMatrix");
	m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");

	m_program->setUniformValue(m_program->uniformLocation("lightPos"), QVector3D(0, 0, 70));

	m_vao.create();
	QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

	arrayBuffer.create();
	arrayBuffer.bind();
	arrayBuffer.allocate(this->objLoader.vertexes, this->objLoader.vertexNum * sizeof(VertexData));

	indexBuffer.create();
	indexBuffer.bind();
	indexBuffer.allocate(this->objLoader.indices, this->objLoader.indiceNum * sizeof(unsigned int));

	m_program->enableAttributeArray(0);
	m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(VertexData));
	m_program->enableAttributeArray(1);
	m_program->setAttributeBuffer(1, GL_FLOAT, sizeof(QVector3D), 3, sizeof(VertexData));

	// Our camera never changes in this example.
	m_camera.setToIdentity();
	m_camera.translate(0, 0, -12);

	m_program->release();

	m_world.setToIdentity();
	rotateAngle = 0;
	rotateAxis = QVector3D(1, 0, 0);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	QMatrix4x4 tmp;
	tmp.rotate(rotateAngle*180.0 / 3.14, rotateAxis);
	m_world = tmp * m_world;

	QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
	m_program->bind();
	m_program->setUniformValue(m_projMatrixLoc, m_proj);
	m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
	m_program->setUniformValue(m_program->uniformLocation("normalMatrix"), m_world.normalMatrix());

	glDrawElements(GL_TRIANGLES, this->objLoader.indiceNum, GL_UNSIGNED_INT, 0);

	m_program->release();
}

void GLWidget::resizeGL(int w, int h)
{
	m_proj.setToIdentity();
	m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);

	this->WINDOW_WIDTH = this->width();
	this->WINDOW_HEIGHT = this->height();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	m_lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	m_currPos = event->pos();
	if (event->buttons() & Qt::LeftButton )
	{
		arcBall(m_lastPos, m_currPos);
		update();
	}
	m_lastPos = m_currPos;
}

void GLWidget::arcBall(QPoint last_pnt, QPoint curr_pnt)
{
	QVector3D lastPoint3d, currPoint3d;
	lastPoint3d = QVector3D();
	currPoint3d = QVector3D();

	lastPoint3d.setX(calculateX(last_pnt));
	lastPoint3d.setY(calculateY(last_pnt));
	lastPoint3d.setZ(calculateZ(lastPoint3d.x(), lastPoint3d.y()));

	currPoint3d.setX(calculateX(curr_pnt));
	currPoint3d.setY(calculateY(curr_pnt));
	currPoint3d.setZ(calculateZ(currPoint3d.x(), currPoint3d.y()));

	// 目前还不知道是弧度制还是角度制
	this->rotateAngle = acos(QVector3D::dotProduct(lastPoint3d, currPoint3d) / (lastPoint3d.length()*currPoint3d.length()));

	this->rotateAxis = QVector3D::crossProduct(lastPoint3d, currPoint3d).normalized();
}

double GLWidget::calculateX(QPoint point)
{
	return 2.0 * point.x() / WINDOW_WIDTH - 1.0;
}

double GLWidget::calculateY(QPoint point)
{
	return -(2.0*point.y() / WINDOW_HEIGHT - 1);
}

double GLWidget::calculateZ(double x, double y)
{
	return (pow(x, 2.0) + pow(y, 2.0) <= 1) ? sqrt(1 - pow(x, 2.0) - pow(y, 2.0)) : 0;
}

void GLWidget::load_file()
{
	std::string filePath = QFileDialog::getOpenFileName(this, tr("Load File"), "", "obj file(*.obj)").toStdString();

	char* charPath = (char*)filePath.c_str();
	this->objLoader = ObjLoader();
	this->objLoader.loadObj(charPath);
}