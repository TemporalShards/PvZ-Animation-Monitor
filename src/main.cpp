#include "mainWindow.h"

class MyApp : public wxApp {
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    mainWindow* frame = new mainWindow(nullptr, wxID_ANY, "PvZ Animation Monitor v1.0.0", wxDefaultPosition, wxSize(650, 860), (wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) | wxWANTS_CHARS);
    frame->Show(true);
    return true;
}