#include "wxPanels/rcLogArgs.h"

#include "data/wxDynStringHashMap.h"

rcLogArgs::rcLogArgs(wxWindow* parent, const wxString& label, long style) : wxOptionBase(parent, label)
{
	logOptions = new wxDynStringHashMap({"No File List", "No Folder List", "No Progress", "No File Size", "No File Class"}, {"/NFL", "/NDL", "/NP", "/NS", "/NC"});
	logChoice = new wxCheckListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, logOptions->keys(), style);

	sizer_->Add(logChoice, 1, wxALL | wxEXPAND, 5);

	rcLogArgs::BindEvents();
}

rcLogArgs::~rcLogArgs()
{
	delete logOptions;
}

wxString rcLogArgs::GetArgs() const
{
	wxArrayInt selections;
	logChoice->GetCheckedItems(selections);

	wxString retStr;
	for(const int& idx : selections)
	{
		AppendArg(retStr, logOptions->values()[idx]);
	}

	return retStr;
}

void rcLogArgs::BindEvents()
{
	logChoice->Bind(wxEVT_CHECKLISTBOX, &wxOptionBase::OnArgsUpdated, this);
}
