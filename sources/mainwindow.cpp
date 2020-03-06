#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secdialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    texts.push_back(ui->CountOfGenerators);
    texts.push_back(ui->countOfBuffers);
    texts.push_back(ui->countOfDevices);
    texts.push_back(ui->countOfRequests);
    texts.push_back(ui->alpha);
    texts.push_back(ui->beta);
    texts.push_back(ui->lyambda);

    ui->modeling_error->setVisible(false);

    mainCmoSystem = new MainCMOSystem();

    isModeling = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_modeling_button_clicked()
{
    for(auto text : texts){
        if(is_number(text->toPlainText().toStdString())){
           isModeling = true;
        } else {
           isModeling = false;
           text->setText("Invalid input");
        }
    }

    if(isModeling) {
        std::vector<double> values;
        for(auto &text: texts) {
            values.push_back(text->toPlainText().toDouble());
        }

        mainCmoSystem->init(values);
        mainCmoSystem->generateAllRequests();
        mainCmoSystem->start();
    }
}

void MainWindow::bestParametrs(){
    std::vector<std::vector<double>> values;
    //Generator, buffers, devices, requests, alpha, beta , lyambda;
    values.push_back({4,10,3,2000, 0.5, 1.5, 0.8});
    values.push_back({4,10,2,2000, 0.5, 1.5, 0.9});
    values.push_back({4,10,4,2000, 0.5, 1.5, 0.7});
    values.push_back({2,12,6,2000, 0.5, 1.5, 0.6});
    values.push_back({2,10,6,2000, 0.5, 1.5, 0.6});
    values.push_back({3,12,6,2000, 0.5, 1.5, 0.6});

    BestParametrs *bestparametrs = new BestParametrs();
    bestparametrs->initTable(values.size());
    bestparametrs->show();

    for(auto &val : values){
        MainCMOSystem *mainsystemd = new MainCMOSystem();
        mainsystemd->init(val);
        mainsystemd->generateAllRequests();
        mainsystemd->start();

        double deviceUs = 0;
        std::cout << " max : " << mainsystemd->getMaxRealizationTime() << std::endl;


        for(auto&dev: mainsystemd->getDevices()){
            deviceUs += dev.getWorkingTime() / mainsystemd->getMaxRealizationTime();
            std::cout << " working: " << dev.getWorkingTime() << " max : " << mainsystemd->getMaxRealizationTime() << std::endl;
        }

        double reject = 0;
        double waiting = 0;

        for(auto& gen : mainsystemd->getResults()){
            reject = reject + ((double)gen.getCountOfRejectedApplications()/(double)gen.getGeneratedRequests());
            waiting += ((double)gen.getWaitingTime() / (double)gen.getGeneratedRequests());
        }

        bestparametrs->insertRow(val.at(0),val.at(1),val.at(2),val.at(3),val.at(4),val.at(5),val.at(6),
                                 reject / (double)val.at(0),
                                 waiting / val.at(0),(double)deviceUs / val.at(2));

    }

}

bool MainWindow::is_number(const std::string& s)
{
  return !s.empty() && std::find_if(s.begin(),
      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void MainWindow::on_results_button_clicked()
{
   results = new resultsTable();
   results->initTable(mainCmoSystem->getCountGenerators(), mainCmoSystem->getCountDevices());

   for(auto& gen : mainCmoSystem->getResults()){
       results->insertRow(gen.getGeneratedRequests(),                      // generated
                 gen.getCountOfProcessedApplications(),                    // processed
                 gen.getCountOfRejectedApplications(),                     // rejected
                 (double)gen.getCountOfRejectedApplications()/(double)gen.getGeneratedRequests(),  // reject prob
                 gen.getWorkingTime()/gen.getGeneratedRequests() + gen.getWaitingTime()/gen.getGeneratedRequests(), // time in system
                 (double)gen.getWaitingTime() / (double)gen.getGeneratedRequests(), // waiting disp
                 gen.getWorkingTime()/ gen.getGeneratedRequests()); // servising disp

   }

   std::cout << "max time : " << mainCmoSystem->getMaxRealizationTime() << std::endl;

   for(auto& dev : mainCmoSystem->getDevices()){
       results->insertDevice(dev.getWorkingTime() / mainCmoSystem->getMaxRealizationTime()); // device usage
   }
   results->insertAverageResults();
   results->show();
}

void MainWindow::showResults(){
   mainCmoSystem->getResults();
}

void MainWindow::on_simple_modeling_button_clicked()
{
    SecDialog *secdialog = new SecDialog();
    secdialog->setModal(true);
    secdialog->show();

    std::vector<double> values;
    for(auto &text: texts) {
        values.push_back(text->toPlainText().toDouble());
    }

    secdialog->setSystem(mainCmoSystem);
    secdialog->setValues(values);
}

void MainWindow::on_pushButton_clicked()
{
    bestParametrs();
}
