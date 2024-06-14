/*!
    \file    at24cxx.c
    \brief   the read and write function file

    \version 2022-04-16, V2.0.0, demo for GD32F30x
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "I2C.h"
#include "gd32f30x.h"

uint16_t i2cTimeout;


ErrStatus I2C_buff_write(uint32_t i2c_periph,uint8_t dev_addr, uint16_t write_address,uint16_t addr_len, uint8_t *p_buffer, uint8_t number_of_byte)
{
	//i2c_bus_reset();
    /* wait until I2C bus is idle */
	i2cTimeout = 0xFFFF;
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY))
	{
		if(!i2cTimeout--){
            //i2c_bus_reset();
			return ERROR;
        }
	};

    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);

    /* wait until SBSEND bit is set */
 
	i2cTimeout = 0xFFFF;
   while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND))
	{
		if(!i2cTimeout--){
            //i2c_bus_reset();
			return ERROR;
        }
	};
    

    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, dev_addr, I2C_TRANSMITTER);

	i2cTimeout = 0xFFFF;
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
		
	{
		if(!i2cTimeout--){
            //i2c_bus_reset();
			return ERROR;
        }
	};

    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph, I2C_FLAG_ADDSEND);

    /* wait until the transmit data buffer is empty */
	i2cTimeout = 0xFFFF;
    while(SET != i2c_flag_get(i2c_periph, I2C_FLAG_TBE))
		
	{
		if(!i2cTimeout--){
            //i2c_bus_reset();
			return ERROR;
        }
	};

    if(addr_len == 16){
        /* send the EEPROM's internal address to write to : only one byte address */
        i2c_data_transmit(i2c_periph, write_address >> 8);

        /* wait until BTC bit is set */
        i2cTimeout = 0xFFFF;
        while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
        {
            if(!i2cTimeout--){
                //i2c_bus_reset();
                return ERROR;
            }
        };
    }
	/* wait until the transmit data buffer is empty */
	i2cTimeout = 0xFFFF;
	  while(SET != i2c_flag_get(i2c_periph, I2C_FLAG_TBE))
		  {
			if(!i2cTimeout--){
            //i2c_bus_reset();
			return ERROR;
        }
		  };
	
	  /* send the EEPROM's internal address to write to : only one byte address */
	  i2c_data_transmit(i2c_periph, write_address & 0xFF);
	
	  /* wait until BTC bit is set */
	  i2cTimeout = 0xFFFF;
	  while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
		  {
		if(!i2cTimeout--){
            //i2c_bus_reset();
			return ERROR;
        }
		  };


    /* while there is data to be written */
    while(number_of_byte--) {
        i2c_data_transmit(i2c_periph, *p_buffer);

        /* point to the next byte to be written */
        p_buffer++;

        /* wait until BTC bit is set */
		i2cTimeout = 0xFFFF;
        while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
		{
		if(!i2cTimeout--){
            //i2c_bus_reset();
			return ERROR;
        }
		};
    }
    /* send a stop condition to I2C bus */
    i2c_stop_on_bus(i2c_periph);

    /* wait until the stop condition is finished */
	i2cTimeout = 0xFFFF;
    while(I2C_CTL0(i2c_periph) & 0x0200)
	{
		if(!i2cTimeout--){
            //i2c_bus_reset();
			return ERROR;
        }
	};
	return SUCCESS;
}

