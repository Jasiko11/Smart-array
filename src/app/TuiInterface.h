#ifndef TUI_INTERFACE_H
#define TUI_INTERFACE_H

#include "Manager.h"
#include <ftxui/component/screen_interactive.hpp>
#include <string>

/**
 * @brief Tekstowy interfejs użytkownika (TUI) do obsługi bazy studentów.
 *
 * Klasa odpowiada za prezentację menu, formularzy oraz ekranów operacji
 * wykonywanych na danych zarządzanych przez klasę StudentManager.
 */
class TuiInterface {
public:
    /**
     * @brief Tworzy interfejs TUI i inicjalizuje widok pełnoekranowy.
     */
    TuiInterface();

    /**
     * @brief Uruchamia główną pętlę aplikacji i menu nawigacyjne.
     */
    void render();

private:
    ftxui::ScreenInteractive screen;
    StudentManager manager;

    /**
     * @brief Wyświetla pełną listę studentów z kompletem danych.
     */
    void renderListStudents();

    /**
     * @brief Wyświetla formularz dodawania nowego studenta.
     */
    void renderAddStudent();

    /**
     * @brief Wyświetla ekran usuwania studenta po pozycji na liście.
     */
    void renderRemoveStudent();

    /**
     * @brief Wyświetla ekran zapisu i odczytu danych z pliku binarnego.
     */
    void renderFiles();

    /**
     * @brief Wyświetla aktualną liczbę studentów w bazie.
     */
    void renderCount();

    /**
     * @brief Wyświetla formularz edycji danych istniejącego studenta.
     */
    void renderEditStudent();

    /**
     * @brief Wyświetla studentów z zakresu indeksów pozycji na liście.
     */
    void renderListByRange();

    /**
     * @brief Wyświetla szczegóły pojedynczego studenta na podstawie pozycji.
     */
    void renderSingleStudent();

    /**
     * @brief Wyświetla skróconą listę studentów (podstawowe dane).
     */
    void renderShortList();

    /**
     * @brief Wyświetla ekran obliczania średniej ocen.
     */
    void renderSrednia();

    /**
     * @brief Wyświetla ekran wyszukiwania studentów po wielu kryteriach.
     */
    void renderSearchByField();

    /**
     * @brief Bezpiecznie konwertuje tekst na liczbę zmiennoprzecinkową.
     * @param str Tekst wejściowy.
     * @return Wartość typu double lub 0.0 przy błędzie konwersji.
     */
    double safe_stod(const std::string& str);

    /**
     * @brief Bezpiecznie konwertuje tekst na liczbę całkowitą.
     * @param str Tekst wejściowy.
     * @return Wartość typu int lub 0 przy błędzie konwersji.
     */
    int safe_stoi(const std::string& str);
};

#endif // TUI_INTERFACE_H