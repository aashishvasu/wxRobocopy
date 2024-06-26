#ifndef RCOPTIONCHECKLIST_H
#define RCOPTIONCHECKLIST_H

#include "wxOptionBase.h"

class wxCheckListBox;
class wxDynStringHashMap;

class rcOptionChecklist : public wxOptionBase
{
public:
	rcOptionChecklist(wxWindow* parent, const wxString& label, wxDynStringHashMap* opts, long style = wxBORDER_DEFAULT);
	~rcOptionChecklist() override;

	wxString GetArgs() const override;

private:
	void BindEvents() override;
	
	wxDynStringHashMap* options_;
	wxCheckListBox* choice_;
};

#endif // RCOPTIONCHECKLIST_H
