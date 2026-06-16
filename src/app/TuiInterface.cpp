#include "TuiInterface.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>
#include <utility>

using namespace ftxui;

TuiInterface::TuiInterface() : screen(ScreenInteractive::Fullscreen()) {}

double TuiInterface::safe_stod(const std::string& str) {
    try {
        return std::stod(str.empty() ? "0" : str);
    }
    catch (...) {
        return 0.0;
    }
}

int TuiInterface::safe_stoi(const std::string& str) {
    try {
        return std::stoi(str.empty() ? "0" : str);
    }
    catch (...) {
        return 0;
    }
}

void TuiInterface::render() {
    std::vector<std::string> menuEndpoints = {
        "Lista studentow",
        "Skrocona lista",
        "Lista z zakresu",
        "Wyswietl element",
        "Wyszukaj po dowolnym polu",
        "Srednia",
        "Liczba elementow",
        "Dodaj studenta",
        "Edytuj studenta",
        "Usun studenta",
        "Zapisz / Wczytaj dane",
        "Zamknij aplikacje"
    };
    int selectedItems = 0;

    MenuOption menuOpt;
    menuOpt.on_enter = screen.ExitLoopClosure();
    auto menu = Menu(&menuEndpoints, &selectedItems, menuOpt);

    auto rend = Renderer(menu, [&] {
        return window(text(" Baza Studentow "),
            vbox({
                text("Wybierz akcje:"),
                separator(),
                menu->Render()
            })
        ) | yframe | yflex | vscroll_indicator;
    });

    bool isWorking = true;
    while (isWorking) {
        screen.Loop(rend);
        screen.Clear();

        const std::string& selected = menuEndpoints[selectedItems];

        if (selected == "Lista studentow") {
            renderListStudents();
        }
        else if (selected == "Skrocona lista") {
            renderShortList();
        }
        else if (selected == "Lista z zakresu") {
            renderListByRange();
        }
        else if (selected == "Wyswietl element") {
            renderSingleStudent();
        }
        else if (selected == "Wyszukaj po dowolnym polu") {
            renderSearchByField();
        }
        else if (selected == "Srednia") {
            renderSrednia();
        }
        else if (selected == "Liczba elementow") {
            renderCount();
        }
        else if (selected == "Dodaj studenta") {
            renderAddStudent();
        }
        else if (selected == "Edytuj studenta") {
            renderEditStudent();
        }
        else if (selected == "Usun studenta") {
            renderRemoveStudent();
        }
        else if (selected == "Zapisz / Wczytaj dane") {
            renderFiles();
        }
        else if (selected == "Zamknij aplikacje") {
            isWorking = false;
        }
    }
}

void TuiInterface::renderListStudents() {
    auto okButton = Button("Wroc do menu", screen.ExitLoopClosure());
    auto navContainer = Container::Vertical({okButton});

    auto rend = Renderer(navContainer, [&] {
        Elements list_elements;
        list_elements.push_back(text("Liczba studentow w bazie: " + std::to_string(manager.getCount())) | bold);
        list_elements.push_back(separator());

        for (unsigned i = 0; i < manager.getCount(); ++i) {
            Student s = manager.getStudent(i);
            std::string info = "[" + std::to_string(i) + "] " + s.name + " " + s.surname +
                               " | Indeks: " + std::to_string(s.indexNumber) +
                               " | Rok: " + std::to_string(s.year) +
                               " | GPA: " + std::to_string(s.gpa);
            list_elements.push_back(text(info));
        }

        if (manager.getCount() == 0) {
            list_elements.push_back(text("Baza jest pusta."));
        }

        list_elements.push_back(separator());
        list_elements.push_back(hbox({filler(), okButton->Render(), filler()}));

        return window(text("Lista Studentow"), vbox(std::move(list_elements))) | yframe | yflex | vscroll_indicator;
    });

    screen.Loop(rend);
    screen.Clear();
}

