#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTextEdit>
#include <QButtonGroup>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>


#include "secdialog.h"
#include "resultstable.h"
#include "bestparametrs.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);

        ~MainWindow();
        bool is_number(const std::string& s);
        int getDelay();
        void bestParametrs();
        void showResults();

   private slots:

        void on_results_button_clicked();
        void on_modeling_button_clicked();
        void on_simple_modeling_button_clicked();

        void on_pushButton_clicked();

private:
        MainCMOSystem* mainCmoSystem;

   private:
        QVBoxLayout *layout;
        bool isModeling;
        resultsTable *results;
        std::vector<QTextEdit*> texts;

    private:
        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