ErrStatus I2C_Byte_write(uint32_t i2c_periph,uint8_t dev_addr, uint16_t write_address,uint16_t addr_len, uint8_t p_buffer)
{
	//i2c_bus_reset();
    /* wait until I2C bus is idle */
	i2cTimeout = 0xFFFF;
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY))
	{
		if(!i2cTimeout--){
            //i2c_bus_reset();
			return ERROR;
        }
	};

    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);

    /* wait until SBSEND bit is set */
 
	i2cTimeout = 0xFFFF;
   while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND))
	{
		if(!i2cTimeout--){
            //i2c_bus_reset();
			return ERROR;
        }
	};
    

    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, dev_addr, I2C_TRANSMITTER);

	i2cTimeout = 0xFFFF;
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
		
	{
		if(!i2cTimeout--){
            //i2c_bus_reset();
			return ERROR;
        }
	};

    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph, I2C_FLAG_ADDSEND);

    /* wait until the transmit data buffer is empty */
	i2cTimeout = 0xFFFF;
    while(SET != i2c_flag_get(i2c_periph, I2C_FLAG_TBE))
		
	{
		if(!i2cTimeout--){
            //i2c_bus_reset();
			return ERROR;
        }
	};

    if(addr_len == 16){
        /* send the EEPROM's internal address to write to : only one byte address */
        i2c_data_transmit(i2c_periph, write_address >> 8);

        /* wait until BTC bit is set */
        i2cTimeout = 0xFFFF;
        while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
        {
            if(!i2cTimeout--){
                //i2c_bus_reset();
                return ERROR;
            }
        };
    }
	/* wait until the transmit data buffer is empty */
	i2cTimeout = 0xFFFF;
    while(SET != i2c_flag_get(i2c_periph, I2C_FLAG_TBE))
    {
        if(!i2cTimeout--){
            //i2c_bus_reset();
            return ERROR;
        }
    };
	
    /* send the EEPROM's internal address to write to : only one byte address */
    i2c_data_transmit(i2c_periph, write_address & 0xFF);

    /* wait until BTC bit is set */
    i2cTimeout = 0xFFFF;
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
	{
		if(!i2cTimeout--){
            //i2c_bus_reset();
			return ERROR;
        }
    };


    /* while there is data to be written */
   
    i2c_data_transmit(i2c_periph, p_buffer);

    
    /* wait until BTC bit is set */
    i2cTimeout = 0xFFFF;
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
    {
        if(!i2cTimeout--){
            //i2c_bus_reset();
            return ERROR;
        }
    };
  
    /* send a stop condition to I2C bus */
    i2c_stop_on_bus(i2c_periph);

    /* wait until the stop condition is finished */
	i2cTimeout = 0xFFFF;
    while(I2C_CTL0(i2c_periph) & 0x0200)
	{
		if(!i2cTimeout--){
            //i2c_bus_reset();
			return ERROR;
        }
	};
	return SUCCESS;
}

/*!
    \brief      read data from the EEPROM
    \param[in]  p_buffer: pointer to the buffer that receives the data read from the EEPROM
    \param[in]  read_address: EEPROM's internal address to start reading from
    \param[in]  number_of_byte: number of bytes to reads from the EEPROM
    \param[out] none
    \retval     none
*/

