# Librairie Arduino SPI pour AD9850 #
F4GOJ Christophe f4goj@free.fr

Août 2014

Mise à jour vers SPI par F4GOH Anthony f4goh@orange.fr

Cette librairie utilise l'Interface de Périphérique Série (SPI) pour accélérer la mise à jour de l'AD9850 de 700µs par la liaison série logicielle à 90µs (54µs pour le calcul du mot deltaphase et 36µs pour le transfert)

Documentation de l'AD9850 à http://www.analog.com/static/imported-files/data_sheets/AD9850.pdf

Utilisez cette librairie librement.

## Installation ##
Pour utiliser la librairie **AD9850SPI** :
- Allez à https://github.com/F4GOJ/AD9850SPI, cliquez le bouton [Download ZIP](https://github.com/F4GOJ/AD9850SPI/archive/master.zip) et enregistrez le fichier ZIP à l'endroit de votre convenance.
- Décompressez le fichier. Vous obtiendrez un répertoire contenant tous les fichiers de la librairie avec un nom comprenant le nom de branche, typiquement **AD9850SPI-master**.
- Renommez le répertoire en **AD9850SPI**.
- Copiez le répertoire renommé dans le répertoire Arduino \libraries.


## Notes d'utilisation##

La librairie **AD9850SPI** crée une instance de l'objet **DDS**, l'utilisateur n'a pas pas besoin de le faire.

Pour utiliser la librairie **AD9850SPI**, la librairie SPI doit être incluse.

```c++
#include <AD9850SPI.h> //http://github.com/F4GOJ/AD9850SPI
#include <SPI.h>       //http://arduino.cc/en/Reference/SPI (incluse dans l'IDE Arduino)
```
## Connexions : ##

![ad9850](https://raw.githubusercontent.com/F4GOJ/AD9850SPI/master/images/AD9850.png)

- W_CLK   -> 13 arduino UNO/NANO, D52 MEGA.
- FQ_UD   -> n'importe quelle broche exceptées les 10 et 12 sur un UNO/NANO, 50 et 53 sur un MEGA.
- DATA/D7 -> 11 arduino UNO/NANO, D51 MEGA.
- RESET   -> n'importe quelle broche exceptées les 10 et 12 sur un UNO/NANO, 50 et 53 sur un MEGA.

## Fonctions : ##

###begin(int w_clk_pin, int fq_ud_pin, int reset_pin)
#####Description
Initialise les broches de sortie et effectue une remise à zéro générale de l'AD9850.
#####Syntaxe
`DDS.begin(w_clk, fq_ud, reset);`
#####Paramètres
**w_clk :** Broche de sortie SPI SCK (13 sur un UNO/NANO, 52 sur un MEGA) *(int)*<br>
**fq_ud :** Broche de sortie de mise à jour de la fréquence, n'importe quelle broche exceptées les 10 et 12 sur un UNO/NANO, 50 et 53 sur un MEGA. *(int)*<br>
**reset :** Broche de sortie de RàZ, n'importe quelle broche exceptées les 10 et 12 sur un UNO/NANO, 50 et 53 sur un MEGA. *(int)*
#####Retourne
Rien.
#####Exemple
```c++
void setup(){
 DDS.begin(13, 8, 9);
}
```
###calibrate(double trim_frequency)
#####Description
Compensation de la féquence de l'oscillateur.<br>
Peut être utilisée à n'importe quel moment après l'initialisation.
#####Syntaxe
`DDS.calibrate(trim_freq);`
#####Paramètres
**trim_freq :** Ajuster autour de 125000000 pour correspondre à la fréquence réelle de l'oscillateur. *(double)*
#####Retourne
Rien.
#####Exemple
```c++
void setup(){
 DDS.begin(13, 8, 9);
}

void loop(){
 DDS.calibrate(124999000);
}
```
###setfreq(double frequency, int phase)
#####Description
Détermine la fréquence de sortie de l'AD9850 et la phase du signal.
#####Syntaxe
`DDS.setfreq(frequency, phase);`
#####Paramètres
**frequency :** Fréquence de sortie en HZ. *(double)*<br>
**phase :** Phase du signal, codée sur 5 bits permet 32 pas de phase de 11,25° *(int)*
#####Retourne
Rien.
#####Exemple
```c++
double frequency = 10000000;
int phase = 0;
DDS.setfreq(frequency, phase);
```
###down()
#####Description
Mode "extinction" réduisant la puissance dissipée de 380mW à 30mW sous 5V
#####Syntaxe
`DDS.down();`
#####Paramètres
Aucun.
#####Retourne
Rien.
#####Exemple
```c++
DDS.down();
```
###up()
#####Description
Sort l'AD9850 du mode "extinction"
#####Syntaxe
`DDS.up();`
#####Paramètres
Aucun.
#####Retourne
Rien.
#####Exemple
```c++
DDS.down(); // Entrée en mode "extinction"

// du code faisant quelquechose

...

DDS.up(); // REVEIL !!! :)
```
