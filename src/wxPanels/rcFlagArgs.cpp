#include "wxPanels/rcFlagArgs.h"

#include "data/wxDynStringHashMap.h"

rcFlagArgs::rcFlagArgs(wxWindow* parent, const wxString& label, long style) : wxOptionBase(parent, label)
{
	flagOptions = new wxDynStringHashMap({"Restartable", "Backup", "Restartable with backup fallback"}, {"/Z", "/B", "/ZB"});
	flagsChoice = new wxCheckListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, flagOptions->keys(), style);

	sizer_->Add(flagsChoice, 1, wxALL | wxEXPAND, 5);

	rcFlagArgs::BindEvents();
}

rcFlagArgs::~rcFlagArgs()
{
	delete flagOptions;
}

wxString rcFlagArgs::GetArgs() const
{
	wxArrayInt selections;
	flagsChoice->GetCheckedItems(selections);

	wxString retStr;
	for(const int& idx : selections)
	{
		AppendArg(retStr, flagOptions->values()[idx]);
	}

	return retStr;
}

void rcFlagArgs::BindEvents()
{
	flagsChoice->Bind(wxEVT_CHECKLISTBOX, &wxOptionBase::OnArgsUpdated, this);
}