void TuiInterface::renderAddStudent() {
    std::string name, surname, index, year, gpa;
    std::string statusMsg;

    InputOption inputOpt;
    inputOpt.multiline = false;

    auto input_name = Input(&name, inputOpt);
    auto input_surname = Input(&surname, inputOpt);
    auto input_index = Input(&index, inputOpt);
    auto input_year = Input(&year, inputOpt);
    auto input_gpa = Input(&gpa, inputOpt);

    auto btn_add = Button("Zapisz", [&] {
        Student s;
        s.name = name;
        s.surname = surname;
        s.indexNumber = safe_stoi(index);
        s.year = safe_stoi(year);
        s.gpa = safe_stod(gpa);
        manager.addStudent(s);
        statusMsg = "Dodano studenta: " + name + " " + surname;

        name = ""; surname = ""; index = ""; year = ""; gpa = "";
    });

    auto btn_back = Button("Wroc", screen.ExitLoopClosure());

    auto navContainer = Container::Vertical({
        input_name, input_surname, input_index, input_year, input_gpa, btn_add, btn_back
    });

    auto rend = Renderer(navContainer, [&] {
        return window(text(" Dodawanie Studenta "), vbox({
            hbox({text("Imie:       "), input_name->Render()}),
            hbox({text("Nazwisko:   "), input_surname->Render()}),
            hbox({text("Nr indeksu: "), input_index->Render()}),
            hbox({text("Rok studiow:"), input_year->Render()}),
            hbox({text("Srednia:    "), input_gpa->Render()}),
            separator(),
            text(statusMsg) | color(Color::Green),
            separator(),
            vbox({btn_add->Render(), filler(), btn_back->Render()})
        })) | yframe | yflex | vscroll_indicator;
    });

    screen.Loop(rend);
    screen.Clear();
}

void TuiInterface::renderRemoveStudent() {
    std::string index_str;
    std::string statusMsg;

    InputOption inputOpt;
    inputOpt.multiline = false;
    auto input_id = Input(&index_str, "Podaj ID (np. 0, 1...)", inputOpt);

    auto btn_remove = Button("Usun", [&] {
        unsigned idx = safe_stoi(index_str);
        if (manager.removeStudent(idx)) {
            statusMsg = "Usunieto studenta o ID: " + index_str;
        } else {
            statusMsg = "Blad: Nie znaleziono studenta o podanym ID!";
        }
        index_str = "";
    });

    auto btn_back = Button("Wroc", screen.ExitLoopClosure());

    auto navContainer = Container::Vertical({input_id, btn_remove, btn_back});

    auto rend = Renderer(navContainer, [&] {
        return window(text(" Usun Studenta "), vbox({
            text("Aby usunac studenta, podaj jego pozycje (ID) z listy."),
            separator(),
            hbox({text("ID studenta: "), input_id->Render()}),
            separator(),
            text(statusMsg) | color(Color::Yellow),
            separator(),
            vbox({btn_remove->Render(), filler(), btn_back->Render()})
        })) | yframe | yflex | vscroll_indicator;
    });

    screen.Loop(rend);
    screen.Clear();
}

void TuiInterface::renderFiles() {
    std::string filename = "data.bin";
    std::string statusMsg;

    InputOption inputOpt;
    inputOpt.multiline = false;
    auto input_file = Input(&filename, inputOpt);

    auto btn_save = Button("Zapisz", [&] {
        if (manager.saveToBinaryFile(filename)) statusMsg = "Zapisano poprawnie.";
        else statusMsg = "Blad zapisu!";
    });

    auto btn_load = Button("Wczytaj", [&] {
        if (manager.loadFromBinaryFile(filename)) statusMsg = "Wczytano poprawnie.";
        else statusMsg = "Blad odczytu!";
    });

    auto btn_back = Button("Wroc", screen.ExitLoopClosure());

    auto navContainer = Container::Vertical({input_file, btn_save, btn_load, btn_back});

    auto rend = Renderer(navContainer, [&] {
        return window(text(" Obsluga Pliku "), vbox({
            hbox({text("Nazwa pliku: "), input_file->Render()}),
            separator(),
            text(statusMsg) | color(Color::Green),
            separator(),
            vbox({btn_save->Render(), btn_load->Render(), filler(), btn_back->Render()})
        })) | yframe | yflex | vscroll_indicator;
    });

    screen.Loop(rend);
    screen.Clear();
}

void TuiInterface::renderCount() {
    auto btn_back = Button("Wroc", screen.ExitLoopClosure());
    auto navContainer = Container::Vertical({btn_back});

    auto rend = Renderer(navContainer, [&] {
        return window(text(" Liczba Elementow "), vbox({
            text("Aktualna liczba studentow w bazie: " + std::to_string(manager.getCount())) | bold,
            separator(),
            vbox({filler(), btn_back->Render(), filler()})
        })) | yframe | yflex | vscroll_indicator;
    });

    screen.Loop(rend);
    screen.Clear();
}

