///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 16 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __APPGUIBASE_H__
#define __APPGUIBASE_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/clrpicker.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/scrolwin.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class AppGUIBase
///////////////////////////////////////////////////////////////////////////////
class AppGUIBase : public wxFrame {
private:

protected:
    wxButton *read_img_button;
    wxButton *read_mask_btn;
    wxColourPickerCtrl *mask_color_picker;
    wxRadioBox *applying_method_radiobox;
    wxButton *save_to_file;
    wxButton *apply_mask_btn;
    wxStaticLine *m_staticline1;
    wxStaticText *alpha_label;
    wxSlider *alpha_level_slider;
    wxScrolledWindow *canvas;

    // Virtual event handlers, overide them in your derived class
    virtual void readImgPath(wxCommandEvent &event) { event.Skip(); }
    virtual void readMaskPath(wxCommandEvent &event) { event.Skip(); }
    virtual void changeTransparencyColor(wxColourPickerEvent &event) { event.Skip(); }
    virtual void changeApplyingMethod(wxCommandEvent &event) { event.Skip(); }
    virtual void applyMask(wxCommandEvent &event) { event.Skip(); }
    virtual void saveToFile(wxCommandEvent &event) { event.Skip(); }
    virtual void changeAlphaLevel(wxScrollEvent &event) { event.Skip(); }
    virtual void updateCanvas(wxUpdateUIEvent &event) { event.Skip(); }

public:

    AppGUIBase(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &title = wxEmptyString,
               const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize(800, 600),
               long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

    ~AppGUIBase();

};

#endif //__APPGUIBASE_H__
