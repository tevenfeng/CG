
// ddaDrawingDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CddaDrawingDlg �Ի���
class CddaDrawingDlg : public CDialogEx
{
// ����
public:
	CddaDrawingDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DDADRAWING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton button_Grid;
	afx_msg void OnBnClickedButtonGrid();
	afx_msg void OnBnClickedButtonDda();
	afx_msg void OnBnClickedButtonBresenham();
	afx_msg bool getCoordinate();
	afx_msg void drawPixel(int x, int y, int test);
	afx_msg void exchange();
};
