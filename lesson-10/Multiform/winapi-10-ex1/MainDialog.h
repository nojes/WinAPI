#include "Controller.h"

class MainDialog : public Controller
{
	HWND hEdit1;
	HWND hButton1;
public:
	MainDialog();
	~MainDialog();
	
	BOOL Cls_OnInitDialog(HWND hDlg, HWND hDlgFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hDlg, int ctl_ID, HWND ctl_Handle, UINT codeNotify);
};