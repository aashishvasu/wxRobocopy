#include "OptionPanel.h"

#include "wxPanels/rcCopyArg.h"
#include "wxPanels/rcFlagArgs.h"
#include "wxPanels/rcCpuArg.h"
#include "utils/rcUtils.h"

wxDEFINE_EVENT(rcEVT_OPTIONS_UPDATED, wxCommandEvent);

OptionPanel::OptionPanel(wxWindow* parent) : wxPanel(parent)
{
	// Type of copying to be done
	copyChoice = new rcCopyArg(this, "Copy Type");

	// Flags to be chosen
	flagsChoice = new rcFlagArgs(this, "Flags");

	// Number of CPU thread choice
	coreChoice = new rcCpuArg(this, "CPU Threads");

	// sizers
	wxFlexGridSizer* gSizer = new wxFlexGridSizer(1, 3, wxDefaultSize);
	gSizer->AddGrowableCol(1, 1);
	gSizer->Add(copyChoice, 1, wxALL | wxEXPAND, 5);
	gSizer->Add(flagsChoice, 1, wxALL | wxEXPAND, 5);
	gSizer->Add(coreChoice, 1, wxALL | wxEXPAND, 5);

	SetSizer(gSizer);

	BindEvents();
}

OptionPanel::~OptionPanel() { }

wxString OptionPanel::GetOptions() const
{
	wxString cmdStr;
	Application::AppendArg(cmdStr, copyChoice->GetArgs());
	Application::AppendArg(cmdStr, flagsChoice->GetArgs());
	Application::AppendArg(cmdStr, coreChoice->GetArgs());
	
	return cmdStr;
}

void OptionPanel::BindEvents()
{
	Bind(rcEVT_ARG_UPDATED, &OptionPanel::OnOptionsChanged, this);
}

void OptionPanel::SendEvent()
{
	wxCommandEvent e(rcEVT_OPTIONS_UPDATED, GetId());
	e.SetEventObject(this);

	ProcessWindowEvent(e);
}

void OptionPanel::OnOptionsChanged(wxCommandEvent& e)
{
	SendEvent();
}
