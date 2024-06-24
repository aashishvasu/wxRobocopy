#ifndef RCUTILS_H
#define RCUTILS_H

#include <wx/string.h>

namespace Application
{
	inline void AppendArg(wxString& cmdStr, const wxString& arg)
	{
		if (!arg.IsEmpty())
		{
			if (!cmdStr.IsEmpty())
			{
				cmdStr += " ";
			}
			cmdStr += arg;
		}
	}
}

#endif // RCUTILS_H
