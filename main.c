/*EQUIPO
Eduardo Rodriguez
Adriana Martinez
Ashley Resendiz
Vanessa Escobedo
*/

#include "lib/include.h" //librerias

#define SENSOR  (*((volatile uint32_t *)0x4002400C)) //0x4002.4000 GPIO -> dirección base del puerto E
#define LIGHT   (*((volatile uint32_t *)0x400050FC)) //0x4000.5000 GPIO -> dirección base del puerto B
// Linked data structure

struct State //estructura de nombre State
{
  uint32_t Out; //variables 
  uint32_t Time; 
  uint32_t Next[4];
};

typedef const struct State State_t; //se crea un nuevo tipo de datos con typedef (State_t)
//typedef -> permite proporcionar nombre alternativos 
//const -> para asignar la estructura en ROM 
#define goN   0 
#define waitN 1
#define goE   2
#define waitE 3

State_t FSM[4]= //arreglo de estructuras
{
 {0x21,300,{goN,waitN,goN,waitN}},
 {0x22, 50,{goE,goE,goE,goE}},
 {0x0C,300,{goE,goE,waitE,waitE}},
 {0x14, 50,{goN,goN,goN,goN}}};

uint32_t S;  // index to the current state
uint32_t Input;

int main(void)
{
  Configurar_PLL(_80MHZ); //configuración de la velocidad de reloj      
  SysTick_Init();   // Program 10.2
  Configurar_GPIO(); //configuración GPIO
  
  S = goN; //0
  
  while(1)
  {
    LIGHT = FSM[S].Out;  // set lights //en la posición S del arreglo FMS se almacena el valor de out que es light
    SysTick_Wait10ms(FSM[S].Time);
    Input = SENSOR;     // read sensors
    S = FSM[S].Next[Input]; 
  }
}