void TuiInterface::renderEditStudent() {
    std::string target_id;
    std::string name, surname, index, year, gpa;
    std::string statusMsg = "Podaj ID studenta z listy i kliknij 'Wczytaj'.";

    InputOption inputOpt;
    inputOpt.multiline = false;

    auto input_id = Input(&target_id, "ID...", inputOpt);
    auto input_name = Input(&name, inputOpt);
    auto input_surname = Input(&surname, inputOpt);
    auto input_index = Input(&index, inputOpt);
    auto input_year = Input(&year, inputOpt);
    auto input_gpa = Input(&gpa, inputOpt);

    auto btn_load = Button("Wczytaj", [&] {
        unsigned idx = safe_stoi(target_id);
        if (target_id.empty()) {
            statusMsg = "Podaj najpierw ID!";
            return;
        }
        if (idx < manager.getCount()) {
            Student s = manager.getStudent(idx);
            name = s.name;
            surname = s.surname;
            index = std::to_string(s.indexNumber);
            year = std::to_string(s.year);
            gpa = std::to_string(s.gpa);
            statusMsg = "Wczytano dane. Mozesz je teraz edytowac i zapisac.";
        } else {
            statusMsg = "Blad: Nie znaleziono studenta o podanym ID!";
        }
    });

    auto btn_save = Button("Zapisz zmiany", [&] {
        unsigned idx = safe_stoi(target_id);
        if (idx < manager.getCount()) {
            Student s;
            s.name = name;
            s.surname = surname;
            s.indexNumber = safe_stoi(index);
            s.year = safe_stoi(year);
            s.gpa = safe_stod(gpa);
            if (manager.editStudent(idx, s)) {
                statusMsg = "Zapisano zmiany dla studenta ID: " + target_id;
            } else {
                statusMsg = "Blad podczas zapisu edycji!";
            }
        } else {
            statusMsg = "Blad: Nieprawidlowe ID przed zapisem!";
        }
    });

    auto btn_back = Button("Wroc", screen.ExitLoopClosure());

    auto navContainer = Container::Vertical({
        input_id, btn_load,
        input_name, input_surname, input_index, input_year, input_gpa,
        btn_save, btn_back
    });

    auto rend = Renderer(navContainer, [&] {
        return window(text(" Edycja Studenta "), vbox({
            hbox({text("ID do edycji: "), input_id->Render(), text(" "), btn_load->Render()}),
            separator(),
            hbox({text("Imie:       "), input_name->Render()}),
            hbox({text("Nazwisko:   "), input_surname->Render()}),
            hbox({text("Nr indeksu: "), input_index->Render()}),
            hbox({text("Rok studiow:"), input_year->Render()}),
            hbox({text("Srednia:    "), input_gpa->Render()}),
            separator(),
            text(statusMsg) | color(Color::Yellow),
            separator(),
            vbox({btn_save->Render(), filler(), btn_back->Render()})
        })) | yframe | yflex | vscroll_indicator;
    });

    screen.Loop(rend);
    screen.Clear();
}

void TuiInterface::renderListByRange() {
    std::string start_str;
    std::string end_str;

    InputOption inputOpt;
    inputOpt.multiline = false;

    auto input_start = Input(&start_str, "Od...", inputOpt);
    auto input_end = Input(&end_str, "Do...", inputOpt);

    auto btn_back = Button("Wroc", screen.ExitLoopClosure());

    auto navContainer = Container::Vertical({
        input_start,
        input_end,
        btn_back
    });

    auto rend = Renderer(navContainer, [&] {
        int start_idx = safe_stoi(start_str);
        int end_idx = safe_stoi(end_str);
        unsigned count = manager.getCount();

        int safe_start = start_idx < 0 ? 0 : start_idx;
        unsigned safe_end = end_idx >= count ? (count > 0 ? count - 1 : 0) : end_idx;

        Elements list_elements;

        if (count == 0) {
            list_elements.push_back(text("Baza jest pusta."));
        } else if (start_idx > end_idx || safe_start > safe_end) {
            list_elements.push_back(text("Podano nieprawidlowy zakres.") | color(Color::Red));
        } else {
            for (int i = safe_start; i <= safe_end; ++i) {
                Student s = manager.getStudent(i);
                std::string info = "[" + std::to_string(i) + "] " + s.name + " " + s.surname +
                                   " | Indeks: " + std::to_string(s.indexNumber) +
                                   " | Rok: " + std::to_string(s.year) +
                                   " | GPA: " + std::to_string(s.gpa);
                list_elements.push_back(text(info));
            }
        }

        return window(text(" Wyswietlanie Zakresu "), vbox({
            vbox({
                text("Od indeksu: "), input_start->Render() | size(WIDTH, EQUAL, 10),
                text("Do indeksu: "), input_end->Render() | size(WIDTH, EQUAL, 10)
            }),
            separator(),
            vbox(std::move(list_elements)),
            separator(),
            btn_back->Render()
        })) | yframe | yflex | vscroll_indicator;
    });

    screen.Loop(rend);
    screen.Clear();
}

