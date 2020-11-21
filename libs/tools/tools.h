/*
 * tools.h
 *
 * Created: 09.06.2020 21:13:41
 *  Author: ar725
 */ 


#ifndef TOOLS_H_
#define TOOLS_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define SH(BITx) (1 << (BITx))
#define NSH(BITx) ~(1 << (BITx))
#define SB(PORTx, BITx) ((PORTx) |= (1 << (BITx)))
#define CB(PORTx, BITx) ((PORTx) &= ~(1 << (BITx)))
#define TB(PORTx, BITx) ((PORTx) ^= (1 << (BITx)))

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
(byte & 0x80 ? '1' : '0'), \
(byte & 0x40 ? '1' : '0'), \
(byte & 0x20 ? '1' : '0'), \
(byte & 0x10 ? '1' : '0'), \
(byte & 0x08 ? '1' : '0'), \
(byte & 0x04 ? '1' : '0'), \
(byte & 0x02 ? '1' : '0'), \
(byte & 0x01 ? '1' : '0')

#define WORD_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN
#define WORD_TO_BINARY(byte) BYTE_TO_BINARY(byte>>8), BYTE_TO_BINARY(byte)

#define DWORD_TO_BINARY_PATTERN WORD_TO_BINARY_PATTERN WORD_TO_BINARY_PATTERN
#define DWORD_TO_BINARY(byte) WORD_TO_BINARY(byte>>16), WORD_TO_BINARY(byte)

void delay_ms(uint16_t count);

#endif /* TOOLS_H_ */