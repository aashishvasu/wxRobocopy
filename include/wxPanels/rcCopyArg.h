#ifndef RCCOPYARG_H
#define RCCOPYARG_H

#include "wxOptionBase.h"

class wxChoice;
class wxDynStringHashMap;

class rcCopyArg : public wxOptionBase
{
public:
	rcCopyArg(wxWindow* parent, const wxString& label, long style = wxBORDER_DEFAULT);
	~rcCopyArg() override;

	wxString GetArgs() const override;

private:
	void BindEvents() override;
	
	wxDynStringHashMap* copyOptions;
	wxChoice* copyChoice;
};

#endif // RCCOPYARG_H
