#include "wxPanels/rcCopyArg.h"

#include <wx/choice.h>
#include "data/wxDynStringHashMap.h"

rcCopyArg::rcCopyArg(wxWindow* parent, const wxString& label) : wxOptionBase(parent, label)
{
	// Type of copying to be done
	copyOptions = new wxDynStringHashMap({"Normal Copy", "Sync/Mirror", "Move"}, {"", "/MIR", "/MOVE"});
	copyChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, copyOptions->keys());
	copyChoice->SetSelection(0);

	sizer_->Add(copyChoice, 0, wxALL | wxEXPAND, 5);

	rcCopyArg::BindEvents();
}

wxString rcCopyArg::GetArgs() const
{
	return copyOptions->values()[copyChoice->GetCurrentSelection()];
}

void rcCopyArg::BindEvents()
{
	copyChoice->Bind(wxEVT_CHOICE, &wxOptionBase::OnArgsUpdated, this);
}
