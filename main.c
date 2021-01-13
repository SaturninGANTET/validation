#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <getopt.h>
#include <ctype.h>
#include <errno.h>

void envoie_message_urgence()
{
    printf("Message urgence envoyé au CDB avec position, dynamique et heure\n");
}

void freinage_urgence()
{
    printf("Freinage urgence enclenché\n");
}

bool detection_danger_radar(long int distance)
{
    if (distance < 0)
    {
        printf("Erreur radar distance négative\n");
    }
    if (distance < 10)
    {
        envoie_message_urgence();
        freinage_urgence();
        return true;
    }
    return false;
}

bool detection_danger_message(long int x, long int y, long int z, long int vx, long int vy, long int vz, long int time)
{
    envoie_message_urgence();
    return true;
}

long int getValue(char *str)
{
    errno = 0;
    long int val = strtol(str, NULL, 10);
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val == 0))
    {
        printf("Erreur getValue");
        return LONG_MIN;
    }
    return val;
}

/* return {
    bit0 -> distance
    bit1 -> frein
    bit2 -> message
}*/
//(distance - etat frein - isMessage - message{x,y,z,vx,vy,vz,time})
int CSC(int argc, char *argv[])
{
    int retour = 0;
    if (argc < 4)
    {
        printf("Erreur argument\n");
        return -1;
    }
    long int distance = getValue(argv[1]);
    long int freinUrgence = getValue(argv[2]);
    long int isMessage = getValue(argv[3]);
    if (distance == LONG_MIN || freinUrgence == LONG_MIN || isMessage == LONG_MIN)
        return -1;
    long int x;
    long int y;
    long int z;
    long int vx;
    long int vy;
    long int vz;
    long int time;
    if (isMessage)
    {
        if (argc != 11)
        {
            printf("Erreur argument\n");
            return -1;
        }
        x = getValue(argv[4]);
        y = getValue(argv[5]);
        z = getValue(argv[6]);
        vx = getValue(argv[7]);
        vy = getValue(argv[8]);
        vz = getValue(argv[9]);
        time = getValue(argv[10]);
    }
    if (detection_danger_radar(distance))
    {
        retour = retour | 1;
    }
    if (freinUrgence)
    {
        envoie_message_urgence();
        retour = retour | 2;
    }
    if (!isMessage)
    {
        return retour;
    }
    if (detection_danger_message(x, y, z, vx, vy, vz, time))
    {
        retour = retour | 4;
    }
    return retour;
}