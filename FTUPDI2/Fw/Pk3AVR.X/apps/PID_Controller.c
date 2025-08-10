#include "PID_Controller.h"
#include "oc1.h"

// Saturation in PID task
#define UPPER_LIMIT     31
#define LOWER_LIMIT     0
// PID parameters
#define KP              100
#define KI              30
#define KD              10
#define SYS_GAIN        1
#define TS              1 // unit time

int32_t C0_k; // the current PID output
int32_t C0_k_1; // the previous PID output
int32_t E_k; // the current PID error
int32_t E_k_1; // the 1st previous PID error
int32_t E_k_2; // the 2nd previous PID error
int32_t SetPoint=9000U;

const int32_t a=((2*KP)*SYS_GAIN+(KI*TS)*SYS_GAIN+(KD*SYS_GAIN)/TS); //(2*KP+KI*TS+KD/TS)*SYS_GAIN;
const int32_t b=((-2*KP)*SYS_GAIN+(KI*TS)*SYS_GAIN-((4*KD)*SYS_GAIN)/TS); //(-2*KP+KI*TS-(4*KD)/TS)*SYS_GAIN;
const int32_t c=((KD*SYS_GAIN)/TS); //(KD/TS)*SYS_GAIN;

uint16_t PID_Task(int32_t Realpoint) // <editor-fold defaultstate="collapsed" desc="PID control">
{
    int16_t rslt;

    // Calculate error
    E_k=SYS_GAIN*SetPoint;
    E_k-=Realpoint;

    // Calculate output
    //C0_k=(C0_k_1+a*E_k)+(b*E_k_1)+(c*E_k_2);
    C0_k=a;
    C0_k*=E_k;
    C0_k+=C0_k_1;

    C0_k_1=b;
    C0_k_1*=E_k_1;
    C0_k+=C0_k_1;

    C0_k_1=c;
    C0_k_1*=E_k_2;
    C0_k+=C0_k_1;

    // Backup current state
    E_k_2=E_k_1;
    E_k_1=E_k;
    C0_k_1=C0_k;
    C0_k/=SYS_GAIN;
    // Saturation

    if(C0_k>UPPER_LIMIT)
        C0_k=UPPER_LIMIT;
    else if(C0_k<LOWER_LIMIT)
        C0_k=LOWER_LIMIT;

    rslt=(int16_t) (C0_k);

    return (uint16_t) rslt;
} // </editor-fold>

uint16_t PID_GetSetpoint(void) // <editor-fold defaultstate="collapsed" desc="Get setpoint">
{
    return (uint16_t)SetPoint;
} // </editor-fold>

void PID_Init(uint16_t setPoint) // <editor-fold defaultstate="collapsed" desc="PID init">
{
    C0_k=0;
    C0_k_1=0;
    E_k=E_k_1=E_k_2=0;
    SetPoint=setPoint;
} // </editor-fold>
