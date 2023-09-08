#include "mbed.h"

DigitalOut myled(LED1);
DigitalIn enable(p17);
Timer t;

// main() runs in its own thread in the OS
int main() {
  t.start();
  int t_start = -1;
  while (true) {

    if (enable && t_start == -1) { // Empiezo a pulsar
      t_start = t.read_ms();

    } else if (enable && t_start != -1) { // Continuo pulsando
      if (t.read_ms() - t_start > 2000) { // Comparo tiempo pulsado
        myled = !myled;
        t_start = -1;
      }
    } else { // Dejo de pulsar
      t_start = -1;
    }
  }
}
