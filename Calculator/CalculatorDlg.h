#pragma once

#ifdef Calculator_Lib
#define DECLSPEC __declspec(dllexport)
#else 
#define DECLSPEC __declspec(dllimport)
#endif

#include "afxwin.h"
#include <memory>
#include "Calculator.h"

class CCalculatorDlg : public CDialogEx
{
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CCalculatorDlg();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	//afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//afx_msg void OnPaint();
	//afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonEquals();
	afx_msg void OnBnClickedButtonC();
	afx_msg void OnBnClickedButtonDivide();
	afx_msg void OnBnClickedButtonMultiply();
	afx_msg void OnBnClickedButtonMinus();
private:
	bool m_errorInput = false;
	const CString m_outputResetString{"0"};
	void resetOutput();
	void reset();
	void addDigit(char digit);
	void doOperation(Calculator::ActionType operation, bool handleNumber=true);

	Calculator m_calculator;
	CString m_output;
	CFont   m_font;
	BOOL    m_firstDigitEntered = FALSE;
	CEdit   editResult;
	CButton button0;
	CButton button1;
	CButton button2;
	CButton button3;
	CButton button4;
	CButton button5;
	CButton button6;
	CButton button7;
	CButton button8;
	CButton button9;
	CButton button10;
	CButton buttonPlus;
	CButton buttonEquals;
	CButton buttonC;
	CButton buttonMinus;
	CButton buttonMultiply;
	CButton buttonDivide;
};
