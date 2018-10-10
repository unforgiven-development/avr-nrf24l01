/**
 * \file nrf24l01.h
 * \brief Defines the implementation of the nRF24L01(+) driver for AVR-LibC
 */


#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


#ifndef _NRF24L01_H__
#define _NRF24L01_H__


typedef struct _nRF24L01Message {
    int pipe_number;
    uint8_t data[32];
    uint8_t length;
} nRF24L01Message;


/*! \brief Defines a GPIO pin on an AVR microcontroller */
typedef struct _gpio_pin {
    volatile uint8_t *port;	/*!< The \b PORT of the \b AVR microcontroller on which the GPIO is located */
    uint8_t pin;			/*!< The \b PIN of the \b PORT on which the GPIO is located */
} gpio_pin;

/*! \brief Defines the physical connections between the AVR microcontroller and the nRF24L01(+) device */
typedef struct _nRF24L01 {
	gpio_pin ss;	/*!< The \b SPI (active-low) slave select signal */
	gpio_pin ce;	/*!< The \b nRF24L01(+) "chip enable" signal */
	gpio_pin sck;	/*!< The \b SPI serial clock signal */
	gpio_pin mosi;	/*!< The \b SPI "master-out slave-in" signal */
	gpio_pin miso;	/*!< The \b SPI "master-in slave-out" signal */
	gpio_pin irq;	/*!< The \b nRF24L01(+) interrupt-request signal */
	uint8_t status;
} nRF24L01;




nRF24L01 *nRF24L01_init(void);


void nRF24L01_begin(nRF24L01 *rf);


uint8_t nRF24L01_send_command(nRF24L01 *rf, uint8_t command, void *data, size_t length);


uint8_t nRF24L01_write_register(nRF24L01 *rf, uint8_t reg_address, void *data, size_t length);


uint8_t nRF24L01_read_register(nRF24L01 *rf, uint8_t regAddress, void *data, size_t length);


uint8_t nRF24L01_no_op(nRF24L01 *rf);


uint8_t nRF24L01_update_status(nRF24L01 *rf);


uint8_t nRF24L01_get_status(nRF24L01 *rf);


void nRF24L01_listen(nRF24L01 *rf, int pipe, uint8_t *address);


bool nRF24L01_data_received(nRF24L01 *rf);


bool nRF24L01_read_received_data(nRF24L01 *rf, nRF24L01Message *message);


int nRF24L01_pipe_number_received(nRF24L01 *rf);


void nRF24L01_transmit(nRF24L01 *rf, void *address, nRF24L01Message *msg);


int nRF24L01_transmit_success(nRF24L01 *rf);


void nRF24L01_flush_transmit_message(nRF24L01 *rf);


void nRF24L01_retry_transmit(nRF24L01 *rf);


void nRF24L01_clear_interrupts(nRF24L01 *rf);


void nRF24L01_clear_transmit_interrupts(nRF24L01 *rf);


void nRF24L01_clear_receive_interrupt(nRF24L01 *rf);



#endif	/* !_NRF24L01_H__ */
