#include "Arduino.h"
#include "Wire.h"
#include "wireUtils.h"

#define DEVICE_ADDRESS 0x36

// corrections
#define VOLTAGE_MULTIPLIER (1.25 / 16)
#define CURRENT_MULTIPLIER (156.25 / 1000)
#define CAP_MULTIPLIER 0.5
#define PERCENTAGE_MULTIPLIER (1 / 256)
#define TIME_MULTIPLIER 5625
#define TEMP_MULTIPLIER (1 / 256)

// voltages
#define VCELL_REG 0x09
#define AVG_VCELL_REG 0x19
#define VRIPPLE_REG 0xBC

// temp
#define TEMP_REG 0x08
#define AVG_TA_REG 0x16
#define AIN_REG 0x027
#define T_GAIN_REG 0x2C
#define T_OFF_REG 0x02D
#define DIE_TEMP_REG 0x34

// capacity
#define REP_CAP_REG 0x05
#define Q_RESIDUAL_REG 0x0C
#define MIX_CAP_REG 0x0F
#define FULL_CAP_REP_REG 0x10
#define DESIGN_CAP_REG 0x18
#define AV_CAP_REG 0x1F
#define FULL_CAP_NOM_REG 0x23
#define DQ_ACC_REG 0x45
#define VFR_REM_CAP_REG 0x4A
#define QH_REG 0x4D
#define AT_QRESIDUAL_REG 0xDC
#define AT_AV_CAP_REG 0xDF

// current/timers
#define AT_RATE_REG 0x04
#define CURRENT_REG 0x0A
#define AVG_CURRENT_REG 0x0B
#define TTE_REG 0x11
#define TTF_REG 0x20
#define TIMER_REG 0x3E
#define TIMER_H_REG 0xBE
#define AT_TTE_REG 0xDD

// percentages
#define REP_SOC_REG 0x06
#define AGE_REG 0x07
#define MIX_SOC_REG 0x0D
#define AV_SOC_REG 0x0E
#define DP_ACC_REG 0x46
#define AT_AV_SOC_REG 0xDE

// model
#define QR_TABLE_00_REG 0x12
#define FULL_SOC_THR_REG 0x13
#define CONFIG_REG 0x1D
#define I_CHG_TERM_REG 0x1E
#define QR_TABLE_10_REG 0x22
#define LEARN_CFG_REG 0x28
#define FILTER_CFG_REG 0x29
#define RELAX_CFG_REG 0x2A
#define MISC_CFG_REG 0x2B
#define QR_TABLE_20_REG 0x32
#define FULL_CAP_REG 0x35
#define R_COMP_0_REG 0x38
#define TEMP_CO_REG 0x39
#define V_EMPTY_REG 0x3A
#define QR_TABLE_30_REG 0x42

// status
#define STATUS_REG 0x00
#define F_STAT_REG 0x3D
#define HIB_CFG_REG 0xBA
#define SHDN_TIMER 0x3F
#define SOFT_WAKEUP_REG 0x60
#define MODEL_CFG_REG 0xDB
#define CYCLES_REG 0x17
#define DEV_NAME_REG 0x21
#define POWER_REG 0xB1
#define AVG_POWER_REG 0xB3

#define POR_BIT 1
#define DNR_BIT 0
#define EN_HIBERNATION_BIT 15
#define MODEL_CFG_REFRESH_BIT 15

/**
 * @file Battery.h
 * @brief Battery class definition and member function declarations.
*/

class Battery {
    public: 
        /**
         * @brief Constructor for the Battery class. 
        */
        Battery();

        /**
         * @brief Initializes the battery communication and configuration.
        */
        void begin();

        /**
         * @brief Checks if a battery is connected to the system. 
         * @return True if a battery has been connected, false otherwise
        */
        boolean isConnected();

        /**
         * @brief Reads the current voltage of the battery.
         * @return The current voltage in millivolts (mV).
        */
        unsigned int readVoltage();

        /**
         * @brief Reads the average voltage of the battery.
         * @return The average voltage in millivolts (mV). 
        */
        unsigned int readVoltageAvg();

        /**
         * @brief Reads the instantaneous current of the battery.
         * @return The instantaneous current in miliamperes (mA)
        */
        int readCurrent();

        /**
         * @brief Reads the average current of the battery.
         * @return The average current in millivolts (mV). 
        */
        int readCurrentAvg();

        /**
         * @brief Reads the current temperature of the battery.
         * @return The current temperature in degrees Celsius.
        */
        int readTemp();

        /**
         * @brief Reads the average temperature of the battery.
         * @return The current temperature in degrees Celsius.
        */
        int readTempAvg();
        
        /**
         * @brief Reads the battery's state of charge (SOC).
         * @return The state of charge as a percentage.
        */
        unsigned int readPercentage();

        /**
         * @brief Reads the estimated time to empty (discharge) of the battery.
         * @return The estimated time to empty in minutes.
        */
        unsigned int readTimeToEmpty();

        /**
         * @brief Reads the estimated time to full (charge) of the battery.
         * @return The estimated time to full in minutes.
        */
        unsigned int readTimeToFull();

        /**
         * @brief Reads the remaining capacity of the battery.
         * @return The remaining capacity in milliampere-hours (mAh).
        */
        unsigned int readRemainingCapacity();

        /**
         * @brief Reads the reported capacity of the battery.
         * @return The reported capacity in milliampere-hours (mAh).
        */
        unsigned int readReportedCapacity();

    private:
          #if defined(ARDUINO_PORTENTA_C33)
                TwoWire *  _wire = &Wire3;
            #elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4)
                TwoWire * _wire = &Wire1;
            #elif defined(ARDUINO_NICLA_VISION) 
                TwoWire * _wire = &Wire1;
            #endif
};