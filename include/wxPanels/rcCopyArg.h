#ifndef RCCOPYARG_H
#define RCCOPYARG_H

#include "wxOptionBase.h"
#include "data/wxDynStringHashMap.h"

class rcCopyArg : public wxOptionBase
{
public:
	rcCopyArg(wxWindow* parent, const wxString& label);
	~rcCopyArg() override { delete copyOptions; }
	
	wxString GetArgs() const override;

private:
	void BindEvents() override;
	
	wxDynStringHashMap* copyOptions;
	wxChoice* copyChoice;
};

#endif // RCCOPYARG_H
