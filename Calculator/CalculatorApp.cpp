
// Calculator.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CalculatorApp.h"
#include "CalculatorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCalculatorApp

BEGIN_MESSAGE_MAP(CCalculatorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCalculatorApp construction

CCalculatorApp::CCalculatorApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}


// The one and only CCalculatorApp object

CCalculatorApp theApp;


// CCalculatorApp initialization

BOOL CCalculatorApp::InitInstance()
{

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	//SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	HKEY hKey;
	const wchar_t* subkey = L"Software\\CalculatorApplication";
	const wchar_t* valueName = L"UseCButton";
	DWORD valueData = 0; // Default to CButton style

	// Open or create the key
	LONG result = RegCreateKeyEx(HKEY_CURRENT_USER, subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
	if (result == ERROR_SUCCESS)
	{
		// Set the registry value
		result = RegSetValueEx(hKey, valueName, 0, REG_DWORD, (BYTE*)&valueData, sizeof(DWORD));
		if (result != ERROR_SUCCESS)
		{
			// Failed to set registry value
		}

		// Close the key
		RegCloseKey(hKey);
	}

	CCalculatorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{

	}
	else if (nResponse == IDCANCEL)
	{
	
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit
	return FALSE;
}

