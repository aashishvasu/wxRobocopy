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

	// Robocopy
	void GenerateRobocopyCmd();

	// Vars
	// File pickers
	wxDirPickerCtrl* srcDirPicker;
	wxDirPickerCtrl* dstDirPicker;

	// Panels
	OptionPanel* optPanel;

	// Robocopy Text
	wxTextCtrl* rcpCommandText;
};

#endif // MAINFRAME_H