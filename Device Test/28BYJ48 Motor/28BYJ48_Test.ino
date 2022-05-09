#include <Stepper.h> // Hinzufügen der Programmbibliothek.
int SPU = 2048; // Schritte pro Umdrehung.
Stepper Motor(SPU, 7,5,6,4); // Der Schrittmotor erhält die Bezeichnung "Motor" und es wird angegeben an welchen Pins der Motor angeschlossen ist.

void setup() //Hier beginnt das Setup.
{
Motor.setSpeed(15); // Angabe der Geschwindigkeit in Umdrehungen pro Minute.
}

void loop() {
Motor.step(2048); // Der Motor macht 2048 Schritte, das entspricht einer Umdrehung.
delay(1000); // Durch diese Pause bleibt der Motor nach der Drehung für eine Sekunde stehen.
Motor.step(-2048); // Der Motor macht durch das Minuszeichen 2048 Schritte in die andere Richtung.
delay(1000); // Durch diese Pause bleibt der Motor nach der Drehung für eine Sekunde stehen.
}