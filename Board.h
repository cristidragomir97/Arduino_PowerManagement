#ifndef BOARD_H
#define BOARD_H

#include <Arduino_PMIC.h>
#include "wireUtils.h"

#define CONTEXT_LDO1 1
#define CONTEXT_LDO2 2
#define CONTEXT_SW 3 


class Board {
    public:
        /**
         * @brief Default constructor for the Board class.
        */
        Board();

        /**
         * @brief Constructor for the Board class with a PF1550 PMIC instance.
         * @param _pPMIC Pointer to the PF1550 PMIC instance.
        */
        Board(PF1550 * _pPMIC);

        /**
         * @brief Check if the board is powered through USB.
         * @return True if powered through USB, false otherwise.
        */
        bool isUSBPowered();

        /**
         * @brief Check if the board is powered by the battery.
         * @return True if powered by the battery, false otherwise.
        */
        bool isBatteryPowered();

        /**
         * @brief Set the external power lane switch state.
         * @param on True to turn on the switch, false to turn it off.
         */
        void setExternalSwitch(bool on);

        /**
         * @brief Set the voltage for the external power rail.
         * @param v Voltage value to set. (as float)
         * @return True if successful, false otherwise.
        */
        bool setExternalVoltage(float v); 
    
        #if defined(ARDUINO_NICLA_VISION)
        /**
         * @brief Set the camera power rail switch state on Nicla Vision.
         * @param on True to turn on the switches, false to turn them off.
        */
        void setCameraSwitch(bool on); 
        #endif 

        #if defined(ARDUINO_PORTENTA_C33)
        void lowPowerMode(bool on);

        /**
         * @brief Set the communication power rail switch state on Portenta C33
         * @param on True to turn on the switches, false to turn them off.
        */
        void setCommunicationSwitch(bool on);
        
        /**
         * @brief Set the analog voltage on Portenta C33.
         * @param v Voltage value to set (as float).
         * @return True if successful, false otherwise.
        */
        bool setAnalogVoltage(float v);

        /**
         * @brief Set the reference voltage on Portenta C33.
         * @param v Voltage value to set (as float).
         * @return True if successful, false otherwise.
        */
        bool setReferenceVoltage(float v);
        #endif
        
     

    private:
       PF1550 * pPMIC;
        
};

