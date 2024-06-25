#ifndef APPINFO_H
#define APPINFO_H

#include <wx/string.h>

namespace Application
{

	// Application name
	constexpr char APP_NAME[] = "wxRobocopy";

	// Version numbers
	constexpr int MAJ_VER = 1;
	constexpr int MIN_VER = 0;
	constexpr int PAT_VER = 0;

	/**
	 * Generates the semantic version string.
	 */
	inline wxString GenerateSemanticVersion()
	{
		wxString version = "v" + wxString::Format(wxT("%i.%i"), MAJ_VER, MIN_VER);

		if (PAT_VER != 0) {
			version += wxString::Format(wxT(".%i"), PAT_VER);
		}

		return version;
	}

	/**
	 * Gets the application name.
	 */
	inline wxString GetAppName()
	{
		return wxString(APP_NAME);
	}

	/**
	 * Gets the application name with version.
	 */
	inline wxString GetAppNameWithVersion()
	{
		return GetAppName() + " " + GenerateSemanticVersion();
	}

	/**
	 * Checks if the current version is at least the specified version.
	 * @return True if the current version is at least the specified version, otherwise false.
	 */
	inline bool IsAtLeastVersion(int major, int minor, int patch = 0)
	{
		if (MAJ_VER > major) return true;
		if (MAJ_VER == major && MIN_VER > minor) return true;
		if (MAJ_VER == major && MIN_VER == minor && PAT_VER >= patch) return true;
		return false;
	}

} // namespace Application

#endif // APPINFO_H
