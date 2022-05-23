	.file	"dualMoco.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.RingBuffer_Insert,"ax",@progbits
	.type	RingBuffer_Insert, @function
RingBuffer_Insert:
.LFB77:
	.file 1 "Lib/LightweightRingBuff.h"
	.loc 1 160 0
	.cfi_startproc
.LVL0:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 161 0
	movw r30,r24
	subi r30,-128
	sbci r31,-1
	ld r26,Z
	ldd r27,Z+1
	st X,r22
	.loc 1 163 0
	ld r26,Z
	ldd r27,Z+1
	movw r18,r26
	subi r18,-1
	sbci r19,-1
	std Z+1,r19
	st Z,r18
	cp r18,r30
	cpc r19,r31
	brne .L2
	.loc 1 164 0
	adiw r26,1+1
	st X,r25
	st -X,r24
	sbiw r26,1
.L2:
.LBB41:
	.loc 1 166 0
	in r18,__SREG__
.LVL1:
.LBB42:
.LBB43:
	.file 2 "/usr/lib/avr/include/util/atomic.h"
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL2:
/* #NOAPP */
.LBE43:
.LBE42:
	.loc 1 168 0
	movw r30,r24
	subi r30,124
	sbci r31,-1
	ld r24,Z
.LVL3:
	subi r24,lo8(-(1))
	st Z,r24
.LVL4:
.LBB44:
.LBB45:
	.loc 2 70 0
	out __SREG__,r18
	.loc 2 71 0
.LVL5:
	ret
.LBE45:
.LBE44:
.LBE41:
	.cfi_endproc
.LFE77:
	.size	RingBuffer_Insert, .-RingBuffer_Insert
	.section	.text.RingBuffer_Remove,"ax",@progbits
	.type	RingBuffer_Remove, @function
RingBuffer_Remove:
.LFB78:
	.loc 1 183 0
	.cfi_startproc
.LVL6:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 184 0
	movw r26,r24
	subi r26,126
	sbci r27,-1
	ld r30,X+
	ld r31,X
	sbiw r26,1
	ld r18,Z+
.LVL7:
	.loc 1 186 0
	adiw r26,1
	st X,r31
	st -X,r30
	movw r20,r24
	subi r20,-128
	sbci r21,-1
	cp r30,r20
	cpc r31,r21
	brne .L5
	.loc 1 187 0
	st X+,r24
	st X,r25
.L5:
.LBB46:
	.loc 1 189 0
	in r19,__SREG__
.LVL8:
.LBB47:
.LBB48:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL9:
/* #NOAPP */
.LBE48:
.LBE47:
	.loc 1 191 0
	movw r30,r24
	subi r30,124
	sbci r31,-1
	ld r25,Z
	subi r25,lo8(-(-1))
	st Z,r25
.LVL10:
.LBB49:
.LBB50:
	.loc 2 70 0
	out __SREG__,r19
	.loc 2 71 0
.LVL11:
.LBE50:
.LBE49:
.LBE46:
	.loc 1 195 0
	mov r24,r18
.LVL12:
	ret
	.cfi_endproc
.LFE78:
	.size	RingBuffer_Remove, .-RingBuffer_Remove
	.section	.text.parseUSBMidiMessage,"ax",@progbits
.global	parseUSBMidiMessage
	.type	parseUSBMidiMessage, @function
parseUSBMidiMessage:
.LFB91:
	.file 3 "dualMoco.c"
	.loc 3 115 0
	.cfi_startproc
.LVL13:
	push r28
.LCFI0:
	.cfi_def_cfa_offset 3
	.cfi_offset 28, -2
	push r29
.LCFI1:
	.cfi_def_cfa_offset 4
	.cfi_offset 29, -3
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	movw r30,r24
	lds r25,uwptr
.LVL14:
.L14:
	.loc 3 116 0
	ld r19,Z
	mov r24,r19
	andi r24,lo8(15)
.LVL15:
	.loc 3 119 0
	cpi r24,lo8(2)
	brsh .L7
.L11:
	.loc 3 138 0
	cpi r22,lo8(5)
	brlo .L26
	.loc 3 139 0
	subi r22,lo8(-(-4))
	adiw r30,4
	rjmp .L14
.L7:
	movw r28,r30
	adiw r28,1
	.loc 3 119 0
	ldi r18,lo8(1)
	.loc 3 129 0
	andi r19,lo8(11)
	.loc 3 130 0
	ldi r20,lo8(-12)
	add r20,r24
.L13:
.LVL16:
	.loc 3 121 0
	ld r21,Y+
	mov r26,r25
	ldi r27,0
	subi r26,lo8(-(tx_buf))
	sbci r27,hi8(-(tx_buf))
	st X,r21
	.loc 3 122 0
	subi r25,lo8(-(1))
	andi r25,lo8(31)
	.loc 3 123 0
	cpi r18,lo8(1)
	brne .L10
.LVL17:
	.loc 3 124 0
	cpi r24,lo8(5)
	breq .L11
	.loc 3 124 0 is_stmt 0 discriminator 1
	cpi r24,lo8(15)
	brne .L12
	rjmp .L11
.LVL18:
.L10:
	.loc 3 128 0 is_stmt 1
	cpi r18,lo8(2)
	brne .L12
	.loc 3 129 0
	cpi r19,lo8(2)
	breq .L11
	.loc 3 130 0
	cpi r20,lo8(2)
	brlo .L11
.LVL19:
.L12:
	.loc 3 120 0 discriminator 2
	subi r18,lo8(-(1))
.LVL20:
	cpi r18,lo8(4)
	brne .L13
	rjmp .L11
.LVL21:
.L26:
	sts uwptr,r25
/* epilogue start */
	.loc 3 141 0
	pop r29
	pop r28
	ret
	.cfi_endproc
.LFE91:
	.size	parseUSBMidiMessage, .-parseUSBMidiMessage
	.section	.text.parseSerialMidiMessage,"ax",@progbits
.global	parseSerialMidiMessage
	.type	parseSerialMidiMessage, @function
parseSerialMidiMessage:
.LFB92:
	.loc 3 143 0
	.cfi_startproc
.LVL22:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	mov r25,r24
	.loc 3 165 0
	lds r24,SysEx.3320
.LVL23:
	tst r24
	breq .L28
	.loc 3 166 0
	cpi r25,lo8(-9)
	brne .L36
	.loc 3 167 0
	sts SysEx.3320,__zero_reg__
.L36:
	.loc 3 169 0
	ldi r24,0
	ret
.L28:
	.loc 3 171 0
	cpi r25,lo8(-8)
	brlo .L31
	.loc 3 172 0
	ldi r24,lo8(15)
	sts utx_buf,r24
	.loc 3 173 0
	sts utx_buf+1,r25
	.loc 3 174 0
	sts utx_buf+2,__zero_reg__
	.loc 3 175 0
	sts utx_buf+3,__zero_reg__
	rjmp .L37
.L31:
	.loc 3 179 0
	sbrs r25,7
	rjmp .L32
	.loc 3 180 0
	cpi r25,lo8(-16)
	brne .L33
	.loc 3 181 0
	ldi r25,lo8(1)
.LVL24:
	sts SysEx.3320,r25
	.loc 3 182 0
	ret
.LVL25:
.L33:
	.loc 3 184 0
	sts PC.3319,__zero_reg__
.L32:
	.loc 3 187 0
	lds r24,PC.3319
	cpse r24,__zero_reg__
	rjmp .L34
	.loc 3 188 0
	mov r19,r25
	swap r19
	andi r19,lo8(15)
	mov r18,r19
	andi r18,lo8(7)
	lsl r18
	subi r18,lo8(-(2))
	sts PC.3319,r18
	.loc 3 191 0
	sts rx_buf,r19
	.loc 3 192 0
	sts rx_buf+1,r25
	.loc 3 193 0
	sts rx_buf+3,__zero_reg__
	ret
.L34:
.LBB51:
	.loc 3 195 0
	mov r30,r24
	ldi r31,0
	subi r30,lo8(-(stateTransTable.3321))
	sbci r31,hi8(-(stateTransTable.3321))
	ld r20,Z
.LVL26:
	.loc 3 196 0
	mov r18,r24
	andi r18,1
	ldi r19,0
	movw r30,r18
	subi r30,lo8(-(rx_buf))
	sbci r31,hi8(-(rx_buf))
	std Z+2,r25
	.loc 3 197 0
	mov r24,r20
	andi r24,lo8(15)
	sts PC.3319,r24
	.loc 3 198 0
	sbrs r20,7
	rjmp .L36
	.loc 3 199 0
	ldi r24,lo8(4)
	ldi r30,lo8(rx_buf)
	ldi r31,hi8(rx_buf)
	ldi r26,lo8(utx_buf)
	ldi r27,hi8(utx_buf)
	0:
	ld r0,Z+
	st X+,r0
	dec r24
	brne 0b
.LVL27:
.L37:
	.loc 3 200 0
	ldi r24,lo8(1)
.LBE51:
	.loc 3 204 0
	ret
	.cfi_endproc
.LFE92:
	.size	parseSerialMidiMessage, .-parseSerialMidiMessage
	.section	.text.processMIDI,"ax",@progbits
.global	processMIDI
	.type	processMIDI, @function
processMIDI:
.LFB94:
	.loc 3 221 0
	.cfi_startproc
	push r28
.LCFI2:
	.cfi_def_cfa_offset 3
	.cfi_offset 28, -2
	push r29
.LCFI3:
	.cfi_def_cfa_offset 4
	.cfi_offset 29, -3
	rcall .
	rcall .
.LCFI4:
	.cfi_def_cfa_offset 8
	in r28,__SP_L__
	in r29,__SP_H__
.LCFI5:
	.cfi_def_cfa_register 28
/* prologue: function */
/* frame size = 4 */
/* stack size = 6 */
.L__stack_usage = 6
	.loc 3 222 0
/* #APP */
 ;  222 "dualMoco.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.LBB61:
	.loc 3 229 0
	ldi r17,lo8(3)
.L50:
	.loc 3 226 0
	lds r24,200
	sbrs r24,7
	rjmp .L39
	.loc 3 227 0
	lds r24,206
	call parseSerialMidiMessage
.LVL28:
	lds r25,utxrdy
	or r24,r25
	sts utxrdy,r24
.LVL29:
.LBB62:
.LBB63:
	.file 4 "./Board/LEDs.h"
	.loc 4 75 0
	cbi 0xb,5
.LVL30:
.LBE63:
.LBE62:
	.loc 3 229 0
	sts PulseMSRemaining,r17
.L39:
	.loc 3 233 0
	lds r24,utxrdy
	tst r24
	breq .L41
	.loc 3 234 0
	ldi r22,lo8(utx_buf)
	ldi r23,hi8(utx_buf)
	ldi r24,lo8(Keyboard_MIDI_Interface)
	ldi r25,hi8(Keyboard_MIDI_Interface)
	call MIDI_Device_SendEventPacket
.LVL31:
	.loc 3 235 0
	ldi r24,lo8(Keyboard_MIDI_Interface)
	ldi r25,hi8(Keyboard_MIDI_Interface)
	call MIDI_Device_Flush
.LVL32:
	.loc 3 236 0
	sts utxrdy,__zero_reg__
.L41:
	.loc 3 241 0
	movw r22,r28
	subi r22,-1
	sbci r23,-1
	ldi r24,lo8(Keyboard_MIDI_Interface)
	ldi r25,hi8(Keyboard_MIDI_Interface)
	call MIDI_Device_ReceiveEventPacket
.LVL33:
	tst r24
	breq .L60
	.loc 3 243 0
	ldi r22,lo8(4)
	movw r24,r28
	adiw r24,1
	call parseUSBMidiMessage
.LVL34:
.LBB64:
.LBB65:
	.loc 4 75 0
	cbi 0xb,4
.LVL35:
.LBE65:
.LBE64:
	.loc 3 245 0
	sts PulseMSRemaining+1,r17
	rjmp .L41
