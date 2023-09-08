#include "mbed.h"

DigitalOut myled(LED1);
DigitalIn enable(p17);
Timer t;

// main() runs in its own thread in the OS
int main() {
  t.start();
  int t_start = -1;
  int t_flash = 0;
  while (true) {

    if (enable && t_start == -1) { // Empiezo a pulsar
      t_start = t.read_ms();

    } else if (enable && t_start != -1) { // Continuo pulsando
      if (t.read_ms() - t_start > 2000) {
        t_flash = t.read_ms();
        t_start = -1;

        while (t.read_ms() - t_flash < 10000) {
          myled = !myled;
          wait_ms(100);
          if (enable && t_start == -1) { // Empiezo a pulsar
            t_start = t.read_ms();
          } else if (enable && t_start != -1) {
            if (t.read_ms() - t_start > 2000) {
              t_flash = t.read_ms();
              t_start = -1;
            }
          }else{
              t_start = -1;
          }
          t_start = -1;
        }
      } else { // Dejo de pulsar
        t_start = -1;
      }
    }
  }
}