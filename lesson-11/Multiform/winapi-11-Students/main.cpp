#include "Controller.h"

/**
 *	WinAPI
 *	Lesson #11
 *	"Students Accounting System"
 */

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	Controller c;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), nullptr, Controller::DlgProc);
}