//
// Created by Mayeul Boucher on 13/12/2024.
//
#include "LoginFrame.h"
#include "InstrumentListFrame.h"

LoginFrame::LoginFrame(APIManager& apiManager)
        : wxFrame(nullptr, wxID_ANY, "Login", wxDefaultPosition, wxSize(300, 200)),
          apiManager(apiManager) {
    wxPanel* panel = new wxPanel(this);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Username:"), 0, wxALL, 5);
    usernameCtrl = new wxTextCtrl(panel, wxID_ANY);
    sizer->Add(usernameCtrl, 0, wxALL | wxEXPAND, 5);

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Password:"), 0, wxALL, 5);
    passwordCtrl = new wxTextCtrl(panel, wxID_ANY);
    sizer->Add(passwordCtrl, 0, wxALL | wxEXPAND, 5);

    wxButton* loginButton = new wxButton(panel, wxID_ANY, "Login");
    sizer->Add(loginButton, 0, wxALL | wxALIGN_CENTER, 10);

    panel->SetSizer(sizer);

    Bind(wxEVT_BUTTON, &LoginFrame::OnLogin, this, loginButton->GetId());
}

void LoginFrame::OnLogin(wxCommandEvent& event) {
    wxString username = usernameCtrl->GetValue();
    wxString password = passwordCtrl->GetValue();

    if (apiManager.login(std::string(username.mb_str()), std::string(password.mb_str()))) {
        wxMessageBox("Login successful!", "Success", wxOK | wxICON_INFORMATION);
        Close();
        InstrumentListFrame* instrumentListFrame = new InstrumentListFrame(apiManager);
        instrumentListFrame->Show();
    } else {
        wxMessageBox("Invalid username or password.", "Error", wxOK | wxICON_ERROR);
    }
}