ErrStatus I2C_buffer_read( uint32_t i2c_periph,uint8_t dev_addr, uint16_t read_address,uint16_t addr_len, uint8_t *p_buffer, uint8_t number_of_byte)
{
	//i2c_bus_reset();
    i2c_0_bus_reset();
    /* wait until I2C bus is idle */
	i2cTimeout = 0xFFFF;
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY))
	{
		if(!i2cTimeout--)
			return ERROR;
	};

    if(2 == number_of_byte) {
        i2c_ackpos_config(i2c_periph, I2C_ACKPOS_NEXT);
    }

    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);

    /* wait until SBSEND bit is set */
	i2cTimeout = 0xFFFF;
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND))
	{
		if(!i2cTimeout--)
			return ERROR;
	};

    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, dev_addr, I2C_TRANSMITTER);

    /* wait until ADDSEND bit is set */
	i2cTimeout = 0xFFFF;
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
	{
		if(!i2cTimeout--)
			return ERROR;
	};

    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph, I2C_FLAG_ADDSEND);

    /* wait until the transmit data buffer is empty */
	i2cTimeout = 0xFFFF;
    while(SET != i2c_flag_get(i2c_periph, I2C_FLAG_TBE))
	{
		if(!i2cTimeout--)
			return ERROR;
	};

    /* enable i2c_periph*/
    i2c_enable(i2c_periph);
    if(addr_len ==  16){
        /* send the EEPROM's internal address to write to */
        i2c_data_transmit(i2c_periph, read_address >> 8);

        /* wait until BTC bit is set */
        i2cTimeout = 0xFFFF;
        while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
        {
            if(!i2cTimeout--)
                return ERROR;
        };
    }
    /* send the EEPROM's internal address to write to */
    i2c_data_transmit(i2c_periph, read_address & 0xFF);

    /* wait until BTC bit is set */
	i2cTimeout = 0xFFFF;
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
	{
		if(!i2cTimeout--)
			return ERROR;
	};

    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);

    /* wait until SBSEND bit is set */
	i2cTimeout = 0xFFFF;
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND))
	{
		if(!i2cTimeout--)
			return ERROR;
	};
    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, dev_addr, I2C_RECEIVER);

    if(number_of_byte < 3) {
        /* disable acknowledge */
        i2c_ack_config(i2c_periph, I2C_ACK_DISABLE);
    }

    /* wait until ADDSEND bit is set */
	i2cTimeout = 0xFFFF;
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
	{
		if(!i2cTimeout--)
			return ERROR;
	};

    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph, I2C_FLAG_ADDSEND);

    if(1 == number_of_byte) {
        /* send a stop condition to I2C bus */
        i2c_stop_on_bus(i2c_periph);
    }

    /* while there is data to be read */
    while(number_of_byte) {
        if(3 == number_of_byte) {
            /* wait until BTC bit is set */
			i2cTimeout = 0xFFFF;
            while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
			{
				if(!i2cTimeout--)
					return ERROR;
			};

            /* disable acknowledge */
            i2c_ack_config(i2c_periph, I2C_ACK_DISABLE);
        }
        if(2 == number_of_byte) {
            /* wait until BTC bit is set */
			i2cTimeout = 0xFFFF;
            while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC))
			{
				if(!i2cTimeout--)
					return ERROR;
			};

            /* send a stop condition to I2C bus */
            i2c_stop_on_bus(i2c_periph);
        }

        /* wait until the RBNE bit is set and clear it */
        if(i2c_flag_get(i2c_periph, I2C_FLAG_RBNE)) {
            /* read a byte from the EEPROM */
            *p_buffer = i2c_data_receive(i2c_periph);

            /* point to the next location where the byte read will be saved */
            p_buffer++;

            /* decrement the read bytes counter */
            number_of_byte--;
        }
    }

    /* wait until the stop condition is finished */
	i2cTimeout = 0xFFFF;
    while(I2C_CTL0(i2c_periph) & 0x0200)
	{
		if(!i2cTimeout--)
			return ERROR;
	};

    /* enable acknowledge */
    i2c_ack_config(i2c_periph, I2C_ACK_ENABLE);

    i2c_ackpos_config(i2c_periph, I2C_ACKPOS_CURRENT);
	return SUCCESS;
}



/*!
    \brief      wait for EEPROM standby state
    \param[in]  none
    \param[out] none
    \retval     none
*/
void I2C_wait_standby_state(uint32_t i2c_periph,uint8_t dev_addr)
{
    __IO uint32_t val = 0;

    while(1) {
        /* wait until I2C bus is idle */
        while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY));

        /* send a start condition to I2C bus */
        i2c_start_on_bus(i2c_periph);

        /* wait until SBSEND bit is set */
        while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND));

        /* send slave address to I2C bus */
        i2c_master_addressing(i2c_periph, dev_addr, I2C_TRANSMITTER);

        /* keep looping till the Address is acknowledged or the AE flag is set (address not acknowledged at time) */
        do {
            /* get the current value of the I2C_STAT0 register */
            val = I2C_STAT0(i2c_periph);

        } while(0 == (val & (I2C_STAT0_ADDSEND | I2C_STAT0_AERR)));

        /* check if the ADDSEND flag has been set */
        if(val & I2C_STAT0_ADDSEND) {

            /* clear ADDSEND flag */
            i2c_flag_clear(i2c_periph, I2C_FLAG_ADDSEND);

            /* send a stop condition to I2C bus */
            i2c_stop_on_bus(i2c_periph);

            /* exit the function */
            return ;

        } else {
            /* clear the bit of AE */
            i2c_flag_clear(i2c_periph, I2C_FLAG_AERR);
        }

        /* send a stop condition to I2C bus */
        i2c_stop_on_bus(i2c_periph);
        /* wait until the stop condition is finished */
        while(I2C_CTL0(i2c_periph) & 0x0200);
    }
}
