#include "stateFunction.h"

// #LOG2410&LOG1000 represent
// #DesignPatterns
// #ClassIsHUGEaf

// MISC
void stateFunction::calibrer()
{
    if (tracker.calibrer())
    {
        for (int i = 0; i < 5; i++)
        {
            DEL[i].turnON();
            _delay_ms(100);
            DEL[i].turnOFF();
            _delay_ms(50);
        }
        for (int i = 4; 0 <= i; i--)
        {
            DEL[i].turnON();
            _delay_ms(100);
            DEL[i].turnOFF();
            _delay_ms(50);
        }

        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 5; i++)
            {
                DEL[i].turnON();
                _delay_ms(5);
            }
            _delay_ms(100);
            for (int i = 0; i < 5; i++)
            {
                DEL[i].turnOFF();
                _delay_ms(5);
            }
            _delay_ms(100);
        }
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            DEL[1].turnON();
            _delay_ms(1000);
            DEL[1].turnOFF();
            _delay_ms(1000);
        }
    }
}
void stateFunction::displayLED()
{
    for (int i = 0; i < 5; i++)
        DEL[i].set(tracker.capteurs[i]);
}
void stateFunction::computeDIR()
{
    displayLED();
    sum = 0;
    nb_Inputs = 0;

    for (int i = 0; i < 5; i++)
    {
        sum += tracker.capteurs[i] * ((2 * i) + 1);
        nb_Inputs += tracker.capteurs[i];
    }
    (nb_Inputs != 0) ? (sum /= nb_Inputs) : (sum = 0);
}
int stateFunction::readCapteurs()
{

    tracker.lecture();
    computeDIR();     
    return 0;
}
void stateFunction::followLine()
{
    if (sum > 5)
    {
        robot.setMotors(SLOW / 2 + 10, NORMAL);
    }
    else if (sum == 5)
    {
        robot.setMotors(NORMAL, NORMAL);
    }
    else if (sum < 5 && sum != 0)
    {
        robot.setMotors(NORMAL, SLOW / 2 + 10);
    }
}
void stateFunction::followCurve_Slow()
{
    if (sum > 5 )
    {
        robot.setMotors(SLOW/2, SLOW);
    }
   
    else if (sum == 5)
    {
        robot.setMotors(SLOW, SLOW);
    }
    else if (sum < 5)
    {
        robot.setMotors(SLOW, SLOW/2);
    }
}
void stateFunction::turnCorner()
{
    bool running = true;
    while(!AllDown()){
        readCapteurs();
        robot.setMotors(NORMAL,NORMAL);
    }
    robot.setMotors(0,0);
    while(!(!tracker.capteurs[0] && !tracker.capteurs[1] && tracker.capteurs[2] && !tracker.capteurs[3]  && !tracker.capteurs[4])){
        readCapteurs();        
        if (sum < 5 || sum == 0) 
        {
            robot.setMotors(SLOW, SLOW/2);
        }
    }  
}

void stateFunction::box()
{
    // if its black (all tape) : getting out of the box
    // if its white (no tape) : go forward
    // if its some leds : need to reorient (its leaving the box)
    //robot.setMotors(0,0);
    Sonorite::jouerSonoriteSonAigu();
    _delay_ms(50);
    Sonorite::arreterSon();
    _delay_ms(20);
    Sonorite::jouerSonoriteSonAigu();
    _delay_ms(50);
    Sonorite::arreterSon();
    while(!AllDown()){
        readCapteurs();
        robot.setMotors(NORMAL,NORMAL);
    }
    while (true)
    {
        readCapteurs();
        if (isBlackLine()) // fonction de sortie
        {  
            Sonorite::jouerSonoriteSonAigu();
            _delay_ms(50);
            Sonorite::arreterSon();
            _delay_ms(20);
            Sonorite::jouerSonoriteSonAigu();
            _delay_ms(50);
            Sonorite::arreterSon();
            while(!oneHot()){
                readCapteurs();
                robot.setMotors(NORMAL,NORMAL);}
            return;
        }

        if (sum < 5)
        {
            robot.setMotors(60, 90); // Dans la boite : evite la ligne
        }
        else if (sum == 0)
        {
            robot.setMotors(70, 70); // Aucune ligne - Avance tout droit
        }
        else if (sum > 5)
        {
            robot.setMotors(90, 60); // Dans la boite : evite la ligne
        }
    }
}
bool stateFunction::oneHot()
{
    int somme = 0;
    for (int i = 0; i < 5; i++)
        somme += tracker.capteurs[i];
    if(somme == 1)
      return true; 
    else 
      return false;
}
bool stateFunction::isLeftCorner()
{
    // capteurs 1-2-3 ON
    // capteur 4 - X; capteur 5 - LOW
    return tracker.capteurs[0] && tracker.capteurs[1] && tracker.capteurs[2] && !tracker.capteurs[4];
}
bool stateFunction::isLeftLine()
{
    return isLeftCorner();
}
bool stateFunction::isRightLine()
{
    // capteurs 5-4-3=ON
    // capteur 2=X; capteur 1=LOW
    return tracker.capteurs[4] && tracker.capteurs[3] && tracker.capteurs[2] && !tracker.capteurs[0];
}
bool stateFunction::isBlackLine()
{
    return AllUp();
}
bool  stateFunction::AllUp(){
    return (tracker.capteurs[0] && tracker.capteurs[1] && tracker.capteurs[2] && tracker.capteurs[3] && tracker.capteurs[4]);
}

