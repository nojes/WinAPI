#include "Controller.h"

class AdditionalDialog : public Controller
{
	HWND hEdit;
	HWND hStatic;
	TCHAR *text;
public:
	AdditionalDialog();
	~AdditionalDialog();
	AdditionalDialog(TCHAR *text);

	BOOL Cls_OnInitDialog(HWND hDlg, HWND hDlgFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hDlg, int ctl_ID, HWND ctl_Handle, UINT codeNotify);
};
