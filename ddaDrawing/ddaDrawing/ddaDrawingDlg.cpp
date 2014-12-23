
// ddaDrawingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ddaDrawing.h"
#include "ddaDrawingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CddaDrawingDlg �Ի���

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


// CddaDrawingDlg ��Ϣ�������

BOOL CddaDrawingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_NORMAL);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CddaDrawingDlg::OnPaint()
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

		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CddaDrawingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CddaDrawingDlg::OnBnClickedButtonGrid()
{
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

//DDA�㷨
//�Ȼ�ȡ���꣬�������б�������Ϊ����ֵС��1�ʹ���1����
//ÿ�����ַ�Ϊ����0��С�ڵ���0�������
void CddaDrawingDlg::OnBnClickedButtonDda()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	bool test = getCoordinate();                              //��ȡ���꣬����ֵ��ʾ�����Ƿ�Ϸ�
	if (!test)
	{
		MessageBox(_T("�������"));
	}
	else
	{
		drawPixel(startX, startY, 1);
		drawPixel(endX, endY, 1);
		int nextX = startX, nextY = startY;
		double tmp;
		double k = (double)(endY - startY) / (endX - startX);

		//��Ϊk���ڵ���1��С��1���������
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
				//�ж�ֱ��б��Ϊ��orΪ��
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

//Bresenham�㷨����
//��Ϊ���������б��k<-1��-1<=k<0��0<=k<=1�Լ�k>1�������
void CddaDrawingDlg::OnBnClickedButtonBresenham()
{
	bool test = getCoordinate();                              //��ȡ����
	if (!test)
	{
		MessageBox(_T("�������"));
	}
	else
	{
		drawPixel(startX, startY, 2);
		drawPixel(endX, endY, 2);
		double k = (double)(endY - startY) / (endX - startX);

		if (k >= 0)
		{
			if (k <= 1)     //0<=k<=1�����
			{
				if (startX - endX > 0){ exchange(); }					//��������x��������յ㣬��������֤�ӽϵ͵����

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
						yk1 = yk + 1;							//��ʱ��P��k+1��>0��k>0����Y��k+1��=Yk+1
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
			else    //k>1�������Ӧ��y��Ϊ��׼����,��y++
			{
				if (startY - endY > 0){ exchange(); }					//��������y��������յ㣬��������֤�ӽϵ͵����

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
						xk1 = xk + 1;									//��ʱ��k>1��P(k+1)>0����X(k+1)=Xk+1
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
		else        //k<0
		{
			if (k >= -1)				//-1<=k<0
			{
				if (startX - endX > 0){ exchange(); }					//��������x��������յ㣬��������֤�ӽϵ͵����
				int dy = -(endY - startY);								//��ʱk<0��dyӦ��ȡ���෴��
				int dx = -(endX - startX);								//�� - �ŵ�����ͬ��
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
			else      //k<-1
			{
				if (startY - endY > 0){ exchange(); }					//��������y��������յ㣬��������֤�ӽϵ͵����

				int dy = -(endY - startY);								//k<0����Ӧ��ȡ�෴��
				int dx = -(endX - startX);								//ͬ��
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

//�ӱ༭���л�ȡ�����յ�����꣬����ֵΪbool�ͣ���ʾ����������Ƿ�Ϸ�
bool CddaDrawingDlg::getCoordinate()
{
	startX = GetDlgItemInt(IDC_EDIT_startX, NULL, TRUE);
	startY = GetDlgItemInt(IDC_EDIT_startY, NULL, TRUE);                 
	endX = GetDlgItemInt(IDC_EDIT_endX, NULL, TRUE);
	endY = GetDlgItemInt(IDC_EDIT_endY, NULL, TRUE);						

	//�ж������Ƿ�Ϸ�
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


//����һ�������ء�
//�����ء�ʵ������һ���䳤Ϊ4�ķ���
//xΪ�����꣬yΪ�����꣬test��ʾ�����ַ�����1ΪDDA��2ΪBresenham�㷨
void CddaDrawingDlg::drawPixel(int x,int y, int test)
{
	CClientDC pdc(this);
	y = 149 - y;

	//ת������Ļ����ϵ
	POINT p1, p2;
	p1.x = x * 4 + 12;
	p1.y = y * 4 + 12;
	p2.x = p1.x + 4;
	p2.y = p1.y + 4;
	CRect rectangle(p1, p2);

	//1ΪDDA�㷨����ɫֵΪ��ɫ��2ΪBresenham�㷨����ɫֵΪ��ɫ
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

//��������
//Ϊ��ȷ��������������ʱ�ӽϵ͵ĵ����
void CddaDrawingDlg::exchange()
{
	int tmp = startX;
	startX = endX;
	endX = tmp;

	tmp = startY;
	startY = endY;
	endY = tmp;
}
