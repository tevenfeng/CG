
// ddaDrawingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ddaDrawing.h"
#include "ddaDrawingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CddaDrawingDlg 对话框

int startX, startY, endX, endY;

CddaDrawingDlg::CddaDrawingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CddaDrawingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CddaDrawingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_Grid, button_Grid);
}

BEGIN_MESSAGE_MAP(CddaDrawingDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Grid, &CddaDrawingDlg::OnBnClickedButtonGrid)
	ON_BN_CLICKED(IDC_BUTTON_DDA, &CddaDrawingDlg::OnBnClickedButtonDda)
	ON_BN_CLICKED(IDC_BUTTON_Bresenham, &CddaDrawingDlg::OnBnClickedButtonBresenham)
END_MESSAGE_MAP()


// CddaDrawingDlg 消息处理程序

BOOL CddaDrawingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_NORMAL);

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CddaDrawingDlg::OnPaint()
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

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CddaDrawingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CddaDrawingDlg::OnBnClickedButtonGrid()
{
	//TODO:  在此添加控件通知处理程序代码
	CClientDC pDC(this);
	CPen myPen;
	myPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *pOldPen = pDC.SelectObject(&myPen);
	for (int i = 0; i <= 150; i++)
	{
		pDC.MoveTo(12, 4 * i+12);
		pDC.LineTo(1212, 4 * i+12);
	}
	for (int i = 0; i <= 300; i++)
	{
		pDC.MoveTo(4 * i+12, 12);
		pDC.LineTo(4 * i+12, 612);
	}
}

//DDA算法
void CddaDrawingDlg::OnBnClickedButtonDda()
{
	// TODO:  在此添加控件通知处理程序代码
	bool test = getCoordinate();                              //获取坐标
	if (!test)
	{
		MessageBox(_T("坐标错误！"));
	}
	else
	{
		drawPixel(startX, startY, 1);
		drawPixel(endX, endY, 1);
		int nextX = startX, nextY = startY;
		double tmp;
		double k = (double)(endY - startY) / (endX - startX);

		//分为k大于等于1和小于1两种情况做
		if ((k <= 1) && (k>=-1))
		{
			tmp = startY;
			double k = (double)(endY - startY) / (endX - startX);
			for (int i = 1; i <= abs(startX - endX); i++)
			{
				if (startX-endX <= 0)
				{
					nextX++;
					tmp = (double)tmp + k;
				}
				else
				{
					nextX--;
					tmp = (double)tmp - k;
				}
				nextY = (int)tmp;
				drawPixel(nextX, nextY, 1);
			}
		}
		else
		{
			tmp = startX;
			double k = (double)(endX - startX) / (endY - startY);
			for (int i = 1; i <= abs(startY - endY); i++)
			{
				//判断直线斜率为正or为负
				if (startY-endY <= 0)
				{
					nextY++;
					tmp = (double)tmp + k;
				}
				else
				{
					nextY--;
					tmp = (double)tmp - k;
				}
				nextX = (int)tmp;
				drawPixel(nextX, nextY, 1);
			}
		}
	}
}

