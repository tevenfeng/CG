
// Sutherland-HodgmanDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Sutherland-Hodgman.h"
#include "Sutherland-HodgmanDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSutherlandHodgmanDlg 对话框

bool m_rBtndown;																			//用于判断鼠标右键是否按下
bool m_lBtndbclk;																			//用于判断矩形是否闭合
CPoint m_startPoint;																		//绘制窗口过程中左上角顶点
CPoint m_endPoint;																			//绘制窗口过程中右下角顶点
CPoint rect_topleft, rect_topright, rect_btmleft, rect_btmright;							//窗口四个顶点
CPoint pointArray[100],cuttedPoint1[100],cuttedPoint2[100],cuttedPoint3[100],cuttedPoint4[100];								//存储多边形的点
int pointCount = 0;																			//多边形点的计数
int cuttedNum = 0;																			//裁剪队列中已存在的点的数量

CSutherlandHodgmanDlg::CSutherlandHodgmanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSutherlandHodgmanDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSutherlandHodgmanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSutherlandHodgmanDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_rect, &CSutherlandHodgmanDlg::OnBnClickedButtonrect)
	ON_BN_CLICKED(IDC_BUTTON_reset, &CSutherlandHodgmanDlg::OnBnClickedButtonreset)
	ON_BN_CLICKED(IDC_BUTTON_cut, &CSutherlandHodgmanDlg::OnBnClickedButtoncut)
END_MESSAGE_MAP()


// CSutherlandHodgmanDlg 消息处理程序
BOOL CSutherlandHodgmanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_NORMAL);

	// TODO:  在此添加额外的初始化代码
	m_rBtndown = false;
	m_lBtndbclk = false;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CSutherlandHodgmanDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		
		CRect rect;
		GetClientRect(&rect);
		CBrush myBrush(RGB(255, 255, 255));
		dc.FillRect(&rect, &myBrush);

		dc.MoveTo(pointArray[0].x,pointArray[0].y);
		for (int i = 1; i < pointCount; i++)
		{
			dc.LineTo(pointArray[i].x, pointArray[i].y);
		}

		if (m_lBtndbclk)
		{
			dc.LineTo(pointArray[0].x,pointArray[0].y);
		}

		if (m_rBtndown)
		{
			CRect rect(m_startPoint,m_endPoint);
			rect.NormalizeRect();
			CBrush myBrush(RGB(0, 0, 255));
			dc.FrameRect(&rect, &myBrush);
		}

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSutherlandHodgmanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//鼠标左键按下，获取获取一个多边形的点，存入数组中
//若点的计数超过两个则同时调用OnPaint函数画出来
void CSutherlandHodgmanDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_lBtndbclk == false)
	{
		pointArray[pointCount] = point;
		pointCount++;
		OnPaint();
		Invalidate(FALSE);
	}
	else
	{
		MessageBox(_T("矩形已闭合！"));
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

//闭合按钮，使得矩形闭合
void CSutherlandHodgmanDlg::OnBnClickedButtonrect()
{
	m_lBtndbclk = true;
	OnPaint();
	Invalidate(FALSE);
}

//鼠标右键按住，开始捕捉鼠标移动的动作
void CSutherlandHodgmanDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_startPoint = point;
	m_endPoint = point;
	m_rBtndown = true;
	SetCapture();

	CDialogEx::OnRButtonDown(nFlags, point);
}

//鼠标右键松开，释放鼠标移动动作的捕捉
void CSutherlandHodgmanDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
	{
		ReleaseCapture();
	}
	m_rBtndown = false;

	CDialogEx::OnRButtonUp(nFlags, point);
}

//按住右键移动过程中不断更新m_endPoint，同时将其画出来
void CSutherlandHodgmanDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_rBtndown)
	{
		m_endPoint = point;
		Invalidate(FALSE);
	}

	rect_topleft = CPoint(m_startPoint.x, m_startPoint.y);
	rect_topright = CPoint(m_endPoint.x, m_startPoint.y);
	rect_btmleft = CPoint(m_startPoint.x, m_endPoint.y);
	rect_btmright = CPoint(m_endPoint.x, m_endPoint.y);

	CDialogEx::OnMouseMove(nFlags, point);
}

//刷新背景
BOOL CSutherlandHodgmanDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}

//重置按钮
void CSutherlandHodgmanDlg::OnBnClickedButtonreset()
{
	m_lBtndbclk = false;
	m_rBtndown = false;
	pointCount = 0;
	Invalidate(FALSE);
}

