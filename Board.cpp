#include "Board.h"


Board::Board() {}

Board::Board(PF1550 * _pPMIC) {
    this -> pPMIC = _pPMIC;

}


bool Board::isUSBPowered() {
    uint16_t reg_val = this -> pPMIC ->  readPMICreg(Register::CHARGER_VBUS_SNS);
    return getBitFromOffset(reg_val, 2) == 0;
}

bool Board::isBatteryPowered() {
    uint8_t reg_val = this -> pPMIC ->  readPMICreg(Register::CHARGER_BATT_SNS);
    uint8_t batPower = extractBits(reg_val, 0, 2);
    Serial.println(batPower);
    return batPower == 0;
}

void Board::setExternalSwitch(bool on) {
        if(on)
            this -> pPMIC -> getControlPointer()  -> turnSw2On(Sw2Mode::Normal);    
        else 
            this -> pPMIC -> getControlPointer()  -> turnSw2Off(Sw2Mode::Normal); 
}

bool Board::setExternalVoltage(float v) {
        this -> setExternalSwitch(false);
        uint8_t voltage_reg = getRailVoltage(v, 4);
        if (voltage_reg != 0xFF){
            this -> pPMIC ->  writePMICreg(Register::PMIC_SW2_VOLT, voltage_reg);
            if(this -> pPMIC ->  readPMICreg(Register::PMIC_SW2_VOLT) == voltage_reg){
                this -> setExternalSwitch(true);
                return true;
            } else 
                return false;
        } else {
            return false;
        }
}


