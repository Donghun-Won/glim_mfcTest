
// mfcTestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "mfcTest.h"
#include "mfcTestDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <vector>
#include <cmath>
//#include <algorithm>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmfcTestDlg 대화 상자



CmfcTestDlg::CmfcTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTEST_DIALOG, pParent), m_centerX(0), m_centerY(0), m_circleRadius(10), m_circleColor(0x00)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_START_X, m_centerX);
	DDX_Text(pDX, IDC_EDIT_START_Y, m_centerY);
	DDX_Text(pDX, IDC_EDIT_END_X, m_endX);
	DDX_Text(pDX, IDC_EDIT_END_Y, m_endY);
}

BEGIN_MESSAGE_MAP(CmfcTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CmfcTestDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_DRAW, &CmfcTestDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CmfcTestDlg::OnBnClickedBtnAction)
END_MESSAGE_MAP()


// CmfcTestDlg 메시지 처리기

BOOL CmfcTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CmfcTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CmfcTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CmfcTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CmfcTestDlg::OnBnClickedBtnDraw()
{
	UpdateData(TRUE);

	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	if (!m_image.IsNull()) {
		m_image.Destroy();
	}

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);

	int radius = (rand() % 100) + 10;
	m_circleRadius = radius;

	if (m_centerX < 0) m_centerX = 0;
	if (m_centerX >= nWidth) m_centerX = nWidth - 1;
	if (m_centerY < 0) m_centerY = 0;
	if (m_centerY >= nHeight) m_centerY = nHeight - 1;

	for (int y = 0; y < nHeight; ++y) {
		for (int x = 0; x < nWidth; ++x) {
			if ((x - m_centerX) * (x - m_centerX) + (y - m_centerY) * (y - m_centerY) <= radius * radius) {
				fm[y * nPitch + x] = m_circleColor;
			}
		}
	}

	UpdateDisplay();
}

void CmfcTestDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

bool FindCircleCenterAndRadius(const CImage& image, int& centerX, int& centerY, int& radius)
{
	int nWidth = image.GetWidth();
	int nHeight = image.GetHeight();
	int nPitch = image.GetPitch();
	unsigned char* pBits = (unsigned char*)image.GetBits();

	std::vector<CPoint> boundaryPoints;

	for (int y = 0; y < nHeight; ++y)
	{
		for (int x = 0; x < nWidth; ++x)
		{
			if (pBits[y * nPitch + x] == 0)
			{
				boundaryPoints.push_back(CPoint(x, y));
			}
		}
	}

	if (boundaryPoints.empty())
	{
		return false;
	}

	int sumX = 0, sumY = 0;
	for (const auto& pt : boundaryPoints)
	{
		sumX += pt.x;
		sumY += pt.y;
	}

	centerX = sumX / boundaryPoints.size();
	centerY = sumY / boundaryPoints.size();

	int sumRadiusSquared = 0;
	for (const auto& pt : boundaryPoints)
	{
		int dx = pt.x - centerX;
		int dy = pt.y - centerY;
		sumRadiusSquared += dx * dx + dy * dy;
	}

	radius = static_cast<int>(std::sqrt(static_cast<double>(sumRadiusSquared) / boundaryPoints.size()));

	return true;
}

void CmfcTestDlg::OnBnClickedBtnOpen()
{
	CFileDialog dlg(TRUE, _T("bmp"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("Image Files (*.bmp;*.jpg;*.png)|*.bmp;*.jpg;*.png|All Files (*.*)|*.*||"));

	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();

		if (!m_image.IsNull())
		{
			m_image.Destroy();
		}

		HRESULT hr = m_image.Load(filePath);

		if (SUCCEEDED(hr))
		{
			int centerX, centerY, radius;
			if (FindCircleCenterAndRadius(m_image, centerX, centerY, radius))
			{
				m_centerX = centerX;
				m_centerY = centerY;
				m_circleRadius = radius;

				CClientDC dc(this);
				CDC memDC;
				CBitmap bitmap;
				CBitmap* pOldBitmap;

				memDC.CreateCompatibleDC(&dc);
				bitmap.CreateCompatibleBitmap(&dc, m_image.GetWidth(), m_image.GetHeight());
				pOldBitmap = memDC.SelectObject(&bitmap);

				m_image.Draw(memDC, 0, 0);

				CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
				memDC.SelectObject(&pen);

				memDC.MoveTo(centerX - 10, centerY - 10);
				memDC.LineTo(centerX + 10, centerY + 10);
				memDC.MoveTo(centerX - 10, centerY + 10);
				memDC.LineTo(centerX + 10, centerY - 10);

				dc.BitBlt(0, 0, m_image.GetWidth(), m_image.GetHeight(), &memDC, 0, 0, SRCCOPY);

				memDC.SelectObject(pOldBitmap);

				CString radiusText, coordinateText;
				radiusText.Format(_T("%d"), radius);
				coordinateText.Format(_T("(%d, %d)"), centerX, centerY);

				SetDlgItemText(IDC_STATIC_RADIUS, radiusText);

				SetDlgItemText(IDC_STATIC_COORDINATE, coordinateText);
			}
			else
			{
				AfxMessageBox(_T("원 찾기 실패!"));
			}
		}
		else
		{
			AfxMessageBox(_T("이미지 로드 실패!"));
		}
	}
}

bool CmfcTestDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		bRet = true;
	}

	return bRet;
}

void CmfcTestDlg::DrawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();

	for (int j = max(0, y); j < min(y + nRadius * 2, m_image.GetHeight()); j++) {
		for (int i = max(0, x); i < min(x + nRadius * 2, m_image.GetWidth()); i++) {
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j * nPitch + i] = nGray;
		}
	}
}

CString g_strFolderPath = _T(".\\Image\\");

int GetFileCountInDirectory(const std::wstring& directoryPath) {
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile((directoryPath + L"\\*").c_str(), &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		return 0;
	}

	int fileCount = 0;
	do {
		if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
			fileCount++;
		}
	} while (FindNextFile(hFind, &findFileData) != 0);

	FindClose(hFind);
	return fileCount;
}

void CmfcTestDlg::moveRect()
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);

	DrawCircle(fm, m_centerX - 51, m_centerY - 51, m_circleRadius, m_circleColor);

	UpdateDisplay();
}



void CmfcTestDlg::OnBnClickedBtnAction()
{
	UpdateData(TRUE);

	int steps = 100;
	int deltaX = (m_endX - m_centerX) / steps;
	int deltaY = (m_endY - m_centerY) / steps;

	CString fileBaseName = g_strFolderPath + _T("CircleImage_");

	if ((_waccess(g_strFolderPath, 0)) == -1)
		CreateDirectory(g_strFolderPath, NULL);

	int startIndex = GetFileCountInDirectory(g_strFolderPath.GetString()) + 1;

	for (int i = 0; i < steps; i++) {
		moveRect();

		CString fileName;
		fileName.Format(_T("%s%d.bmp"), fileBaseName, startIndex + i);

		m_image.Save(fileName);

		m_centerX += deltaX;
		m_centerY += deltaY;

		Sleep(10);
	}
}
