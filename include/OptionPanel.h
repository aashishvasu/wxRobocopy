#ifndef OPTIONPANEL_H
#define OPTIONPANEL_H

#include <wx/wx.h>

class rcLogArgs;
class rcCpuArg;
class rcFlagArgs;
class rcCopyArg;
class rcDirArg;

// Events
wxDECLARE_EVENT(rcEVT_OPTIONS_UPDATED, wxCommandEvent);

class OptionPanel : public wxPanel
{
public:
	OptionPanel(wxWindow* parent);
	~OptionPanel() override;

	wxString GetOptions() const;

private:
	// Events
	void BindEvents();
	void SendEvent();
	void OnOptionsChanged(wxCommandEvent& e);

	rcCopyArg* copyChoice;
	rcDirArg* dirChoice;
	rcFlagArgs* flagsChoice;
	rcLogArgs* logChoice;
	rcCpuArg* coreChoice;
};

#endif // OPTIONPANEL_H
