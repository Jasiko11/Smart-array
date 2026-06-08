

#ifndef TUI_INTERFACE_H
#define TUI_INTERFACE_H

#include "Manager.h"
#include <ftxui/component/screen_interactive.hpp>
#include <string>

class TuiInterface {
public:
    TuiInterface();
    ~TuiInterface();
    void render();

private:
    ftxui::ScreenInteractive screen;
    StudentManager manager;

    void renderListStudents();
    void renderAddStudent();
    void renderRemoveStudent();
    void renderFiles();
    void renderCount();
    void renderEditStudent();
    void renderListByRange();
    void renderSingleStudent();
    void renderShortList();

    double safe_stod(const std::string& str);
    int safe_stoi(const std::string& str);
};

#endif // TUI_INTERFACE_H