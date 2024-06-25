#ifndef RCLOGARGS_H
#define RCLOGARGS_H

#include "wxOptionBase.h"

class wxCheckListBox;
class wxDynStringHashMap;

class rcLogArgs : public wxOptionBase
{
public:
	rcLogArgs(wxWindow* parent, const wxString& label, long style = wxBORDER_DEFAULT);
	~rcLogArgs() override;

	wxString GetArgs() const override;

private:
	void BindEvents() override;
	
	wxDynStringHashMap* logOptions;
	wxCheckListBox* logChoice;
};

#endif // RCLOGARGS_H
