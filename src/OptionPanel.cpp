#include "OptionPanel.h"

#include "wxPanels/rcCpuArg.h"
#include "wxPanels/rcOptionChoice.h"
#include "wxPanels/rcOptionChecklist.h"
#include "utils/rcUtils.h"
#include "data/wxDynStringHashMap.h"

wxDEFINE_EVENT(rcEVT_OPTIONS_UPDATED, wxCommandEvent);

OptionPanel::OptionPanel(wxWindow* parent) : wxPanel(parent)
{
	// Type of copying to be done
	copyChoice = new rcOptionChoice(
		this,
		"Copy Type",
		new wxDynStringHashMap(
			{"Normal Copy", "Sync/Mirror", "Move"},
			{"", "/MIR", "/MOVE"}
		)
	);

	// What files to copy
	dirChoice = new rcOptionChoice(
		this,
		"Filter",
		new wxDynStringHashMap(
			{"Copy non empty subfolders", "Copy everything", "Copy only files"},
			{"/S", "/E", ""}
		)
	);

	// Flags to be chosen
	flagsChoice = new rcOptionChecklist(
		this,
		"Flags",
		new wxDynStringHashMap(
			{"Restartable", "Backup", "Restartable with backup fallback"},
			{"/Z", "/B", "/ZB"}
		)
	);

	// Number of CPU thread choice
	coreChoice = new rcCpuArg(this, "CPU Threads");

	// What type of logging to filter
	logChoice = new rcOptionChecklist(
		this,
		"Logging",
		new wxDynStringHashMap(
			{"No File List", "No Folder List", "No Progress", "No File Size", "No File Class"},
			{"/NFL", "/NDL", "/NP", "/NS", "/NC"}
		)
	);

	// sizers
	wxFlexGridSizer* gSizer = new wxFlexGridSizer(1, 5, wxDefaultSize);
	gSizer->AddGrowableCol(2, 1);
	gSizer->Add(copyChoice, 1, wxALL | wxEXPAND, 5);
	gSizer->Add(dirChoice, 1, wxALL | wxEXPAND, 5);
	gSizer->Add(flagsChoice, 1, wxALL | wxEXPAND, 5);
	gSizer->Add(coreChoice, 1, wxALL | wxEXPAND, 5);
	gSizer->Add(logChoice, 1, wxALL | wxEXPAND, 5);

	SetSizer(gSizer);

	BindEvents();
}

OptionPanel::~OptionPanel() { }

wxString OptionPanel::GetOptions() const
{
	wxString cmdStr;
	Application::AppendArg(cmdStr, copyChoice->GetArgs());
	Application::AppendArg(cmdStr, dirChoice->GetArgs());
	Application::AppendArg(cmdStr, flagsChoice->GetArgs());
	Application::AppendArg(cmdStr, coreChoice->GetArgs());
	Application::AppendArg(cmdStr, logChoice->GetArgs());
	
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