.L60:
	.loc 3 249 0
	lds r24,200
	sbrs r24,5
	rjmp .L43
	.loc 3 249 0 is_stmt 0 discriminator 1
	lds r30,irptr
	lds r24,uwptr
	cp r24,r30
	breq .L43
	.loc 3 250 0 is_stmt 1
	ldi r24,lo8(1)
	add r24,r30
	sts irptr,r24
	ldi r31,0
	subi r30,lo8(-(tx_buf))
	sbci r31,hi8(-(tx_buf))
	ld r24,Z
	sts 206,r24
	.loc 3 251 0
	lds r24,irptr
	andi r24,lo8(31)
	sts irptr,r24
.L43:
	.loc 3 254 0
	sbis 0x15,0
	rjmp .L45
	.loc 3 255 0
	sbi 0x15,0
	.loc 3 257 0
	lds r24,PulseMSRemaining
	tst r24
	breq .L47
	.loc 3 257 0 is_stmt 0 discriminator 1
	lds r24,PulseMSRemaining
	subi r24,lo8(-(-1))
	sts PulseMSRemaining,r24
	cpse r24,__zero_reg__
	rjmp .L47
.LVL36:
.LBB66:
.LBB67:
	.loc 4 80 0 is_stmt 1
	sbi 0xb,5
.LVL37:
.L47:
.LBE67:
.LBE66:
	.loc 3 261 0
	lds r24,PulseMSRemaining+1
	tst r24
	breq .L45
	.loc 3 261 0 is_stmt 0 discriminator 1
	lds r24,PulseMSRemaining+1
	subi r24,lo8(-(-1))
	sts PulseMSRemaining+1,r24
	cpse r24,__zero_reg__
	rjmp .L45
.LVL38:
.LBB68:
.LBB69:
	.loc 4 80 0 is_stmt 1
	sbi 0xb,4
.LVL39:
.L45:
.LBE69:
.LBE68:
	.loc 3 266 0
	call USB_USBTask
.LVL40:
.LBE61:
	.loc 3 267 0
	rjmp .L50
	.cfi_endproc
.LFE94:
	.size	processMIDI, .-processMIDI
	.section	.text.processSerial,"ax",@progbits
.global	processSerial
	.type	processSerial, @function
processSerial:
.LFB95:
	.loc 3 272 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
.LVL41:
.LBB121:
.LBB122:
	.loc 1 87 0
	in r18,__SREG__
.LVL42:
.LBB123:
.LBB124:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL43:
/* #NOAPP */
.LBE124:
.LBE123:
	.loc 1 89 0
	ldi r24,lo8(USBtoUSART_Buffer)
	ldi r25,hi8(USBtoUSART_Buffer)
	sts USBtoUSART_Buffer+128+1,r25
	sts USBtoUSART_Buffer+128,r24
	.loc 1 90 0
	sts USBtoUSART_Buffer+130+1,r25
	sts USBtoUSART_Buffer+130,r24
.LVL44:
.LBB125:
.LBB126:
	.loc 2 70 0
	out __SREG__,r18
	.loc 2 71 0
.LVL45:
.LBE126:
.LBE125:
.LBE122:
.LBE121:
.LBB127:
.LBB128:
	.loc 1 87 0
	in r18,__SREG__
.LVL46:
.LBB129:
.LBB130:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL47:
/* #NOAPP */
.LBE130:
.LBE129:
	.loc 1 89 0
	ldi r24,lo8(USARTtoUSB_Buffer)
	ldi r25,hi8(USARTtoUSB_Buffer)
	sts USARTtoUSB_Buffer+128+1,r25
	sts USARTtoUSB_Buffer+128,r24
	.loc 1 90 0
	sts USARTtoUSB_Buffer+130+1,r25
	sts USARTtoUSB_Buffer+130,r24
.LVL48:
.LBB131:
.LBB132:
	.loc 2 70 0
	out __SREG__,r18
	.loc 2 71 0
.LVL49:
.LBE132:
.LBE131:
.LBE128:
.LBE127:
	.loc 3 277 0
/* #APP */
 ;  277 "dualMoco.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.LBB133:
	.loc 3 299 0
	ldi r29,lo8(3)
.LVL50:
.L76:
.LBB134:
.LBB135:
.LBB136:
.LBB137:
	.loc 1 111 0
	in r25,__SREG__
.LVL51:
.LBB138:
.LBB139:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL52:
/* #NOAPP */
.LBE139:
.LBE138:
	.loc 1 113 0
	lds r24,USBtoUSART_Buffer+132
.LVL53:
.LBB140:
.LBB141:
	.loc 2 70 0
	out __SREG__,r25
	.loc 2 71 0
.LVL54:
.LBE141:
.LBE140:
.LBE137:
.LBE136:
.LBE135:
.LBE134:
	.loc 3 282 0
	cpi r24,lo8(-128)
	breq .L63
.LBB142:
	.loc 3 284 0
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	call CDC_Device_ReceiveByte
.LVL55:
	.loc 3 287 0
	sbrc r25,7
	rjmp .L63
	.loc 3 288 0
	mov r22,r24
	ldi r24,lo8(USBtoUSART_Buffer)
	ldi r25,hi8(USBtoUSART_Buffer)
.LVL56:
	call RingBuffer_Insert
.LVL57:
.L63:
.LBE142:
.LBB143:
.LBB144:
.LBB145:
	.loc 1 111 0
	in r24,__SREG__
.LVL58:
.LBB146:
.LBB147:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL59:
/* #NOAPP */
.LBE147:
.LBE146:
	.loc 1 113 0
	lds r28,USARTtoUSB_Buffer+132
.LVL60:
.LBB148:
.LBB149:
	.loc 2 70 0
	out __SREG__,r24
	.loc 2 71 0
.LVL61:
.LBE149:
.LBE148:
.LBE145:
.LBE144:
.LBE143:
	.loc 3 293 0
	sbic 0x15,0
	rjmp .L65
	.loc 3 293 0 is_stmt 0 discriminator 1
	cpi r28,lo8(97)
	brlo .L66
.L65:
	.loc 3 295 0 is_stmt 1
	sbi 0x15,0
	.loc 3 297 0
	lds r24,USARTtoUSB_Buffer+132
	tst r24
	breq .L68
.LVL62:
.LBB150:
.LBB151:
	.loc 4 75 0
	cbi 0xb,5
.LVL63:
.LBE151:
.LBE150:
	.loc 3 299 0
	sts PulseMSRemaining,r29
.L68:
.LVL64:
	.loc 3 303 0
	tst r28
	breq .L88
	.loc 3 304 0
	ldi r24,lo8(USARTtoUSB_Buffer)
	ldi r25,hi8(USARTtoUSB_Buffer)
	call RingBuffer_Remove
.LVL65:
	mov r22,r24
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	call CDC_Device_SendByte
.LVL66:
	subi r28,lo8(-(-1))
.LVL67:
	rjmp .L68
.LVL68:
.L88:
	.loc 3 307 0
	lds r24,PulseMSRemaining
	tst r24
	breq .L71
	.loc 3 307 0 is_stmt 0 discriminator 1
	lds r24,PulseMSRemaining
	subi r24,lo8(-(-1))
	sts PulseMSRemaining,r24
	cpse r24,__zero_reg__
	rjmp .L71
.LVL69:
.LBB152:
.LBB153:
	.loc 4 80 0 is_stmt 1
	sbi 0xb,5
.LVL70:
.L71:
.LBE153:
.LBE152:
	.loc 3 311 0
	lds r24,PulseMSRemaining+1
	tst r24
	breq .L66
	.loc 3 311 0 is_stmt 0 discriminator 1
	lds r24,PulseMSRemaining+1
	subi r24,lo8(-(-1))
	sts PulseMSRemaining+1,r24
	cpse r24,__zero_reg__
	rjmp .L66
.LVL71:
.LBB154:
.LBB155:
	.loc 4 80 0 is_stmt 1
	sbi 0xb,4
.LVL72:
.L66:
.LBE155:
.LBE154:
.LBB156:
.LBB157:
.LBB158:
.LBB159:
	.loc 1 111 0
	in r25,__SREG__
.LVL73:
.LBB160:
.LBB161:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/lib/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL74:
/* #NOAPP */
.LBE161:
.LBE160:
	.loc 1 113 0
	lds r24,USBtoUSART_Buffer+132
.LVL75:
.LBB162:
.LBB163:
	.loc 2 70 0
	out __SREG__,r25
	.loc 2 71 0
.LVL76:
.LBE163:
.LBE162:
.LBE159:
.LBE158:
.LBE157:
.LBE156:
	.loc 3 316 0
	tst r24
	breq .L74
	.loc 3 317 0
	ldi r24,lo8(USBtoUSART_Buffer)
	ldi r25,hi8(USBtoUSART_Buffer)
	call RingBuffer_Remove
.LVL77:
.L75:
.LBB164:
.LBB165:
	.file 5 "../LUFA/Drivers/Peripheral/Serial.h"
	.loc 5 142 0
	lds r25,200
	sbrs r25,5
	rjmp .L75
	.loc 5 143 0
	sts 206,r24
.LVL78:
.LBE165:
.LBE164:
.LBB166:
.LBB167:
	.loc 4 75 0
	cbi 0xb,4
.LVL79:
.LBE167:
.LBE166:
	.loc 3 320 0
	sts PulseMSRemaining+1,r29
.L74:
	.loc 3 323 0
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	call CDC_Device_USBTask
.LVL80:
	.loc 3 324 0
	call USB_USBTask
.LVL81:
.LBE133:
	.loc 3 325 0
	rjmp .L76
	.cfi_endproc
.LFE95:
	.size	processSerial, .-processSerial
	.section	.text.SetupHardware,"ax",@progbits
.global	SetupHardware
	.type	SetupHardware, @function
SetupHardware:
.LFB96:
	.loc 3 331 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 3 333 0
	in r24,0x34
	andi r24,lo8(-9)
	out 0x34,r24
.LBB174:
.LBB175:
	.file 6 "/usr/lib/avr/include/avr/wdt.h"
	.loc 6 515 0
/* #APP */
 ;  515 "/usr/lib/avr/include/avr/wdt.h" 1
	in __tmp_reg__,__SREG__
	cli
	wdr
	lds r24,96
	ori r24,24
	sts 96,r24
	sts 96,__zero_reg__
	out __SREG__,__tmp_reg__
	
 ;  0 "" 2
/* #NOAPP */
.LBE175:
.LBE174:
	.loc 3 336 0
	out 0x4,__zero_reg__
	.loc 3 337 0
	ldi r24,lo8(4)
	out 0x5,r24
	.loc 3 339 0
	sbic 0x3,2
	rjmp .L90
	.loc 3 340 0
	ldi r24,lo8(1)
	sts mocoMode,r24
.L90:
	.loc 3 344 0
	lds r24,mocoMode
	cpi r24,lo8(1)
	brne .L91
	.loc 3 346 0
	ldi r24,lo8(31)
	sts 204,r24
	.loc 3 348 0
	ldi r24,lo8(24)
	sts 201,r24
	rjmp .L92
.L91:
.LVL82:
.LBB176:
.LBB177:
	.loc 5 102 0
	ldi r24,lo8(103)
	ldi r25,0
	sts 204+1,r25
	sts 204,r24
	.loc 5 104 0
	ldi r24,lo8(6)
	sts 202,r24
	.loc 5 105 0
	sts 200,__zero_reg__
	.loc 5 106 0
	ldi r24,lo8(24)
	sts 201,r24
	.loc 5 108 0
	sbi 0xa,3
	.loc 5 109 0
	sbi 0xb,2
.LVL83:
.L92:
.LBE177:
.LBE176:
	.loc 3 353 0
	call USB_Init
.LVL84:
.LBB178:
.LBB179:
	.loc 4 69 0
	in r24,0xa
	ori r24,lo8(48)
	out 0xa,r24
	.loc 4 70 0
	in r24,0xb
	ori r24,lo8(48)
	out 0xb,r24
.LBE179:
.LBE178:
	.loc 3 357 0
	ldi r24,lo8(4)
	out 0x25,r24
	.loc 3 359 0
	lds r24,mocoMode
	cpse r24,__zero_reg__
	rjmp .L89
	.loc 3 361 0
	sbi 0xb,7
	.loc 3 362 0
	sbi 0xa,7
