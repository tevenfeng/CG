
// ddaDrawingDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CddaDrawingDlg 对话框
class CddaDrawingDlg : public CDialogEx
{
// 构造
public:
	CddaDrawingDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DDADRAWING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