#if defined(ARDUINO_NICLA_VISION)
void Board::setCameraSwitch(bool on) {
        if(on){
            this -> pPMIC -> getControlPointer() -> turnLDO1On(Ldo1Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO2On(Ldo2Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO3On(Ldo3Mode::Normal);
        } else {
            this -> pPMIC -> getControlPointer() -> turnLDO1Off(Ldo1Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO2Off(Ldo2Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO3Off(Ldo3Mode::Normal);
        }
}
#endif

#if defined(ARDUINO_PORTENTA_C33)
    void Board::lowPowerMode(bool on){
        if(!on){
          
            this -> pPMIC -> getControlPointer() -> clrBit(Register::PMIC_VSNVS_CTRL, (uint8_t)5);       


            this -> pPMIC -> getControlPointer() -> turnLDO1On(Ldo1Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO1On(Ldo1Mode::Sleep);
            this -> pPMIC -> getControlPointer() -> turnLDO1On(Ldo1Mode::Standby);

            this -> pPMIC -> getControlPointer() -> turnLDO2On(Ldo2Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO2On(Ldo2Mode::Sleep);
            this -> pPMIC -> getControlPointer() -> turnLDO2On(Ldo2Mode::Standby);

            this -> pPMIC -> getControlPointer() -> turnLDO3On(Ldo3Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO3On(Ldo3Mode::Sleep);
            this -> pPMIC -> getControlPointer() -> turnLDO3On(Ldo3Mode::Standby);

            this -> pPMIC -> getControlPointer() -> turnSw2On(Sw2Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnSw2On(Sw2Mode::Sleep);
            this -> pPMIC -> getControlPointer() -> turnSw2On(Sw2Mode::Standby);

            this -> pPMIC -> getControlPointer() ->  turnSw1On(Sw1Mode::Normal);
            this -> pPMIC -> getControlPointer() ->  turnSw1On(Sw1Mode::Sleep);
            this -> pPMIC -> getControlPointer() ->  turnSw1On(Sw1Mode::Standby);


         

        } else {

           this -> pPMIC -> getControlPointer() -> clrBit(Register::PMIC_VREFDDR_CTRL,  0);
            
            this -> pPMIC -> getControlPointer() -> setBit(Register::PMIC_VSNVS_CTRL,  (uint8_t)5);
           // this -> pPMIC -> getControlPointer() -> setBit(Register::PMIC_PWRCTRL3, 1);
        
        

            this -> pPMIC -> getControlPointer() -> clrBit(Register::PMIC_LDO1_CTRL, 0); // turns of LDO1
            this -> pPMIC -> getControlPointer() -> clrBit(Register::PMIC_LDO1_CTRL, 1); // turns of LDO1
            this -> pPMIC -> getControlPointer() -> clrBit(Register::PMIC_LDO1_CTRL, 2); // turns of LDO1
            this -> pPMIC -> getControlPointer() -> setBit(Register::PMIC_LDO1_CTRL, 3); //  enables low power mode for LDO1

            this -> pPMIC -> getControlPointer() -> clrBit(Register::PMIC_LDO2_CTRL, 0); // turns of LDO2
            this -> pPMIC -> getControlPointer() -> clrBit(Register::PMIC_LDO2_CTRL, 1); // turns of LDO2
            this -> pPMIC -> getControlPointer() -> clrBit(Register::PMIC_LDO2_CTRL, 2); // turns of LDO2
            this -> pPMIC -> getControlPointer() -> setBit(Register::PMIC_LDO2_CTRL, 3); //  enables low power mode for LDO2

            this -> pPMIC -> getControlPointer() -> clrBit(Register::PMIC_LDO3_CTRL, 0); // turns of LDO3 
            this -> pPMIC -> getControlPointer() -> clrBit(Register::PMIC_LDO3_CTRL, 1); //  enables low power mode for LDO3
            this -> pPMIC -> getControlPointer() -> clrBit(Register::PMIC_LDO3_CTRL, 2); //  enables low power mode for LDO3
            this -> pPMIC -> getControlPointer() -> setBit(Register::PMIC_LDO3_CTRL, 3); //  enables low power mode for LDO3

/*
            this -> pPMIC -> getControlPointer() -> turnLDO1Off(Ldo1Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO1Off(Ldo1Mode::Sleep);
            this -> pPMIC -> getControlPointer() -> turnLDO1Off(Ldo1Mode::Standby);

            this -> pPMIC -> getControlPointer() -> turnLDO2Off(Ldo2Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO2Off(Ldo2Mode::Sleep);
            this -> pPMIC -> getControlPointer() -> turnLDO2Off(Ldo2Mode::Standby);

            this -> pPMIC -> getControlPointer() -> turnLDO3Off(Ldo3Mode::Normal);
            this -> pPMIC -> getControlPointer() -> turnLDO3Off(Ldo3Mode::Sleep);
            this -> pPMIC -> getControlPointer() -> turnLDO3Off(Ldo3Mode::Standby);

*/

            this -> pPMIC -> getControlPointer() -> clrBit(Register::PMIC_SW2_CTRL, 0); // turns off BUCK       
            this -> pPMIC -> getControlPointer() -> setBit(Register::PMIC_SW2_CTRL, 3); // enables low power mode for BUCK 
            this -> pPMIC -> getControlPointer() -> setBit(Register::PMIC_SW2_CTRL, 7); // turns off load resistor

            this -> pPMIC -> getControlPointer() -> clrBit(Register::PMIC_SW1_CTRL, 0); // turns off BUCK       
            this -> pPMIC -> getControlPointer() -> setBit(Register::PMIC_SW1_CTRL, 3); // enables low power mode for BUCK 
            this -> pPMIC -> getControlPointer() -> setBit(Register::PMIC_SW1_CTRL,7);  // turns off load resistor

            this -> pPMIC -> getControlPointer() -> setBit(Register::PMIC_SW3_CTRL, 3); // enables low power mode for BUCK 
            this -> pPMIC -> getControlPointer() -> setBit(Register::PMIC_SW3_CTRL,7);  // turns off load resistor



            this -> pPMIC -> setPMICbit(Register::PMIC_VSNVS_CTRL, 5);
        }
       
    }

    void Board::setCommunicationSwitch(bool on){
        if(on)
            this -> pPMIC -> getControlPointer()  -> turnSw1On(Sw1Mode::Normal);     
        else
            this -> pPMIC -> getControlPointer()  -> turnSw1Off(Sw1Mode::Normal);   
    }

    bool Board::setAnalogVoltage(float v) {
        uint8_t voltage_reg = getRailVoltage(v, CONTEXT_LDO1);
        if (voltage_reg != 0xFF){
            this -> pPMIC ->  writePMICreg(Register::PMIC_LDO1_VOLT, voltage_reg);
            if(this -> pPMIC ->  readPMICreg(Register::PMIC_LDO1_VOLT) == voltage_reg)
                return true;
            else 
                return false;
        } else {
            return false;
        }
    }

    bool Board::setReferenceVoltage(float v){
        uint8_t voltage_reg = getRailVoltage(v, CONTEXT_LDO2);
        if (voltage_reg != 0xFF){
            this -> pPMIC ->  writePMICreg(Register::PMIC_LDO2_VOLT, voltage_reg);
            if(this -> pPMIC ->  readPMICreg(Register::PMIC_LDO2_VOLT) == voltage_reg)
                return true;
            else 
                return false;
        } else {
            return false;
        }
    }

#endif