.L89:
	ret
	.cfi_endproc
.LFE96:
	.size	SetupHardware, .-SetupHardware
	.section	.text.startup.main,"ax",@progbits
.global	main
	.type	main, @function
main:
.LFB93:
	.loc 3 210 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 3 211 0
	call SetupHardware
.LVL85:
	.loc 3 213 0
	lds r24,mocoMode
	cpi r24,lo8(1)
	brne .L95
	.loc 3 214 0
	call processMIDI
.LVL86:
.L95:
	.loc 3 216 0
	call processSerial
.LVL87:
	.cfi_endproc
.LFE93:
	.size	main, .-main
	.section	.text.EVENT_USB_Device_Connect,"ax",@progbits
.global	EVENT_USB_Device_Connect
	.type	EVENT_USB_Device_Connect, @function
EVENT_USB_Device_Connect:
.LFB110:
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ret
	.cfi_endproc
.LFE110:
	.size	EVENT_USB_Device_Connect, .-EVENT_USB_Device_Connect
	.section	.text.EVENT_USB_Device_Disconnect,"ax",@progbits
.global	EVENT_USB_Device_Disconnect
	.type	EVENT_USB_Device_Disconnect, @function
EVENT_USB_Device_Disconnect:
.LFB108:
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ret
	.cfi_endproc
.LFE108:
	.size	EVENT_USB_Device_Disconnect, .-EVENT_USB_Device_Disconnect
	.section	.text.EVENT_USB_Device_ConfigurationChanged,"ax",@progbits
.global	EVENT_USB_Device_ConfigurationChanged
	.type	EVENT_USB_Device_ConfigurationChanged, @function
EVENT_USB_Device_ConfigurationChanged:
.LFB99:
	.loc 3 378 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 3 379 0
	lds r24,mocoMode
	cpi r24,lo8(1)
	brne .L99
.LVL88:
.LBB180:
	.loc 3 381 0
	ldi r24,lo8(Keyboard_MIDI_Interface)
	ldi r25,hi8(Keyboard_MIDI_Interface)
	jmp MIDI_Device_ConfigureEndpoints
.LVL89:
.L99:
.LBE180:
	.loc 3 383 0
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	jmp CDC_Device_ConfigureEndpoints
.LVL90:
	.cfi_endproc
.LFE99:
	.size	EVENT_USB_Device_ConfigurationChanged, .-EVENT_USB_Device_ConfigurationChanged
	.section	.text.EVENT_USB_Device_ControlRequest,"ax",@progbits
.global	EVENT_USB_Device_ControlRequest
	.type	EVENT_USB_Device_ControlRequest, @function
EVENT_USB_Device_ControlRequest:
.LFB100:
	.loc 3 389 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ret
	.cfi_endproc
.LFE100:
	.size	EVENT_USB_Device_ControlRequest, .-EVENT_USB_Device_ControlRequest
	.section	.text.EVENT_USB_Device_UnhandledControlRequest,"ax",@progbits
.global	EVENT_USB_Device_UnhandledControlRequest
	.type	EVENT_USB_Device_UnhandledControlRequest, @function
EVENT_USB_Device_UnhandledControlRequest:
.LFB101:
	.loc 3 397 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 3 398 0
	lds r24,mocoMode
	cpse r24,__zero_reg__
	rjmp .L101
	.loc 3 399 0
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	jmp CDC_Device_ProcessControlRequest
.LVL91:
.L101:
	ret
	.cfi_endproc
.LFE101:
	.size	EVENT_USB_Device_UnhandledControlRequest, .-EVENT_USB_Device_UnhandledControlRequest
	.section	.text.EVENT_CDC_Device_LineEncodingChanged,"ax",@progbits
.global	EVENT_CDC_Device_LineEncodingChanged
	.type	EVENT_CDC_Device_LineEncodingChanged, @function
EVENT_CDC_Device_LineEncodingChanged:
.LFB102:
	.loc 3 410 0
	.cfi_startproc
.LVL92:
	push r16
.LCFI6:
	.cfi_def_cfa_offset 3
	.cfi_offset 16, -2
	push r17
.LCFI7:
	.cfi_def_cfa_offset 4
	.cfi_offset 17, -3
	push r28
.LCFI8:
	.cfi_def_cfa_offset 5
	.cfi_offset 28, -4
/* prologue: function */
/* frame size = 0 */
/* stack size = 3 */
.L__stack_usage = 3
	movw r16,r24
.LVL93:
	.loc 3 413 0
	movw r30,r24
	ldd r24,Z+20
.LVL94:
	cpi r24,lo8(1)
	breq .L105
	cpi r24,lo8(2)
	brne .L118
.LVL95:
	.loc 3 419 0
	ldi r28,lo8(32)
	.loc 3 420 0
	rjmp .L104
.LVL96:
.L105:
	.loc 3 416 0
	ldi r28,lo8(48)
	rjmp .L104
.L118:
	.loc 3 411 0
	ldi r28,0
.LVL97:
.L104:
	.loc 3 423 0
	movw r30,r16
	ldd r24,Z+19
	cpi r24,lo8(2)
	brne .L107
	.loc 3 424 0
	ori r28,lo8(8)
.LVL98:
.L107:
	.loc 3 426 0
	movw r30,r16
	ldd r24,Z+21
	cpi r24,lo8(7)
	breq .L109
	cpi r24,lo8(8)
	breq .L110
	cpi r24,lo8(6)
	brne .L108
	.loc 3 429 0
	ori r28,lo8(2)
.LVL99:
	.loc 3 430 0
	rjmp .L108
.L109:
	.loc 3 432 0
	ori r28,lo8(4)
.LVL100:
	.loc 3 433 0
	rjmp .L108
.L110:
	.loc 3 435 0
	ori r28,lo8(6)
.LVL101:
.L108:
	.loc 3 440 0
	sts 201,__zero_reg__
	.loc 3 441 0
	sts 200,__zero_reg__
	.loc 3 442 0
	sts 202,__zero_reg__
	.loc 3 445 0
	movw r30,r16
	ldd r18,Z+15
	ldd r19,Z+16
	ldd r20,Z+17
	ldd r21,Z+18
	cp r18,__zero_reg__
	ldi r31,-31
	cpc r19,r31
	cpc r20,__zero_reg__
	cpc r21,__zero_reg__
	breq .L115
	.loc 3 445 0 is_stmt 0 discriminator 2
	movw r26,r20
	movw r24,r18
	lsr r27
	ror r26
	ror r25
	ror r24
	movw r22,r24
	movw r24,r26
	subi r22,-128
	sbci r23,123
	sbci r24,-31
	sbci r25,-1
	call __udivmodsi4
	subi r18,1
	sbc r19,__zero_reg__
	rjmp .L112
.L115:
	.loc 3 445 0
	ldi r18,lo8(16)
	ldi r19,0
.L112:
	.loc 3 445 0 discriminator 4
	sts 204+1,r19
	sts 204,r18
	.loc 3 449 0 is_stmt 1 discriminator 4
	sts 202,r28
	.loc 3 450 0 discriminator 4
	movw r30,r16
	ldd r24,Z+15
	ldd r25,Z+16
	ldd r26,Z+17
	ldd r27,Z+18
	cp r24,__zero_reg__
	sbci r25,-31
	cpc r26,__zero_reg__
	cpc r27,__zero_reg__
	breq .L116
	.loc 3 450 0 is_stmt 0
	ldi r24,lo8(2)
	rjmp .L113
.L116:
	ldi r24,0
.L113:
	.loc 3 450 0 discriminator 4
	sts 200,r24
	.loc 3 451 0 is_stmt 1 discriminator 4
	ldi r24,lo8(-104)
	sts 201,r24
/* epilogue start */
	.loc 3 452 0 discriminator 4
	pop r28
.LVL102:
	pop r17
	pop r16
.LVL103:
	ret
	.cfi_endproc
.LFE102:
	.size	EVENT_CDC_Device_LineEncodingChanged, .-EVENT_CDC_Device_LineEncodingChanged
	.section	.text.__vector_23,"ax",@progbits
.global	__vector_23
	.type	__vector_23, @function
__vector_23:
.LFB103:
	.loc 3 458 0
	.cfi_startproc
	push r1
.LCFI9:
	.cfi_def_cfa_offset 3
	.cfi_offset 1, -2
	push r0
.LCFI10:
	.cfi_def_cfa_offset 4
	.cfi_offset 0, -3
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
.LCFI11:
	.cfi_def_cfa_offset 5
	.cfi_offset 18, -4
	push r19
.LCFI12:
	.cfi_def_cfa_offset 6
	.cfi_offset 19, -5
	push r20
.LCFI13:
	.cfi_def_cfa_offset 7
	.cfi_offset 20, -6
	push r21
.LCFI14:
	.cfi_def_cfa_offset 8
	.cfi_offset 21, -7
	push r22
.LCFI15:
	.cfi_def_cfa_offset 9
	.cfi_offset 22, -8
	push r23
.LCFI16:
	.cfi_def_cfa_offset 10
	.cfi_offset 23, -9
	push r24
.LCFI17:
	.cfi_def_cfa_offset 11
	.cfi_offset 24, -10
	push r25
.LCFI18:
	.cfi_def_cfa_offset 12
	.cfi_offset 25, -11
	push r26
.LCFI19:
	.cfi_def_cfa_offset 13
	.cfi_offset 26, -12
	push r27
.LCFI20:
	.cfi_def_cfa_offset 14
	.cfi_offset 27, -13
	push r30
.LCFI21:
	.cfi_def_cfa_offset 15
	.cfi_offset 30, -14
	push r31
.LCFI22:
	.cfi_def_cfa_offset 16
	.cfi_offset 31, -15
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 15 */
.L__stack_usage = 15
	.loc 3 459 0
	lds r24,mocoMode
	cpse r24,__zero_reg__
	rjmp .L119
.LBB181:
	.loc 3 460 0
	lds r22,206
.LVL104:
	.loc 3 462 0
	in r24,0x1e
	cpi r24,lo8(4)
	brne .L119
	.loc 3 463 0
	ldi r24,lo8(USARTtoUSB_Buffer)
	ldi r25,hi8(USARTtoUSB_Buffer)
	call RingBuffer_Insert
.LVL105:
.L119:
/* epilogue start */
.LBE181:
	.loc 3 465 0
	pop r31
	pop r30
	pop r27
	pop r26
	pop r25
	pop r24
	pop r23
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r0
	out __SREG__,r0
	pop r0
	pop r1
	reti
	.cfi_endproc
.LFE103:
	.size	__vector_23, .-__vector_23
	.section	.text.EVENT_CDC_Device_ControLineStateChanged,"ax",@progbits
.global	EVENT_CDC_Device_ControLineStateChanged
	.type	EVENT_CDC_Device_ControLineStateChanged, @function
EVENT_CDC_Device_ControLineStateChanged:
.LFB104:
	.loc 3 472 0
	.cfi_startproc
.LVL106:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 3 475 0
	movw r30,r24
	ldd r24,Z+13
.LVL107:
	sbrs r24,0
	rjmp .L122
	.loc 3 476 0
	cbi 0xb,7
	ret
.L122:
	.loc 3 478 0
	sbi 0xb,7
	ret
	.cfi_endproc
.LFE104:
	.size	EVENT_CDC_Device_ControLineStateChanged, .-EVENT_CDC_Device_ControLineStateChanged
	.section	.rodata
	.type	stateTransTable.3321, @object
	.size	stateTransTable.3321, 16
stateTransTable.3321:
	.byte	0
	.byte	0
	.byte	3
	.byte	-126
	.byte	5
	.byte	-124
	.byte	7
	.byte	-122
	.byte	9
	.byte	-120
	.byte	-118
	.byte	0
	.byte	-116
	.byte	0
	.byte	15
	.byte	-114
	.local	PC.3319
	.comm	PC.3319,1,1
	.local	SysEx.3320
	.comm	SysEx.3320,1,1
.global	Keyboard_MIDI_Interface
	.data
	.type	Keyboard_MIDI_Interface, @object
	.size	Keyboard_MIDI_Interface, 9
