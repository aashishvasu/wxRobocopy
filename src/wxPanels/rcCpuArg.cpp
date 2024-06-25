#include "wxPanels/rcCpuArg.h"

#include "utils/CoreCount.h"

rcCpuArg::rcCpuArg(wxWindow* parent, const wxString& label, long style) : wxOptionBase(parent, label)
{
	// Number of CPU thread choice
	const int numCores = wxMin(wxMax(1, GetCPUCoreCount()), 128);
	wxArrayString coreChoices;
	for (int i = 1; i <= numCores; ++i)
	{
		coreChoices.Add(wxString::Format("%d", i));
	}
	coreChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, coreChoices, style);
	coreChoice->SetSelection(0);

	sizer_->Add(coreChoice, 1, wxALL | wxEXPAND, 5);

	rcCpuArg::BindEvents();
}

wxString rcCpuArg::GetArgs() const
{
	const int coreVal = coreChoice->GetCurrentSelection();
	if(coreVal != 0)
	{
		return wxString::Format("/MT:%i", coreVal + 1);
	}
	return {};
}

void rcCpuArg::BindEvents()
{
	coreChoice->Bind(wxEVT_CHOICE, &wxOptionBase::OnArgsUpdated, this);
}
