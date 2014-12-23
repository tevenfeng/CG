
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
CPoint m_startPoint;																		//���ƴ��ڹ��������ϽǶ���
CPoint m_endPoint;																			//���ƴ��ڹ��������½Ƕ���
CPoint rect_topleft, rect_topright, rect_btmleft, rect_btmright;							//�����ĸ�����
CPoint pointArray[100],cuttedPoint1[100],cuttedPoint2[100],cuttedPoint3[100],cuttedPoint4[100];								//�洢����εĵ�
int pointCount = 0;																			//����ε�ļ���
int cuttedNum = 0;																			//�ü��������Ѵ��ڵĵ������

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

	rect_topleft = CPoint(m_startPoint.x, m_startPoint.y);
	rect_topright = CPoint(m_endPoint.x, m_startPoint.y);
	rect_btmleft = CPoint(m_startPoint.x, m_endPoint.y);
	rect_btmright = CPoint(m_endPoint.x, m_endPoint.y);

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

//�ü��㷨
void CSutherlandHodgmanDlg::OnBnClickedButtoncut()
{
	POINT p1, p2, p3, p4, p;

	//��ü�
	p3 = rect_topleft;
	p4 = rect_btmleft;
	cuttedNum = 0;
	for (int i = 0; i < pointCount; i++)
	{
		//������ʼ�߶�
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

		//�ж��Ƿ�ֱ
		if (p1.x == p2.x)
		{
			//�ѽ�������������
			if (p1.x>p3.x)
				cuttedPoint1[cuttedNum++] = p2;
		}
		else
		{
			//����ֱ�Ϳ���ͨ��б��
			//�����ӳ��߽���
			int x = p3.x;
			int y = p2.y - (double)(p2.y - p1.y)*(double)(p2.x - x) / (double)(p2.x - p1.x);

			//�н���
			if (y > min(p1.y, p2.y) && y < max(p1.y, p2.y))
			{
				p.x = x;
				p.y = y;
				cuttedPoint1[cuttedNum++] = p;
			}

			//�������ڻ��ߴ��ڵ���
			if (p2.x > p3.x)
			{
				cuttedPoint1[cuttedNum++] = p2;
			}
		}
	}

	//�Ҳü�
	p3 = rect_topright;
	p4 = rect_btmright;
	pointCount = cuttedNum;
	cuttedNum = 0;
	for (int i = 0; i < pointCount; i++)
	{
		//�����߶���ʼ��
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
		//�жϴ�ֱ
		if (p1.x == p2.x)
		{
			if (p1.x<p3.x)
				cuttedPoint2[cuttedNum++] = p2;
		}
		else
		{
			int x = p3.x;
			int y = p2.y - (double)(p2.y - p1.y)*(double)(p2.x - x) / (double)(p2.x - p1.x);
			//�н���
			if (y > min(p1.y, p2.y) && y < max(p1.y, p2.y))
			{
				p.x = x;
				p.y = y;
				cuttedPoint2[cuttedNum++] = p;
			}
			if (p2.x < p3.x)//�������ڻ���ڵ���
			{
				cuttedPoint2[cuttedNum++] = p2;
			}
		}
	}

	//�²ü�
	p3 = rect_btmleft;
	p4 = rect_btmright;
	pointCount = cuttedNum;
	cuttedNum = 0;
	for (int i = 0; i < pointCount; i++)
	{
		//�����߶���ʼ��
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

		//�ж�ƽ��
		if (p1.y == p2.y)//���ڵ���
		{
			if (p1.y<p3.y)
				cuttedPoint3[cuttedNum++] = p2;
		}
		else
		{
			if (p1.x == p2.x)//��ֱֱ�Ӽ��㽻��
			{
				if (p3.y>min(p1.y, p2.y) && p3.y<max(p1.y, p2.y))//��������
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

			//��������
			if (p2.y < p3.y)
			{
				cuttedPoint3[cuttedNum++] = p2;
			}
		}
	}

	//�ϲü�
	p3 = rect_topleft;
	p4 = rect_topright;
	pointCount = cuttedNum;
	cuttedNum = 0;
	for (int i = 0; i < pointCount; i++)
	{
		//�����߶���ʼ��
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

		//�ж�ƽ��
		if (p1.y == p2.y)
		{
			//���ڵ���
			if (p1.y>p3.y)
				cuttedPoint4[cuttedNum++] = p2;
		}
		else
		{
			if (p1.x == p2.x)
			{
				//��ֱֱ�Ӽ��㽻��
				if (p3.y>min(p1.y, p2.y) && p3.y<max(p1.y, p2.y))
				{
					//��������
					p.x = p1.x;
					p.y = p3.y;
					cuttedPoint4[cuttedNum++] = p;
				}
			}
			else
			{
				//�󽻵�
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
				//��������
				cuttedPoint4[cuttedNum++] = p2;
			}
		}
	}

	//��ʼ����
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