Keyboard_MIDI_Interface:
	.byte	1
	.byte	2
	.word	64
	.byte	0
	.byte	1
	.word	64
	.byte	0
.global	VirtualSerial_CDC_Interface
	.type	VirtualSerial_CDC_Interface, @object
	.size	VirtualSerial_CDC_Interface, 22
VirtualSerial_CDC_Interface:
	.byte	0
	.byte	3
	.word	64
	.byte	0
	.byte	4
	.word	64
	.byte	0
	.byte	2
	.word	8
	.byte	0
	.zero	9
	.local	tx_buf
	.comm	tx_buf,32,1
	.local	irptr
	.comm	irptr,1,1
	.local	uwptr
	.comm	uwptr,1,1
	.local	utx_buf
	.comm	utx_buf,8,1
	.local	rx_buf
	.comm	rx_buf,8,1
	.local	utxrdy
	.comm	utxrdy,1,1
	.comm	PulseMSRemaining,3,1
	.comm	USARTtoUSB_Buffer,133,1
	.comm	USBtoUSART_Buffer,133,1
.global	mocoMode
	.section .bss
	.type	mocoMode, @object
	.size	mocoMode, 1
mocoMode:
	.zero	1
	.text
.Letext0:
	.file 7 "/usr/lib/avr/include/stdint.h"
	.file 8 "../LUFA/Drivers/USB/HighLevel/../LowLevel/Device.h"
	.file 9 "../LUFA/Drivers/USB/Class/Device/../Common/CDC.h"
	.file 10 "../LUFA/Drivers/USB/Class/Device/CDC.h"
	.file 11 "../LUFA/Drivers/USB/Class/Device/../Common/MIDI.h"
	.file 12 "../LUFA/Drivers/USB/Class/Device/MIDI.h"
	.file 13 "dualMoco.h"
	.file 14 "../LUFA/Drivers/USB/HighLevel/USBTask.h"
	.file 15 "../LUFA/Drivers/USB/HighLevel/../LowLevel/USBController.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x10d9
	.word	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF132
	.byte	0xc
	.long	.LASF133
	.long	.LASF134
	.long	.Ldebug_ranges0+0
	.long	0
	.long	0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF0
	.uleb128 0x3
	.long	.LASF2
	.byte	0x7
	.byte	0x7e
	.long	0x3b
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x3
	.long	.LASF3
	.byte	0x7
	.byte	0x7f
	.long	0x4d
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.long	.LASF4
	.byte	0x7
	.byte	0x80
	.long	0x5f
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF5
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.long	.LASF6
	.uleb128 0x3
	.long	.LASF7
	.byte	0x7
	.byte	0x82
	.long	0x78
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF9
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF10
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF11
	.uleb128 0x5
	.long	.LASF18
	.byte	0x1
	.long	0x3b
	.byte	0x8
	.byte	0x72
	.long	0xc9
	.uleb128 0x6
	.long	.LASF12
	.byte	0
	.uleb128 0x6
	.long	.LASF13
	.byte	0x1
	.uleb128 0x6
	.long	.LASF14
	.byte	0x2
	.uleb128 0x6
	.long	.LASF15
	.byte	0x3
	.uleb128 0x6
	.long	.LASF16
	.byte	0x4
	.uleb128 0x6
	.long	.LASF17
	.byte	0x5
	.byte	0
	.uleb128 0x5
	.long	.LASF19
	.byte	0x1
	.long	0x3b
	.byte	0x9
	.byte	0x9b
	.long	0xec
	.uleb128 0x6
	.long	.LASF20
	.byte	0
	.uleb128 0x6
	.long	.LASF21
	.byte	0x1
	.uleb128 0x6
	.long	.LASF22
	.byte	0x2
	.byte	0
	.uleb128 0x5
	.long	.LASF23
	.byte	0x1
	.long	0x3b
	.byte	0x9
	.byte	0xa3
	.long	0x11b
	.uleb128 0x6
	.long	.LASF24
	.byte	0
	.uleb128 0x6
	.long	.LASF25
	.byte	0x1
	.uleb128 0x6
	.long	.LASF26
	.byte	0x2
	.uleb128 0x6
	.long	.LASF27
	.byte	0x3
	.uleb128 0x6
	.long	.LASF28
	.byte	0x4
	.byte	0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF29
	.uleb128 0x7
	.byte	0xd
	.byte	0xa
	.byte	0x64
	.long	0x1b7
	.uleb128 0x8
	.long	.LASF30
	.byte	0xa
	.byte	0x66
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF31
	.byte	0xa
	.byte	0x68
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x8
	.long	.LASF32
	.byte	0xa
	.byte	0x69
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x8
	.long	.LASF33
	.byte	0xa
	.byte	0x6a
	.long	0x1b7
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.long	.LASF34
	.byte	0xa
	.byte	0x6c
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x5
	.uleb128 0x8
	.long	.LASF35
	.byte	0xa
	.byte	0x6d
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.uleb128 0x8
	.long	.LASF36
	.byte	0xa
	.byte	0x6e
	.long	0x1b7
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x8
	.long	.LASF37
	.byte	0xa
	.byte	0x70
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x9
	.uleb128 0x8
	.long	.LASF38
	.byte	0xa
	.byte	0x71
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0xa
	.uleb128 0x8
	.long	.LASF39
	.byte	0xa
	.byte	0x72
	.long	0x1b7
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.byte	0
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.long	.LASF40
	.uleb128 0x7
	.byte	0x2
	.byte	0xa
	.byte	0x78
	.long	0x1e3
	.uleb128 0x8
	.long	.LASF41
	.byte	0xa
	.byte	0x7a
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF42
	.byte	0xa
	.byte	0x7d
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.byte	0
	.uleb128 0x7
	.byte	0x7
	.byte	0xa
	.byte	0x83
	.long	0x224
	.uleb128 0x8
	.long	.LASF43
	.byte	0xa
	.byte	0x85
	.long	0x6d
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF44
	.byte	0xa
	.byte	0x86
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.long	.LASF45
	.byte	0xa
	.byte	0x89
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x5
	.uleb128 0x8
	.long	.LASF46
	.byte	0xa
	.byte	0x8c
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.byte	0
	.uleb128 0x7
	.byte	0x9
	.byte	0xa
	.byte	0x76
	.long	0x249
	.uleb128 0x8
	.long	.LASF47
	.byte	0xa
	.byte	0x81
	.long	0x1be
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF48
	.byte	0xa
	.byte	0x8d
	.long	0x1e3
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.byte	0
	.uleb128 0x7
	.byte	0x16
	.byte	0xa
	.byte	0x62
	.long	0x26e
	.uleb128 0x8
	.long	.LASF49
	.byte	0xa
	.byte	0x73
	.long	0x26e
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF50
	.byte	0xa
	.byte	0x90
	.long	0x224
	.byte	0x2
	.byte	0x23
	.uleb128 0xd
	.byte	0
	.uleb128 0x9
	.long	0x122
	.uleb128 0x3
	.long	.LASF51
	.byte	0xa
	.byte	0x93
	.long	0x249
	.uleb128 0x7
	.byte	0x4
	.byte	0xb
	.byte	0xae
	.long	0x2d3
	.uleb128 0xa
	.long	.LASF52
	.byte	0xb
	.byte	0xb0
	.long	0x3b
	.byte	0x1
	.byte	0x4
	.byte	0x4
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xa
	.long	.LASF53
	.byte	0xb
	.byte	0xb1
	.long	0x3b
	.byte	0x1
	.byte	0x4
	.byte	0
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF54
	.byte	0xb
	.byte	0xb3
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x8
	.long	.LASF55
	.byte	0xb
	.byte	0xb4
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x8
	.long	.LASF56
	.byte	0xb
	.byte	0xb5
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x3
	.byte	0
	.uleb128 0x3
	.long	.LASF57
	.byte	0xb
	.byte	0xb6
	.long	0x27e
	.uleb128 0x7
	.byte	0x9
	.byte	0xc
	.byte	0x52
	.long	0x349
	.uleb128 0x8
	.long	.LASF58
	.byte	0xc
	.byte	0x54
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF31
	.byte	0xc
	.byte	0x56
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x8
	.long	.LASF32
	.byte	0xc
	.byte	0x57
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x8
	.long	.LASF33
	.byte	0xc
	.byte	0x58
	.long	0x1b7
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.long	.LASF34
	.byte	0xc
	.byte	0x5a
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x5
	.uleb128 0x8
	.long	.LASF35
	.byte	0xc
	.byte	0x5b
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.uleb128 0x8
	.long	.LASF36
	.byte	0xc
	.byte	0x5c
	.long	0x1b7
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0xb
	.byte	0
	.byte	0xc
	.byte	0x60
	.uleb128 0x7
	.byte	0x9
	.byte	0xc
	.byte	0x50
	.long	0x372
	.uleb128 0x8
	.long	.LASF49
	.byte	0xc
	.byte	0x5d
	.long	0x372
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF50
	.byte	0xc
	.byte	0x63
	.long	0x349
	.byte	0x2
	.byte	0x23
	.uleb128 0x9
	.byte	0
	.uleb128 0x9
	.long	0x2de
	.uleb128 0x3
	.long	.LASF59
	.byte	0xc
	.byte	0x66
	.long	0x34d
	.uleb128 0x7
	.byte	0x85
	.byte	0x1
	.byte	0x46
	.long	0x3c5
	.uleb128 0x8
	.long	.LASF60
	.byte	0x1
	.byte	0x48
	.long	0x3c5
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xc
	.string	"In"
	.byte	0x1
	.byte	0x49
	.long	0x3d5
	.byte	0x3
	.byte	0x23
	.uleb128 0x80
	.uleb128 0xc
	.string	"Out"
	.byte	0x1
	.byte	0x4a
	.long	0x3d5
	.byte	0x3
	.byte	0x23
	.uleb128 0x82
	.uleb128 0x8
	.long	.LASF61
	.byte	0x1
	.byte	0x4b
	.long	0x30
	.byte	0x3
	.byte	0x23
	.uleb128 0x84
	.byte	0
	.uleb128 0xd
	.long	0x30
	.long	0x3d5
	.uleb128 0xe
	.long	0x8d
	.byte	0x7f
	.byte	0
	.uleb128 0xf
	.byte	0x2
	.long	0x30
	.uleb128 0x3
	.long	.LASF62
	.byte	0x1
	.byte	0x4c
	.long	0x382
	.uleb128 0x3
	.long	.LASF63
	.byte	0xd
	.byte	0x4e
	.long	0x30
	.uleb128 0x7
	.byte	0x3
	.byte	0x3
	.byte	0x39
	.long	0x424
	.uleb128 0x8
	.long	.LASF64
	.byte	0x3
	.byte	0x3b
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF65
	.byte	0x3
	.byte	0x3c
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x8
	.long	.LASF66
	.byte	0x3
	.byte	0x3d
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.byte	0
	.uleb128 0x10
	.long	.LASF69
	.byte	0x2
	.byte	0x44
	.byte	0x1
	.byte	0x3
	.long	0x43d
	.uleb128 0x11
	.string	"__s"
	.byte	0x2
	.byte	0x44
	.long	0x43d
	.byte	0
	.uleb128 0xf
	.byte	0x2
	.long	0x443
	.uleb128 0x9
	.long	0x30
	.uleb128 0x12
	.long	.LASF135
	.byte	0x2
	.byte	0x30
	.byte	0x1
	.long	0x30
	.byte	0x3
	.uleb128 0x13
	.long	.LASF77
	.byte	0x1
	.byte	0x6b
	.byte	0x1
	.long	0x30
	.byte	0x3
	.long	0x495
	.uleb128 0x14
	.long	.LASF60
	.byte	0x1
	.byte	0x6b
	.long	0x49b
	.uleb128 0x15
	.long	.LASF61
	.byte	0x1
	.byte	0x6d
	.long	0x30
	.uleb128 0x16
	.uleb128 0x15
	.long	.LASF67
	.byte	0x1
	.byte	0x6f
	.long	0x30
	.uleb128 0x15
	.long	.LASF68
	.byte	0x1
	.byte	0x6f
	.long	0x30
	.byte	0
	.byte	0
	.uleb128 0xf
	.byte	0x2
	.long	0x3db
	.uleb128 0x9
	.long	0x495
	.uleb128 0x10
	.long	.LASF70
	.byte	0xc
	.byte	0xa1
	.byte	0x1
	.byte	0x3
	.long	0x4b9
	.uleb128 0x14
	.long	.LASF71
	.byte	0xc
	.byte	0xa1
	.long	0x4bf
	.byte	0
	.uleb128 0xf
	.byte	0x2
	.long	0x377
	.uleb128 0x9
	.long	0x4b9
	.uleb128 0x10
	.long	.LASF72
	.byte	0x5
	.byte	0x8c
	.byte	0x1
	.byte	0x3
	.long	0x4dd
	.uleb128 0x14
	.long	.LASF73
	.byte	0x5
	.byte	0x8c
	.long	0x4dd
	.byte	0
	.uleb128 0x9
	.long	0x11b
	.uleb128 0x17
	.long	.LASF74
	.byte	0x6
	.word	0x1ec
	.byte	0x1
	.byte	0x3
	.long	0x4ff
	.uleb128 0x16
	.uleb128 0x18
	.long	.LASF75
	.byte	0x6
	.word	0x202
	.long	0x30
	.byte	0
	.byte	0
	.uleb128 0x10
	.long	.LASF76
	.byte	0xc
	.byte	0xac
	.byte	0x1
	.byte	0x3
	.long	0x518
	.uleb128 0x14
	.long	.LASF71
	.byte	0xc
	.byte	0xac
	.long	0x4bf
	.byte	0
	.uleb128 0x13
	.long	.LASF78
	.byte	0x1
	.byte	0x7f
	.byte	0x1
	.long	0x1b7
	.byte	0x3
	.long	0x535
	.uleb128 0x14
	.long	.LASF60
	.byte	0x1
	.byte	0x7f
	.long	0x49b
	.byte	0
	.uleb128 0x13
	.long	.LASF79
	.byte	0x1
	.byte	0x90
	.byte	0x1
	.long	0x1b7
	.byte	0x3
	.long	0x552
	.uleb128 0x14
	.long	.LASF60
	.byte	0x1
	.byte	0x90
	.long	0x49b
	.byte	0
	.uleb128 0x10
	.long	.LASF80
	.byte	0x5
	.byte	0x63
	.byte	0x1
	.byte	0x3
	.long	0x576
	.uleb128 0x14
	.long	.LASF81
	.byte	0x5
	.byte	0x63
	.long	0x576
	.uleb128 0x14
	.long	.LASF82
	.byte	0x5
	.byte	0x64
	.long	0x57b
	.byte	0
	.uleb128 0x9
	.long	0x6d
	.uleb128 0x9
	.long	0x1b7
	.uleb128 0x19
	.long	.LASF136
	.byte	0x1
	.byte	0x9e
	.byte	0x1
	.long	.LFB77
	.long	.LFE77
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x609
	.uleb128 0x1a
	.long	.LASF60
	.byte	0x1
	.byte	0x9e
	.long	0x49b
	.long	.LLST0
	.uleb128 0x1b
	.long	.LASF83
	.byte	0x1
	.byte	0x9f
	.long	0x443
	.byte	0x1
	.byte	0x66
	.uleb128 0x1c
	.long	.LBB41
	.long	.LBE41
	.uleb128 0x1d
	.long	.LASF67
	.byte	0x1
	.byte	0xa6
	.long	0x30
	.long	.LLST1
	.uleb128 0x1d
	.long	.LASF68
	.byte	0x1
	.byte	0xa6
	.long	0x30
	.long	.LLST2
	.uleb128 0x1e
	.long	0x448
	.long	.LBB42
	.long	.LBE42
	.byte	0x1
	.byte	0xa6
	.uleb128 0x1f
	.long	0x424
	.long	.LBB44
	.long	.LBE44
	.byte	0x1
	.byte	0xa6
	.uleb128 0x20
	.long	0x431
	.byte	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1470
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x21
	.long	.LASF137
	.byte	0x1
	.byte	0xb6
	.byte	0x1
	.long	0x30
	.long	.LFB78
	.long	.LFE78
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x696
	.uleb128 0x1a
	.long	.LASF60
	.byte	0x1
	.byte	0xb6
	.long	0x49b
	.long	.LLST3
	.uleb128 0x22
	.long	.LASF83
	.byte	0x1
	.byte	0xb8
	.long	0x30
	.byte	0x1
	.byte	0x62
	.uleb128 0x1c
	.long	.LBB46
	.long	.LBE46
	.uleb128 0x1d
	.long	.LASF67
	.byte	0x1
	.byte	0xbd
	.long	0x30
	.long	.LLST4
	.uleb128 0x1d
	.long	.LASF68
	.byte	0x1
	.byte	0xbd
	.long	0x30
	.long	.LLST5
	.uleb128 0x1e
	.long	0x448
	.long	.LBB47
	.long	.LBE47
	.byte	0x1
	.byte	0xbd
	.uleb128 0x1f
	.long	0x424
	.long	.LBB49
	.long	.LBE49
	.byte	0x1
	.byte	0xbd
	.uleb128 0x20
	.long	0x431
	.byte	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1611
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x23
	.byte	0x1
	.long	.LASF98
	.byte	0x3
	.byte	0x73
	.byte	0x1
	.long	.LFB91
	.long	.LFE91
	.long	.LLST6
	.byte	0x1
	.long	0x6e9
	.uleb128 0x1a
	.long	.LASF84
	.byte	0x3
	.byte	0x73
	.long	0x6e9
	.long	.LLST7
	.uleb128 0x24
	.string	"len"
	.byte	0x3
	.byte	0x73
	.long	0x3e6
	.long	.LLST8
	.uleb128 0x25
	.string	"cin"
	.byte	0x3
	.byte	0x74
	.long	0x3e6
	.byte	0x1
	.byte	0x68
	.uleb128 0x26
	.string	"i"
	.byte	0x3
	.byte	0x75
	.long	0x3e6
	.long	.LLST9
	.byte	0
	.uleb128 0xf
	.byte	0x2
	.long	0x3e6
	.uleb128 0x27
	.byte	0x1
	.long	.LASF91
	.byte	0x3
	.byte	0x8f
	.byte	0x1
	.long	0x3e6
	.long	.LFB92
	.long	.LFE92
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x767
	.uleb128 0x1a
	.long	.LASF85
	.byte	0x3
	.byte	0x8f
	.long	0x3e6
	.long	.LLST10
	.uleb128 0x25
	.string	"PC"
	.byte	0x3
	.byte	0x90
	.long	0x3e6
	.byte	0x5
	.byte	0x3
	.long	PC.3319
	.uleb128 0x22
	.long	.LASF86
	.byte	0x3
	.byte	0x91
	.long	0x3e6
	.byte	0x5
	.byte	0x3
	.long	SysEx.3320
	.uleb128 0x22
	.long	.LASF87
	.byte	0x3
	.byte	0x92
	.long	0x777
	.byte	0x5
	.byte	0x3
	.long	stateTransTable.3321
	.uleb128 0x1c
	.long	.LBB51
	.long	.LBE51
	.uleb128 0x26
	.string	"tt"
	.byte	0x3
	.byte	0xc3
	.long	0x3e6
	.long	.LLST11
	.byte	0
	.byte	0
	.uleb128 0xd
	.long	0x3e6
	.long	0x777
	.uleb128 0xe
	.long	0x8d
	.byte	0xf
	.byte	0
	.uleb128 0x9
	.long	0x767
	.uleb128 0x10
	.long	.LASF88
	.byte	0x4
	.byte	0x49
	.byte	0x1
	.byte	0x3
	.long	0x795
	.uleb128 0x14
	.long	.LASF89
	.byte	0x4
	.byte	0x49
	.long	0x443
	.byte	0
	.uleb128 0x10
	.long	.LASF90
	.byte	0x4
	.byte	0x4e
	.byte	0x1
	.byte	0x3
	.long	0x7ae
	.uleb128 0x14
	.long	.LASF89
	.byte	0x4
	.byte	0x4e
	.long	0x443
	.byte	0
	.uleb128 0x28
	.byte	0x1
	.long	.LASF92
	.byte	0x3
	.byte	0xdc
	.byte	0x1
	.byte	0x1
	.long	.LFB94
	.long	.LFE94
	.long	.LLST12
	.byte	0x1
	.long	0x8f5
	.uleb128 0x1c
	.long	.LBB61
	.long	.LBE61
	.uleb128 0x22
	.long	.LASF93
	.byte	0x3
	.byte	0xf0
	.long	0x2d3
	.byte	0x2
	.byte	0x8c
	.sleb128 1
	.uleb128 0x29
	.long	0x77c
	.long	.LBB62
	.long	.LBE62
	.byte	0x3
	.byte	0xe4
	.long	0x7fd
	.uleb128 0x2a
	.long	0x789
	.long	.LLST13
	.byte	0
	.uleb128 0x29
	.long	0x77c
	.long	.LBB64
	.long	.LBE64
	.byte	0x3
	.byte	0xf4
	.long	0x81a
	.uleb128 0x2a
	.long	0x789
	.long	.LLST14
	.byte	0
	.uleb128 0x2b
	.long	0x795
	.long	.LBB66
	.long	.LBE66
	.byte	0x3
	.word	0x102
	.long	0x838
	.uleb128 0x2a
	.long	0x7a2
	.long	.LLST15
	.byte	0
	.uleb128 0x2b
	.long	0x795
	.long	.LBB68
	.long	.LBE68
	.byte	0x3
	.word	0x106
	.long	0x856
	.uleb128 0x2a
	.long	0x7a2
	.long	.LLST16
	.byte	0
	.uleb128 0x2c
	.long	.LVL28
	.long	0x6ef
	.uleb128 0x2d
	.long	.LVL31
	.long	0x104b
	.long	0x889
	.uleb128 0x2e
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	Keyboard_MIDI_Interface
	.uleb128 0x2e
	.byte	0x6
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	utx_buf
	.byte	0
	.uleb128 0x2d
	.long	.LVL32
	.long	0x1058
	.long	0x8a5
	.uleb128 0x2e
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	Keyboard_MIDI_Interface
	.byte	0
	.uleb128 0x2d
	.long	.LVL33
	.long	0x1065
	.long	0x8cc
	.uleb128 0x2e
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	Keyboard_MIDI_Interface
	.uleb128 0x2e
	.byte	0x6
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.byte	0x2
	.byte	0x8c
	.sleb128 1
	.byte	0
	.uleb128 0x2d
	.long	.LVL34
	.long	0x696
	.long	0x8ea
	.uleb128 0x2e
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x2
	.byte	0x8c
	.sleb128 1
	.uleb128 0x2e
	.byte	0x1
	.byte	0x66
	.byte	0x1
	.byte	0x34
	.byte	0
	.uleb128 0x2c
	.long	.LVL40
	.long	0x1072
	.byte	0
	.byte	0
	.uleb128 0x10
	.long	.LASF94
	.byte	0x1
	.byte	0x55
	.byte	0x1
	.byte	0x3
	.long	0x926
	.uleb128 0x14
	.long	.LASF60
	.byte	0x1
	.byte	0x55
	.long	0x49b
	.uleb128 0x16
	.uleb128 0x15
	.long	.LASF67
	.byte	0x1
	.byte	0x57
	.long	0x30
	.uleb128 0x15
	.long	.LASF68
	.byte	0x1
	.byte	0x57
	.long	0x30
	.byte	0
	.byte	0
	.uleb128 0x2f
	.byte	0x1
	.long	.LASF95
	.byte	0x3
	.word	0x10f
	.byte	0x1
	.byte	0x1
	.long	.LFB95
	.long	.LFE95
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xd01
	.uleb128 0x2b
	.long	0x8f5
	.long	.LBB121
	.long	.LBE121
	.byte	0x3
	.word	0x112
	.long	0x9a0
	.uleb128 0x30
	.long	0x902
	.uleb128 0x1c
	.long	.LBB122
	.long	.LBE122
	.uleb128 0x31
	.long	0x90e
	.long	.LLST17
	.uleb128 0x31
	.long	0x919
	.long	.LLST18
	.uleb128 0x1e
	.long	0x448
	.long	.LBB123
	.long	.LBE123
	.byte	0x1
	.byte	0x57
	.uleb128 0x1f
	.long	0x424
	.long	.LBB125
	.long	.LBE125
	.byte	0x1
	.byte	0x57
	.uleb128 0x2a
	.long	0x431
	.long	.LLST19
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2b
	.long	0x8f5
	.long	.LBB127
	.long	.LBE127
	.byte	0x3
	.word	0x113
	.long	0x9fe
	.uleb128 0x30
	.long	0x902
	.uleb128 0x1c
	.long	.LBB128
	.long	.LBE128
	.uleb128 0x31
	.long	0x90e
	.long	.LLST20
	.uleb128 0x31
	.long	0x919
	.long	.LLST21
	.uleb128 0x1e
	.long	0x448
	.long	.LBB129
	.long	.LBE129
	.byte	0x1
	.byte	0x57
	.uleb128 0x1f
	.long	0x424
	.long	.LBB131
	.long	.LBE131
	.byte	0x1
	.byte	0x57
	.uleb128 0x2a
	.long	0x431
	.long	.LLST22
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1c
	.long	.LBB133
	.long	.LBE133
	.uleb128 0x32
	.long	.LASF96
	.byte	0x3
	.word	0x124
	.long	0x30
	.long	.LLST23
	.uleb128 0x2b
	.long	0x518
	.long	.LBB134
	.long	.LBE134
	.byte	0x3
	.word	0x11a
	.long	0xa9d
	.uleb128 0x30
	.long	0x529
	.uleb128 0x1f
	.long	0x455
	.long	.LBB135
	.long	.LBE135
	.byte	0x1
	.byte	0x81
	.uleb128 0x30
	.long	0x466
	.uleb128 0x1c
	.long	.LBB136
	.long	.LBE136
	.uleb128 0x31
	.long	0x471
	.long	.LLST24
	.uleb128 0x1c
	.long	.LBB137
	.long	.LBE137
	.uleb128 0x31
	.long	0x47d
	.long	.LLST25
	.uleb128 0x31
	.long	0x488
	.long	.LLST26
	.uleb128 0x1e
	.long	0x448
	.long	.LBB138
	.long	.LBE138
	.byte	0x1
	.byte	0x6f
	.uleb128 0x1f
	.long	0x424
	.long	.LBB140
	.long	.LBE140
	.byte	0x1
	.byte	0x6f
	.uleb128 0x2a
	.long	0x431
	.long	.LLST27
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x33
	.long	.LBB142
	.long	.LBE142
	.long	0xaef
	.uleb128 0x32
	.long	.LASF97
	.byte	0x3
	.word	0x11c
	.long	0x42
	.long	.LLST28
	.uleb128 0x2d
	.long	.LVL55
	.long	0x107f
	.long	0xad6
	.uleb128 0x2e
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.byte	0
	.uleb128 0x34
	.long	.LVL57
	.long	0x580
	.uleb128 0x2e
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	USBtoUSART_Buffer
	.byte	0
	.byte	0
	.uleb128 0x2b
	.long	0x455
	.long	.LBB143
	.long	.LBE143
	.byte	0x3
	.word	0x124
	.long	0xb60
	.uleb128 0x30
	.long	0x466
	.uleb128 0x1c
	.long	.LBB144
	.long	.LBE144
	.uleb128 0x31
	.long	0x471
	.long	.LLST29
	.uleb128 0x1c
	.long	.LBB145
	.long	.LBE145
	.uleb128 0x31
	.long	0x47d
	.long	.LLST30
	.uleb128 0x31
	.long	0x488
	.long	.LLST31
	.uleb128 0x1e
	.long	0x448
	.long	.LBB146
	.long	.LBE146
	.byte	0x1
	.byte	0x6f
	.uleb128 0x1f
	.long	0x424
	.long	.LBB148
	.long	.LBE148
	.byte	0x1
	.byte	0x6f
	.uleb128 0x2a
	.long	0x431
	.long	.LLST32
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2b
	.long	0x77c
	.long	.LBB150
	.long	.LBE150
	.byte	0x3
	.word	0x12a
	.long	0xb7e
	.uleb128 0x2a
	.long	0x789
	.long	.LLST33
	.byte	0
	.uleb128 0x2b
	.long	0x795
	.long	.LBB152
	.long	.LBE152
	.byte	0x3
	.word	0x134
	.long	0xb9c
	.uleb128 0x2a
	.long	0x7a2
	.long	.LLST34
	.byte	0
	.uleb128 0x2b
	.long	0x795
	.long	.LBB154
	.long	.LBE154
	.byte	0x3
	.word	0x138
	.long	0xbba
	.uleb128 0x2a
	.long	0x7a2
	.long	.LLST35
	.byte	0
	.uleb128 0x2b
	.long	0x535
	.long	.LBB156
	.long	.LBE156
	.byte	0x3
	.word	0x13c
	.long	0xc4a
	.uleb128 0x30
	.long	0x546
	.uleb128 0x1f
	.long	0x455
	.long	.LBB157
	.long	.LBE157
	.byte	0x1
	.byte	0x92
	.uleb128 0x20
	.long	0x466
	.byte	0x6
	.byte	0x3
	.long	USBtoUSART_Buffer
	.byte	0x9f
	.uleb128 0x1c
	.long	.LBB158
	.long	.LBE158
	.uleb128 0x31
	.long	0x471
	.long	.LLST36
	.uleb128 0x1c
	.long	.LBB159
	.long	.LBE159
	.uleb128 0x31
	.long	0x47d
	.long	.LLST37
	.uleb128 0x31
	.long	0x488
	.long	.LLST38
	.uleb128 0x1e
	.long	0x448
	.long	.LBB160
	.long	.LBE160
	.byte	0x1
	.byte	0x6f
	.uleb128 0x1f
	.long	0x424
	.long	.LBB162
	.long	.LBE162
	.byte	0x1
	.byte	0x6f
	.uleb128 0x20
	.long	0x431
	.byte	0x6
	.byte	0xf2
	.long	.Ldebug_info0+3081
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2b
	.long	0x4c4
	.long	.LBB164
	.long	.LBE164
	.byte	0x3
	.word	0x13d
	.long	0xc68
	.uleb128 0x2a
	.long	0x4d1
	.long	.LLST39
	.byte	0
	.uleb128 0x2b
	.long	0x77c
	.long	.LBB166
	.long	.LBE166
	.byte	0x3
	.word	0x13f
	.long	0xc86
	.uleb128 0x2a
	.long	0x789
	.long	.LLST40
	.byte	0
	.uleb128 0x2d
	.long	.LVL65
	.long	0x609
	.long	0xca2
	.uleb128 0x2e
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	USARTtoUSB_Buffer
	.byte	0
	.uleb128 0x2d
	.long	.LVL66
	.long	0x108d
	.long	0xcbe
	.uleb128 0x2e
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.byte	0
	.uleb128 0x2d
	.long	.LVL77
	.long	0x609
	.long	0xcda
	.uleb128 0x2e
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	USBtoUSART_Buffer
	.byte	0
	.uleb128 0x2d
	.long	.LVL80
	.long	0x109a
	.long	0xcf6
	.uleb128 0x2e
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.byte	0
	.uleb128 0x2c
	.long	.LVL81
	.long	0x1072
	.byte	0
	.byte	0
	.uleb128 0x35
	.long	.LASF138
	.byte	0x4
	.byte	0x43
	.byte	0x1
	.byte	0x3
	.uleb128 0x36
	.byte	0x1
	.long	.LASF99
	.byte	0x3
	.word	0x14a
	.byte	0x1
	.long	.LFB96
	.long	.LFE96
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xd8a
	.uleb128 0x2b
	.long	0x4e2
	.long	.LBB174
	.long	.LBE174
	.byte	0x3
	.word	0x14e
	.long	0xd49
	.uleb128 0x1c
	.long	.LBB175
	.long	.LBE175
	.uleb128 0x37
	.long	0x4f1
	.byte	0
	.byte	0
	.uleb128 0x2b
	.long	0x552
	.long	.LBB176
	.long	.LBE176
	.byte	0x3
	.word	0x15e
	.long	0xd70
	.uleb128 0x2a
	.long	0x55f
	.long	.LLST41
	.uleb128 0x2a
	.long	0x56a
	.long	.LLST42
	.byte	0
	.uleb128 0x38
	.long	0xd01
	.long	.LBB178
	.long	.LBE178
	.byte	0x3
	.word	0x162
	.uleb128 0x2c
	.long	.LVL84
	.long	0x10a7
	.byte	0
	.uleb128 0x39
	.byte	0x1
	.long	.LASF139
	.byte	0x3
	.byte	0xd1
	.byte	0x1
	.long	0x4d
	.byte	0x1
	.long	.LFB93
	.long	.LFE93
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xdc5
	.uleb128 0x2c
	.long	.LVL85
	.long	0xd0a
	.uleb128 0x2c
	.long	.LVL86
	.long	0x7ae
	.uleb128 0x2c
	.long	.LVL87
	.long	0x926
	.byte	0
	.uleb128 0x36
	.byte	0x1
	.long	.LASF100
	.byte	0x3
	.word	0x179
	.byte	0x1
	.long	.LFB99
	.long	.LFE99
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xe31
	.uleb128 0x33
	.long	.LBB180
	.long	.LBE180
	.long	0xe17
	.uleb128 0x32
	.long	.LASF101
	.byte	0x3
	.word	0x17c
	.long	0x1b7
	.long	.LLST43
	.uleb128 0x3a
	.long	.LVL89
	.byte	0x1
	.long	0x10b5
	.uleb128 0x2e
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	Keyboard_MIDI_Interface
	.byte	0
	.byte	0
	.uleb128 0x3a
	.long	.LVL90
	.byte	0x1
	.long	0x10c2
	.uleb128 0x2e
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.byte	0
	.byte	0
	.uleb128 0x3b
	.byte	0x1
	.long	.LASF140
	.byte	0x3
	.word	0x184
	.byte	0x1
	.byte	0x1
	.uleb128 0x3c
	.long	0xe31
	.long	.LFB100
	.long	.LFE100
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.uleb128 0x36
	.byte	0x1
	.long	.LASF102
	.byte	0x3
	.word	0x18c
	.byte	0x1
	.long	.LFB101
	.long	.LFE101
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xe83
	.uleb128 0x3a
	.long	.LVL91
	.byte	0x1
	.long	0x10cf
	.uleb128 0x2e
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.byte	0
	.byte	0
	.uleb128 0x3d
	.byte	0x1
	.long	.LASF103
	.byte	0x3
	.word	0x199
	.byte	0x1
	.long	.LFB102
	.long	.LFE102
	.long	.LLST44
	.byte	0x1
	.long	0xebf
	.uleb128 0x3e
	.long	.LASF104
	.byte	0x3
	.word	0x199
	.long	0xec5
	.long	.LLST45
	.uleb128 0x32
	.long	.LASF105
	.byte	0x3
	.word	0x19b
	.long	0x30
	.long	.LLST46
	.byte	0
	.uleb128 0xf
	.byte	0x2
	.long	0x273
	.uleb128 0x9
	.long	0xebf
	.uleb128 0x3d
	.byte	0x1
	.long	.LASF106
	.byte	0x3
	.word	0x1c9
	.byte	0x1
	.long	.LFB103
	.long	.LFE103
	.long	.LLST47
	.byte	0x1
	.long	0xf18
	.uleb128 0x1c
	.long	.LBB181
	.long	.LBE181
	.uleb128 0x32
	.long	.LASF97
	.byte	0x3
	.word	0x1cc
	.long	0x30
	.long	.LLST48
	.uleb128 0x34
	.long	.LVL105
	.long	0x580
	.uleb128 0x2e
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x5
	.byte	0x3
	.long	USARTtoUSB_Buffer
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x36
	.byte	0x1
	.long	.LASF107
	.byte	0x3
	.word	0x1d7
	.byte	0x1
	.long	.LFB104
	.long	.LFE104
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xf54
	.uleb128 0x3e
	.long	.LASF104
	.byte	0x3
	.word	0x1d7
	.long	0xec5
	.long	.LLST49
	.uleb128 0x32
	.long	.LASF108
	.byte	0x3
	.word	0x1d9
	.long	0x1b7
	.long	.LLST50
	.byte	0
	.uleb128 0x22
	.long	.LASF109
	.byte	0x3
	.byte	0x41
	.long	0x3e6
	.byte	0x5
	.byte	0x3
	.long	utxrdy
	.uleb128 0xd
	.long	0x3e6
	.long	0xf75
	.uleb128 0xe
	.long	0x8d
	.byte	0x7
	.byte	0
	.uleb128 0x22
	.long	.LASF110
	.byte	0x3
	.byte	0x42
	.long	0xf65
	.byte	0x5
	.byte	0x3
	.long	rx_buf
	.uleb128 0x22
	.long	.LASF111
	.byte	0x3
	.byte	0x43
	.long	0xf65
	.byte	0x5
	.byte	0x3
	.long	utx_buf
	.uleb128 0x22
	.long	.LASF112
	.byte	0x3
	.byte	0x47
	.long	0x3e6
	.byte	0x5
	.byte	0x3
	.long	uwptr
	.uleb128 0x22
	.long	.LASF113
	.byte	0x3
	.byte	0x47
	.long	0x3e6
	.byte	0x5
	.byte	0x3
	.long	irptr
	.uleb128 0xd
	.long	0x3e6
	.long	0xfc9
	.uleb128 0xe
	.long	0x8d
	.byte	0x1f
	.byte	0
	.uleb128 0x22
	.long	.LASF114
	.byte	0x3
	.byte	0x48
	.long	0xfb9
	.byte	0x5
	.byte	0x3
	.long	tx_buf
	.uleb128 0x3f
	.long	.LASF115
	.byte	0x3
	.byte	0x30
	.long	0x3e6
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	mocoMode
	.uleb128 0x3f
	.long	.LASF116
	.byte	0x3
	.byte	0x33
	.long	0x3db
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	USBtoUSART_Buffer
	.uleb128 0x3f
	.long	.LASF117
	.byte	0x3
	.byte	0x36
	.long	0x3db
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	USARTtoUSB_Buffer
	.uleb128 0x3f
	.long	.LASF118
	.byte	0x3
	.byte	0x3e
	.long	0x1022
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	PulseMSRemaining
	.uleb128 0x40
	.long	0x3f1
	.uleb128 0x3f
	.long	.LASF119
	.byte	0x3
	.byte	0x4f
	.long	0x273
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.uleb128 0x3f
	.long	.LASF120
	.byte	0x3
	.byte	0x63
	.long	0x377
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	Keyboard_MIDI_Interface
	.uleb128 0x41
	.byte	0x1
	.byte	0x1
	.long	.LASF121
	.long	.LASF121
	.byte	0xc
	.byte	0x7f
	.uleb128 0x41
	.byte	0x1
	.byte	0x1
	.long	.LASF122
	.long	.LASF122
	.byte	0xc
	.byte	0x8a
	.uleb128 0x41
	.byte	0x1
	.byte	0x1
	.long	.LASF123
	.long	.LASF123
	.byte	0xc
	.byte	0x97
	.uleb128 0x41
	.byte	0x1
	.byte	0x1
	.long	.LASF124
	.long	.LASF124
	.byte	0xe
	.byte	0xb2
	.uleb128 0x42
	.byte	0x1
	.byte	0x1
	.long	.LASF125
	.long	.LASF125
	.byte	0xa
	.word	0x106
	.uleb128 0x41
	.byte	0x1
	.byte	0x1
	.long	.LASF126
	.long	.LASF126
	.byte	0xa
	.byte	0xe9
	.uleb128 0x41
	.byte	0x1
	.byte	0x1
	.long	.LASF127
	.long	.LASF127
	.byte	0xa
	.byte	0xac
	.uleb128 0x42
	.byte	0x1
	.byte	0x1
	.long	.LASF128
	.long	.LASF128
	.byte	0xf
	.word	0x123
	.uleb128 0x41
	.byte	0x1
	.byte	0x1
	.long	.LASF129
	.long	.LASF129
	.byte	0xc
	.byte	0x71
	.uleb128 0x41
	.byte	0x1
	.byte	0x1
	.long	.LASF130
	.long	.LASF130
	.byte	0xa
	.byte	0x9e
	.uleb128 0x41
	.byte	0x1
	.byte	0x1
	.long	.LASF131
	.long	.LASF131
	.byte	0xa
	.byte	0xa5
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0xc
	.uleb128 0xb
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x13
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x1d
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x87
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x87
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x32
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x33
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x34
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x35
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x36
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x37
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x38
	.uleb128 0x1d
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x39
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x87
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3a
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x2115
	.uleb128 0xc
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3b
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x3c
	.uleb128 0x2e
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x3d
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3e
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x3f
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x40
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x41
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x42
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LVL0
	.long	.LVL3
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL3
	.long	.LFE77
	.word	0x4
	.byte	0x8e
	.sleb128 -132
	.byte	0x9f
	.long	0
	.long	0