void CddaDrawingDlg::OnBnClickedButtonBresenham()
{
	// TODO:  在此添加控件通知处理程序代码
	bool test = getCoordinate();                              //获取坐标
	if (!test)
	{
		MessageBox(_T("坐标错误！"));
	}
	else
	{
		drawPixel(startX, startY, 2);
		drawPixel(endX, endY, 2);
		double k = (double)(endY - startY) / (endX - startX);

		if (k >= 0)
		{
			if (k <= 1)
			{
				if (startX - endX > 0){ exchange(); }
				int dy = endY - startY;
				int dx = endX - startX;
				int pk = 2 * dy - dx;
				int pk1 = pk;
				int yk, yk1;
				yk1 = yk = startY;
				int nextX = startX;
				for (int i = 1; i <= abs(startX - endX); i++)
				{
					nextX++;
					if (pk > 0)
					{
						yk1 = yk + 1;
					}
					else
					{
						yk1 = yk;
					}
					drawPixel(nextX, yk1, 2);
					pk1 = pk + 2 * dy - 2 * dx*(yk1 - yk);
					yk = yk1;
					pk = pk1;
				}
			}
			else
			{
				if (startY - endY > 0){ exchange(); }
				int dy = endY - startY;
				int dx = endX - startX;
				int pk = 2 * dx - dy;
				int pk1 = pk;
				int xk, xk1;
				xk1 = xk = startX;
				int nextY = startY;
				for (int i = 1; i <= abs(startY - endY); i++)
				{
					nextY++;
					if (pk > 0)
					{
						xk1 = xk + 1;
					}
					else
					{
						xk1 = xk;
					}
					drawPixel(xk1, nextY, 2);
					pk1 = pk + 2 * dx - 2 * dy*(xk1 - xk);
					xk = xk1;
					pk = pk1;
				}
			}
		}
		else
		{
			if (k >= -1)
			{
				if (startX - endX > 0){ exchange(); }
				int dy = -(endY - startY);
				int dx = -(endX - startX);
				int pk = 2 * dy - dx;
				int pk1 = pk;
				int yk, yk1;
				yk1 = yk = startY;
				int nextX = startX;
				for (int i = 1; i <= abs(startX - endX); i++)
				{
					nextX++;
					if (pk > 0)
					{
						yk1 = yk - 1;
					}
					else
					{
						yk1 = yk;
					}
					drawPixel(nextX, yk1, 2);
					pk1 = pk + 2 * dy - 2 * dx*(yk1 - yk);
					yk = yk1;
					pk = pk1;
				}
			}
			else
			{
				if (startY - endY > 0){ exchange(); }
				int dy = -(endY - startY);
				int dx = -(endX - startX);
				int pk = 2 * dx - dy;
				int pk1 = pk;
				int xk, xk1;
				xk1 = xk = startX;
				int nextY = startY;
				for (int i = 1; i <= abs(startY - endY); i++)
				{
					nextY++;
					if (pk > 0)
					{
						xk1 = xk - 1;
					}
					else
					{
						xk1 = xk;
					}
					drawPixel(xk1, nextY, 2);
					pk1 = pk + 2 * dx - 2 * dy*(xk1 - xk);
					xk = xk1;
					pk = pk1;
				}
			}
		}
	}
}

//从编辑框中获取起点和终点的坐标
bool CddaDrawingDlg::getCoordinate()
{
	startX = GetDlgItemInt(IDC_EDIT_startX, NULL, TRUE);
	startY = GetDlgItemInt(IDC_EDIT_startY, NULL, TRUE);                        //149减是为了使原点在左下方
	endX = GetDlgItemInt(IDC_EDIT_endX, NULL, TRUE);
	endY = GetDlgItemInt(IDC_EDIT_endY, NULL, TRUE);							//149减是为了使原点在左下方

	//判断坐标是否合法
	if ((startX < 0) 
		|| (startX >= 300) 
		|| (startY < 0) 
		|| (startY >= 150) 
		|| (endX < 0) 
		|| (endX >= 300) 
		|| (endY < 0) 
		|| (endY >= 150))
	{
		return false;
	}
	else
	{
		return true;
	}
}


//画出一个“像素”
void CddaDrawingDlg::drawPixel(int x,int y, int test)
{
	CClientDC pdc(this);
	y = 149 - y;

	POINT p1, p2;
	p1.x = x * 4 + 12;
	p1.y = y * 4 + 12;
	p2.x = p1.x + 4;
	p2.y = p1.y + 4;
	CRect rectangle(p1, p2);
	if (test == 1)
	{
		CBrush myBrush(RGB(255, 0, 0));
		pdc.FillRect(rectangle, &myBrush);
	}
	else
	{
		CBrush myBrush(RGB(0, 0, 255));
		pdc.FillRect(rectangle, &myBrush);
	}
}

void CddaDrawingDlg::exchange()
{
	int tmp = startX;
	startX = endX;
	endX = tmp;

	tmp = startY;
	startY = endY;
	endY = tmp;
}
