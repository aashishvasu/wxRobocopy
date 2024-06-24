#ifndef RCCPUARG_H
#define RCCPUARG_H

#include "wxOptionBase.h"

class wxChoice;

class rcCpuArg : public wxOptionBase
{
public:
	rcCpuArg(wxWindow* parent, const wxString& label);
	
	wxString GetArgs() const override;

private:
	void BindEvents() override;
	
	wxChoice* coreChoice;
	
};

#endif // RCCPUARG_H