.LLST1:
	.long	.LVL1
	.long	.LVL5
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST2:
	.long	.LVL2
	.long	.LVL4
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL4
	.long	.LFE77
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST3:
	.long	.LVL6
	.long	.LVL12
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL12
	.long	.LFE78
	.word	0x4
	.byte	0x8e
	.sleb128 -132
	.byte	0x9f
	.long	0
	.long	0
.LLST4:
	.long	.LVL8
	.long	.LVL11
	.word	0x1
	.byte	0x63
	.long	0
	.long	0
.LLST5:
	.long	.LVL9
	.long	.LVL10
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL10
	.long	.LFE78
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST6:
	.long	.LFB91
	.long	.LCFI0
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI0
	.long	.LCFI1
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI1
	.long	.LFE91
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	0
	.long	0
.LLST7:
	.long	.LVL13
	.long	.LVL14
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL14
	.long	.LFE91
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST8:
	.long	.LVL13
	.long	.LVL14
	.word	0x1
	.byte	0x66
	.long	.LVL14
	.long	.LFE91
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x66
	.byte	0x9f
	.long	0
	.long	0
.LLST9:
	.long	.LVL16
	.long	.LVL17
	.word	0x1
	.byte	0x62
	.long	.LVL17
	.long	.LVL18
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL18
	.long	.LVL19
	.word	0x1
	.byte	0x62
	.long	.LVL20
	.long	.LVL21
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST10:
	.long	.LVL22
	.long	.LVL23
	.word	0x1
	.byte	0x68
	.long	.LVL23
	.long	.LVL24
	.word	0x1
	.byte	0x69
	.long	.LVL24
	.long	.LVL25
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	.LVL25
	.long	.LFE92
	.word	0x1
	.byte	0x69
	.long	0
	.long	0
