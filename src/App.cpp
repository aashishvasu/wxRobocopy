#include "App.h"
#include "MainFrame.h"
#include "utils/AppInfo.h"
#include <wx/config.h>
#include <wx/fileconf.h>

wxIMPLEMENT_APP(RCPApp);

bool RCPApp::OnInit()
{
    // Initialize logging
    wxLog::SetActiveTarget(new wxLogStderr());

    // Load configuration
    wxConfigBase* config = new wxFileConfig(Application::GetAppName());
    wxConfigBase::Set(config);
    
    MainFrame* frame = new MainFrame(Application::GetAppNameWithVersion());
    frame->Show(true);
    frame->SetClientSize(850, 600);
    frame->Layout();
    
    return true;
}

int RCPApp::OnExit()
{
    // Clean up configuration
    wxConfigBase* config = wxConfigBase::Get();
    delete config;
    wxConfigBase::Set(nullptr);
    
    return wxApp::OnExit();
}
