#include "mainwindow.h"


int Elevator::nextId = 1;
int Floor::nextFloorNum = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setConnections();

    //add one starting elevator
    current_elevator = 1;
    Elevator* e = new Elevator;
    controller.addElevatorToList(e);
    elevatorScreenList.push_back(ui->e1LCD);
    ui->comboBox->addItem(QString::number(e->getId()));
    ui->e1LCD->display(1);
    QPalette p = ui->e1LCD->palette();
    p.setColor(QPalette::Light, Qt::black);
    ui->e1LCD->setPalette(p);
    ui->e1LCD->setAutoFillBackground(true);

    ui->eleDisplayBox->setText(e->getMessage());
    floorButtonList.push_back(ui->e1f1);

    //add one starting floor
    Floor* f = new Floor;
    controller.addFloorToList(f);
    ui->comboBox_2->addItem(QString::number(f->getFloorNum()));
    current_floor = 1;

    initFloorQueue();
    initElevatorQueue();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//set connections for ui
void MainWindow::setConnections(){
    connect(ui->pushButton, SIGNAL(released()), this, SLOT (addElevator()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT (sendElevators()));
    connect(ui->e1f1, &QPushButton::released, this, [=]() {
        handleElevatorButton(1);
    });
    connect(ui->e1f2, &QPushButton::released, this, [=]() {
        handleElevatorButton(2);
    });
    connect(ui->e1f3, &QPushButton::released, this, [=]() {
        handleElevatorButton(3);
    });
    connect(ui->e1f4, &QPushButton::released, this, [=]() {
        handleElevatorButton(4);
    });
    connect(ui->e1f5, &QPushButton::released, this, [=]() {
        handleElevatorButton(5);
    });
    connect(ui->e1f6, &QPushButton::released, this, [=]() {
        handleElevatorButton(6);
    });
    connect(ui->e1f7, &QPushButton::released, this, [=]() {
        handleElevatorButton(7);
    });
    connect(ui->e1f8, &QPushButton::released, this, [=]() {
        handleElevatorButton(8);
    });
    connect(ui->e1f9, &QPushButton::released, this, [=]() {
        handleElevatorButton(9);
    });


    ui->floorUpButton->setIcon(QIcon::fromTheme("go-up"));
    ui->floorDownButton->setIcon(QIcon::fromTheme("go-down"));
}

//init floor queue
void MainWindow::initFloorQueue(){
    floorButtonQueue.push(ui->e1f2);
    floorButtonQueue.push(ui->e1f3);
    floorButtonQueue.push(ui->e1f4);
    floorButtonQueue.push(ui->e1f5);
    floorButtonQueue.push(ui->e1f6);
    floorButtonQueue.push(ui->e1f7);
    floorButtonQueue.push(ui->e1f8);
    floorButtonQueue.push(ui->e1f9);
}


//init elevator queue
void MainWindow::initElevatorQueue(){
    elevatorScreenQueue.push(ui->e2LCD);
    elevatorScreenQueue.push(ui->e3LCD);
    elevatorScreenQueue.push(ui->e4LCD);
    elevatorScreenQueue.push(ui->e5LCD);
    elevatorScreenQueue.push(ui->e6LCD);
    elevatorScreenQueue.push(ui->e7LCD);
    elevatorScreenQueue.push(ui->e8LCD);
    elevatorScreenQueue.push(ui->e9LCD);
}

//update the elevator screens
void MainWindow::updateEleScreen(){
    for(int i = 0; i < elevatorScreenList.size(); i++){
        elevatorScreenList[i]->display(controller.getElevator(i+1)->getFloor());
    }
    ui->eleFloorNumberDisplay->display(controller.getElevator(current_elevator)->getFloor());
    ui->eleDisplayBox->setText(controller.getElevator(current_elevator)->getMessage());
}

//update the ele buttons
void MainWindow::updateEleButtons(){
    Elevator* e = controller.getElevator(current_elevator);
    for(int i = 0; i < floorButtonList.size(); i++){
        floorButtonList[i]->setChecked(e->checkIfButtonChecked(i+1));
    }
}

//add elevator to the simulation
void MainWindow::addElevator() {
    if(controller.getElevatorCount() == 9){
        qInfo("Max elevators of 9 has been reached!");
    }
    else{
        Elevator* e = new Elevator;
        controller.addElevatorToList(e);
        qInfo("added elevator %d to the simulation", e->getId());
        ui->comboBox->addItem(QString::number(e->getId()));
        elevatorScreenQueue.front()->setEnabled(true);
        QPalette p = elevatorScreenQueue.front()->palette();
        p.setColor(QPalette::Light, Qt::black);
        elevatorScreenQueue.front()->setPalette(p);
        elevatorScreenQueue.front()->display(1);
        elevatorScreenList.push_back(elevatorScreenQueue.front());
        elevatorScreenQueue.pop();
    }

}


//move all elevators to next in queue
void MainWindow::sendElevators() {
    controller.controlElevators();
    ui->eleFloorNumberDisplay->display(controller.getElevator(current_elevator)->getFloor());
    ui->floorUpButton->setChecked(controller.getFloor(current_floor)->getUpPressed());
    ui->floorUpButton->setEnabled(!controller.getFloor(current_floor)->getUpPressed());
    ui->floorDownButton->setChecked(controller.getFloor(current_floor)->getDownPressed());
    ui->floorDownButton->setEnabled(!controller.getFloor(current_floor)->getDownPressed());
    updateEleScreen();
    updateEleButtons();
}

//handles when a elevator floor button is pressed
void MainWindow::handleElevatorButton(int f){
    Elevator* e = controller.getElevator(current_elevator);
    e->addToQueue(f);
    e->addChecked(f);
    qInfo() << "Elevator " << e->getId() << " added floor " << f << " to its queue.";
}



//when the current elevator box changed, update all the ui
void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    elevatorScreenList.at(current_elevator-1)->setAutoFillBackground(false);
    current_elevator = arg1.toInt();
    elevatorScreenList[current_elevator-1]->setAutoFillBackground(true);
    Elevator* e = controller.getElevator(current_elevator);
    ui->eleNumLcd->display(e->getId());
    ui->eleFloorNumberDisplay->display(e->getFloor());
    ui->eleDisplayBox->setText(e->getMessage());
    ui->eleWeight->setText(QString::number(e->getWeight()));
    ui->doorBlockerButton->setChecked(e->getDoorBlocked());
    updateEleButtons();
}





