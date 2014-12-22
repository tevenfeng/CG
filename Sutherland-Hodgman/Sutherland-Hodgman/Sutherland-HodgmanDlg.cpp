
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

bool m_rBtndown;
CPoint m_startPoint;
CPoint m_endPoint;


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


void CSutherlandHodgmanDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CSutherlandHodgmanDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_startPoint = point;
	m_endPoint = point;
	m_rBtndown = true;
	SetCapture();

	CDialogEx::OnRButtonDown(nFlags, point);
}


void CSutherlandHodgmanDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
	{
		ReleaseCapture();
	}
	
	m_rBtndown = false;
	//Invalidate(FALSE);

	CDialogEx::OnRButtonUp(nFlags, point);
}


void CSutherlandHodgmanDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_rBtndown)
	{
		m_endPoint = point;
		Invalidate(FALSE);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL CSutherlandHodgmanDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}
