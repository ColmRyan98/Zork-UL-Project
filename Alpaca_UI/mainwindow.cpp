#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <time.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);
     encrypted = false;
     gameEnded = false;
     protagonist = new Characters("you");
     protagonist->addToInvent(Item("Straw Hat", 10, 10.0));
     calculateHealth();
     createRooms();
     printWelcome();
}

//Victory Condition triggered when character contains both the item "Alpaca" and item "Brush"
//Loss Condition triggered when character runs out of stamina
//Stamina decreases everytime player moves into a room that is not the bedroom

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createRooms()  {

    a1 = new Room("Bedroom");
    a = new Room("Farmer's House");
        a->addItem(new Item("Apple", 1, 11));
        a->addItem(new Item("Odd Shaped Rock", 2, 22, "Tiny Turtle Statue"));
    b = new Room("Tool Shed");
        b->addItem(new Item("Brush", 3, 33));
        b->addItem(new Item("Poking Stick", 4, 44));
    c = new Room("Alpaca Pen");
        c->addItem(new Item("Alpaca", 6,66));
    d = new Room("Llama Pen");
    e = new Room("Petting Zoo");
    f = new Room("Shearing Pen");
    g = new Room("Behind Shearing Pen");
    h = new Room("Fleece Mill");
    i = new Room("Sheep Pen");
    j = new Room ("Dead End");
        j->addItem(new Item("Pit Warning Sign", 5, 55));
    j1 = new Room ("Inescapable Pit");
        j1->addItem(new Item("Excali-Sheep", 9001, 10, "YOU ARE UNWORTHY"));

//             (N, E, S, W, Down, Up)
    a1->setExits(NULL, NULL, NULL, NULL, a, NULL);
    a->setExits(f, b, d, c, NULL, a1);
    b->setExits(NULL, NULL, NULL, a, NULL, NULL);
    c->setExits(NULL, a, NULL, NULL, NULL, NULL);
    d->setExits(a, e, NULL, i, NULL, NULL);
    e->setExits(NULL, NULL, NULL, d, NULL, NULL);
    f->setExits(NULL, g, a, h, NULL, NULL);
    g->setExits(NULL, j, NULL, f, NULL, NULL);
    h->setExits(NULL, f, NULL, NULL, NULL, NULL);
    i->setExits(NULL, d, NULL, NULL, NULL, NULL);
    j ->setExits(NULL, NULL, NULL, g, j1, NULL);
    j1 ->setExits(NULL,NULL,NULL,NULL,NULL,NULL);

        currentRoom = a1;
}

/**
 *  Main play routine.  Loops until end of play.
 */
void MainWindow::play() {
    printWelcome();

    // Enter the main command loop.  Here we repeatedly read commands and
    // execute them until the MainWindow game is over.

    bool finished = false;
    while (!finished) {
        // Create pointer to command and give it a command.
        Command* command = parser.getCommand();
        // Pass dereferenced command and check for end of game.
        finished = processCommand(*command);
        // Free the memory allocated by "parser.getCommand()"
        //   with ("return new Command(...)")
        delete command;
    }
    ui->textEdit->append("\n");
    ui->textEdit->append("end \n");
}

void MainWindow::printWelcome() {
    ui->textEdit->setText("start \n");
    ui->textEdit->append("info for help \n");
    ui->textEdit->append("\n");
    ui->textEdit->append(currentRoom->longDescription());
    calculateInvent();
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the MainWindow game, true is returned, otherwise false is
 * returned.
 */
bool MainWindow::processCommand(Command command) {
    if (command.isUnknown()) {
        ui->textEdit->append("invalid input \n");
        return false;
    }

    QString commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0)
        printHelp();

    else if (commandWord.compare("map") == 0)
        {
             if (command.hasSecondWord()) {
                 ui->textEdit->append("overdefined input \n");
             }
             else {
                 map();
             }
        }

    else if (commandWord.compare("go") == 0)
        goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
        if (!command.hasSecondWord()) {
        ui->textEdit->append("incomplete input \n");
        }
        else
         if (command.hasSecondWord()) {
            take(command.getSecondWord());
        }
    }


    else if (commandWord.compare("put") == 0)
    {


    {
    /*if (!command.hasSecondWord()) {
        ui->textEdit->append("incomplete input \n");
        }
        else
            if (command.hasSecondWord()) {
            ui->textEdit->append("you're adding");
            ui->textEdit->append(command.getSecondWord());
            ui->textEdit->append("\n");
            if(currentRoom->isItemInRoom(command.getSecondWord()) != (-1)){
            protagonist->addToInvent(command.getSecondWord());}
        }*/
    }
    }
    else if (commandWord.compare("teleport") == 0)
    {
        if (command.hasSecondWord()) {
            ui->textEdit->append("overdefined input \n");
        }
        else {
            teleport();
        }
    }

    else if (commandWord.compare("quit") == 0) {
        if (command.hasSecondWord())
            ui->textEdit->append("overdefined input \n");
        else
            return true; /**signal to quit*/
    }
    return false;
}
/** COMMANDS **/
void MainWindow::printHelp() {
    ui->textEdit->append("valid inputs are \n");
    parser.showCommands();

}