//when current floor box changed, update all the ui
void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    current_floor = arg1.toInt();
    ui->lcdNumber_1->display(current_floor);
    ui->floorUpButton->setChecked(controller.getFloor(current_floor)->getUpPressed());
    ui->floorUpButton->setEnabled(!controller.getFloor(current_floor)->getUpPressed());
    ui->floorDownButton->setChecked(controller.getFloor(current_floor)->getDownPressed());
    ui->floorDownButton->setEnabled(!controller.getFloor(current_floor)->getDownPressed());

}

//add more floors to simulation
void MainWindow::on_addFloorButton_clicked()
{
    if(floorButtonQueue.size() == 0){
        qInfo("Max amount of floors reached!");
    }else{
        Floor* f = new Floor;
        ui->comboBox_2->addItem(QString::number(f->getFloorNum()));
        controller.addFloorToList(f);
        floorButtonQueue.front()->setEnabled(true);
        floorButtonList.push_back(floorButtonQueue.front());
        floorButtonQueue.pop();

    }
}




//handle floor up button
void MainWindow::on_floorUpButton_clicked()
{
    //request elevator, find best elevator
    Elevator* e = controller.findBestElevator(current_floor);
    e->addToQueue(current_floor);
    controller.getFloor(current_floor)->toggleUpPressed();
    qInfo() << "Elevator " << e->getId() << " added floor " << current_floor << " to its queue.";
    ui->floorUpButton->setEnabled(false);
}

//handle floor down button
void MainWindow::on_floorDownButton_clicked()
{
    //request elevator, find best elevator
    Elevator* e = controller.findBestElevator(current_floor);
    e->addToQueue(current_floor);
    controller.getFloor(current_floor)->toggleDownPressed();
    qInfo() << "Elevator " << e->getId() << " added floor " << current_floor << " to its queue.";
    ui->floorDownButton->setEnabled(false);
}

//handle elevator button help button
void MainWindow::on_eleHelpButton_clicked()
{
    qInfo("Help button pressed on elevator #%d, contacting building safety service", current_elevator);
    controller.getElevator(current_elevator)->changeMessage("Help button pressed, contacting building services.");
    updateEleScreen();
    qInfo("... No response within 5 seconds, calling 911");
}

//handle fire button clicked
void MainWindow::on_fireButton_clicked()
{
    qInfo("Fire Detected! Sending all elevators to a safe floor");
    controller.fireAlarmPressed();
    updateEleScreen();
    updateEleButtons();
    qInfo("\nAll Elevators reached a safe floor. Passengers exiting now");
}

//handle power out button clicked
void MainWindow::on_powerOutButton_clicked()
{
    qInfo("Power Outage Detected! Sending all elevators to a safe floor");
    controller.powerOutPressed();
    updateEleScreen();
    updateEleButtons();
    qInfo("\nAll Elevators reached a safe floor. Passengers exiting now");
}

//handle when the weight changes
void MainWindow::on_eleWeight_editingFinished()
{
    controller.getElevator(current_elevator)->setWeight(ui->eleWeight->text().toInt());
}

//handle door blocked button
void MainWindow::on_doorBlockerButton_clicked()
{
    controller.getElevator(current_elevator)->toggleDoorBlocked();

}

//handle door open button
void MainWindow::on_openDoorButton_clicked()
{
    controller.getElevator(current_elevator)->doorOpenPressed();
}


//handle door close button
void MainWindow::on_closeDoorButton_clicked()
{
    controller.getElevator(current_elevator)->doorClosedPressed();
}



