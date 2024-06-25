#include "wxPanels/rcDirArg.h"

#include <wx/choice.h>
#include "data/wxDynStringHashMap.h"

rcDirArg::rcDirArg(wxWindow* parent, const wxString& label, long style) : wxOptionBase(parent, label)
{
	// Choose what type of filtering to use when copying
	dirOptions = new wxDynStringHashMap({"Copy non empty subfolders", "Copy everything", "Copy only files"}, {"/S", "/E", ""});
	dirChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, dirOptions->keys(), style);
	dirChoice->SetSelection(0);

	sizer_->Add(dirChoice, 1, wxALL | wxEXPAND, 5);

	rcDirArg::BindEvents();
}

rcDirArg::~rcDirArg()
{
	delete dirOptions;
}

wxString rcDirArg::GetArgs() const
{
	return dirOptions->values()[dirChoice->GetCurrentSelection()];
}

void rcDirArg::BindEvents()
{
	dirChoice->Bind(wxEVT_CHOICE, &wxOptionBase::OnArgsUpdated, this);
}