void TuiInterface::renderSingleStudent() {
    std::string index_str;

    InputOption inputOpt;
    inputOpt.multiline = false;

    auto input_id = Input(&index_str, "Podaj indeks...", inputOpt);
    auto btn_back = Button("Wroc", screen.ExitLoopClosure());

    auto navContainer = Container::Vertical({
        input_id,
        btn_back
    });

    auto rend = Renderer(navContainer, [&] {
        Elements details;

        if (index_str.empty()) {
            details.push_back(text("Wpisz numer indeksu (pozycji na liscie), aby zobaczyc dane."));
        } else {
            int idx = safe_stoi(index_str);
            unsigned count = manager.getCount();

            if (count == 0) {
                details.push_back(text("Baza jest pusta.") | color(Color::Red));
            } else if (idx < 0 || idx >= count) {
                details.push_back(text("Indeks poza zakresem! Dostepne indeksy: 0 - " + std::to_string(count - 1)) | color(Color::Red));
            } else {
                Student s = manager.getStudent(idx);
                details.push_back(text("Znaleziono studenta:") | bold | color(Color::Green));
                details.push_back(separator());
                details.push_back(text("Imie:       " + s.name));
                details.push_back(text("Nazwisko:   " + s.surname));
                details.push_back(text("Nr indeksu: " + std::to_string(s.indexNumber)));
                details.push_back(text("Rok studiow:" + std::to_string(s.year)));
                details.push_back(text("Srednia:    " + std::to_string(s.gpa)));
            }
        }

        return window(text(" Pojedynczy Element "), vbox({
            hbox({text("Indeks z listy: "), input_id->Render() | size(WIDTH, EQUAL, 15)}),
            separator(),
            vbox(std::move(details)),
            separator(),
            btn_back->Render()
        })) | yframe | yflex | vscroll_indicator;
    });

    screen.Loop(rend);
    screen.Clear();
}

void TuiInterface::renderSearchByField() {
    std::string val_name, val_surname, val_index, val_year, val_gpa;

    std::string statusMsg;

    InputOption inputOpt;
    inputOpt.multiline = false;

    auto in_name = Input(&val_name, "Wpisz imię...", inputOpt);
    auto in_surname = Input(&val_surname, "Wpisz nazwisko...", inputOpt);
    auto in_index = Input(&val_index, "Wpisz numer indeksu...", inputOpt);
    auto in_year = Input(&val_year, "Wpisz rok studiów...", inputOpt);
    auto in_gpa = Input(&val_gpa, "Wpisz GPA...", inputOpt);

    auto btn_search = Button("Szukaj", [&] {
        std::map<std::string, std::string> criteria;

        if (!val_name.empty()) criteria["name"] = val_name;
        if (!val_surname.empty()) criteria["surname"] = val_surname;
        if (!val_index.empty()) criteria["index"] = val_index;
        if (!val_year.empty()) criteria["year"] = val_year;
        if (!val_gpa.empty()) criteria["gpa"] = val_gpa;

        if (criteria.empty()) {
            statusMsg = "Podaj wartość dla przynajmniej jednego pola.";
            return;
        }

        SmartArray<Student> results = manager.searchByField(criteria);

        if (results.size() == 0) {
            statusMsg = "Brak wynikow dla podanych kryteriów.";
        } else {
            std::string out = "Znaleziono " + std::to_string(results.size()) + " wynikow:\n";
            for (unsigned i = 0; i < results.size(); ++i) {
                Student s = results.at(i);
                out += s.name + " " + s.surname + " | Indeks: " + std::to_string(s.indexNumber)
                       + " | Rok: " + std::to_string(s.year) + " | GPA: " + std::to_string(s.gpa);
                if (i + 1 < results.size()) out += "\n";
            }
            statusMsg = out;
        }
    });

    auto btn_back = Button("Wroc", screen.ExitLoopClosure());

    auto form_container = Container::Vertical({
        in_name,
        in_surname,
        in_index,
        in_year,
        in_gpa,
        btn_search,
        btn_back
    });

    auto rend = Renderer(form_container, [&] {
        Elements elems;
        elems.push_back(text("Wyszukiwanie zaawansowane (wiele kryteriów)") | bold);
        elems.push_back(separator());
        elems.push_back(text("Wypełnij dowolne pola. Puste zostaną zignorowane."));
        elems.push_back(separator());

        auto make_row = [](const std::string &label, Element input_el) {
            return hbox({ text(label) | size(WIDTH, EQUAL, 12), std::move(input_el) | size(WIDTH, EQUAL, 30) });
        };

        elems.push_back(make_row("Imię:", in_name->Render()));
        elems.push_back(make_row("Nazwisko:", in_surname->Render()));
        elems.push_back(make_row("Indeks:", in_index->Render()));
        elems.push_back(make_row("Rok:", in_year->Render()));
        elems.push_back(make_row("GPA:", in_gpa->Render()));
        elems.push_back(separator());

        if (!statusMsg.empty()) {
            elems.push_back(paragraph(statusMsg) | color(Color::Green));
            elems.push_back(separator());
        }

        elems.push_back(vbox({ btn_search->Render(), filler(), btn_back->Render() }));

        return window(text(" Wyszukaj studentów "), vbox(std::move(elems))) | yframe | yflex | vscroll_indicator;
    });

    screen.Loop(rend);
    screen.Clear();
}

