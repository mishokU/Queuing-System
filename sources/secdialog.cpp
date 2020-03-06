#include "secdialog.h"
#include "ui_secdialog.h"

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);

    waitCond = new QWaitCondition();

    count_of_request = ui->requests;
    priority_request = ui->priority_request;
    progress_bar = ui->progressBar;

    mMinStep = ui->min_step;
    mMaxStep = ui->max_step;

    mCurrentStep = ui->current_step;

    systemTime = ui->system_time;

    generators.push_back(ui->first_generator);
    generators.push_back(ui->second_generator);
    generators.push_back(ui->third_generator);
    generators.push_back(ui->fourth_generator);

    buffers.push_back(ui->first_buffer);
    buffers.push_back(ui->second_buffer);
    buffers.push_back(ui->third_buffer);
    buffers.push_back(ui->fourth_buffer);

    devices.push_back(ui->first_device);
    devices.push_back(ui->second_device);
    devices.push_back(ui->third_device);
    devices.push_back(ui->fourth_device);

    rejected_cells.push_back(ui->first_rej);
    rejected_cells.push_back(ui->first_rej);
    rejected_cells.push_back(ui->second_rej);
    rejected_cells.push_back(ui->third_rej);
    rejected_cells.push_back(ui->fourth_rej);

    buffer_references.push_back(ui->first_ref);
    buffer_references.push_back(ui->second_ref);
    buffer_references.push_back(ui->third_ref);
    buffer_references.push_back(ui->fourth_ref);

    setBufferRef(1);

    device_release_time.push_back(ui->first_device_rel_time);
    device_release_time.push_back(ui->second_device_rel_time);
    device_release_time.push_back(ui->third_device_rel_time);
    device_release_time.push_back(ui->fourth_device_rel_time);

    device_references.push_back(ui->first_dev_ref);
    device_references.push_back(ui->second_dev_ref);
    device_references.push_back(ui->third_dev_ref);
    device_references.push_back(ui->fourth_dev_ref);

    setDeviceRef(1);
}

void SecDialog::setSystem(MainCMOSystem *system){
    CMOsystem = system;
}

void SecDialog::setSystemTime(double system_time){
    systemTime->setText(QString::number(system_time));
}

void SecDialog::setValues(std::vector<double> values){

    if(steps.size() == 0) {
        CMOsystem->init(values);
        CMOsystem->generateAllRequests();
        CMOsystem->setSteps(&steps);
        CMOsystem->start();
        CMOsystem->getResults();
    }
    mMaxStep->setText(QString::number(steps.size()));
    mMinStep->setText("0");

    progress_bar->setMaximum(steps.size());
}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::setMaxProgressBar(unsigned long max){
    progress_bar->setMaximum((int)max);
}

void SecDialog::setDeviceRef(int device){

    for(QTextEdit *dev_ref : device_references){
        dev_ref->setText("");
    }

    if(device == 1){
       device_references.at(0)->setText("->");
    } else if(device == 2){
        device_references.at(1)->setText("->");
     } else if(device == 3){
        device_references.at(2)->setText("->");
     } else if(device == 4){
        device_references.at(3)->setText("->");
     }
}

void SecDialog::clearDevices(){
    for(QTextEdit *text : devices){
        text->setText("");
    }
}

void SecDialog::clearGenerators(){
    for(QTextEdit *text : generators){
        text->setText("");
    }
}

void SecDialog::clearBuffers(){
    for(QTextEdit *text : buffers){
        text->setText("");
    }
}

void SecDialog::clearAll(){
    clearDevices();
    clearBuffers();
    clearGenerators();
}

void SecDialog::setGenerator(int generator, double time) {

    clearGenerators();

    if(generator == 1){
        generators.at(0)->setText(QString::number(generator) + "\n" + QString::number(time));
    } else if(generator == 2){
        generators.at(1)->setText(QString::number(generator) + "\n" + QString::number(time));
    } else if(generator == 3){
        generators.at(2)->setText(QString::number(generator) + "\n" + QString::number(time));
    } else if(generator == 4){
        generators.at(3)->setText(QString::number(generator) + "\n" + QString::number(time));
    }
}

void SecDialog::setBuffer(int buffer, int generator, double time){

    clearGenerators();

    if(buffer == 1){
       buffers.at(3)->setText(QString::number(generator) + "\n" + QString::number(time));
    } else if(buffer == 2){
       buffers.at(2)->setText(QString::number(generator) + "\n" + QString::number(time));
    } else if(buffer == 3){
       buffers.at(1)->setText(QString::number(generator) + "\n" + QString::number(time));
    } else if(buffer == 4){
       buffers.at(0)->setText(QString::number(generator) + "\n" + QString::number(time));
    }
}

