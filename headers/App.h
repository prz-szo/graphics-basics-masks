#ifndef PROJEKT_GFK_16_APP_H
#define PROJEKT_GFK_16_APP_H

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif


class App : public wxApp {
public:
	bool OnInit() override;
	int OnExit() override;
};


#endif //PROJEKT_GFK_16_APP_H