.LLST11:
	.long	.LVL26
	.long	.LVL27
	.word	0x1
	.byte	0x64
	.long	0
	.long	0
.LLST12:
	.long	.LFB94
	.long	.LCFI2
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI2
	.long	.LCFI3
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI3
	.long	.LCFI4
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI4
	.long	.LCFI5
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 8
	.long	.LCFI5
	.long	.LFE94
	.word	0x2
	.byte	0x8c
	.sleb128 8
	.long	0
	.long	0
.LLST13:
	.long	.LVL29
	.long	.LVL30
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	0
	.long	0
.LLST14:
	.long	.LVL34
	.long	.LVL35
	.word	0x2
	.byte	0x40
	.byte	0x9f
	.long	0
	.long	0
.LLST15:
	.long	.LVL36
	.long	.LVL37
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	0
	.long	0
.LLST16:
	.long	.LVL38
	.long	.LVL39
	.word	0x2
	.byte	0x40
	.byte	0x9f
	.long	0
	.long	0
.LLST17:
	.long	.LVL42
	.long	.LVL45
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST18:
	.long	.LVL43
	.long	.LVL44
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL44
	.long	.LVL45
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST19:
	.long	.LVL44
	.long	.LVL48
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2404
	.sleb128 0
	.long	.LVL48
	.long	.LVL50
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2498
	.sleb128 0
	.long	.LVL53
	.long	.LVL60
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2655
	.sleb128 0
	.long	.LVL60
	.long	.LVL75
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2851
	.sleb128 0
	.long	.LVL75
	.long	.LFE95
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+3081
	.sleb128 0
	.long	0
	.long	0
