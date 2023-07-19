#include <Arduino.h>


typedef struct {
    long     CTr;
    long     VTr;
    int      DemandPeriod;

    byte baudrate;                    
    byte datasize;
    byte parity;
    byte stopbit;
}typeMeterSetting;

typedef struct{
    byte  IP[4];                      // IP Address
    byte  Netmask[4];                 // Subnet Mask
    byte  Gateway[4];                 // Default Gateway
    byte  dns1[4];                    // primary DNS
    byte  dns2[4];                    // secondary Gateway
    boolean dhcp;                     // DHCP
}typeMeterIP;

typedef struct  strModbus {

    
    long    VoltR;
    long    VoltS;
    long    VoltT;
    long    AvgVoltphase;
    long    Volt_RS;
    long    Volt_ST;
    long    Volt_TR;
    long    AvgVoltLL;
    int     Volt_unit;
    int     Volt_DP;
    long    Amp_R;
    long    Amp_S;
    long    Amp_T;
    long    Amp_N;
    long    Amp_AVG;
    int     Amp_DP;

    int     None1;

    int     PF_R;
    int     PF_S;
    int     PF_T;
    int     Avg_PF;
    int     Freq_R;
    int     Freq_S;
    int     Freq_T;
    long    Watt_R;
    long    Watt_S;
    long    Watt_T;
    long    TotalWatt;
    long    var_R;
    long    var_S;
    long    var_T;
    long    Total_var;
    long    VA_R;
    long    VA_S;
    long    VA_T;
    long    Total_VA;
    int     Power_Unit;
    int     Power_Dp;
    long    Demand_kW;
    long    Demand_kvar;
    long    Demand_kVA;
    int     UangleR;
    int     UangleS;
    int     UangleT;

    int     None2;
    int     None3;
    int     None4;

    int     IangleR;
    int     IangleS;
    int     IangleT;

    int     None5[9];
    int     inputCounter;
    //      Setting         //
    typeMeterSetting    vSetting;
    typeMeterIP         ipMeter;

    void (*init)(void);
    void (*update)(void);
} Typekm07;


extern Typekm07 regKm07;