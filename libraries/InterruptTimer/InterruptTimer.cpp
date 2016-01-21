#include "InterruptTimer.h"
#include <Arduino.h>

using namespace InterruptTimer;

volatile uint8_t *tccrA[] = {&TCCR0A, &TCCR1A, &TCCR2A};
volatile uint8_t *tccrB[] = {&TCCR0B, &TCCR1B, &TCCR2B};
volatile uint8_t *tcnt[] = {&TCNT0, 0, &TCNT2};
volatile uint8_t *ocrA[] = {&OCR0A, 0, &OCR2A};
volatile uint8_t *timsk[] = {&TIMSK0, &TIMSK1, &TIMSK2};
uint8_t ocieA[] = {OCIE0A, OCIE1A, OCIE2A};

uint8_t prescaler_1[] = {(1 << CS10),
                         (1 << CS11),
                         (1 << CS10) | (1 << CS11),
                         (1 << CS12),
                         (1 << CS12) | (1 << CS10)};

uint8_t prescaler_02[] = {(1 << CS00),
                          (1 << CS01),
                          (1 << CS00) | (1 << CS01),
                          (1 << CS02),
                          (1 << CS02) | (1 << CS00)};

void InterruptTimer::configure(Timer timer, int count, Prescaler prescaler){
  volatile uint8_t *ptccrA = tccrA[timer];
  volatile uint8_t *ptccrB = tccrB[timer];
  volatile uint8_t *ptcnt = tcnt[timer];
  volatile uint8_t *pocrA = ocrA[timer];
  volatile uint8_t *ptimsk = timsk[timer];
  cli();
  *ptccrA = 0;
  *ptccrB = 0;
  if(TIMER_1 == timer){
    TCNT1 = 0;
    OCR1A = count;
    TCCR1B |= (1 << WGM12); // CTC mode
    TCCR1B |= prescaler_1[prescaler];
  }else{
    *ptcnt = 0;
    *pocrA = count;
    if(TIMER_0 == timer){
      *ptccrA |= (1 << WGM01);
    }else{
      *ptccrA |= (1 << WGM21);
    }
    *ptccrB |= prescaler_02[prescaler];
  }
  *ptimsk |= (1 << ocieA[timer]);
}

void InterruptTimer::start(){
  sei();
}