void MainWindow::gameOver(bool win)
{
    if (win == true){
        gameEnded = true;
        ui->textEdit->setText("\n");
        ui->textEdit->append("\n");
        ui->textEdit->append("\n");
        ui->textEdit->append("\n");
        ui->textEdit->append("You have brushed the alpaca, you win! \n Congrats!");
    }
    else {
        gameEnded = true;
        ui->textEdit->setText("\n");
        ui->textEdit->append("\n");
        ui->textEdit->append("\n");
        ui->textEdit->append("\n");
        ui->textEdit->append("You ran out of stamina and died from overworking yourself \n Game Over, You Lose");
    }
}

void MainWindow::gameOver()
{
    gameEnded = true;
    ui->textEdit->setText("\n");
    ui->textEdit->append("\n");
    ui->textEdit->append("\n");
    ui->textEdit->append("\n");
    ui->textEdit->append("You were crushed by the weight of what you carried \n Game Over, You Lose");
}

void MainWindow::map(){
    //First Row
    if (currentRoom == h)
        ui->textEdit->append("[*]--[f]--[g]-[i]--[j] \n");
    else if (currentRoom == g)
        ui->textEdit->append("[h]--[f]--[*]-[i]--[j] \n");
    else if (currentRoom == f)
        ui->textEdit->append("[h]--[*]--[g]-[i]--[j] \n");
    else if (currentRoom == i)
        ui->textEdit->append("[h]--[f]--[g]-[*]--[j] \n");
    else if (currentRoom == j)
        ui->textEdit->append("[h]--[f]--[g]-[i]--[*] \n");
    else if (currentRoom == j1)
        ui->textEdit->append("[h]--[f]--[g]-[i]--[j+] \n");
    else
        ui->textEdit->append("[h]--[f]--[g]-[i]--[j] \n");
    //Connector
    ui->textEdit->append("      | \n");
    //Second Row
    if (currentRoom == c)
        ui->textEdit->append("[*]--[a]--[b] \n");
    else if (currentRoom == a)
        ui->textEdit->append("[c]--[*]--[b] \n");
    else if (currentRoom == a1)
        ui->textEdit->append("[c]--[a+]--[b] \n");
    else if (currentRoom == b)
        ui->textEdit->append("[c]--[a]--[*] \n");
    else
        ui->textEdit->append("[c]--[a]--[b] \n");
    //Connector
    ui->textEdit->append("      | \n");
    //Third Row
    if (currentRoom == i)
        ui->textEdit->append("[*]--[d]--[e] \n");
    else if (currentRoom == d)
        ui->textEdit->append("[i]--[*]--[e] \n");
    else if (currentRoom == e)
        ui->textEdit->append("[i]--[d]--[*] \n");
    else
        ui->textEdit->append("[i]--[d]--[e] \n");
    //Legend
    ui->textEdit->append("(* = Player Location | + = Player on different floor) \n");
}

void MainWindow::teleport() {
    int random = rand();
    ui->textEdit->append("Teleporting...");
    switch(random%11){
        case 0 :
            currentRoom = a;
            ui->textEdit->append(currentRoom->longDescription());
        break;
        case 1 :
            currentRoom = b;
            ui->textEdit->append(currentRoom->longDescription());
        break;
        case 2 :
            currentRoom = c;
            ui->textEdit->append(currentRoom->longDescription());
        break;
    case 3 :
        currentRoom = d;
        ui->textEdit->append(currentRoom->longDescription());
    break;
    case 4 :
        currentRoom = e;
        ui->textEdit->append(currentRoom->longDescription());
        ui->textEdit->append("\n");
    break;
    case 5 :
        currentRoom = f;
        ui->textEdit->append(currentRoom->longDescription());
    break;
    case 6 :
        currentRoom = g;
        ui->textEdit->append(currentRoom->longDescription());
    break;
    case 7 :
        currentRoom = h;
        ui->textEdit->append(currentRoom->longDescription());
    break;
    case 8 :
        currentRoom = i;
        ui->textEdit->append(currentRoom->longDescription());
    break;
    case 9 :
        currentRoom = j;
        ui->textEdit->append(currentRoom->longDescription());
    break;
    case 10 :
        currentRoom = a1;
        ui->textEdit->append(currentRoom->longDescription());
    break;
    default :
        ui->textEdit->append("Teleport failed \n");
    }
    protagonist->setStamina(protagonist->getStamina()-25);
    calculateHealth();
    if(protagonist->staminaCheck() == true)
    {
        gameOver(false);
    }
}

