#ifndef OPTIONPANEL_H
#define OPTIONPANEL_H

#include <wx/wx.h>

class rcCpuArg;
class rcOptionChecklist;
class rcOptionChoice;

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

	rcOptionChoice* copyChoice;
	rcOptionChoice* dirChoice;
	rcOptionChecklist* flagsChoice;
	rcOptionChecklist* logChoice;
	rcCpuArg* coreChoice;
};

#endif // OPTIONPANEL_H
