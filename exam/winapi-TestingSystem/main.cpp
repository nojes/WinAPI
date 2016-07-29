#include "RegisterController.h"

/**
 *	WinAPI
 *	Exam Project
 *	"Simple Testing System"
 */

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	RegisterController register_c;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_REG), NULL, RegisterController::DlgProc);
}