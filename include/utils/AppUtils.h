#ifndef APPUTILS_H
#define APPUTILS_H

#include <wx/stdpaths.h>
#include <wx/string.h>

namespace Application
{
	inline wxString UserDataDir()
	{
		return wxStandardPaths::Get().GetUserDataDir();
	}
}

#endif // APPUTILS_H
