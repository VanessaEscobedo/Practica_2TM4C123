#include "lib/include.h"

extern void Configurar_GPIO(void)
{
  volatile uint32_t delay= SYSCTL->RCGCGPIO;      // no need to unlock;
  SYSCTL->RCGCGPIO |= (1<<1) | (1<<4); //habilitar modulos GPIO (RCGCGPIO) p. 656, 340
  //habilitar reloj del puerto B y E
  GPIOE->DIR &= ~0x03; //configurar pines GPIO (GPIODIR)
  GPIOB->DIR |= 0x3F; 
  //1 -> salida (PB0-5)
  //0 -> entrada (PE0-1)
  GPIOE->DEN |= 0x03; //habilitar pines como digitales (GPIODEN)
  GPIOB->DEN |= 0x3F;  
}

extern void Delay(void)
{
 
  unsigned long volatile time;
  time = 1600000;
  while(time)
  {
		time--;
  }
}