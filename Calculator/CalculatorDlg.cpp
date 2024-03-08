#include "stdafx.h"
#include <string>
#include <sstream>
#include "CalculatorApp.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCalculatorDlg dialog

CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, m_output(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CCalculatorDlg::~CCalculatorDlg()
{
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_output);
	DDX_Control(pDX, IDC_EDIT_RESULT, editResult);
	DDX_Control(pDX, IDC_BUTTON_0, button0);
	DDX_Control(pDX, IDC_BUTTON_1, button1);
	DDX_Control(pDX, IDC_BUTTON_2, button2);
	DDX_Control(pDX, IDC_BUTTON_3, button3);
	DDX_Control(pDX, IDC_BUTTON_4, button4);
	DDX_Control(pDX, IDC_BUTTON_5, button5);
	DDX_Control(pDX, IDC_BUTTON_6, button6);
	DDX_Control(pDX, IDC_BUTTON_7, button7);
	DDX_Control(pDX, IDC_BUTTON_8, button8);
	DDX_Control(pDX, IDC_BUTTON_9, button9);
	DDX_Control(pDX, IDC_BUTTON_10, button10);
	DDX_Control(pDX, IDC_BUTTON_PLUS, buttonPlus);
	DDX_Control(pDX, IDC_BUTTON_EQUALS, buttonEquals);
	DDX_Control(pDX, IDC_BUTTON_C, buttonC);
	DDX_Control(pDX, IDC_BUTTON_MINUS, buttonMinus);
	DDX_Control(pDX, IDC_BUTTON_MULTIPLY, buttonMultiply);
	DDX_Control(pDX, IDC_BUTTON_DIVIDE, buttonDivide);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_1, &CCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CCalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_0, &CCalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_4, &CCalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_10, &CCalculatorDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CCalculatorDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_EQUALS, &CCalculatorDlg::OnBnClickedButtonEquals)
	ON_BN_CLICKED(IDC_BUTTON_C, &CCalculatorDlg::OnBnClickedButtonC)
	ON_BN_CLICKED(IDC_BUTTON_DIVIDE, &CCalculatorDlg::OnBnClickedButtonDivide)
	ON_BN_CLICKED(IDC_BUTTON_MULTIPLY, &CCalculatorDlg::OnBnClickedButtonMultiply)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CCalculatorDlg::OnBnClickedButtonMinus)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_font.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 
		0, 0, 0, 0, _T("Microsoft Sans Serif"));
	editResult.SetFont(&m_font);
	button0.SetFont(&m_font);
	button1.SetFont(&m_font);
	button2.SetFont(&m_font);
	button3.SetFont(&m_font);
	button4.SetFont(&m_font);
	button5.SetFont(&m_font);
	button6.SetFont(&m_font);
	button7.SetFont(&m_font);
	button8.SetFont(&m_font);
	button9.SetFont(&m_font);
	buttonPlus.SetFont(&m_font);
	buttonC.SetFont(&m_font);
	buttonMinus.SetFont(&m_font);
	buttonMultiply.SetFont(&m_font);
	buttonDivide.SetFont(&m_font);
	buttonEquals.SetFont(&m_font);
	reset();

	return TRUE;  // return TRUE  unless you set the focus to a control 
}

void CCalculatorDlg::reset()
{
	m_calculator.reset();
	m_errorInput = false;
	m_firstDigitEntered = FALSE;
	resetOutput();
	UpdateData(FALSE);
}

void CCalculatorDlg::resetOutput()
{
	m_output = m_outputResetString;
}

void CCalculatorDlg::addDigit(char digit)
{
	if (m_errorInput)
		return;

	UpdateData();

	if (m_calculator.isOperation(m_calculator.getLastInput().actionType)  &&
		!m_firstDigitEntered)
	{
		// (3 + 4 x 6 = input: 2 => 2)
		m_output = digit;
	}
	else
	{
		if (m_output == m_outputResetString && digit == '0')
			return; //if zero is the first digit typed, ignore it
		else if (m_output == m_outputResetString)
			m_output = digit; // (0 : input: 6 => 6) first digit
		else
			m_output += digit; // (45 : input: 9 => 459)
	}
	// a valid digit was added
	m_firstDigitEntered = TRUE;
	UpdateData(FALSE);
}

