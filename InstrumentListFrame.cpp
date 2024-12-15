#include "InstrumentListFrame.h"

// Enum for button IDs
enum {
    ID_REFRESH_BUTTON = wxID_HIGHEST + 1,
    ID_ADD_MODIFY_BUTTON
};

InstrumentListFrame::InstrumentListFrame(APIManager& apiManager)
        : wxFrame(nullptr, wxID_ANY, "Instruments", wxDefaultPosition, wxSize(800, 700)),
          apiManager(apiManager) {
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Refresh Button
    wxButton* refreshButton = new wxButton(panel, ID_REFRESH_BUTTON, "Refresh");
    mainSizer->Add(refreshButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);

    // wxGrid for Instruments
    instrumentGrid = new wxGrid(panel, wxID_ANY);
    instrumentGrid->CreateGrid(0, 4);
    instrumentGrid->SetColLabelValue(0, "ISIN");
    instrumentGrid->SetColLabelValue(1, "MIC");
    instrumentGrid->SetColLabelValue(2, "Currency");
    instrumentGrid->SetColLabelValue(3, "Status");
    instrumentGrid->SetColSize(0, 200);
    instrumentGrid->SetColSize(1, 100);
    instrumentGrid->SetColSize(2, 100);
    instrumentGrid->SetColSize(3, 100);
    mainSizer->Add(instrumentGrid, 1, wxALL | wxEXPAND, 10);
// Form Layout: One row per field
    wxBoxSizer* formSizer = new wxBoxSizer(wxVERTICAL);

    // ISIN Row
    wxBoxSizer* isinSizer = new wxBoxSizer(wxHORIZONTAL);
    isinSizer->Add(new wxStaticText(panel, wxID_ANY, "ISIN:"), 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 10);
    isinEntry = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(300, -1));
    isinSizer->Add(isinEntry, 1);
    formSizer->Add(isinSizer, 0, wxALL | wxEXPAND, 5);

    // MIC Row
    wxBoxSizer* micSizer = new wxBoxSizer(wxHORIZONTAL);
    micSizer->Add(new wxStaticText(panel, wxID_ANY, "MIC:"), 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 10);
    micEntry = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(300, -1));
    micSizer->Add(micEntry, 1);
    formSizer->Add(micSizer, 0, wxALL | wxEXPAND, 5);

    // Currency Row
    wxBoxSizer* currencySizer = new wxBoxSizer(wxHORIZONTAL);
    currencySizer->Add(new wxStaticText(panel, wxID_ANY, "Currency:"), 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 10);
    currencyEntry = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(300, -1));
    currencySizer->Add(currencyEntry, 1);
    formSizer->Add(currencySizer, 0, wxALL | wxEXPAND, 5);

    // Status Row
    wxBoxSizer* statusSizer = new wxBoxSizer(wxHORIZONTAL);
    statusSizer->Add(new wxStaticText(panel, wxID_ANY, "Status:"), 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 10);
    statusEntry = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(300, -1));
    statusSizer->Add(statusEntry, 1);
    formSizer->Add(statusSizer, 0, wxALL | wxEXPAND, 5);

    mainSizer->Add(formSizer, 0, wxALL | wxEXPAND, 10);

    // Add/Modify Button
    wxButton* addModifyButton = new wxButton(panel, ID_ADD_MODIFY_BUTTON, "Add/Modify");
    mainSizer->Add(addModifyButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);


    panel->SetSizer(mainSizer);

    // Event bindings
    Bind(wxEVT_BUTTON, &InstrumentListFrame::OnRefresh, this, ID_REFRESH_BUTTON);
    Bind(wxEVT_BUTTON, &InstrumentListFrame::OnAddModify, this, ID_ADD_MODIFY_BUTTON);

    // Populate the grid with data
    PopulateInstrumentTable();
}

void InstrumentListFrame::PopulateInstrumentTable() {
    std::vector<std::unordered_map<std::string, std::string>> instruments = apiManager.getInstruments();

    instrumentGrid->ClearGrid();
    if (instrumentGrid->GetNumberRows() > 0) {
        instrumentGrid->DeleteRows(0, instrumentGrid->GetNumberRows());
    }

    for (const auto& instrument : instruments) {
        int newRow = instrumentGrid->GetNumberRows();
        instrumentGrid->AppendRows(1);

        instrumentGrid->SetCellValue(newRow, 0, instrument.at("isin"));
        instrumentGrid->SetCellValue(newRow, 1, instrument.at("mic"));
        instrumentGrid->SetCellValue(newRow, 2, instrument.at("currency"));
        instrumentGrid->SetCellValue(newRow, 3, instrument.at("status"));
    }
}

void InstrumentListFrame::OnRefresh(wxCommandEvent& event) {
    PopulateInstrumentTable();
}

void InstrumentListFrame::OnAddModify(wxCommandEvent& event) {
    std::string isin = isinEntry->GetValue().ToStdString();
    std::string mic = micEntry->GetValue().ToStdString();
    std::string currency = currencyEntry->GetValue().ToStdString();
    std::string status = statusEntry->GetValue().ToStdString();

    if (isin.empty() || mic.empty() || currency.empty() || status.empty()) {
        wxMessageBox("All fields must be filled!", "Error", wxICON_ERROR);
        return;
    }

    // Prepare JSON payload
    std::string data = "{\"isin\":\"" + isin + "\",\"mic\":\"" + mic +
                       "\",\"currency\":\"" + currency + "\",\"status\":\"" + status + "\"}";

    // Send POST request to API to add/modify the instrument
    std::string response = apiManager.post("/instruments", data);

    // Check response and notify user
    if (response.find("successfully") != std::string::npos) {
        wxMessageBox("Instrument added/modified successfully!", "Success", wxICON_INFORMATION);
        PopulateInstrumentTable(); // Refresh grid
    } else {
        wxMessageBox("Failed to add/modify instrument.", "Error", wxICON_ERROR);
    }
}

void InstrumentListFrame::OnGridCellSelected(wxGridEvent& event) {
    int row = event.GetRow(); // Get the row index of the selected cell

    // Retrieve the values from the selected row in the grid
    wxString isin = instrumentGrid->GetCellValue(row, 0);
    wxString mic = instrumentGrid->GetCellValue(row, 1);
    wxString currency = instrumentGrid->GetCellValue(row, 2);
    wxString status = instrumentGrid->GetCellValue(row, 3);

    // Populate the form fields with the retrieved values
    isinEntry->SetValue(isin);
    micEntry->SetValue(mic);
    currencyEntry->SetValue(currency);
    statusEntry->SetValue(status);

    // Allow the default processing for the event
    event.Skip();
}

