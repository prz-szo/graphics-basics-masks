#include <wx/wx.h>
#include "../headers/AppGUI.h"


AppGUI::AppGUI(wxWindow *parent) : AppGUIBase(parent) {
    this->SetBackgroundColour(wxColor(192, 192, 192));
    canvas->SetBackgroundColour(wxColor(192, 192, 192));
    transparencyColor = mask_color_picker->GetColour();

    method = SUM;

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
            canvas->SetScrollbars(20, 20, image.GetWidth() / 20, image.GetHeight() / 20);
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
            wxMessageBox(wxT("Nie uda\u0142o si\u0119 za\u0142adowa\u0107 pliku"));
            WxOpenFileDialog.Destroy();
        } else if ( image.IsOk() && ( maskToLoad.GetHeight() < image.GetHeight()
                                      || maskToLoad.GetWidth() < image.GetWidth())) {
            wxMessageBox(wxT("Maska nie może być mniejsza niż obraz"));
            WxOpenFileDialog.Destroy();
        } else
            this->mask = maskToLoad.Copy();
    }
    WxOpenFileDialog.Destroy();
}

void AppGUI::changeTransparencyColor(wxColourPickerEvent &event) {
    transparencyColor = mask_color_picker->GetColour();
    applyMask(event);
}

void AppGUI::changeApplyingMethod(wxCommandEvent &event) {
    method = static_cast<ApplyingMethod>(applying_method_radiobox->GetSelection());
    applyMask(event);
}

void AppGUI::applyMask(wxCommandEvent &event) {
    if ( !image.IsOk() || !mask.IsOk())
        return;

    SetBackgroundColour(wxColor(192, 192, 192));
    canvas->ClearBackground();
    Refresh();

    imageCopy = image.Copy();
    wxColor newColor;
    for (int i = 1; i < imageCopy.GetWidth() - 1; ++i) {
        for (int j = 1; j < imageCopy.GetHeight() - 1; ++j) {
            if ( !isColorTransparent(i, j)) {
                switch (applying_method_radiobox->GetSelection()) {
                    case CHANGE:
                        newColor = changeColors(i, j);
                        break;
                    case SUM:
                        newColor = addColors(i, j);
                        break;
                    case MULTIPLY:
                        newColor = multiplyColors(i, j);
                        break;
                    case SUBTRACT:
                        newColor = subtractColors(i, j);
                        break;
                    case LIGHTEN:
                        newColor = onlyLighten(i, j);
                        break;
                    case DARKEN:
                        newColor = onlyDarken(i, j);
                        break;
                    case DIFFERENCE:
                        newColor = differenceBetweenColors(i, j);
                        break;
                }
                imageCopy.SetRGB(i, j, newColor.Red(), newColor.Green(), newColor.Blue());
            }
        }
    }
}

void AppGUI::changeAlphaLevel(wxScrollEvent &event) {
    applyMask(event);
}

void AppGUI::updateCanvas(wxUpdateUIEvent &event) {
    if (imageCopy.IsOk()) {
        wxBitmap bitmap(imageCopy);
        wxClientDC dc(canvas);
        canvas->DoPrepareDC(dc);
        dc.DrawBitmap(bitmap, 0, 0, true);
    }
}

wxColor AppGUI::addColors(int &i, int &j) {
    const double alpha = alpha_level_slider->GetValue()/100.;
    const double inv_alpha = 1.-alpha;

    int red = alpha*image.GetRed(i, j) + inv_alpha*(image.GetRed(i, j)+mask.GetRed(i, j));
    int green = alpha*image.GetGreen(i, j) + inv_alpha*(image.GetGreen(i, j)+mask.GetGreen(i, j));
    int blue = alpha*image.GetBlue(i, j) + inv_alpha*(image.GetBlue(i, j)+mask.GetBlue(i, j));

    correctColor(red);
    correctColor(green);
    correctColor(blue);

    return wxColor(red, green, blue, alpha);
}

wxColor AppGUI::changeColors(int &i, int &j) {
    const double alpha = (alpha_level_slider->GetValue() / 100.);
    const double inv_alpha = 1.-alpha;

    int red = alpha*image.GetRed(i, j) + inv_alpha*mask.GetRed(i, j);
    int green = alpha*image.GetGreen(i, j) + inv_alpha*mask.GetGreen(i, j);
    int blue = alpha*image.GetBlue(i, j) + inv_alpha*mask.GetBlue(i, j);

    return wxColor(red, green, blue);
}

wxColor AppGUI::multiplyColors(int &i, int &j) {
    const double alpha = alpha_level_slider->GetValue()/100.;
    const double inv_alpha = 1.-alpha;

    int red = alpha * image.GetRed(i, j) + inv_alpha*image.GetRed(i, j)*mask.GetRed(i, j)/255.;
    int green = alpha * image.GetGreen(i, j) + inv_alpha*image.GetGreen(i, j)*mask.GetGreen(i, j)/255.;
    int blue = alpha * image.GetBlue(i, j) + inv_alpha*image.GetBlue(i, j)*mask.GetBlue(i, j)/255.;

    return wxColor(red, green, blue);
}

