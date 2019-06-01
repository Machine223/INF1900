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
        this->DEL[i].set(tracker.capteurs[i]);
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
    nb_Inputs != 0 ? sum /= nb_Inputs : sum = 0;
}
int stateFunction::readCapteurs()
{

    int VALUE = ERROR;
    pushCapteurs();
    if (tracker.lecture())
    {
        computeDIR();

        if (isBlackLine())
            return BLACK_LINE;
        if (isWhiteLine())
            return WHITE_LINE;
        if (sum > 5)
            return LEFT_LINE;
        if (sum == 5)
            return LINE;
        if (sum < 5)
            return RIGHT_LINE;
    }
    return VALUE;
}
void stateFunction::followLine()
{
    if (sum > 5)
    {
        robot.setMotors(SLOW, NORMAL);
    }
    else if (sum == 5)
    {
        robot.setMotors(NORMAL, NORMAL);
    }
    else if (sum < 5 && sum != 0)
    {
        robot.setMotors(NORMAL, SLOW);
    }
}
void stateFunction::followCurve_Slow()
{
    if (sum > 5)
    {
        robot.setMotors(SLOW / 2, SLOW);
    }
    else if (sum == 5)
    {
        robot.setMotors(NORMAL, NORMAL);
    }
    else if (sum < 5)
    {
        robot.setMotors(SLOW, SLOW / 2);
    }
}
void stateFunction::turnCorner()
{

    bool running = true;
    unsigned int compteur = clock::sysClock;

    robot.setMotors(NORMAL, NORMAL);

    while (running)
    {
        if (clock::sysClock - compteur >= 100000)
        {
            readCapteurs();

            if (sum == 0)
                robot.setMotors(0, 150);
            else
                running = false;
        }
        else
            compteur++;
    }
    robot.setMotors(0, 0);
}
void stateFunction::box()
{
    // if its black (all tape) : getting out of the box
    // if its white (no tape) : go forward
    // if its some leds : need to reorient (its leaving the box)
    Sonorite::jouerSonoriteSonAigu();
    _delay_ms(50);
    Sonorite::arreterSon();
    _delay_ms(20);
    Sonorite::jouerSonoriteSonAigu();
    _delay_ms(50);
    Sonorite::arreterSon();
    int state;
    while (true)
    {
        state = readCapteurs();

        if (isBlackLine())
        {
            Sonorite::jouerSonoriteSonAigu();
            _delay_ms(50);
            Sonorite::arreterSon();
            _delay_ms(20);
            Sonorite::jouerSonoriteSonAigu();
            _delay_ms(50);
            Sonorite::arreterSon();
            pass(BLACK_LINE);
            return;
        }

        if (sum > 5)
        {
            robot.setMotors(NORMAL, SLOW); // Dans la boite : evite la ligne
        }
        else if (sum == 0)
        {
            robot.setMotors(NORMAL, NORMAL); // Aucune ligne - Avance tout droit
        }
        else if (5 > sum)
        {
            robot.setMotors(SLOW, NORMAL); // Dans la boite : evite la ligne
        }
    }
}
bool stateFunction::oneHot()
{
    int sum = 0;
    for (int i = 0; i < 5; i++)
        sum += tracker.capteurs[i];
    return sum == 1 ? true : false;
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
    return isBlackLine(tracker.capteurs) && previousIs(BLACK_LINE, 3);
}
bool stateFunction::isBlackLine(bool array[])
{
    return array[0] && array[1] && array[2] && array[3] && array[4];
}
bool stateFunction::isWhiteLine()
{
    return isWhiteLine(tracker.capteurs) && previousIs(WHITE_LINE, 5);
}
bool stateFunction::isWhiteLine(bool array[])
{
    return !(array[0] || array[1] || array[2] || array[3] || array[4]);
}
int stateFunction::waitForSignal()
{
    // TODO faire la lecture du IR ou du bouton

    // int signal = sirc.getCommand();

    return 0 /*signal*/; // retourner le signal (la valeur entre 0 et 9)
}
void stateFunction::gotoPN(int dotNumber)
{
    // TODO partir de la ligne noire
    // et aller au point demandé par le dotNumber
}
void stateFunction::pass(int arg)
{
    robot.setMotors(NORMAL, NORMAL);

    for (bool running = true; running;)
    {
        running = false;
        for (int i = 0; i < 10; i++)
        {
            readCapteurs();
            running |= isBlackLine();
        }
    }
    robot.setMotors(0, 0);
}
void stateFunction::pushCapteurs()
{
    for (int i = 0; i < 5; i++)
    {
        p4Capteurs[i] = p3Capteurs[i];
        p3Capteurs[i] = p2Capteurs[i];
        p2Capteurs[i] = p1Capteurs[i];
        p1Capteurs[i] = p0Capteurs[i];
        p0Capteurs[i] = tracker.capteurs[i];
    }
}
bool stateFunction::previousIs(int arg, unsigned int count)
{
    bool value = true;
    if (arg == BLACK_LINE)
    {
        switch (count)
        {
        case 5:
            value &= isBlackLine(p4Capteurs);
        case 4:
            value &= isBlackLine(p3Capteurs);
        case 3:
            value &= isBlackLine(p2Capteurs);
        case 2:
            value &= isBlackLine(p1Capteurs);
        case 1:
            value &= isBlackLine(p0Capteurs);
        case 0:
            break;
        }
    }
    else if (arg == WHITE_LINE)
    {
        switch (count)
        {
        case 5:
            value &= isWhiteLine(p4Capteurs);
        case 4:
            value &= isWhiteLine(p3Capteurs);
        case 3:
            value &= isWhiteLine(p2Capteurs);
        case 2:
            value &= isWhiteLine(p1Capteurs);
        case 1:
            value &= isWhiteLine(p0Capteurs);
        case 0:
            break;
        }
    }
    return value;
}
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

        if (4 <= sum && cum <= 6)
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
        if (isBlackLine())
        {
            robot.setMotors(0, 0);
            return true;
        }
        followLine();
    }
}
bool stateFunction::s2()
{
    // Attendre le signal IR/bouton puis se rendre au point approprié

    // Passe à pn
    int signal = waitForSignal();
    gotoPN(signal);

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

    // TODO all this ^

    /*Temporaire : en attendant le code pour 
    effectuer le déplacement vers le point */
    while (!(PIND & 0x04))
    {
        readCapteurs();
    }
    return true;
}
bool stateFunction::s3()
{
    // Suivre la ligne jusqu'au coin

    // Passe à C2

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
    //    - Il doit ralentir dans une courbe

    // Passe à C3

    bool running = true;
    int index = 0;
    while (running)
    {
        readCapteurs();

        // Lorsqu'il n'y à pas de ligne
        if (isWhiteLine())
        {
            // Tourne à droite la première fois
            if (index == 0)
                findLine(RIGHT);

            // Change d'état la seconde fois
            else if (index == 1)
                return true;

            i++;
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

        if (isBlackLine())
            return true;

        followLine();
    }
    return false;
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

        if (PIND & 0x04) //attendre interrupt
            return true;
    }
}
bool stateFunction::dn()
{
    // Suivre la ligne

    // Passer à dnend et retourner la lecture

    if (isBlackLine() && !BEG)
    {
        compteur = 0;
        BEG = true;
        do
        {
            if (tracker.lecture())
            {
                readCapteurs();
                sum = 5;
                followLine();
            }
        } while (!oneHot());
    }
    if (BEG && isLeftLine() && !RIGHT)
    {
        tableau[index++] = 1; // left
        tableau[index++] = compteur;
        compteur = 0;
        RIGHT = true;
        do
        {
            if (tracker.lecture())
            {
                //displayLED();
                sum = 5;
                followLine();
                //computeDIR();
            }
        } while (!oneHot());
    }
    if (BEG && isRightLine() && !LEFT)
    {
        tableau[index++] = 2; // right = 2
        tableau[index++] = compteur;
        compteur = 0;
        LEFT = true;
        do
        {
            if (tracker.lecture())
            {
                //displayLED();
                sum = 5;
                followLine();
                //computeDIR();
            }
        } while (!oneHot());
    }
    compteur++;
    return true;
}
bool stateFunction::dnend(uint8_t num)
{
    // Montrer la DEL correspondante à la ligne lue

    // Passer à pa

    for (int i = 0; i < 5; i++)
        DEL[i].turnOFF();

    switch (num)
    {
    // turn on 1
    case 1:
        DEL[0].turnON();
        break;

    // turn on 2
    case 2:
        DEL[1].turnON();
        break;

    // turn on 3
    case 3:
        DEL[2].turnON();
        break;

    // turn on 4
    case 4:
        DEL[3].turnON();
        break;

    // turn on 5 (error)
    default:
        DEL[4].turnON();
        break;
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

        if (PIND & 0x04)
            return true;
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
        if (isBlackLine())
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

    // if (itNeedsToTurn)
    //     turnCorner();

    // For all three boxes
    for (int i = 0; i < 3;)
    {

        readCapteurs();
        if (isWhiteLine())
        {
            PORTB |= (1 << 0);
            _delay_ms(500);
            PORTB &= ~(1 << 0);
            _delay_ms(100);

            box();
            i++;

            PORTB |= (1 << 1);
            _delay_ms(500);
            PORTB &= ~(1 << 1);
            _delay_ms(100);
        }
        else
            followLine();
    }

    bool running = true;
    while (running)
    {
        readCapteurs();

        if (isWhiteLine())
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