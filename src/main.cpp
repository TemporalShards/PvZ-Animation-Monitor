#include "mainWindow.h"

class MyApp : public wxApp {
public:
    bool OnInit() override
    {
        SetAppearance(Appearance::System);
#ifdef __WXMSW__
        SetProcessDPIAware();
#endif

#if wxCHECK_VERSION(3, 1, 0)
        wxImage::SetDefaultLoadFlags(wxImage::GetDefaultLoadFlags() | wxIMAGE_QUALITY_HIGH);
#endif

        // 基础尺寸
        double baseWidth = 750, baseHeight = 860;

        // 获取DPI缩放因子
        wxSize dpi = wxGetDisplayPPI();
        double scale = dpi.x / 96.0;

        wxSize windowSize(baseWidth * scale, baseHeight * scale);

        mainWindow* frame = new mainWindow(nullptr, wxID_ANY, "PvZ Animation Monitor v1.0.5", windowSize, (wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) | wxWANTS_CHARS);
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);