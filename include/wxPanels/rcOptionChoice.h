#ifndef RCOPTIONCHOICE_H
#define RCOPTIONCHOICE_H

#include "wxOptionBase.h"

class wxChoice;
class wxDynStringHashMap;

class rcOptionChoice : public wxOptionBase
{
public:
	rcOptionChoice(wxWindow* parent, const wxString& label, wxDynStringHashMap* opts, long style = wxBORDER_DEFAULT);
	~rcOptionChoice() override;

	wxString GetArgs() const override;

private:
	void BindEvents() override;
	
	wxDynStringHashMap* options_;
	wxChoice* choice_;	
};

#endif // RCOPTIONCHOICE_H
