#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include "qopengl.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QFileDialog>
#include <QMouseEvent>
#include <QMatrix4x4>
#include <QPainter>
#include <math.h>
#include "ObjLoader.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);
	~GLWidget();

	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;
	QSize minimumSizeHint() const override;
	void arcBall(QPoint last_pnt, QPoint curr_pnt);

	double calculateX(QPoint point);
	double calculateY(QPoint point);
	double calculateZ(double x, double y);

	double WINDOW_WIDTH, WINDOW_HEIGHT;

	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer m_vbo;
	QOpenGLShaderProgram *m_program;
	QMatrix4x4 m_proj;
	QMatrix4x4 m_camera;
	QMatrix4x4 m_world;
	QMatrix4x4 m_world_tmp;
	int m_mvMatrixLoc;
	int m_projMatrixLoc;
	QPoint m_lastPos;
	QPoint m_currPos;
	QVector3D rotateAxis;
	float rotateAngle;

	ObjLoader objLoader;
	QOpenGLBuffer arrayBuffer, indexBuffer;

	bool isNormalShown = false;

	public slots:
	void load_file();
	void show_normal();
};

#endif
