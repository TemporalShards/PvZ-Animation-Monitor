#include "mainWindow.h"

class MyApp : public wxApp {
public:
    bool OnInit() override
    {
        SetAppearance(Appearance::System);
        mainWindow* frame = new mainWindow(nullptr, wxID_ANY, "PvZ Animation Monitor v1.0.4", wxSize(750, 860), (wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) | wxWANTS_CHARS);
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);