//
// Created by Mayeul Boucher on 13/12/2024.
//

#ifndef APIMANAGERTEST_LOGINFRAME_H
#define APIMANAGERTEST_LOGINFRAME_H

#include <wx/wx.h>
#include "APIManager.h"

class LoginFrame : public wxFrame {
public:
    LoginFrame(APIManager& apiManager);

private:
    APIManager& apiManager;
    wxTextCtrl* usernameCtrl;
    wxTextCtrl* passwordCtrl;

    void OnLogin(wxCommandEvent& event);
};


#endif //APIMANAGERTEST_LOGINFRAME_H