void CCalculatorDlg::OnBnClickedButton0()
{
	addDigit('0');
}

void CCalculatorDlg::OnBnClickedButton1()
{
	addDigit('1');
}

void CCalculatorDlg::OnBnClickedButton2()
{
	addDigit('2');
}

void CCalculatorDlg::OnBnClickedButton3()
{
	addDigit('3');
}

void CCalculatorDlg::OnBnClickedButton4()
{
	addDigit('4');
}

void CCalculatorDlg::OnBnClickedButton5()
{
	addDigit('5');
}

void CCalculatorDlg::OnBnClickedButton6()
{
	addDigit('6');
}

void CCalculatorDlg::OnBnClickedButton7()
{
	addDigit('7');
}

void CCalculatorDlg::OnBnClickedButton8()
{
	addDigit('8');
}

void CCalculatorDlg::OnBnClickedButton9()
{
	addDigit('9');
}

void CCalculatorDlg::OnBnClickedButton10()
{
	addDigit('.');
}


// if handleNumber == true then first handles the number entered in the output
// window before doing the operation.
void CCalculatorDlg::doOperation(Calculator::ActionType operation, bool handleNumber)
{
	if (m_errorInput)
		return;

	UpdateData();
	Calculator::Action input;
	if (handleNumber)
	{
		// first add the last entered number
		input.actionType = Calculator::ActionType::Number;
		input.value = _wtof(m_output);
		m_calculator.addInput(input);
	}
	// then add the (last) operation
	input.actionType = operation;
	m_errorInput = false;
	try
	{
		// After a (valid) operation we always print a current result if
		// there is something to print currently. This is the case with all the current 
		// operations. Later on if there is different kind of operation which does not
		// behave like this, then a new code is needed here for that operation.
		if (m_calculator.addInput(input))
		{
			// The only situation we will not print the total result here is if both term and 
			// expression have values currently (are "in use"). For example: "3 + 5 /", 
			// => operation == Divide and we would not like to print the total result of
			// this yet becouse that would be 3; we want to wait until the term part (5 / ...)
			// is finished, then we will print the total 3 + ... .
			if (!m_calculator.hasLeftTermValue() || !m_calculator.hasLeftExpressionValue())
			{
				// print the current total value
				std::stringstream ss;
				ss << m_calculator.getCurrentResult();
				std::string curResult = ss.str();

				m_output = "";
				m_output += curResult.c_str();
				UpdateData(FALSE);
			}
		}
		else // this should never happen; coming here means possible an error in the code
			AfxMessageBox(_T("Error: An unknown operation.")); 
	}
	catch (std::exception& e)
	{
		// note: the user can only continue after "divided by zero" error
		// by pressing "C"/reset.
		m_output = e.what();
		m_firstDigitEntered = FALSE;
		m_errorInput = true;
	}
	/*if (operation == Calculator::ActionType::Equals)
	{
		if (m_errorInput)
			m_historyText += " ";
		m_historyText += m_output;
	}*/
	UpdateData(FALSE);
	m_firstDigitEntered = FALSE;
}

void CCalculatorDlg::OnBnClickedButtonPlus()
{
	doOperation(Calculator::ActionType::Plus);
}

void CCalculatorDlg::OnBnClickedButtonEquals()
{
	doOperation(Calculator::ActionType::Equals);
}

void CCalculatorDlg::OnBnClickedButtonC()
{
	reset();
}

void CCalculatorDlg::OnBnClickedButtonDivide()
{
	doOperation(Calculator::ActionType::Divide);
}

void CCalculatorDlg::OnBnClickedButtonMultiply()
{
	doOperation(Calculator::ActionType::Multiply);
}

void CCalculatorDlg::OnBnClickedButtonMinus()
{
	doOperation(Calculator::ActionType::Minus);
}


