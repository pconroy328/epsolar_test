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
    
    printf( "Charging    Status Bits %u  %0X\n", csb, csb );
    printf( "Battery     Status Bits %u  %0X\n", bsb, bsb );
    printf( "Discharging Status Bits %u  %0X\n", dsb, dsb );

    epsolarModbusDisconnect();
    
    return (EXIT_SUCCESS);
}

