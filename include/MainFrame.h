#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/filepicker.h>

class RobocopyHandler;
class OptionPanel;

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);

private:
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	// Events
	void BindEvents();
	void OnDirPicked(wxFileDirPickerEvent& e);
	void OnOptionsChanged(wxCommandEvent& e);
	
	void OnRcpCommandCopyClicked(wxCommandEvent& e);
	void OnRcpRunBtnClicked(wxCommandEvent& e);
	void OnRcpDryRunClicked(wxCommandEvent& e);
	void OnRcpStopBtnClicked(wxCommandEvent& e);
	
	void OnRcpThreadStarted(wxCommandEvent& e);
	void OnRcpThreadStopped(wxCommandEvent& e);

	// Robocopy
	wxString GenerateRobocopyCmd() const;

	// Vars
	// File pickers
	wxDirPickerCtrl* srcDirPicker;
	wxDirPickerCtrl* dstDirPicker;

	// Buttons
	wxBitmapButton* clipBtn;

	// Panels
	OptionPanel* optPanel;

	// Robocopy
	wxTextCtrl* rcpCommandText;
	wxTextCtrl* rcpOutput;
	wxButton* rcpRunBtn;
	wxButton* rcpDryRunBtn;
	wxButton* rcpStopBtn;
	RobocopyHandler* rcpHandler;
};

#endif // MAINFRAME_H