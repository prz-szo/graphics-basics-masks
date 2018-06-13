#include <wx/wx.h>
#include "../headers/AppGUI.h"

AppGUI::AppGUI(wxWindow *parent) : AppGUIBase(parent) {
    canvas->SetScrollbars(25, 25, 52, 40);

    wxImage::AddHandler(new wxJPEGHandler);
    wxImage::AddHandler(new wxPNGHandler);
}

void AppGUI::readImgPath(wxCommandEvent &event) {
    wxFileDialog WxOpenFileDialog(this, wxT("Wybierz obrazek"), wxT(""), wxT(""),
                                  wxT("Pliki BMP,JPG,PNG (*.bmp;*.jpg;*.png)|*.bmp;*.jpg;*.png"),
                                  wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    wxImage imageToLoad;
    if ( WxOpenFileDialog.ShowModal() == wxID_OK ) {
        if (!imageToLoad.LoadFile(WxOpenFileDialog.GetPath())) {
            wxMessageBox(_("Nie uda\u0142o si\u0119 za\u0142adowa\u0107 obrazka"));
            this->Destroy();
        } else {
            this->image = imageToLoad.Copy();
            this->imageCopy = imageToLoad.Copy();
        }
    }
}

void AppGUI::readMaskPath(wxCommandEvent &event) {
    wxFileDialog WxOpenFileDialog(this, wxT("Wybierz plik z maską"), wxT(""), wxT(""),
                                  wxT("Pliki BMP,JPG,PNG (*.bmp;*.jpg;*.png)|*.bmp;*.jpg;*.png"),
                                  wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    wxImage maskToLoad;
    if ( WxOpenFileDialog.ShowModal() == wxID_OK ) {
        if (!maskToLoad.LoadFile(WxOpenFileDialog.GetPath())) {
            wxMessageBox(_("Nie uda\u0142o si\u0119 za\u0142adowa\u0107 pliku"));
            this->Destroy();
        } else
            this->mask = maskToLoad.Copy();
    }
}

void AppGUI::changeTransparencyColor(wxColourPickerEvent &event) {
// TODO: Implement changeTransparencyColor
}

void AppGUI::changeApplyingMethod(wxCommandEvent &event) {
// TODO: Implement changeApplyingMethod
}

void AppGUI::invertMask(wxCommandEvent &event) {
// TODO: Implement invertMask
}

void AppGUI::applyMask(wxCommandEvent &event) {
    SetBackgroundColour(wxColor(192, 192, 192));
    canvas->ClearBackground();
    Refresh();

    imageCopy = image.Copy();
    imageCopy.SetMaskFromImage(mask, 0, 0, 0);
}

void AppGUI::changeAlphaLevel(wxScrollEvent &event) {
// TODO: Implement changeAlphaLevel
}

void AppGUI::updateCanvas(wxUpdateUIEvent &event) {
    if(imageCopy.IsOk()) {
        wxBitmap bitmap(imageCopy);
        wxClientDC dc(canvas);
        canvas->DoPrepareDC(dc);
        dc.DrawBitmap(bitmap, 0, 0, true);
    }
}