void SecDialog::getBufferCell(int cell, int generator, double time){

    if(cell == 1){
       buffers.at(3)->setText("");
    } else if(cell == 2){
       buffers.at(2)->setText("");
    } else if(cell == 3){
       buffers.at(1)->setText("");
    } else if(cell == 4){
       buffers.at(0)->setText("");
    }
    priority_request->setText(QString::number(generator) + "\n" + QString::number(time));
}

void SecDialog::setRejectedCell(Cell &cell){

    for(QTextEdit *text : rejected_cells){
        text->setText("");
    }

    if(cell.getNumber() == 1){
       buffers.at(3)->setText("");
       rejected_cells.at(3)->setText("^\n|");
    } else if(cell.getNumber() == 2){
       buffers.at(2)->setText("");
       rejected_cells.at(2)->setText("^\n|");
    } else if(cell.getNumber() == 3){
       buffers.at(1)->setText("");
       rejected_cells.at(1)->setText("^\n|");

    } else if(cell.getNumber() == 4){
       buffers.at(0)->setText("");
       rejected_cells.at(0)->setText("^\n|");

    }
}

void SecDialog::setProgress(int progress){
    progress_bar->setValue(progress);
}

void SecDialog::setBufferRef(int reference){
    for(QTextEdit *refs: buffer_references){
        refs->setText("");
    }

    if(reference == 1){
       buffer_references.at(3)->setText("|\n&");
    } else if(reference == 2){
        buffer_references.at(2)->setText("|\n&");
     } else if(reference == 3){
        buffer_references.at(1)->setText("|\n&");
     } else if(reference == 4){
        buffer_references.at(0)->setText("|\n&");
     }
}

void SecDialog::setDeviceReleaseTime(int device, double time){

    if(device == 1){
       device_release_time.at(0)->setText(QString::number(time));
    } else if(device == 2){
       device_release_time.at(1)->setText(QString::number(time));
    } else if(device == 3){
       device_release_time.at(2)->setText(QString::number(time));
    } else if(device == 4){
       device_release_time.at(3)->setText(QString::number(time));
    }
}

void SecDialog::setDevice(int device, int generator, double time){

    priority_request->setText("");
    if(device == 1){
       devices.at(0)->setText(QString::number(generator) + "\n" + QString::number(time));
    } else if(device == 2){
       devices.at(1)->setText(QString::number(generator) + "\n" + QString::number(time));
    } else if(device == 3){
       devices.at(2)->setText(QString::number(generator) + "\n" + QString::number(time));
    } else if(device == 4){
       devices.at(3)->setText(QString::number(generator) + "\n" + QString::number(time));
    }
}

void SecDialog::setRequests(int count){
   count_of_request->setText(QString::number(count));
}

void SecDialog::on_pushButton_2_clicked()
{
    //Step forward
    if(counter < steps.size()) {
       manageSteps(1);
    }
}

void SecDialog::on_prev_step_clicked()
{
    //Step back
    manageSteps(-1);
}

void SecDialog::manageSteps(int step){

    if(counter <= steps.size()){
        int command     = steps.at(counter).getCommand();
        int number      = steps.at(counter).getNumber();
        int generator   = steps.at(counter).getGenerator();
        int reference   = steps.at(counter).getReference();
        double time     = steps.at(counter).getTime();
        double systemTime = steps.at(counter).getSystemTime();

        switch(command){
            case 0:
                setGenerator(generator, time);
                setSystemTime(systemTime);
                break;
            case 1:
                setBuffer(number, generator, time);
                break;
            case 2:
                getBufferCell(number, generator, time);
                setBufferRef(reference);
                break;
            case 3:
                setDevice(number, generator, time);
                setDeviceRef(reference);
                break;
            case 4:
                setDeviceReleaseTime(generator, time);
                break;
        }
        if(step == 1){
            ++counter;
            setProgress(counter);
            mCurrentStep->setText(QString::number(counter));
        } else {
            --counter;
            setProgress(counter);
            mCurrentStep->setText(QString::number(counter));
        }
    }
}


void SecDialog::on_go_to_step_clicked()
{
    int step = ui->tbWriteStep->toPlainText().toInt();
    std::cout << " step: " << step << std::endl;
    if(step > 0 && step <= mMaxStep->toPlainText().toInt()){
        clearAll();
        counter = 0;

        for(int i= 0; i < step; i++) {
            manageSteps(1);
        }
    }
}
