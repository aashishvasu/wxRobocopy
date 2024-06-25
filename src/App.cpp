#include "App.h"
#include "MainFrame.h"
#include "utils/AppInfo.h"

wxIMPLEMENT_APP(RCPApp);

bool RCPApp::OnInit()
{
    MainFrame* frame = new MainFrame(Application::GetAppNameWithVersion());
    frame->Show(true);
    frame->SetClientSize(850, 600);

    frame->Layout();
    return true;
}