.LLST20:
	.long	.LVL46
	.long	.LVL49
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST21:
	.long	.LVL47
	.long	.LVL48
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL48
	.long	.LVL49
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST22:
	.long	.LVL48
	.long	.LVL50
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2498
	.sleb128 0
	.long	.LVL53
	.long	.LVL60
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2655
	.sleb128 0
	.long	.LVL60
	.long	.LVL75
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2851
	.sleb128 0
	.long	.LVL75
	.long	.LFE95
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+3081
	.sleb128 0
	.long	0
	.long	0
.LLST23:
	.long	.LVL64
	.long	.LVL67
	.word	0x3
	.byte	0x8c
	.sleb128 -1
	.byte	0x9f
	.long	.LVL67
	.long	.LVL68
	.word	0x1
	.byte	0x6c
	.long	.LVL68
	.long	.LVL72
	.word	0x3
	.byte	0x8c
	.sleb128 -1
	.byte	0x9f
	.long	0
	.long	0
.LLST24:
	.long	.LVL53
	.long	.LVL54
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST25:
	.long	.LVL51
	.long	.LVL54
	.word	0x1
	.byte	0x69
	.long	0
	.long	0
.LLST26:
	.long	.LVL52
	.long	.LVL53
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL53
	.long	.LVL54
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST27:
	.long	.LVL53
	.long	.LVL60
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2655
	.sleb128 0
	.long	.LVL60
	.long	.LVL75
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2851
	.sleb128 0
	.long	.LVL75
	.long	.LFE95
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+3081
	.sleb128 0
	.long	0
	.long	0
.LLST28:
	.long	.LVL55
	.long	.LVL56
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST29:
	.long	.LVL60
	.long	.LVL61
	.word	0x1
	.byte	0x6c
	.long	0
	.long	0
.LLST30:
	.long	.LVL58
	.long	.LVL61
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST31:
	.long	.LVL59
	.long	.LVL60
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL60
	.long	.LVL61
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST32:
	.long	.LVL60
	.long	.LVL75
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2851
	.sleb128 0
	.long	.LVL75
	.long	.LFE95
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+3081
	.sleb128 0
	.long	0
	.long	0
.LLST33:
	.long	.LVL62
	.long	.LVL63
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	0
	.long	0
.LLST34:
	.long	.LVL69
	.long	.LVL70
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	0
	.long	0
.LLST35:
	.long	.LVL71
	.long	.LVL72
	.word	0x2
	.byte	0x40
	.byte	0x9f
	.long	0
	.long	0
.LLST36:
	.long	.LVL75
	.long	.LVL76
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST37:
	.long	.LVL73
	.long	.LVL76
	.word	0x1
	.byte	0x69
	.long	0
	.long	0
.LLST38:
	.long	.LVL74
	.long	.LVL75
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL75
	.long	.LVL76
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST39:
	.long	.LVL77
	.long	.LVL78
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST40:
	.long	.LVL78
	.long	.LVL79
	.word	0x2
	.byte	0x40
	.byte	0x9f
	.long	0
	.long	0
.LLST41:
	.long	.LVL82
	.long	.LVL83
	.word	0x4
	.byte	0xa
	.word	0x2580
	.byte	0x9f
	.long	0
	.long	0
.LLST42:
	.long	.LVL82
	.long	.LVL83
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST43:
	.long	.LVL88
	.long	.LVL89
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	0
	.long	0
.LLST44:
	.long	.LFB102
	.long	.LCFI6
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI6
	.long	.LCFI7
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI7
	.long	.LCFI8
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI8
	.long	.LFE102
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	0
	.long	0
