#include "RobocopyHandler.h"

wxDEFINE_EVENT(rcEVT_THREAD_STARTED, wxCommandEvent);
wxDEFINE_EVENT(rcEVT_THREAD_STOPPED, wxCommandEvent);

RobocopyHandler::RobocopyHandler(wxEvtHandler* parent, wxTextCtrl* outputCtrl): parent_(parent), process_(nullptr), outputCtrl_(outputCtrl), timer_(new wxTimer(this))
{
	Bind(wxEVT_TIMER, &RobocopyHandler::ReadOutput, this);
	Bind(wxEVT_END_PROCESS, &RobocopyHandler::OnTerminate, this);
}

RobocopyHandler::~RobocopyHandler()
{
	if (timer_->IsRunning())
	{
		timer_->Stop();
		
		delete timer_;
	}
	
	if (process_)
	{
		process_->Detach();
		delete process_;
		process_ = nullptr;
	}
}

void RobocopyHandler::Execute(const wxString& command)
{
	SendStart();
	
	process_ = new wxProcess(this);
	process_->Redirect();

	if(outputCtrl_)
		outputCtrl_->Clear();
	
	long pid = wxExecute(command, wxEXEC_ASYNC, process_);
	if (pid == 0)
	{
		wxLogError("Failed to execute command: %s", command);
		delete process_;
		process_ = nullptr;
		return;
	}
	
	timer_->Start(100);
}

void RobocopyHandler::Stop()
{
	if (process_)
	{
		wxKillError killError;
		wxKill(process_->GetPid(), wxSIGKILL, &killError);
		if (killError != wxKILL_OK)
		{
			wxLogError("Failed to terminate process: %d", killError);
		}
	}
}

void RobocopyHandler::SendStart()
{
	wxCommandEvent evtStart(rcEVT_THREAD_STARTED, wxID_ANY);
	wxPostEvent(parent_, evtStart);
}

void RobocopyHandler::SendStop()
{
	wxCommandEvent evtStop(rcEVT_THREAD_STOPPED);
	wxPostEvent(parent_, evtStop);
}

void RobocopyHandler::OnTerminate(wxProcessEvent& event)
{
	// Finally read output one more time
	ReadOutput_Internal();

	// Stop the reading
	SendStop();
	timer_->Stop();

	if (process_)
	{
		process_->Detach();
		delete process_;
		process_ = nullptr;
	}
}

void RobocopyHandler::ReadOutput(wxTimerEvent& e)
{
	ReadOutput_Internal();
}

void RobocopyHandler::ReadOutput_Internal()
{
	if (process_ && process_->IsInputAvailable())
	{
		wxInputStream* stream = process_->GetInputStream();
		if (stream && stream->CanRead())
		{
			wxString output;
			while (stream->CanRead())
			{
				char buffer[1024];
				stream->Read(buffer, sizeof(buffer) - 1);
				buffer[stream->LastRead()] = '\0';
				output += wxString::FromUTF8(buffer);

				if(outputCtrl_)
					outputCtrl_->AppendText(output + "\n");
			}
		}
	}
}