wxColor AppGUI::subtractColors(int &i, int &j) {
    const double alpha = alpha_level_slider->GetValue()/100.;
    const double inv_alpha = 1.-alpha;

    int red = alpha*image.GetRed(i, j) + inv_alpha*(image.GetRed(i, j)-mask.GetRed(i, j));
    int green = alpha*image.GetGreen(i, j) + inv_alpha*(image.GetGreen(i, j)-mask.GetGreen(i, j));
    int blue = alpha*image.GetBlue(i, j) + inv_alpha*(image.GetBlue(i, j)-mask.GetBlue(i, j));

    correctColor(red);
    correctColor(green);
    correctColor(blue);

    return wxColor(red, green, blue);
}

wxColor AppGUI::differenceBetweenColors(int &i, int &j) {
    const double alpha = alpha_level_slider->GetValue()/100.;
    const double inv_alpha = 1.-alpha;

    int differenceRed = mask.GetRed(i, j) - image.GetRed(i, j);
    if(differenceRed < 0)
        differenceRed *= -1;

    int differenceGreen = mask.GetGreen(i, j) - image.GetGreen(i, j);
    if(differenceGreen < 0)
        differenceGreen *= -1;

    int differenceBlue = mask.GetBlue(i, j) - image.GetBlue(i, j);
    if(differenceBlue < 0)
        differenceBlue *= -1;

    int red = alpha * image.GetRed(i, j) + inv_alpha*differenceRed;
    int green = alpha * image.GetGreen(i, j) + inv_alpha*differenceGreen;
    int blue = alpha * image.GetBlue(i, j) + inv_alpha*differenceBlue;

    return wxColor(red, green, blue);
}

wxColor AppGUI::onlyLighten(int &i, int &j) {
    const double alpha = (alpha_level_slider->GetValue() / 100.);
    const double inv_alpha = 1.-alpha;

    int lighterRed = mask.GetRed(i, j)>image.GetRed(i, j) ? mask.GetRed(i, j) : image.GetRed(i, j);
    int lighterGreen = mask.GetGreen(i, j)>image.GetGreen(i, j) ? mask.GetGreen(i, j) : image.GetGreen(i, j);
    int lighterBlue = mask.GetBlue(i, j)>image.GetBlue(i, j) ?  mask.GetBlue(i, j) : image.GetBlue(i, j);

    int red = alpha * image.GetRed(i, j) + inv_alpha*lighterRed;
    int green = alpha * image.GetGreen(i, j) + inv_alpha*lighterGreen;
    int blue = alpha * image.GetBlue(i, j) + inv_alpha*lighterBlue;

    return wxColor(red, green, blue);
}

wxColor AppGUI::onlyDarken(int &i, int &j) {
    const double alpha = (alpha_level_slider->GetValue() / 100.);
    const double inv_alpha = 1.-alpha;

    int darkerRed = mask.GetRed(i, j) < image.GetRed(i, j) ? mask.GetRed(i, j) : image.GetRed(i, j);
    int darkerGreen = mask.GetGreen(i, j) < image.GetGreen(i, j) ? mask.GetGreen(i, j) : image.GetGreen(i, j);
    int darkerBlue = mask.GetBlue(i, j) < image.GetBlue(i, j) ?  mask.GetBlue(i, j) : image.GetBlue(i, j);

    int red = alpha * image.GetRed(i, j) + inv_alpha*darkerRed;
    int green = alpha * image.GetGreen(i, j) + inv_alpha*darkerGreen;
    int blue = alpha * image.GetBlue(i, j) + inv_alpha*darkerBlue;

    return wxColor(red, green, blue);
}

void AppGUI::correctColor(int &computedColor) {
    if ( computedColor > 255 )
        computedColor = 255;
    else if ( computedColor < 0 )
        computedColor = 0;
}

bool AppGUI::isColorTransparent(int &i, int &j) {
    return mask.GetRed(i, j) == transparencyColor.Red() &&
           mask.GetGreen(i, j) == transparencyColor.Green() &&
           mask.GetBlue(i, j) == transparencyColor.Blue();
}

void AppGUI::saveToFile(wxCommandEvent &event) {
    if ( !image.IsOk())
        return;

    wxFileDialog WxSaveFileDialog(this, wxT("Wybierz lokalizacje do zapisu"), wxT(""), wxT(""),
                                  wxT("Pliki BMP (*.bmp)|*.bmp;|Pliki JPG (*.jpg)|*.jpg|Pliki PNG (*.png)|*.png"),
                                  wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
    wxImage maskToLoad;
    if ( WxSaveFileDialog.ShowModal() == wxID_OK ) {
        imageCopy.SaveFile(WxSaveFileDialog.GetPath());
    }
    WxSaveFileDialog.Destroy();
}
