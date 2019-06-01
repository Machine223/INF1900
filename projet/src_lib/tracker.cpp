#include "tracker.h"

void Tracker::init()
{
    if (/*!calibrerFromMemory()*/true)
    {
        calibrer();
    }
    // mettre les pin en lecture
    DDRA = 0x00; // PORTA en entree et pour faire la lecture avec PINA
    analogValue[0] = 0;
    analogValue[1] = 0;
    analogValue[2] = 0;
    analogValue[3] = 0;
    analogValue[4] = 0;
}

Tracker::Tracker()
{
    init();
}

uint8_t Tracker::read(uint8_t pos)
{
    can signal;
    uint16_t result; // utiliser pour retourner sur 16bits
    // retourne la valeur numerique correspondant a la valeur
    // analogique sur le port A.  pos doit etre entre 0 et 7
    // inclusivement.  Seulement les 10 bits de poids faible
    // sont significatifs.
    result = signal.lecture(pos);  //pos prend des valeurs entre 0 a 7
    return (uint8_t)(result >> 2); // prend les MSB et retourne sur 8
}

bool Tracker::lecture()
{
    analogValue[0] = read(0); //read portA 1  0b0000 0001     IR1  0-255
    analogValue[1] = read(1); //read portA 2  0b0000 0010     IR2
    analogValue[2] = read(2); //read portA 3  0b0000 0100     IR3
    analogValue[3] = read(3); //read portA 4  0b0000 1000     IR4
    analogValue[4] = read(4); //read portA 5  0b0001 0000     IR5
    // Appel la fonction lecture dans can.cpp
    // Faire une conversion et aller retourner le resultat sur 16 bits
    // dont seulement les 8bits sont significatif avec analog(voir fonction)

    for (unsigned int i = 0; i < 5; i++)
    {
        // if(i != 2){
            if ((analogValue[i] >= (seuil_[i] - 5)) && (analogValue[i] <= (seuil_[i] + 5))){ // temporaire a mettre seuil_ prochainement
                capteurs[i] = false;
            }
            else{
                capteurs[i] = true;
            }
        // }else if (i == 2){
        //     if ((analogValue[i] >= (seuil_[i] - 40)) && (analogValue[i] <= (seuil_[i] + 40))){ // temporaire a mettre seuil_ prochainement
        //         capteurs[i] = true;
        //     }
        //     else{
        //         capteurs[i] = false;
        //     }
        // }
        if (i == 4){
            return true;
        }
    }
    return false;
}

bool Tracker::calibrer()
{
    unsigned int precision = 45;
    unsigned int somme[5] = {0,0,0,0,0};
    for (unsigned int i = 0; i < precision; i++)
    {
        somme[0] += read(0);
        somme[1] += read(1);
        somme[2] += read(2);
        somme[3] += read(3);
        somme[4] += read(4);
    }
    if (somme[0] != 0 && somme[1] != 0 && somme[2] != 0 && somme[3] != 0 && somme[4] != 0)
    {
        seuil_[0] = somme[0] / precision;
        seuil_[1] = somme[1] / precision;
        seuil_[2] = somme[2] / precision;
        seuil_[3] = somme[3] / precision;
        seuil_[4] = somme[4] / precision;
        
        return true;
    }
    else
    {
        return false;
    }
}

bool Tracker::calibrerFromMemory()
{

    Memoire24CXXX memoire;
    uint8_t *opcode;
    uint8_t *data;
    memoire.lecture(0, opcode);

    if (*opcode != 0xff) // si la config nest pas stocker en memoire
    {
        return false;
    }
    memoire.lecture(1, data);
    seuil_[0] = *data;
    memoire.lecture(2, data);
    seuil_[1] = *data;
    memoire.lecture(3, data);
    seuil_[2] = *data;
    memoire.lecture(4, data);
    seuil_[3] = *data;
    memoire.lecture(5, data);
    seuil_[4] = *data;
    return true;
}