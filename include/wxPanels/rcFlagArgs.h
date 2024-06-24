#ifndef RCFLAGARG_H
#define RCFLAGARG_H

#include "wxOptionBase.h"
#include "data/wxDynStringHashMap.h"

class rcFlagArgs : public wxOptionBase
{
public:
	rcFlagArgs(wxWindow* parent, const wxString& label);
	~rcFlagArgs() override { delete flagOptions; }
	
	wxString GetArgs() const override;

private:
	void BindEvents() override;
	
	wxDynStringHashMap* flagOptions;
	wxCheckListBox* flagsChoice;
};

#endif // RCFLAGARG_H
