#include "main.h"
#include "km07reg.h"


void init_value();
void update_value();

Typekm07 regKm07={  
    .init=&init_value,
    .update=&update_value 
    };

void init_value()
{
    regKm07.VoltR=2200;
    regKm07.VoltS=2200;
    regKm07.VoltT=2500;
    regKm07.AvgVoltphase=(regKm07.VoltR+regKm07.VoltS+regKm07.VoltT)/3;
    regKm07.Volt_RS=regKm07.Amp_R*1.732;
    regKm07.Volt_ST=regKm07.Amp_S*1.732;
    regKm07.Volt_TR=regKm07.Amp_T*1.732;
    regKm07.Volt_DP=1;
    regKm07.Volt_unit=0;

    regKm07.Amp_R=100;
    regKm07.Amp_S=200;
    regKm07.Amp_T=150;
    regKm07.Amp_AVG=(regKm07.Amp_R+regKm07.Amp_S+regKm07.Amp_T)/3;
    regKm07.Amp_DP=2;
    regKm07.PF_R=800;
    regKm07.PF_S=900;
    regKm07.PF_T=1000;

    regKm07.VA_R=regKm07.VoltR*regKm07.Amp_R;
    regKm07.VA_S=regKm07.VoltS*regKm07.Amp_S;
    regKm07.VA_T=regKm07.VoltT*regKm07.Amp_T;
    regKm07.Total_VA=regKm07.VA_R+regKm07.VA_S+regKm07.VA_T;

    regKm07.Watt_R=(regKm07.VA_R*regKm07.PF_R)/1000;
    regKm07.Watt_S=(regKm07.VA_S*regKm07.PF_S)/1000;
    regKm07.Watt_T=(regKm07.VA_T*regKm07.PF_T)/1000;
    regKm07.TotalWatt=regKm07.Watt_R+regKm07.Watt_S+regKm07.Watt_T;
    float detaR,detaS,detaT;
    detaR=acos((float)regKm07.PF_R/1000);
    detaS=acos((float)regKm07.PF_S/1000);
    detaT=acos((float)regKm07.PF_T/1000);
    regKm07.var_R=regKm07.VA_R*sin(detaR);
    regKm07.var_S=regKm07.VA_S*sin(detaS);
    regKm07.var_T=regKm07.VA_T*sin(detaT);
    regKm07.Total_var=regKm07.var_R+regKm07.var_S+regKm07.var_T;

    regKm07.Power_Dp=3;
    regKm07.Power_Unit=0;

    regKm07.Freq_R=500;
    regKm07.Freq_S=500;
    regKm07.Freq_T=500;
}

void update_value()
{
    regKm07.VoltR++;
    regKm07.VoltS+=2;
    regKm07.VoltT+=3;
    if(regKm07.VoltR>2500)    regKm07.VoltR=2000;
    if(regKm07.VoltS>2500)    regKm07.VoltS=2000;
    if(regKm07.VoltT>2500)    regKm07.VoltT=2000;
    regKm07.Volt_RS=regKm07.Amp_R*1.732;
    regKm07.Volt_ST=regKm07.Amp_S*1.732;
    regKm07.Volt_TR=regKm07.Amp_T*1.732;
    regKm07.AvgVoltphase=(regKm07.VoltR+regKm07.VoltS+regKm07.VoltT)/3;

    regKm07.PF_R++;
    regKm07.PF_S+=2;
    regKm07.PF_T+=3;

    if(regKm07.PF_R>1000)    regKm07.PF_R=800;
    if(regKm07.PF_S>1000)    regKm07.PF_S=800;
    if(regKm07.PF_T>1000)    regKm07.PF_T=800;

    regKm07.VA_R=regKm07.VoltR*regKm07.Amp_R;
    regKm07.VA_S=regKm07.VoltS*regKm07.Amp_S;
    regKm07.VA_T=regKm07.VoltT*regKm07.Amp_T;
    regKm07.Total_VA=regKm07.VA_R+regKm07.VA_S+regKm07.VA_T;

    regKm07.Watt_R=(regKm07.VA_R*regKm07.PF_R)/1000;
    regKm07.Watt_S=(regKm07.VA_S*regKm07.PF_S)/1000;
    regKm07.Watt_T=(regKm07.VA_T*regKm07.PF_T)/1000;
    regKm07.TotalWatt=regKm07.Watt_R+regKm07.Watt_S+regKm07.Watt_T;
    float detaR,detaS,detaT;
    detaR=acos((float)regKm07.PF_R/1000);
    detaS=acos((float)regKm07.PF_S/1000);
    detaT=acos((float)regKm07.PF_T/1000);
    regKm07.var_R=regKm07.VA_R*sin(detaR);
    regKm07.var_S=regKm07.VA_S*sin(detaS);
    regKm07.var_T=regKm07.VA_T*sin(detaT);
    regKm07.Total_var=regKm07.var_R+regKm07.var_S+regKm07.var_T;

    regKm07.Power_Dp=3;
    regKm07.Power_Unit=0;

}

