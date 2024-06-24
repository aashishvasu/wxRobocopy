#ifndef ROBOCOPYHANDLER_H
#define ROBOCOPYHANDLER_H

#include <wx/wx.h>
#include <wx/process.h>

wxDECLARE_EVENT(rcEVT_THREAD_STARTED, wxCommandEvent);
wxDECLARE_EVENT(rcEVT_THREAD_STOPPED, wxCommandEvent);


class RobocopyHandler : public wxEvtHandler
{
public:
	RobocopyHandler(wxEvtHandler* parent, wxTextCtrl* outputCtrl);
	~RobocopyHandler();
	
	void Execute(const wxString& command);
	void Stop();

private:
	void SendStart();
	void SendStop();
	void OnTerminate(wxProcessEvent& event);
	void ReadOutput(wxTimerEvent& event);
	void ReadOutput_Internal();
	
	wxEvtHandler* parent_;
	wxProcess* process_;
	wxTextCtrl* outputCtrl_;
	wxTimer* timer_;
};

#endif // ROBOCOPYHANDLER_H