void MainWindow::goRoom(Command command) {
    if (!command.hasSecondWord()) {
        ui->textEdit->append("incomplete input \n");
        return;
    }

    QString direction = command.getSecondWord();

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL)
        ui->textEdit->append("underdefined input \n");
    else {
        currentRoom = nextRoom;
        ui->textEdit->append(currentRoom->longDescription());
        ui->textEdit->append("\n");
    }
}

void MainWindow::calculateHealth()
{
    QString staminaBar = "";
    bool second = false;
    for (int s = 0; s < (protagonist->getStamina())/5; s++)
    {
        if(second == true){
            staminaBar.append("]");
            second = false;
        }
        else{
            staminaBar.append("[");
            second = true;
        }
    }
    ui->textHealth->setText(staminaBar);
}

void MainWindow::calculateInvent(){
    ui->textInventory->setText("Inventory\n");
    ui->textInventory->append("________\n");
    ui->textInventory->append(protagonist->longDescription());
}

void MainWindow::take(QString itemName){
     ui->textEdit->append("you're trying to take ");
     ui->textEdit->append(itemName);
     int location = currentRoom->isItemInRoom(itemName);
     if (location  < 0 ){
          ui->textEdit->append("That item is not in the room");
     }
     else
          ui->textEdit->append("That item is in the room ");
     if (location >= 0){
         QString temp;
         for(unsigned int an = 0; an < currentRoom->itemsInRoom.size(); an++)
         {
            ui->textSecret->setText(currentRoom->itemsInRoom[an].getShortDescription());
            temp = ui->textSecret->toPlainText();
            tempItem = new Item(currentRoom->getItem(itemName, temp, an));
            if (itemName.toLower() == temp.toLower())
            {
                protagonist->addToInvent(*tempItem);
                currentRoom->removeItemFromRoom(itemName);
                calculateInvent();
                if(protagonist->W > 1000)
                {
                    gameOver();
                }
                if(protagonist->inventoryCheck() == true)
                {
                    gameOver(true);
                }
            }
         }
     }
        if(gameEnded == false)
        {
          ui->textEdit->append(currentRoom->longDescription());
          ui->textTake->setText("");
        }
}

QString MainWindow::go(QString direction) {
    //Make the direction lowercase
    //transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
    //Move to the next room
    Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        return("direction null");
    else
    {
        currentRoom = nextRoom;
        if (currentRoom == a1)
        {
            protagonist->setStamina(100);
        }
        else {
            protagonist->setStamina((protagonist->getStamina())-5);
        }
        calculateHealth();
        if(protagonist->staminaCheck() == true)
        {
            gameOver(false);
            return("");
        }
        return currentRoom->longDescription();
    }
}

void MainWindow::on_pushButton_3_clicked() //North
{
    if (gameEnded == false)
    ui->textEdit->append(go("North"));
}

void MainWindow::on_pushButton_5_clicked()
{
    if (gameEnded == false)
    ui->textEdit->append(go("South"));
}

void MainWindow::on_pushButton_6_clicked()
{
    if (gameEnded == false)
    ui->textEdit->append(go("East"));
}

void MainWindow::on_pushButton_2_clicked()
{
    if (gameEnded == false)
    ui->textEdit->append(go("West"));
}

void MainWindow::on_pushButton_4_clicked()
{
    if (gameEnded == false)
    ui->textEdit->append(go("Down"));
}

void MainWindow::on_pushButton_clicked()
{
    if (gameEnded == false)
    ui->textEdit->append(go("Up"));
}

void MainWindow::on_pushButton_7_clicked()
{
    if (gameEnded == false)
    map();
}

void MainWindow::on_pushButton_8_clicked()
{
    if (gameEnded == false)
    teleport();
}

void MainWindow::on_pushButton_9_clicked()
{
    if (gameEnded == false)
    take(ui->textTake->toPlainText());
}


