#ifndef RCFLAGARG_H
#define RCFLAGARG_H

#include "wxOptionBase.h"

class wxCheckListBox;
class wxDynStringHashMap;

class rcFlagArgs : public wxOptionBase
{
public:
	rcFlagArgs(wxWindow* parent, const wxString& label);
	~rcFlagArgs() override;

	wxString GetArgs() const override;

private:
	void BindEvents() override;
	
	wxDynStringHashMap* flagOptions;
	wxCheckListBox* flagsChoice;
};

#endif // RCFLAGARG_H
