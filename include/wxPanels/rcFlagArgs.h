#ifndef RCFLAGARGS_H
#define RCFLAGARGS_H

#include "wxOptionBase.h"

class wxCheckListBox;
class wxDynStringHashMap;

class rcFlagArgs : public wxOptionBase
{
public:
	rcFlagArgs(wxWindow* parent, const wxString& label, long style = wxBORDER_DEFAULT);
	~rcFlagArgs() override;

	wxString GetArgs() const override;

private:
	void BindEvents() override;
	
	wxDynStringHashMap* flagOptions;
	wxCheckListBox* flagsChoice;
};

#endif // RCFLAGARGS_H
