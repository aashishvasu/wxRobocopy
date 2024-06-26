#ifndef APP_H
#define APP_H

#include <wx/wx.h>

class RCPApp : public wxApp
{
public:
    bool OnInit() override;
    int OnExit() override;
};

#endif // APP_H