bool stateFunction::isWhiteLine()
{
    return AllDown();
}
bool  stateFunction::AllDown(){
    return (!tracker.capteurs[0] && !tracker.capteurs[1] && !tracker.capteurs[2] && !tracker.capteurs[3]&&  !tracker.capteurs[4]);
}



// *********************** Code Kader section points ********************
int stateFunction::waitForSignal()
{
    // TODO faire la lecture du IR ou du bouton
    SIRC signal;
    int point = 0;
    while (!(point <10 && point>0))
        point = signal.getCommand();

    return point /*signal*/; // retourner le signal (la valeur entre 0 et 9)
}
void stateFunction::gotoPN(int dotNumber)
{
    searchForPoint(dotNumber);
}
void stateFunction::goToWhiteLine(){
       while (!AllDown()){
        tracker.lecture();
        displayLED();
        computeDIR();
        if(sum < 5)
           robot.setMotors(NORMAL,NORMAL);   
         else
           followLine();
        } 
}


bool stateFunction::goHorizontal(uint8_t Horizontal){
int i=0;
while (i<Horizontal){
    readCapteurs();
    ZigZagMag();
    //if (oneHot()){
        i++;
        while(!AllDown()){
            readCapteurs();
            robot.setMotors(NORMAL,NORMAL);
        }
    //}
}
    return true;
}

bool stateFunction::goVertical(uint8_t Vertical){
int i=0;
while (i<Vertical){
    readCapteurs();
    ZigZagMag();
    //if (oneHot()){
        i++;
        while(!AllDown()){
            readCapteurs();
            robot.setMotors(NORMAL,NORMAL);
        }
    //}
}
    return true;
}
void stateFunction::moveForward(int time){
for(int i =0; i<  time; i++){
    robot.setMotors(NORMAL+5,NORMAL);
    _delay_ms(10);
}
}

void stateFunction::turnLeft(int Angle){

for (int i =0; i< Angle; i++){
    robot.setMotors(SLOW,SLOW/2);
    _delay_ms(10);
}
}

void stateFunction::turnRight(int Angle){
for (int i =0; i< Angle; i++){
    robot.setMotors(SLOW/2,SLOW);
    _delay_ms(10);
}
}
void stateFunction::halt(){
robot.setMotors(0,0);
}

void stateFunction::ZigZagMag(){
    bool search = true;
    while (AllDown()){
        if(search) {turnLeft(10); search = false;}
        else {turnRight(10); search = true;}
        moveForward(1);
        readCapteurs();
    }
}
void stateFunction::searchForPoint(uint8_t point){
    point =3;
    int Horizontal = point%3 +1;
    int Vertical = 3 - (point-1)/3 ;
    moveForward(Vertical*20); // avance pas de detection 40 needs good for level 2
    halt();
    _delay_ms(100);
    turnLeft(130); //tourne a gauche 100 needs to turn plus
    halt();
    _delay_ms(100);
    moveForward(Horizontal*45);
    halt();
    _delay_ms(100);
    moveForward(50); // avance pour mettre son centre de rotation
    halt();
    _delay_ms(100);
    turnRight(110); // turn et emmettre un son aigu 100 needs to turn plus Parralllele a S3
    halt();
    Sonorite::jouerSonoriteSonGrave();
    _delay_ms(3000);
    Sonorite::arreterSon();
    turnRight(110); //  turn et emmettre un son aigu Parrallele a S4
    halt();
    
    Sonorite::jouerSonoriteSonGrave();
    _delay_ms(3000);
    Sonorite::arreterSon();
    
    moveForward(Horizontal*80); // Revient sans detection A tester needs plus with 40
    halt();
    _delay_ms(100);

    turnLeft(120);
    halt();
    _delay_ms(100);

    readCapteurs();
    ZigZagMag();
    //goToWhiteLine(); fait par s2
    robot.setMotors(0,0);
}





