#include "OptionPanel.h"

#include "utils/CoreCount.h"
#include "data/wxDynStringHashMap.h"

wxDEFINE_EVENT(rcEVT_OPTIONS_UPDATED, wxCommandEvent);

OptionPanel::OptionPanel(wxWindow* parent) : wxPanel(parent)
{
	// Type of copying to be done
	copyOptions = new wxDynStringHashMap({"Normal Copy", "Sync/Mirror", "Move"}, {"", "/MIR", "/MOVE"});
	copyChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, copyOptions->keys());
	copyChoice->SetSelection(0);

	// Flags to be chosen
	flagOptions = new wxDynStringHashMap({"Restartable", "Backup", "Restartable with backup fallback"}, {"/Z", "/B", "/ZB"});
	flagsChoice = new wxCheckListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, flagOptions->keys());

	// Number of CPU thread choice
	const int numCores = wxMin(wxMax(1, GetCPUCoreCount()), 128);
	wxArrayString coreChoices;
	for (int i = 1; i <= numCores; ++i)
	{
		coreChoices.Add(wxString::Format("%d", i));
	}
	coreChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, coreChoices);
	coreChoice->SetSelection(0);

	// sizers
	wxStaticBoxSizer* copySizer = new wxStaticBoxSizer(wxHORIZONTAL, this, "Copy Type");
	copySizer->Add(copyChoice, 0, wxALL | wxEXPAND, 5);

	wxStaticBoxSizer* flagSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, "Flags");
	flagSizer->Add(flagsChoice, 0, wxALL | wxEXPAND, 5);

	wxStaticBoxSizer* cpuSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, "CPU Threads");
	cpuSizer->Add(coreChoice, 0, wxALL | wxEXPAND, 5);

	wxFlexGridSizer* gSizer = new wxFlexGridSizer(1, 3, wxDefaultSize);
	gSizer->AddGrowableCol(1, 1);
	gSizer->Add(copySizer, 1, wxALL | wxEXPAND, 5);
	gSizer->Add(flagSizer, 1, wxALL | wxEXPAND, 5);
	gSizer->Add(cpuSizer, 1, wxALL | wxEXPAND, 5);

	SetSizer(gSizer);

	BindEvents();
}

OptionPanel::~OptionPanel()
{
	delete copyOptions;
	delete flagOptions;
}

wxString OptionPanel::GetOptions() const
{
	wxString cmdStr;
	AppendArg(cmdStr, "/E");
	AppendArg(cmdStr, GetCopyArg());
	AppendArg(cmdStr, GetFlagArgs());
	AppendArg(cmdStr, GetCoreArg());
	
	return cmdStr;

	return cmdStr;
}

wxString OptionPanel::GetCopyArg() const
{
	return copyOptions->values()[copyChoice->GetCurrentSelection()];
}

wxString OptionPanel::GetFlagArgs() const
{
	wxArrayInt selections;
	flagsChoice->GetCheckedItems(selections);

	wxString retStr;
	for(int& idx : selections)
	{
		AppendArg(retStr, flagOptions->values()[idx]);
	}

	return retStr;
}

wxString OptionPanel::GetCoreArg() const
{
	const int coreVal = coreChoice->GetCurrentSelection();
	if(coreVal != 0)
	{
		return wxString::Format("/MT:%i", coreVal + 1);
	}
	return {};
}

void OptionPanel::AppendArg(wxString& cmdStr, const wxString& arg) const
{
	if (!arg.IsEmpty())
	{
		if (!cmdStr.IsEmpty())
		{
			cmdStr += " ";
		}
		cmdStr += arg;
	}
}

void OptionPanel::BindEvents()
{
	copyChoice->Bind(wxEVT_CHOICE, &OptionPanel::OnOptionsChanged, this);
	flagsChoice->Bind(wxEVT_CHECKLISTBOX, &OptionPanel::OnOptionsChanged, this);
	coreChoice->Bind(wxEVT_CHOICE, &OptionPanel::OnOptionsChanged, this);
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
