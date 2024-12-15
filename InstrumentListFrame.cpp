#include "InstrumentListFrame.h"

// Enum for button IDs
enum {
    ID_REFRESH_BUTTON = wxID_HIGHEST + 1,
    ID_ADD_BUTTON,
    ID_MODIFY_BUTTON,
    ID_DELETE_BUTTON,
    ID_DEACTIVATE_BUTTON
};

// Constructor
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

    // Bind grid row selection event
    instrumentGrid->Bind(wxEVT_GRID_SELECT_CELL, &InstrumentListFrame::OnGridCellSelected, this);

    // Form Layout
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

    // Add Buttons for Add, Modify, Delete, and Deactivate
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton* addButton = new wxButton(panel, ID_ADD_BUTTON, "Add");
    wxButton* modifyButton = new wxButton(panel, ID_MODIFY_BUTTON, "Modify");
    wxButton* deleteButton = new wxButton(panel, ID_DELETE_BUTTON, "Delete");
    wxButton* deactivateButton = new wxButton(panel, ID_DEACTIVATE_BUTTON, "Deactivate");

    buttonSizer->Add(addButton, 1, wxALL | wxEXPAND, 5);
    buttonSizer->Add(modifyButton, 1, wxALL | wxEXPAND, 5);
    buttonSizer->Add(deleteButton, 1, wxALL | wxEXPAND, 5);
    buttonSizer->Add(deactivateButton, 1, wxALL | wxEXPAND, 5);

    mainSizer->Add(buttonSizer, 0, wxALL | wxEXPAND, 10);

    panel->SetSizer(mainSizer);

    // Event bindings
    Bind(wxEVT_BUTTON, &InstrumentListFrame::OnRefresh, this, ID_REFRESH_BUTTON);
    Bind(wxEVT_BUTTON, &InstrumentListFrame::OnAdd, this, ID_ADD_BUTTON);
    Bind(wxEVT_BUTTON, &InstrumentListFrame::OnModify, this, ID_MODIFY_BUTTON);
    Bind(wxEVT_BUTTON, &InstrumentListFrame::OnDelete, this, ID_DELETE_BUTTON);

    // Populate the grid with data
    PopulateInstrumentTable();
}

// Populate the instrument table with data from the API
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

void InstrumentListFrame::OnAdd(wxCommandEvent& event) {
    std::string isin = isinEntry->GetValue().ToStdString();
    std::string mic = micEntry->GetValue().ToStdString();
    std::string currency = currencyEntry->GetValue().ToStdString();
    std::string status = statusEntry->GetValue().ToStdString();

    if (isin.empty() || mic.empty() || currency.empty() || status.empty()) {
        wxMessageBox("All fields are required.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    if (apiManager.addInstrument(isin, mic, currency, status)) {
        wxMessageBox("Instrument added successfully!", "Success", wxOK | wxICON_INFORMATION);
        PopulateInstrumentTable();
    } else {
        wxMessageBox("Failed to add instrument. Please try again.", "Error", wxOK | wxICON_ERROR);
    }
}

void InstrumentListFrame::OnModify(wxCommandEvent& event) {
    std::string isin = isinEntry->GetValue().ToStdString();
    std::string mic = micEntry->GetValue().ToStdString();
    std::string currency = currencyEntry->GetValue().ToStdString();
    std::string status = statusEntry->GetValue().ToStdString();

    if (isin.empty()) {
        wxMessageBox("ISIN is required to modify an instrument.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    if (apiManager.modifyInstrument(isin, mic, currency, status)) {
        wxMessageBox("Instrument modified successfully!", "Success", wxOK | wxICON_INFORMATION);
        PopulateInstrumentTable();
    } else {
        wxMessageBox("Failed to modify instrument. Please try again.", "Error", wxOK | wxICON_ERROR);
    }
}

void InstrumentListFrame::OnDelete(wxCommandEvent& event) {
    std::string isin = isinEntry->GetValue().ToStdString();

    if (isin.empty()) {
        wxMessageBox("ISIN is required to delete an instrument.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    int confirm = wxMessageBox("Are you sure you want to delete this instrument?", 
                                "Confirm Deletion", wxYES_NO | wxICON_WARNING);
    if (confirm != wxYES) {
        return;
    }

    if (apiManager.dellInstrument(isin)) {
        wxMessageBox("Instrument deleted successfully!", "Success", wxOK | wxICON_INFORMATION);
        PopulateInstrumentTable();
    } else {
        wxMessageBox("Failed to delete instrument. Please try again.", "Error", wxOK | wxICON_ERROR);
    }
}