// *********************** FIN Code Kader section points ********************




bool stateFunction::findLine(char arg)
{
    switch (arg)
    {
    case LEFT:
        robot.setMotors(SLOW, NORMAL);
        break;

    case RIGHT:
        robot.setMotors(NORMAL, SLOW);
        break;

    default:
        return false;
    }

    bool running = true;
    while (running)
    {
        readCapteurs();

        if (4 <= sum && sum <= 6)
        {
            robot.setMotors(0, 0);
            return true;
        }
    }
}

// C1
bool stateFunction::c1(bool itNeedsToTurn)
{
    // Tourner de 90. sens anti-horaire (à gauche)
    // Suivre la ligne jusqu'à la ligne noire

    // Passe à S2
    if (itNeedsToTurn) 
        turnCorner();

    while (true)
    {
       readCapteurs();
        followLine();
        if (isBlackLine() || isWhiteLine()){
            while(!AllDown()){
                readCapteurs();
                robot.setMotors(NORMAL,NORMAL);
            }
            robot.setMotors(0,0);

            return true;
        }
    }
}
bool stateFunction::s2()
{
    // Attendre le signal IR/bouton puis se rendre au point approprié

    // Passe à pn
    signal_ = waitForSignal();
    return true;
}
bool stateFunction::pn()
{
    // Se placer parallèle à S3 et en direction de S4
    // Rester immobile et jouer un son pendant 3s (grave)
    // Rotation de 90. sens horaire (vers la droite)
    // Rester immobile et jouer un son pendant 3s (grave)
    // Il se rend à S3

    // Passe à S3

    gotoPN(signal_);

    return true;
}
bool stateFunction::s3()
{
    // Suivre la ligne jusqu'au coin

    // Passe à C2


    // goToWhiteLine();
    // robot.setMotors(0, 0);

    bool running = true;
    while (running)
    {
        readCapteurs();
        // Lorsque le coin est détecté
        if (isWhiteLine())
        {
            robot.setMotors(0, 0);
            return true;
        }
        followLine();
    }
}

// C2
bool stateFunction::c2(bool itNeedsToTurn)
{
    // Tourner de 90. sens anti-horaire (à gauche)

    // Passe à S4

    if (itNeedsToTurn)
        turnCorner();

    return true;
}
bool stateFunction::s4()
{
    // Suivre la ligne jusqu'au coin
    //  ATTENTION:
    //    - Il doit ralentir dans une courbe s4
    // Passe à C3


    bool running = true;
    int index = 0;
    while (running)
    {
        readCapteurs();
        // Lorsqu'il n'y à pas de ligne
        if(tracker.capteurs[4] && tracker.capteurs[3] && tracker.capteurs[2] && !tracker.capteurs[0] && !tracker.capteurs[1] ){
            while(!(!tracker.capteurs[4] && !tracker.capteurs[3] && tracker.capteurs[2] && !tracker.capteurs[0] && !tracker.capteurs[1])){
                readCapteurs();
                robot.setMotors(SLOW/2,NORMAL);
            }
        }
        if(tracker.capteurs[0] && tracker.capteurs[1] && tracker.capteurs[2]){
            robot.setMotors(0,0);
            return true;
        }
        followCurve_Slow();
    }
}

// C3
bool stateFunction::c3(bool itNeedsToTurn)
{
    // Tourner de 90. sens anti-horaire (à gauche)
    // Suivre la ligne jusqu'à une ligne pleine

    // Passe à S5

    if (itNeedsToTurn)
        turnCorner();

    bool running = true;
    while (running)
    {
        readCapteurs();
        followLine();
        if (isBlackLine() || isWhiteLine()){
            robot.setMotors(0,0);
            return true;
        }    
    }
}
bool stateFunction::s5()
{
    // Déplacement physique vers une des sections 'D'
    // Attendre qu'on appuit sur le bouton
    // Passe à Dn
    bool running = true;
    while (running)
    {
        readCapteurs();
        if (PIND & 0x04){
            _delay_ms(10);
            if (PIND & 0x04){
                return true;
            }
        }
    }
}

