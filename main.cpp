#include <wx/wx.h>
#include "APIManager.h"
#include "LoginFrame.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        APIManager* apiManager = new APIManager("http://localhost:18080");
        LoginFrame* loginFrame = new LoginFrame(*apiManager);
        loginFrame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
