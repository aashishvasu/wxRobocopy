#ifndef WXOPTIONBASE_H
#define WXOPTIONBASE_H

#include <wx/panel.h>

wxDECLARE_EVENT(rcEVT_ARG_UPDATED, wxCommandEvent);

class wxStaticBoxSizer;

class wxOptionBase : public wxPanel
{
public:
	wxOptionBase(wxWindow* parent, const wxString& label);
	
	virtual wxString GetArgs() const = 0;
	void OnArgsUpdated(wxCommandEvent& e);

protected:
	// Events
	virtual void BindEvents() = 0;

	// Utils
	static void AppendArg(wxString& cmdStr, const wxString& arg);
	
	wxStaticBoxSizer* sizer_;

private:
	wxString label_;
};

#endif // WXOPTIONBASE_H



