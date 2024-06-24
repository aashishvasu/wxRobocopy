#ifndef OPTIONPANEL_H
#define OPTIONPANEL_H

#include <wx/wx.h>

// Events
wxDECLARE_EVENT(rcEVT_OPTIONS_UPDATED, wxCommandEvent);

class wxDynStringHashMap;

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

	// Command strings
	wxString GetCopyArg() const;
	wxString GetFlagArgs() const;
	wxString GetCoreArg() const;
	void AppendArg(wxString& cmdStr, const wxString& arg) const;

	
	wxDynStringHashMap* copyOptions;
	wxDynStringHashMap* flagOptions;

	wxChoice* copyChoice;
	wxCheckListBox* flagsChoice;
	wxChoice* coreChoice;
};

#endif // OPTIONPANEL_H
