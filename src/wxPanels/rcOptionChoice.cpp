#include "wxPanels/rcOptionChoice.h"

#include "data/wxDynStringHashMap.h"

rcOptionChoice::rcOptionChoice(wxWindow* parent, const wxString& label, wxDynStringHashMap* opts, long style) : wxOptionBase(parent, label), options_(opts)
{
	// Create the wxChoice widget based on options
	choice_ = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, options_->keys(), style);
	choice_->SetSelection(0);

	sizer_->Add(choice_, 1, wxALL | wxEXPAND, 5);

	rcOptionChoice::BindEvents();
}

rcOptionChoice::~rcOptionChoice()
{
	delete options_;
}

wxString rcOptionChoice::GetArgs() const
{
	return options_->values()[choice_->GetCurrentSelection()];
}

void rcOptionChoice::BindEvents()
{
	choice_->Bind(wxEVT_CHOICE, &wxOptionBase::OnArgsUpdated, this);
}
