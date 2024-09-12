
// mfcTestDlg.h: 헤더 파일
//

#pragma once


// CmfcTestDlg 대화 상자
class CmfcTestDlg : public CDialogEx
{
// 생성입니다.

private:
	CImage m_image;
	int m_centerX;
	int m_centerY;
	int m_circleRadius;
	unsigned char m_circleColor;
	int m_endX;
	int m_endY;

public:
	CmfcTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpen();

	void UpdateDisplay();
	void moveRect();
	void DrawCircle(unsigned char* fm, int i, int j, int nRadius, int nGray);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);

	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
};
