
// Sutherland-HodgmanDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sutherland-Hodgman.h"
#include "Sutherland-HodgmanDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSutherlandHodgmanDlg �Ի���

bool m_rBtndown;																			//�����ж�����Ҽ��Ƿ���
bool m_lBtndbclk;																			//�����жϾ����Ƿ�պ�
CPoint m_startPoint;
CPoint m_endPoint;
CPoint pointArray[100];																		//�洢����εĵ�
int pointCount = 0;																			//����ε�ļ���


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
END_MESSAGE_MAP()


// CSutherlandHodgmanDlg ��Ϣ�������

BOOL CSutherlandHodgmanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_NORMAL);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_rBtndown = false;
	m_lBtndbclk = false;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSutherlandHodgmanDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSutherlandHodgmanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//���������£���ȡ��ȡһ������εĵ㣬����������
//����ļ�������������ͬʱ����OnPaint����������
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
		MessageBox(_T("�����ѱպϣ�"));
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

//�պϰ�ť��ʹ�þ��αպ�
void CSutherlandHodgmanDlg::OnBnClickedButtonrect()
{
	m_lBtndbclk = true;
	OnPaint();
	Invalidate(FALSE);
}

//����Ҽ���ס����ʼ��׽����ƶ��Ķ���
void CSutherlandHodgmanDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_startPoint = point;
	m_endPoint = point;
	m_rBtndown = true;
	SetCapture();

	CDialogEx::OnRButtonDown(nFlags, point);
}

//����Ҽ��ɿ����ͷ�����ƶ������Ĳ�׽
void CSutherlandHodgmanDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
	{
		ReleaseCapture();
	}
	m_rBtndown = false;

	CDialogEx::OnRButtonUp(nFlags, point);
}

//��ס�Ҽ��ƶ������в��ϸ���m_endPoint��ͬʱ���仭����
void CSutherlandHodgmanDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_rBtndown)
	{
		m_endPoint = point;
		Invalidate(FALSE);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

//ˢ�±���
BOOL CSutherlandHodgmanDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}

//���ð�ť
void CSutherlandHodgmanDlg::OnBnClickedButtonreset()
{
	m_lBtndbclk = false;
	m_rBtndown = false;
	pointCount = 0;
	Invalidate(FALSE);
}
