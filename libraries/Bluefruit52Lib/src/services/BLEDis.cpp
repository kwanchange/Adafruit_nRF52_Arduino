/**************************************************************************/
/*!
    @file     BLEDis.cpp
    @author   hathach

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2016, Adafruit Industries (adafruit.com)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#include "bluefruit.h"

BLEDis::BLEDis(void) : BLEService(UUID16_SVC_DEVICE_INFORMATION)
{
  _model        = NULL;
  _serial       = NULL;
  _firmware_rev = NULL;
  _hardware_rev = NULL;
  _software_rev = NULL;
  _manufacturer = NULL;
}

BLEDis::BLEDis(const char * model, const char * serial, const char * firmware_rev, 
               const char * hardware_rev, const char * software_rev, const char * manufacturer)
  : BLEService(UUID16_SVC_DEVICE_INFORMATION)
{
  _model        = model;
  _serial       = serial;
  _firmware_rev = firmware_rev;
  _hardware_rev = hardware_rev;
  _software_rev = software_rev;
  _manufacturer = manufacturer;
}

void BLEDis::setModel(const char* model)
{
  _model = model;
}

void BLEDis::setSerial(const char* serial)
{
  _serial = serial;
}

void BLEDis::setFirmwareRev(const char* fw_rev)
{
  _firmware_rev = fw_rev;
}

void BLEDis::setHardwareRev(const char* hw_rev)
{
  _hardware_rev = hw_rev;
}

void BLEDis::setSoftwareRev(const char* sw_rev)
{
  _software_rev = sw_rev;
}

void BLEDis::setManufacturer(const char* manufacturer)
{
  _manufacturer = manufacturer;
}

err_t BLEDis::start(void)
{
  VERIFY_STATUS( this->addToGatt() );

  for(uint8_t i=0; i<arrcount(_strarr); i++)
  {
    if ( _strarr[i] != NULL )
    {
      BLECharacteristic chars(UUID16_CHR_MODEL_NUMBER_STRING+i);

      chars.setProperties(CHR_PROPS_READ);
      chars.setFixedLen(strlen(_strarr[i]));

      VERIFY_STATUS( chars.start() );
      chars.write(_strarr[i]);
    }
  }

  return ERROR_NONE;
}
