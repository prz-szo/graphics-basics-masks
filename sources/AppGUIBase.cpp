///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 16 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../headers/AppGUIBase.h"

///////////////////////////////////////////////////////////////////////////

AppGUIBase::AppGUIBase(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size,
                       long style) : wxFrame(parent, id, title, pos, size, style) {
    this->SetSizeHints(wxSize(800, 600), wxDefaultSize);

    wxBoxSizer *bSizer1;
    bSizer1 = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *side_bar_sizer;
    side_bar_sizer = new wxBoxSizer(wxVERTICAL);


    side_bar_sizer->Add(0, 0, 2, wxEXPAND, 5);

    wxBoxSizer *bSizer9;
    bSizer9 = new wxBoxSizer(wxHORIZONTAL);

    read_img_button = new wxButton(this, wxID_ANY, wxT("Wczytaj obrazek"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer9->Add(read_img_button, 1, wxALL | wxEXPAND, 5);


    side_bar_sizer->Add(bSizer9, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 5);

    wxBoxSizer *mask_sizer;
    mask_sizer = new wxBoxSizer(wxHORIZONTAL);

    mask_sizer->SetMinSize(wxSize(0, 0));
    read_mask_btn = new wxButton(this, wxID_ANY, wxT("Wczytaj maskę"), wxDefaultPosition, wxDefaultSize, 0);
    mask_sizer->Add(read_mask_btn, 1, wxALL | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);

    mask_color_picker = new wxColourPickerCtrl(this, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize,
                                               wxCLRP_DEFAULT_STYLE | wxCLRP_SHOW_LABEL);
    mask_sizer->Add(mask_color_picker, 1, wxALL | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);


    side_bar_sizer->Add(mask_sizer, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 5);

    wxBoxSizer *bSizer7;
    bSizer7 = new wxBoxSizer(wxVERTICAL);

    wxString applying_method_radioboxChoices[] = {wxT("Zmiana kolorów"), wxT("Sumowanie kolorów"),
                                                  wxT("Mnożenie kolorów"), wxT("Odejmowanie kolorów"),
                                                  wxT("Tylko jaśniejsze"), wxT("Tylko ciemniejsze"),
                                                  wxT("Różnica")};
    int applying_method_radioboxNChoices = sizeof(applying_method_radioboxChoices) / sizeof(wxString);
    applying_method_radiobox = new wxRadioBox(this, wxID_ANY, wxT("Metoda nakładania"), wxDefaultPosition,
                                              wxDefaultSize, applying_method_radioboxNChoices,
                                              applying_method_radioboxChoices, 1, wxRA_SPECIFY_COLS);
    applying_method_radiobox->SetSelection(1);
    bSizer7->Add(applying_method_radiobox, 1, wxALL | wxEXPAND | wxALIGN_CENTER_VERTICAL, 10);

    apply_mask_btn = new wxButton(this, wxID_ANY, wxT("Nałóż maskę"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer7->Add(apply_mask_btn, 0, wxALL | wxEXPAND, 5);

    save_to_file = new wxButton(this, wxID_ANY, wxT("Zapis do pliku"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer7->Add(save_to_file, 0, wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 5);

    side_bar_sizer->Add(bSizer7, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 5);

    m_staticline1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    side_bar_sizer->Add(m_staticline1, 0, wxEXPAND | wxALL, 5);

    wxBoxSizer *bSizer10;
    bSizer10 = new wxBoxSizer(wxVERTICAL);

    alpha_label = new wxStaticText(this, wxID_ANY, wxT("Poziom kanału alfa"), wxDefaultPosition, wxDefaultSize,
                                   wxALIGN_CENTRE);
    alpha_label->Wrap(-1);
    bSizer10->Add(alpha_label, 1, wxALL | wxEXPAND, 5);

    alpha_level_slider = new wxSlider(this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);
    bSizer10->Add(alpha_level_slider, 1, wxALL | wxEXPAND, 5);

    side_bar_sizer->Add(bSizer10, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 5);

    side_bar_sizer->Add(0, 0, 10, wxEXPAND, 5);

    bSizer1->Add(side_bar_sizer, 1, wxEXPAND | wxALIGN_CENTER_VERTICAL, 5);

    wxBoxSizer *bSizer5;
    bSizer5 = new wxBoxSizer(wxVERTICAL);

    canvas = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
    canvas->SetScrollRate(5, 5);
    bSizer5->Add(canvas, 1, wxEXPAND | wxALL, 5);


    bSizer1->Add(bSizer5, 5, wxEXPAND, 5);

    this->SetSizer(bSizer1);
    this->Layout();

    this->Centre(wxBOTH);

    // Connect Events
    read_img_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AppGUIBase::readImgPath), NULL, this);
    read_mask_btn->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AppGUIBase::readMaskPath), NULL, this);
    mask_color_picker->Connect(wxEVT_COMMAND_COLOURPICKER_CHANGED,
                               wxColourPickerEventHandler(AppGUIBase::changeTransparencyColor), NULL, this);
    applying_method_radiobox->Connect(wxEVT_COMMAND_RADIOBOX_SELECTED,
                                      wxCommandEventHandler(AppGUIBase::changeApplyingMethod), NULL, this);
    apply_mask_btn->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AppGUIBase::applyMask), NULL, this);
    save_to_file->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AppGUIBase::saveToFile), NULL, this);
    alpha_level_slider->Connect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(AppGUIBase::changeAlphaLevel), NULL, this);
    alpha_level_slider->Connect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(AppGUIBase::changeAlphaLevel), NULL, this);
    alpha_level_slider->Connect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(AppGUIBase::changeAlphaLevel), NULL,
                                this);
    alpha_level_slider->Connect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(AppGUIBase::changeAlphaLevel), NULL, this);
    canvas->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(AppGUIBase::updateCanvas), NULL, this);
}

AppGUIBase::~AppGUIBase() {
    // Disconnect Events
    read_img_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AppGUIBase::readImgPath), NULL,
                                this);
    read_mask_btn->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AppGUIBase::readMaskPath), NULL,
                              this);
    mask_color_picker->Disconnect(wxEVT_COMMAND_COLOURPICKER_CHANGED,
                                  wxColourPickerEventHandler(AppGUIBase::changeTransparencyColor), NULL, this);
    applying_method_radiobox->Disconnect(wxEVT_COMMAND_RADIOBOX_SELECTED,
                                         wxCommandEventHandler(AppGUIBase::changeApplyingMethod), NULL, this);
    apply_mask_btn->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AppGUIBase::applyMask), NULL, this);
    save_to_file->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AppGUIBase::saveToFile), NULL, this);
    alpha_level_slider->Disconnect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(AppGUIBase::changeAlphaLevel), NULL, this);
    alpha_level_slider->Disconnect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(AppGUIBase::changeAlphaLevel), NULL,
                                   this);
    alpha_level_slider->Disconnect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(AppGUIBase::changeAlphaLevel), NULL,
                                   this);

    alpha_level_slider->Disconnect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(AppGUIBase::changeAlphaLevel), NULL,
                                   this);
    canvas->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(AppGUIBase::updateCanvas), NULL, this);

}