void stateFunction::sideLineCalcul(){   
    if (tracker.capteurs[0] && tracker.capteurs[1] && tracker.capteurs[2] && tracker.capteurs[3] && tracker.capteurs[4] && !BEG){
        compteur= 0;
       BEG = true;
       do{
           if(tracker.lecture())
        {
            //displayLED();
            sum=5;
            followLine();
            //computeDIR();
        }
       }
       while(!oneHot());
    }
    if (BEG  && tracker.capteurs[0] && tracker.capteurs[1]   && !tracker.capteurs[4] && !RIGHT_){
        tableau[index++] =1;    // left 
        tableau[index++] =compteur;
        compteur=0;
        RIGHT_ = true;
         do{
            if(tracker.lecture())
            {
                //displayLED();
                sum=5;
                followLine();
                //computeDIR();
            }
        }
       while(!oneHot());
    }
    if (BEG  && tracker.capteurs[3] && tracker.capteurs[4] && !tracker.capteurs[0] && !LEFT_){
        tableau[index++] =2;        // right = 2
        tableau[index++] =compteur;
        compteur=0;
        LEFT_ = true;
         do{
            if(tracker.lecture())
            {
            //displayLED();
                sum=5;
                followLine();
            //computeDIR();
            }
       }
       while(!oneHot());
    }
    compteur++;           
}




bool stateFunction::dn()
{
    // Suivre la ligne

    // Passer à dnend et retourner la lecture
    bool running = true;
    while (running)
    {
            readCapteurs();
            sideLineCalcul();
            followLine();
            if(LEFT_ && RIGHT_ && BEG){
                running = false;
            }
    }
    while (!AllDown()){
        readCapteurs();
    };
    robot.setMotors(0, 0);
    return true;
 
}
bool stateFunction::dnend()
{
    // Montrer la DEL correspondante à la ligne lue

    // Passer à pa

    if (tableau[0] == 1 && tableau[2] == 2 ){ // Rouge
        if (double(tableau[3]/tableau[1]) < 1.2) //D2
        {
            DEL[1].turnON();
            _delay_ms(2000);
            DEL[1].turnOFF();
        }
        else{
            DEL[0].turnON();
            _delay_ms(2000);
            DEL[0].turnOFF();
        }
    }
    else{ 
            if (double(tableau[3]/tableau[1]) < 1.2) //D2
            {
                DEL[3].turnON();
                _delay_ms(2000);
                DEL[3].turnOFF();
            }
            else{
                DEL[2].turnON();
                _delay_ms(2000);
                DEL[2].turnOFF();

            }
        }
    return true;
}
bool stateFunction::pa()
{
    // Attendre l'appuie sur le bouton

    // Passer à s6

    bool running = true;
    while (running)
    {
        if (PIND & 0x04){
            _delay_ms(20);
            if (PIND & 0x04){
                return true;
            }
        }
    }
    return false;
}
bool stateFunction::s6()
{
    // Suivre la ligne jusqu'au coin
    // Is that all (à confirmer)

    // passer à C4

    bool running = true;
    while (running)
    {
        readCapteurs();
        if (isLeftCorner())
        {
            robot.setMotors(0, 0);
            return true;
        }
        followLine();
    }
}

// C4
bool stateFunction::c4(bool itNeedsToTurn)
{
    // Tourner de 90. sens anti-horaire (à gauche)
    // Suivre la ligne

    // Rentrer dans la boite, exécuter le son,
    // Suivre la boite
    // Sortir de la boite, exécuter le son

    // Répéter pour les trois boites (totales)
    // Suivre jusqu'au coin

    // Passer à C1

    if (itNeedsToTurn)
        turnCorner();

    // For all three boxes
    for (int i = 0; i < 3;)
    {

        readCapteurs();
        if (isBlackLine())
        {
            // PORTB |= (1 << 0);
            // _delay_ms(500);
            // PORTB &= ~(1 << 0);
            // _delay_ms(100);

            box();
            i++;

            // PORTB |= (1 << 1);
            // _delay_ms(500);
            // PORTB &= ~(1 << 1);
            // _delay_ms(100);
        }
        else
            followLine();
    }

    bool running = true;
    while (running)
    {
        readCapteurs();

        if (isLeftCorner())
        {
            return true;
        }
        followLine();
    }
}
bool stateFunction::end()
{

    return false;
}
bool stateFunction::start()
{
    return false;
}