void TuiInterface::renderShortList() {
    auto okButton = Button("Wroc do menu", screen.ExitLoopClosure());
    auto navContainer = Container::Vertical({okButton});

    auto rend = Renderer(navContainer, [&] {
        Elements list_elements;
        list_elements.push_back(text("Liczba studentow w bazie: " + std::to_string(manager.getCount())) | bold);
        list_elements.push_back(separator());

        for (unsigned i = 0; i < manager.getCount(); ++i) {
            Student s = manager.getStudent(i);
            std::string info = "[" + std::to_string(i) + "] " + s.name + " " + s.surname;
            list_elements.push_back(text(info));
        }

        if (manager.getCount() == 0) {
            list_elements.push_back(text("Baza jest pusta."));
        }

        list_elements.push_back(separator());
        list_elements.push_back(hbox({filler(), okButton->Render(), filler()}));

        return window(text("Lista Studentow"), vbox(std::move(list_elements))) | yframe | yflex | vscroll_indicator;
    });

    screen.Loop(rend);
    screen.Clear();
}

void TuiInterface::renderSrednia() {
    std::string year_str;
    std::string statusMsg;

    InputOption inputOpt;
    inputOpt.multiline = false;

    auto input_year = Input(&year_str, "Rok (opcjonalnie)...", inputOpt);
    auto btn_calc = Button("Oblicz", [&] {
        unsigned total = manager.getCount();
        if (total == 0) {
            statusMsg = "Baza jest pusta.";
            return;
        }

        double avg_all = manager.calculateAverageGpa();
        std::string res = "Srednia ocen (wszyscy studenci): " + std::to_string(avg_all);

        if (!year_str.empty()) {
            int year = safe_stoi(year_str);
            double avgY = manager.calculateAverageGpaForYear(year);

            if (manager.getCount() == 0) {
                res += "\nBrak studentow z roku " + year_str + ".";
            } else {
                res += "\nSrednia dla roku " + year_str + ": " + std::to_string(avgY);
            }
        }

        statusMsg = res;
    });

    auto btn_back = Button("Wroc", screen.ExitLoopClosure());

    auto navContainer = Container::Vertical({ input_year, btn_calc, btn_back });

    auto rend = Renderer(navContainer, [&] {
        Elements elems;
        elems.push_back(text("Obliczanie sredniej ocen") | bold);
        elems.push_back(separator());
        elems.push_back(hbox({
            text("Rok: "), input_year->Render() | size(WIDTH, EQUAL, 10)
        }));
        elems.push_back(separator());

        if (statusMsg.empty()) {
            elems.push_back(text("Wpisz rok (opcjonalnie) i kliknij 'Oblicz'."));
        } else {
            elems.push_back(text(statusMsg) | color(Color::Green));
        }

        elems.push_back(separator());
        elems.push_back(vbox({ btn_calc->Render(), filler(), btn_back->Render() }));

        return window(text(" Srednia "), vbox(std::move(elems)));
    });

    screen.Loop(rend);
    screen.Clear();
}