//裁剪算法
void CSutherlandHodgmanDlg::OnBnClickedButtoncut()
{
	POINT p1, p2, p3, p4, p;

	//左裁剪
	p3 = rect_topleft;
	p4 = rect_btmleft;
	cuttedNum = 0;
	for (int i = 0; i < pointCount; i++)
	{
		//设置起始线段
		if (i < pointCount - 1)
		{
			p1 = pointArray[i];
			p2 = pointArray[i + 1];
		}
		else if (i == pointCount - 1)
		{
			p1 = pointArray[i];
			p2 = pointArray[0];
		}

		//判断是否垂直
		if (p1.x == p2.x)
		{
			//把交点加入输出队列
			if (p1.x>p3.x)
				cuttedPoint1[cuttedNum++] = p2;
		}
		else
		{
			//不垂直就可以通过斜率
			//计算延长线交点
			int x = p3.x;
			int y = p2.y - (double)(p2.y - p1.y)*(double)(p2.x - x) / (double)(p2.x - p1.x);

			//有交点
			if (y > min(p1.y, p2.y) && y < max(p1.y, p2.y))
			{
				p.x = x;
				p.y = y;
				cuttedPoint1[cuttedNum++] = p;
			}

			//从外向内或者从内到内
			if (p2.x > p3.x)
			{
				cuttedPoint1[cuttedNum++] = p2;
			}
		}
	}

	//右裁剪
	p3 = rect_topright;
	p4 = rect_btmright;
	pointCount = cuttedNum;
	cuttedNum = 0;
	for (int i = 0; i < pointCount; i++)
	{
		//设置线段起始点
		if (i < pointCount - 1)
		{
			p1 = cuttedPoint1[i];
			p2 = cuttedPoint1[i + 1];
		}
		else if (i == pointCount - 1)
		{
			p1 = cuttedPoint1[i];
			p2 = cuttedPoint1[0];
		}
		//判断垂直
		if (p1.x == p2.x)
		{
			if (p1.x<p3.x)
				cuttedPoint2[cuttedNum++] = p2;
		}
		else
		{
			int x = p3.x;
			int y = p2.y - (double)(p2.y - p1.y)*(double)(p2.x - x) / (double)(p2.x - p1.x);
			//有交点
			if (y > min(p1.y, p2.y) && y < max(p1.y, p2.y))
			{
				p.x = x;
				p.y = y;
				cuttedPoint2[cuttedNum++] = p;
			}
			if (p2.x < p3.x)//从外向内或从内到内
			{
				cuttedPoint2[cuttedNum++] = p2;
			}
		}
	}

	//下裁剪
	p3 = rect_btmleft;
	p4 = rect_btmright;
	pointCount = cuttedNum;
	cuttedNum = 0;
	for (int i = 0; i < pointCount; i++)
	{
		//设置线段起始点
		if (i < pointCount - 1)
		{
			p1 = cuttedPoint2[i];
			p2 = cuttedPoint2[i + 1];
		}
		else if (i == pointCount - 1)
		{
			p1 = cuttedPoint2[i];
			p2 = cuttedPoint2[0];
		}

		//判断平行
		if (p1.y == p2.y)//从内到内
		{
			if (p1.y<p3.y)
				cuttedPoint3[cuttedNum++] = p2;
		}
		else
		{
			if (p1.x == p2.x)//垂直直接计算交点
			{
				if (p3.y>min(p1.y, p2.y) && p3.y<max(p1.y, p2.y))//从外向内
				{
					p.x = p1.x;
					p.y = p3.y;
					cuttedPoint3[cuttedNum++] = p;
				}
			}
			else
			{
				int y = p3.y;
				int x = p2.x - (double)(p2.y - y)*(double)(p2.x - p1.x) / (double)(p2.y - p1.y);
				if (x > min(p1.x, p2.x) && x < max(p1.x, p2.x))
				{
					p.x = x;
					p.y = y;
					cuttedPoint3[cuttedNum++] = p;
				}
			}

			//从外向内
			if (p2.y < p3.y)
			{
				cuttedPoint3[cuttedNum++] = p2;
			}
		}
	}

	//上裁剪
	p3 = rect_topleft;
	p4 = rect_topright;
	pointCount = cuttedNum;
	cuttedNum = 0;
	for (int i = 0; i < pointCount; i++)
	{
		//设置线段起始点
		if (i < pointCount - 1)
		{
			p1 = cuttedPoint3[i];
			p2 = cuttedPoint3[i + 1];
		}
		else if (i == pointCount - 1)
		{
			p1 = cuttedPoint3[i];
			p2 = cuttedPoint3[0];
		}

		//判断平行
		if (p1.y == p2.y)
		{
			//从内到内
			if (p1.y>p3.y)
				cuttedPoint4[cuttedNum++] = p2;
		}
		else
		{
			if (p1.x == p2.x)
			{
				//垂直直接计算交点
				if (p3.y>min(p1.y, p2.y) && p3.y<max(p1.y, p2.y))
				{
					//从外向内
					p.x = p1.x;
					p.y = p3.y;
					cuttedPoint4[cuttedNum++] = p;
				}
			}
			else
			{
				//求交点
				int y = p3.y;
				int x = p2.x - (double)(p2.y - y)*(double)(p2.x - p1.x) / (double)(p2.y - p1.y);
				if (x > min(p1.x, p2.x) && x < max(p1.x, p2.x))
				{
					p.x = x;
					p.y = y;
					cuttedPoint4[cuttedNum++] = p;
				}
			}

			if (p2.y > p3.y)
			{
				//从外向内
				cuttedPoint4[cuttedNum++] = p2;
			}
		}
	}

	//开始绘制
	CClientDC dc(this);
	CPen pen(0, 2, RGB(255, 0, 0));
	dc.SelectObject(&pen);
	for (int i = 0; i < cuttedNum - 1; i++)
	{
		dc.MoveTo(cuttedPoint4[i]);
		dc.LineTo(cuttedPoint4[i + 1]);
	}
	dc.MoveTo(cuttedPoint4[cuttedNum - 1]);
	dc.LineTo(cuttedPoint4[0]);
}
