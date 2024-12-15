#ifndef INSTRUMENT_LIST_FRAME_H
#define INSTRUMENT_LIST_FRAME_H

#include <wx/wx.h>
#include <wx/grid.h>
#include <vector>
#include <unordered_map>
#include <string>
#include "APIManager.h"

class InstrumentListFrame : public wxFrame {
public:
    /**
     * Constructor for InstrumentListFrame.
     * @param apiManager Reference to the APIManager for fetching instrument data.
     */
    InstrumentListFrame(APIManager& apiManager);

private:
    APIManager& apiManager;       // Reference to the APIManager for API interactions
    wxGrid* instrumentGrid;       // Grid to display the table of instruments

    // Entry boxes for adding/modifying instruments
    wxTextCtrl* isinEntry;
    wxTextCtrl* micEntry;
    wxTextCtrl* currencyEntry;
    wxTextCtrl* statusEntry;

    // Methods
    void PopulateInstrumentTable();
    void OnRefresh(wxCommandEvent& event);

    //Copy line in fields
    void OnGridCellSelected(wxGridEvent& event);

    //Buttons funct
    void OnAdd(wxCommandEvent& event);
    void OnModify(wxCommandEvent& event);
    void OnDelete(wxCommandEvent& event);
    void OnDeactivate(wxCommandEvent& event);


};

#endif // INSTRUMENT_LIST_FRAME_H
