#include "wxPanels/wxOptionBase.h"

#include <wx/sizer.h>
#include "utils/rcUtils.h"

wxDEFINE_EVENT(rcEVT_ARG_UPDATED, wxCommandEvent);

wxOptionBase::wxOptionBase(wxWindow* parent, const wxString& label): wxPanel(parent), label_(label)
{
	sizer_ = new wxStaticBoxSizer(wxHORIZONTAL, this, label);
	SetSizer(sizer_);
}

void wxOptionBase::OnArgsUpdated(wxCommandEvent& e)
{
	const wxCommandEvent evt = wxCommandEvent(rcEVT_ARG_UPDATED);
	wxPostEvent(m_parent, evt);
}

void wxOptionBase::AppendArg(wxString& cmdStr, const wxString& arg)
{
	Application::AppendArg(cmdStr, arg);
}
