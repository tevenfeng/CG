
// Sutherland-Hodgman.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSutherlandHodgmanApp: 
// �йش����ʵ�֣������ Sutherland-Hodgman.cpp
//

class CSutherlandHodgmanApp : public CWinApp
{
public:
	CSutherlandHodgmanApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSutherlandHodgmanApp theApp;