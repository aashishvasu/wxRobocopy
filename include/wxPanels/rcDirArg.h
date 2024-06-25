#ifndef RCDIRARG_H
#define RCDIRARG_H

#include "wxOptionBase.h"

class wxChoice;
class wxDynStringHashMap;

class rcDirArg : public wxOptionBase
{
public:
	rcDirArg(wxWindow* parent, const wxString& label, long style = wxBORDER_DEFAULT);
	~rcDirArg() override;

	wxString GetArgs() const override;

private:
	void BindEvents() override;
	
	wxDynStringHashMap* dirOptions;
	wxChoice* dirChoice;
	
};

#endif // RCDIRARG_H