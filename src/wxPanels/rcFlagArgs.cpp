#include "wxPanels/rcFlagArgs.h"

#include "data/wxDynStringHashMap.h"

rcFlagArgs::rcFlagArgs(wxWindow* parent, const wxString& label) : wxOptionBase(parent, label)
{
	flagOptions = new wxDynStringHashMap({"Include Empty Folders", "Restartable", "Backup", "Restartable with backup fallback"}, {"/E", "/Z", "/B", "/ZB"});
	flagsChoice = new wxCheckListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, flagOptions->keys());
	flagsChoice->Check(0, true);

	sizer_->Add(flagsChoice, 0, wxALL | wxEXPAND, 5);

	rcFlagArgs::BindEvents();
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
