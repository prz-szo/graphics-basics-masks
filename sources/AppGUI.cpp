#include <wx/wx.h>
#include "../headers/AppGUI.h"


AppGUI::AppGUI(wxWindow *parent) : AppGUIBase(parent) {
    canvas->SetScrollbars(25, 25, 52, 40);
    this->SetBackgroundColour(wxColor(192, 192, 192));
    canvas->SetBackgroundColour(wxColor(192, 192, 192));
    transparencyColor = mask_color_picker->GetColour();

    method = SUM_COLORS;

    wxImage::AddHandler(new wxJPEGHandler);
    wxImage::AddHandler(new wxPNGHandler);
}

void AppGUI::readImgPath(wxCommandEvent &event) {
    wxFileDialog WxOpenFileDialog(this, wxT("Wybierz obrazek"), wxT(""), wxT(""),
                                  wxT("Pliki BMP (*.bmp)|*.bmp;|Pliki JPG (*.jpg)|*.jpg|Pliki PNG (*.png)|*.png"),
                                  wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    wxImage imageToLoad;
    if ( WxOpenFileDialog.ShowModal() == wxID_OK ) {
        if ( !imageToLoad.LoadFile(WxOpenFileDialog.GetPath())) {
            wxMessageBox(_("Nie uda\u0142o si\u0119 za\u0142adowa\u0107 obrazka"));
            WxOpenFileDialog.Destroy();
        } else {
            this->image = imageToLoad.Copy();
            this->imageCopy = imageToLoad.Copy();
        }
    }
    WxOpenFileDialog.Destroy();
}

void AppGUI::readMaskPath(wxCommandEvent &event) {
    wxFileDialog WxOpenFileDialog(this, wxT("Wybierz plik z maską"), wxT(""), wxT(""),
                                  wxT("Pliki BMP (*.bmp)|*.bmp;|Pliki JPG (*.jpg)|*.jpg|Pliki PNG (*.png)|*.png"),
                                  wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    wxImage maskToLoad;
    if ( WxOpenFileDialog.ShowModal() == wxID_OK ) {
        if ( !maskToLoad.LoadFile(WxOpenFileDialog.GetPath())) {
            wxMessageBox(_("Nie uda\u0142o si\u0119 za\u0142adowa\u0107 pliku"));
            WxOpenFileDialog.Destroy();
        } else
            this->mask = maskToLoad.Copy();
    }
    WxOpenFileDialog.Destroy();
}

void AppGUI::changeTransparencyColor(wxColourPickerEvent &event) {
    transparencyColor = mask_color_picker->GetColour();
}

void AppGUI::changeApplyingMethod(wxCommandEvent &event) {
    method = static_cast<ApplyingMethod>(applying_method_radiobox->GetSelection());
}

void AppGUI::applyMask(wxCommandEvent &event) {
    SetBackgroundColour(wxColor(192, 192, 192));
    canvas->ClearBackground();
    Refresh();

    imageCopy = image.Copy();
    wxColor newColor;
    for (int i = 1; i < imageCopy.GetWidth() - 1; ++i) {
        for (int j = 1; j < imageCopy.GetHeight() - 1; ++j) {
            if ( !colorTransparent(i, j)) {
                switch (applying_method_radiobox->GetSelection()) {
                    case CHANGE_COLORS:
                        newColor = changeColors(i, j);
                        break;
                    case SUM_COLORS:
                        newColor = addColors(i, j);
                        break;
                    case MULTIPLY_COLORS:
                        newColor = multiplyColors(i, j);
                        break;
                }
                imageCopy.SetRGB(i, j, newColor.Red(), newColor.Green(), newColor.Blue());
            }
        }
    }
}

void AppGUI::changeAlphaLevel(wxScrollEvent &event) {
// TODO: Implement changeAlphaLevel
}

void AppGUI::updateCanvas(wxUpdateUIEvent &event) {
    if ( imageCopy.IsOk()) {
        wxBitmap bitmap(imageCopy);
        wxClientDC dc(canvas);
        canvas->DoPrepareDC(dc);
        dc.DrawBitmap(bitmap, 0, 0, true);
    }
}

wxColor AppGUI::addColors(int i, int j) {
    int red = image.GetRed(i, j) + mask.GetRed(i, j);
    int green = image.GetGreen(i, j) + mask.GetGreen(i, j);
    int blue = image.GetBlue(i, j) + mask.GetBlue(i, j);
    correctColor(red);
    correctColor(green);
    correctColor(blue);
    return wxColor(red, green, blue);
}

wxColor AppGUI::changeColors(int i, int j) {
    return wxColor(mask.GetRed(i, j), mask.GetGreen(i, j), mask.GetBlue(i, j));
}

wxColor AppGUI::multiplyColors(int i, int j) {
    int red = image.GetRed(i, j) * mask.GetRed(i, j);
    int green = image.GetGreen(i, j) * mask.GetGreen(i, j);
    int blue = image.GetBlue(i, j) * mask.GetBlue(i, j);
    correctColor(red);
    correctColor(green);
    correctColor(blue);
    return wxColor(red, green, blue);
}

void AppGUI::correctColor(int &computedColor) {
    if ( computedColor > 255 )
        computedColor = 255;
    else if ( computedColor < 0 )
        computedColor = 0;
}

bool AppGUI::colorTransparent(int i, int j) {
    return mask.GetRed(i, j) == transparencyColor.Red() &&
           mask.GetGreen(i, j) == transparencyColor.Green() &&
           mask.GetBlue(i, j) == transparencyColor.Blue();
}

void AppGUI::saveToFile(wxCommandEvent &event) {
    wxFileDialog WxSaveFileDialog(this, wxT("Wybierz lokalizacje do zapisu"), wxT(""), wxT(std::tiwxDateTime().Today()),
                                  wxT("Pliki BMP (*.bmp)|*.bmp;|Pliki JPG (*.jpg)|*.jpg|Pliki PNG (*.png)|*.png"),
                                  wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
    wxImage maskToLoad;
    if ( WxSaveFileDialog.ShowModal() == wxID_OK ) {
        imageCopy.SaveFile(WxSaveFileDialog.GetPath());
    }
    WxSaveFileDialog.Destroy();
}