static inline uint8_t getRailVoltage(float voltage, int context) {
    switch (context) {
        case 1: // LDO1
            if (voltage == 0.75f) return static_cast<uint8_t>(Ldo1Voltage::V_0_75);
            else if (voltage == 0.80f) return static_cast<uint8_t>(Ldo1Voltage::V_0_80);
            else if (voltage == 0.85f) return static_cast<uint8_t>(Ldo1Voltage::V_0_85);
            else if (voltage == 0.90f) return static_cast<uint8_t>(Ldo1Voltage::V_0_90);
            else if (voltage == 0.95f) return static_cast<uint8_t>(Ldo1Voltage::V_0_95);
            else if (voltage == 1.00f) return static_cast<uint8_t>(Ldo1Voltage::V_1_00);
            else if (voltage == 1.05f) return static_cast<uint8_t>(Ldo1Voltage::V_1_05);
            else if (voltage == 1.10f) return static_cast<uint8_t>(Ldo1Voltage::V_1_10);
            else if (voltage == 1.15f) return static_cast<uint8_t>(Ldo1Voltage::V_1_15);
            else if (voltage == 1.20f) return static_cast<uint8_t>(Ldo1Voltage::V_1_20);
            else if (voltage == 1.25f) return static_cast<uint8_t>(Ldo1Voltage::V_1_25);
            else if (voltage == 1.30f) return static_cast<uint8_t>(Ldo1Voltage::V_1_30);
            else if (voltage == 1.35f) return static_cast<uint8_t>(Ldo1Voltage::V_1_35);
            else if (voltage == 1.40f) return static_cast<uint8_t>(Ldo1Voltage::V_1_40);
            else if (voltage == 1.45f) return static_cast<uint8_t>(Ldo1Voltage::V_1_45);
            else if (voltage == 1.50f) return static_cast<uint8_t>(Ldo1Voltage::V_1_50);
            else if (voltage == 1.80f) return static_cast<uint8_t>(Ldo1Voltage::V_1_80);
            else if (voltage == 1.90f) return static_cast<uint8_t>(Ldo1Voltage::V_1_90);
            else if (voltage == 2.00f) return static_cast<uint8_t>(Ldo1Voltage::V_2_00);
            else if (voltage == 2.10f) return static_cast<uint8_t>(Ldo1Voltage::V_2_10);
            else if (voltage == 2.20f) return static_cast<uint8_t>(Ldo1Voltage::V_2_20);
            else if (voltage == 2.30f) return static_cast<uint8_t>(Ldo1Voltage::V_2_30);
            else if (voltage == 2.40f) return static_cast<uint8_t>(Ldo1Voltage::V_2_40);
            else if (voltage == 2.50f) return static_cast<uint8_t>(Ldo1Voltage::V_2_50);
            else if (voltage == 2.60f) return static_cast<uint8_t>(Ldo1Voltage::V_2_60);
            else if (voltage == 2.70f) return static_cast<uint8_t>(Ldo1Voltage::V_2_70);
            else if (voltage == 2.80f) return static_cast<uint8_t>(Ldo1Voltage::V_2_80);
            else if (voltage == 2.90f) return static_cast<uint8_t>(Ldo1Voltage::V_2_90);
            else if (voltage == 3.00f) return static_cast<uint8_t>(Ldo1Voltage::V_3_00);
            else if (voltage == 3.10f) return static_cast<uint8_t>(Ldo1Voltage::V_3_10);
            else if (voltage == 3.20f) return static_cast<uint8_t>(Ldo1Voltage::V_3_20);
            else if (voltage == 3.30f) return static_cast<uint8_t>(Ldo1Voltage::V_3_30);
            break;
            
        case 2: // LDO2
            if (voltage == 1.80f) return static_cast<uint8_t>(Ldo2Voltage::V_1_80);
            else if (voltage == 1.90f) return static_cast<uint8_t>(Ldo2Voltage::V_1_90);
            else if (voltage == 2.00f) return static_cast<uint8_t>(Ldo2Voltage::V_2_00);
            else if (voltage == 2.10f) return static_cast<uint8_t>(Ldo2Voltage::V_2_10);
            else if (voltage == 2.20f) return static_cast<uint8_t>(Ldo2Voltage::V_2_20);
            else if (voltage == 2.30f) return static_cast<uint8_t>(Ldo2Voltage::V_2_30);
            else if (voltage == 2.40f) return static_cast<uint8_t>(Ldo2Voltage::V_2_40);
            else if (voltage == 2.50f) return static_cast<uint8_t>(Ldo2Voltage::V_2_50);
            else if (voltage == 2.60f) return static_cast<uint8_t>(Ldo2Voltage::V_2_60);
            else if (voltage == 2.70f) return static_cast<uint8_t>(Ldo2Voltage::V_2_70);
            else if (voltage == 2.80f) return static_cast<uint8_t>(Ldo2Voltage::V_2_80);
            else if (voltage == 2.90f) return static_cast<uint8_t>(Ldo2Voltage::V_2_90);
            else if (voltage == 3.00f) return static_cast<uint8_t>(Ldo2Voltage::V_3_00);
            else if (voltage == 3.10f) return static_cast<uint8_t>(Ldo2Voltage::V_3_10);
            else if (voltage == 3.20f) return static_cast<uint8_t>(Ldo2Voltage::V_3_20);
            else if (voltage == 3.30f) return static_cast<uint8_t>(Ldo2Voltage::V_3_30);
            break;
            
        case 3: // SW1
            if (voltage == 1.10f) return static_cast<uint8_t>(Sw1Voltage::V_1_10);
            else if (voltage == 1.20f) return static_cast<uint8_t>(Sw1Voltage::V_1_20);
            else if (voltage == 1.35f) return static_cast<uint8_t>(Sw1Voltage::V_1_35);
            else if (voltage == 1.50f) return static_cast<uint8_t>(Sw1Voltage::V_1_50);
            else if (voltage == 1.80f) return static_cast<uint8_t>(Sw1Voltage::V_1_80);
            else if (voltage == 2.50f) return static_cast<uint8_t>(Sw1Voltage::V_2_50);
            else if (voltage == 3.00f) return static_cast<uint8_t>(Sw1Voltage::V_3_00);
            else if (voltage == 3.30f) return static_cast<uint8_t>(Sw1Voltage::V_3_30);
            break;

        case 4: // Sw2
          if (voltage == 1.10f) return static_cast<uint8_t>(Sw2Voltage::V_1_10);
            else if (voltage == 1.20f) return static_cast<uint8_t>(Sw2Voltage::V_1_20);
            else if (voltage == 1.35f) return static_cast<uint8_t>(Sw2Voltage::V_1_35);
            else if (voltage == 1.50f) return static_cast<uint8_t>(Sw2Voltage::V_1_50);
            else if (voltage == 1.80f) return static_cast<uint8_t>(Sw2Voltage::V_1_80);
            else if (voltage == 2.50f) return static_cast<uint8_t>(Sw2Voltage::V_2_50);
            else if (voltage == 3.00f) return static_cast<uint8_t>(Sw2Voltage::V_3_00);
            else if (voltage == 3.30f) return static_cast<uint8_t>(Sw2Voltage::V_3_30);
            break;

            
        default:
            return 0xFF;
            break;
    }
    
    return 0xFF;
}


#endif
