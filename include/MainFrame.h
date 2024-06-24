#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/filepicker.h>

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
	void OnSrcDirPicked(wxFileDirPickerEvent& e);
	void OnDstDirPicked(wxFileDirPickerEvent& e);
	void OnOptionsChanged(wxCommandEvent& e);
	void OnRcpCommandCopyClicked(wxCommandEvent& e);

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

	// Robocopy Text
	wxTextCtrl* rcpCommandText;
};

#endif // MAINFRAME_H