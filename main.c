/*
 */

/* 
 * File:   main.c
 * Author: pconroy
 *
 * Created on March 2, 2020, 1:05 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include "log4c.h"
#include "libepsolar.h"

/*
 * 
 */
int main(int argc, char** argv)
{
    //
    //  Connect to the EPSolar Solar Charge Controller
    //  Pass in NULL to use default port defined in libepsolar/epsolar.c
    //  Second parmeter is Modbus Slave ID.  '1' is fine
    if (!epsolarModbusConnect( NULL, 1 )) {
        printf( "Unable to open default device port %s to connect to the solar charge controller\n", epsolarGetDefaultPortName() );
        return( EXIT_FAILURE );
    }
    
    uint16_t csb = eps_getChargingEquipmentStatusBits();
    uint16_t bsb = eps_getBatteryStatusBits();
    uint16_t dsb = eps_getdisChargingEquipmentStatusBits();
    
    printf( "Device/Array/Charging   0x3201  Status Bits %u  %0X\n", csb, csb );
    printf( "Battery                 0x3200  Status Bits %u  %0X\n", bsb, bsb );
    printf( "Load                    0x3200  Status Bits %u  %0X\n", dsb, dsb );
    
    printf( " --------------------------------------------------------\n" );
    printf( "Device/Array/Charging   0x3201  Status Bits %u  %0X\n", csb, csb );
    printf( " --------------------------------------------------------\n" );
    printf( "  PV Status:                   %s\n", getChargingEquipmentStatusInputVoltageStatus( csb ));
    printf( "  Charging MOSFET Shorted      %s\n", (isChargingMOSFETShorted( csb ) ? "Yes" : "No " ));
    printf( "  Charging MOSFET Open         %s\n", (isChargingMOSFETOpen( csb ) ? "Yes" : "No " ));
    printf( "  Anti Reverse MOSFET Shorted  %s\n", (isAntiReverseMOSFETShort( csb ) ? "Yes" : "No " ));
    printf( "  PV Input is Over Current     %s\n", (isInputOverCurrent( csb ) ? "Yes" : "No " ));
    printf( "  Load is Over Current         %s\n", (isLoadOverCurrent( csb ) ? "Yes" : "No " ));
    printf( "  Load is Shorted              %s\n", (isLoadShorted( csb ) ? "Yes" : "No " ));
    printf( "  Load MOSFET is Shorted       %s\n", (isLoadMOSFETShorted( csb ) ? "Yes" : "No " ));
    printf( "  Three Circuits in DisEquilib %s\n", (isDisequilibriumInThreeCircuits( csb ) ? "Yes" : "No " ));
    printf( "  PV Input is Shorted          %s\n", (isPVInputShorted( csb ) ? "Yes" : "No " ));
    printf( "  Charging Status              %s\n", getChargingStatus( csb ) );
    printf( "  Charging Status Normal       %s\n", (isChargingStatusNormal( csb ) ? "Yes" : "No " ));
    printf( "  Charging Status Running      %s\n", (isChargingStatusRunning( csb ) ? "Yes" : "No " ));
         
    printf( " --------------------------------------------------------\n" );
    printf( "Battery                 0x3200  Status Bits %u  %0X\n", bsb, bsb );
    printf( " --------------------------------------------------------\n" );
    printf( "  Identification Status     %s\n", getBatteryStatusIdentification( bsb ));
    printf( "  Inner Resistance Status   %s\n", getBatteryStatusInnerResistance( bsb ));
    printf( "  Temperature Status        %s\n", getBatteryStatusTemperature( bsb ));
    printf( "  Voltage Status            %s\n", getBatteryStatusVoltage( bsb ));

    
    epsolarModbusDisconnect();
    
    return (EXIT_SUCCESS);
}

