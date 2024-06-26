#include "wxPanels/rcOptionChecklist.h"

#include "data/wxDynStringHashMap.h"

rcOptionChecklist::rcOptionChecklist(wxWindow* parent, const wxString& label, wxDynStringHashMap* opts, long style) : wxOptionBase(parent, label), options_(opts)
{
	// Create the wxCheckListBox widget based on options
	choice_ = new wxCheckListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, options_->keys(), style);

	sizer_->Add(choice_, 1, wxALL | wxEXPAND, 5);

	rcOptionChecklist::BindEvents();
}

rcOptionChecklist::~rcOptionChecklist()
{
	delete options_;
}

wxString rcOptionChecklist::GetArgs() const
{
	wxArrayInt selections;
	choice_->GetCheckedItems(selections);

	wxString retStr;
	for(const int& idx : selections)
	{
		AppendArg(retStr, options_->values()[idx]);
	}

	return retStr;
}

void rcOptionChecklist::BindEvents()
{
	choice_->Bind(wxEVT_CHECKLISTBOX, &wxOptionBase::OnArgsUpdated, this);
}
