#include "../headers/App.h"
#include "../headers/AppGUI.h"

IMPLEMENT_APP(App)

bool App::OnInit() {
    auto * window = new AppGUI(nullptr);
    SetTopWindow(window);
    window->Show();
    return wxAppConsoleBase::OnInit();
}

int App::OnExit() {
    return wxAppBase::OnExit();
}