.LLST45:
	.long	.LVL92
	.long	.LVL94
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL94
	.long	.LVL103
	.word	0x6
	.byte	0x60
	.byte	0x93
	.uleb128 0x1
	.byte	0x61
	.byte	0x93
	.uleb128 0x1
	.long	.LVL103
	.long	.LFE102
	.word	0x6
	.byte	0x6e
	.byte	0x93
	.uleb128 0x1
	.byte	0x6f
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST46:
	.long	.LVL93
	.long	.LVL95
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL95
	.long	.LVL96
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	.LVL96
	.long	.LVL97
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL97
	.long	.LVL102
	.word	0x1
	.byte	0x6c
	.long	0
	.long	0
.LLST47:
	.long	.LFB103
	.long	.LCFI9
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI9
	.long	.LCFI10
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI10
	.long	.LCFI11
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI11
	.long	.LCFI12
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI12
	.long	.LCFI13
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	.LCFI13
	.long	.LCFI14
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 7
	.long	.LCFI14
	.long	.LCFI15
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 8
	.long	.LCFI15
	.long	.LCFI16
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 9
	.long	.LCFI16
	.long	.LCFI17
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 10
	.long	.LCFI17
	.long	.LCFI18
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 11
	.long	.LCFI18
	.long	.LCFI19
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 12
	.long	.LCFI19
	.long	.LCFI20
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 13
	.long	.LCFI20
	.long	.LCFI21
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 14
	.long	.LCFI21
	.long	.LCFI22
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 15
	.long	.LCFI22
	.long	.LFE103
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 16
	.long	0
	.long	0
.LLST48:
	.long	.LVL104
	.long	.LVL105-1
	.word	0x1
	.byte	0x66
	.long	0
	.long	0
.LLST49:
	.long	.LVL106
	.long	.LVL107
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL107
	.long	.LFE104
	.word	0x6
	.byte	0x6e
	.byte	0x93
	.uleb128 0x1
	.byte	0x6f
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST50:
	.long	.LVL106
	.long	.LVL107
	.word	0x7
	.byte	0x88
	.sleb128 13
	.byte	0x94
	.byte	0x1
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.long	.LVL107
	.long	.LFE104
	.word	0x5
	.byte	0x88
	.sleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.long	0
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0x84
	.word	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.word	0
	.word	0
	.long	.LFB77
	.long	.LFE77-.LFB77
	.long	.LFB78
	.long	.LFE78-.LFB78
	.long	.LFB91
	.long	.LFE91-.LFB91
	.long	.LFB92
	.long	.LFE92-.LFB92
	.long	.LFB94
	.long	.LFE94-.LFB94
	.long	.LFB95
	.long	.LFE95-.LFB95
	.long	.LFB96
	.long	.LFE96-.LFB96
	.long	.LFB93
	.long	.LFE93-.LFB93
	.long	.LFB99
	.long	.LFE99-.LFB99
	.long	.LFB100
	.long	.LFE100-.LFB100
	.long	.LFB101
	.long	.LFE101-.LFB101
	.long	.LFB102
	.long	.LFE102-.LFB102
	.long	.LFB103
	.long	.LFE103-.LFB103
	.long	.LFB104
	.long	.LFE104-.LFB104
	.long	0
	.long	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.long	.LFB77
	.long	.LFE77
	.long	.LFB78
	.long	.LFE78
	.long	.LFB91
	.long	.LFE91
	.long	.LFB92
	.long	.LFE92
	.long	.LFB94
	.long	.LFE94
	.long	.LFB95
	.long	.LFE95
	.long	.LFB96
	.long	.LFE96
	.long	.LFB93
	.long	.LFE93
	.long	.LFB99
	.long	.LFE99
	.long	.LFB100
	.long	.LFE100
	.long	.LFB101
	.long	.LFE101
	.long	.LFB102
	.long	.LFE102
	.long	.LFB103
	.long	.LFE103
	.long	.LFB104
	.long	.LFE104
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF81:
	.string	"BaudRate"
.LASF100:
	.string	"EVENT_USB_Device_ConfigurationChanged"
.LASF105:
	.string	"ConfigMask"
.LASF48:
	.string	"LineEncoding"
.LASF92:
	.string	"processMIDI"
.LASF111:
	.string	"utx_buf"
.LASF132:
	.string	"GNU C99 5.4.0 -mn-flash=1 -mno-skip-bug -mmcu=avr35 -gdwarf-2 -Os -std=gnu99 -funsigned-char -funsigned-bitfields -ffunction-sections -fno-inline-small-functions -fpack-struct -fshort-enums -fno-strict-aliasing"
.LASF28:
	.string	"CDC_PARITY_Space"
.LASF16:
	.string	"DEVICE_STATE_Configured"
.LASF85:
	.string	"RxByte"
.LASF116:
	.string	"USBtoUSART_Buffer"
.LASF5:
	.string	"unsigned int"
.LASF43:
	.string	"BaudRateBPS"
.LASF86:
	.string	"SysEx"
.LASF99:
	.string	"SetupHardware"
.LASF138:
	.string	"LEDs_Init"
.LASF110:
	.string	"rx_buf"
.LASF94:
	.string	"RingBuffer_InitBuffer"
.LASF46:
	.string	"DataBits"
.LASF50:
	.string	"State"
.LASF33:
	.string	"DataINEndpointDoubleBank"
.LASF104:
	.string	"CDCInterfaceInfo"
.LASF31:
	.string	"DataINEndpointNumber"
.LASF133:
	.string	"dualMoco.c"
.LASF15:
	.string	"DEVICE_STATE_Addressed"
.LASF7:
	.string	"uint32_t"
.LASF36:
	.string	"DataOUTEndpointDoubleBank"
.LASF88:
	.string	"LEDs_TurnOnLEDs"
.LASF102:
	.string	"EVENT_USB_Device_UnhandledControlRequest"
.LASF59:
	.string	"USB_ClassInfo_MIDI_Device_t"
.LASF34:
	.string	"DataOUTEndpointNumber"
.LASF134:
	.string	"/home/cvonk/LUFA-100807-patched/Projects"
.LASF38:
	.string	"NotificationEndpointSize"
.LASF39:
	.string	"NotificationEndpointDoubleBank"
.LASF3:
	.string	"int16_t"
.LASF10:
	.string	"long long unsigned int"
.LASF14:
	.string	"DEVICE_STATE_Default"
.LASF129:
	.string	"MIDI_Device_ConfigureEndpoints"
.LASF19:
	.string	"CDC_LineEncodingFormats_t"
.LASF113:
	.string	"irptr"
.LASF49:
	.string	"Config"
.LASF37:
	.string	"NotificationEndpointNumber"
.LASF121:
	.string	"MIDI_Device_SendEventPacket"
.LASF93:
	.string	"ReceivedMIDIEvent"
.LASF42:
	.string	"DeviceToHost"
.LASF125:
	.string	"CDC_Device_ReceiveByte"
.LASF122:
	.string	"MIDI_Device_Flush"
.LASF80:
	.string	"Serial_Init"
.LASF115:
	.string	"mocoMode"
.LASF40:
	.string	"_Bool"
.LASF118:
	.string	"PulseMSRemaining"
.LASF82:
	.string	"DoubleSpeed"
.LASF79:
	.string	"RingBuffer_IsEmpty"
.LASF61:
	.string	"Count"
.LASF114:
	.string	"tx_buf"
.LASF35:
	.string	"DataOUTEndpointSize"
.LASF18:
	.string	"USB_Device_States_t"
.LASF136:
	.string	"RingBuffer_Insert"
.LASF29:
	.string	"char"
.LASF70:
	.string	"MIDI_Device_USBTask"
.LASF84:
	.string	"data"
.LASF2:
	.string	"uint8_t"
.LASF117:
	.string	"USARTtoUSB_Buffer"
.LASF73:
	.string	"DataByte"
.LASF91:
	.string	"parseSerialMidiMessage"
.LASF65:
	.string	"RxLEDPulse"
.LASF128:
	.string	"USB_Init"
.LASF41:
	.string	"HostToDevice"
.LASF124:
	.string	"USB_USBTask"
.LASF9:
	.string	"long long int"
.LASF108:
	.string	"CurrentDTRState"
.LASF71:
	.string	"MIDIInterfaceInfo"
.LASF69:
	.string	"__iRestore"
.LASF77:
	.string	"RingBuffer_GetCount"
.LASF89:
	.string	"LEDMask"
.LASF12:
	.string	"DEVICE_STATE_Unattached"
.LASF90:
	.string	"LEDs_TurnOffLEDs"
.LASF101:
	.string	"ConfigSuccess"
.LASF120:
	.string	"Keyboard_MIDI_Interface"
.LASF30:
	.string	"ControlInterfaceNumber"
.LASF75:
	.string	"temp_reg"
.LASF63:
	.string	"uchar"
.LASF127:
	.string	"CDC_Device_USBTask"
.LASF76:
	.string	"MIDI_Device_ProcessControlRequest"
.LASF20:
	.string	"CDC_LINEENCODING_OneStopBit"
.LASF25:
	.string	"CDC_PARITY_Odd"
.LASF66:
	.string	"PingPongLEDPulse"
.LASF67:
	.string	"sreg_save"
.LASF4:
	.string	"uint16_t"
.LASF123:
	.string	"MIDI_Device_ReceiveEventPacket"
.LASF62:
	.string	"RingBuff_t"
.LASF54:
	.string	"Data1"
.LASF55:
	.string	"Data2"
.LASF56:
	.string	"Data3"
.LASF78:
	.string	"RingBuffer_IsFull"
.LASF60:
	.string	"Buffer"
.LASF6:
	.string	"long int"
.LASF119:
	.string	"VirtualSerial_CDC_Interface"
.LASF32:
	.string	"DataINEndpointSize"
.LASF131:
	.string	"CDC_Device_ProcessControlRequest"
.LASF13:
	.string	"DEVICE_STATE_Powered"
.LASF52:
	.string	"Command"
.LASF137:
	.string	"RingBuffer_Remove"
.LASF96:
	.string	"BufferCount"
.LASF24:
	.string	"CDC_PARITY_None"
.LASF26:
	.string	"CDC_PARITY_Even"
.LASF72:
	.string	"Serial_TxByte"
.LASF95:
	.string	"processSerial"
.LASF98:
	.string	"parseUSBMidiMessage"
.LASF11:
	.string	"sizetype"
.LASF8:
	.string	"long unsigned int"
.LASF103:
	.string	"EVENT_CDC_Device_LineEncodingChanged"
.LASF140:
	.string	"EVENT_USB_Device_ControlRequest"
.LASF21:
	.string	"CDC_LINEENCODING_OneAndAHalfStopBits"
.LASF1:
	.string	"unsigned char"
.LASF126:
	.string	"CDC_Device_SendByte"
.LASF17:
	.string	"DEVICE_STATE_Suspended"
.LASF53:
	.string	"CableNumber"
.LASF112:
	.string	"uwptr"
.LASF57:
	.string	"MIDI_EventPacket_t"
.LASF51:
	.string	"USB_ClassInfo_CDC_Device_t"
.LASF87:
	.string	"stateTransTable"
.LASF27:
	.string	"CDC_PARITY_Mark"
.LASF97:
	.string	"ReceivedByte"
.LASF0:
	.string	"signed char"
.LASF22:
	.string	"CDC_LINEENCODING_TwoStopBits"
.LASF139:
	.string	"main"
.LASF23:
	.string	"CDC_LineEncodingParity_t"
.LASF135:
	.string	"__iCliRetVal"
.LASF68:
	.string	"__ToDo"
.LASF64:
	.string	"TxLEDPulse"
.LASF45:
	.string	"ParityType"
.LASF130:
	.string	"CDC_Device_ConfigureEndpoints"
.LASF74:
	.string	"wdt_disable"
.LASF58:
	.string	"StreamingInterfaceNumber"
.LASF47:
	.string	"ControlLineStates"
.LASF106:
	.string	"__vector_23"
.LASF107:
	.string	"EVENT_CDC_Device_ControLineStateChanged"
.LASF44:
	.string	"CharFormat"
.LASF83:
	.string	"Data"
.LASF109:
	.string	"utxrdy"
	.ident	"GCC: (GNU) 5.4.0"
.global __do_copy_data
.global __do_clear_bss
