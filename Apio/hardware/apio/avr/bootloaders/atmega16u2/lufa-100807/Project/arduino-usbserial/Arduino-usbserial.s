	.file	"Arduino-usbserial.c"
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
.LFB71:
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
.LBB31:
	.loc 1 166 0
	in r18,__SREG__
.LVL1:
.LBB32:
.LBB33:
	.file 2 "/usr/local/CrossPack-AVR-20131216/avr/include/util/atomic.h"
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/local/CrossPack-AVR-20131216/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL2:
/* #NOAPP */
.LBE33:
.LBE32:
	.loc 1 168 0
	movw r30,r24
	subi r30,124
	sbci r31,-1
	ld r24,Z
.LVL3:
	subi r24,lo8(-(1))
	st Z,r24
.LVL4:
.LBB34:
.LBB35:
	.loc 2 70 0
	out __SREG__,r18
	.loc 2 71 0
	ret
.LBE35:
.LBE34:
.LBE31:
	.cfi_endproc
.LFE71:
	.size	RingBuffer_Insert, .-RingBuffer_Insert
	.section	.text.RingBuffer_Remove,"ax",@progbits
	.type	RingBuffer_Remove, @function
RingBuffer_Remove:
.LFB72:
	.loc 1 183 0
	.cfi_startproc
.LVL5:
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
	ld r20,Z+
.LVL6:
	.loc 1 186 0
	adiw r26,1
	st X,r31
	st -X,r30
	movw r18,r24
	subi r18,-128
	sbci r19,-1
	cp r30,r18
	cpc r31,r19
	brne .L5
	.loc 1 187 0
	st X+,r24
	st X,r25
.L5:
.LBB36:
	.loc 1 189 0
	in r18,__SREG__
.LVL7:
.LBB37:
.LBB38:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/local/CrossPack-AVR-20131216/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL8:
/* #NOAPP */
.LBE38:
.LBE37:
	.loc 1 191 0
	movw r30,r24
	subi r30,124
	sbci r31,-1
	ld r25,Z
	subi r25,lo8(-(-1))
	st Z,r25
.LVL9:
.LBB39:
.LBB40:
	.loc 2 70 0
	out __SREG__,r18
	.loc 2 71 0
.LBE40:
.LBE39:
.LBE36:
	.loc 1 195 0
	mov r24,r20
.LVL10:
	ret
	.cfi_endproc
.LFE72:
	.size	RingBuffer_Remove, .-RingBuffer_Remove
	.section	.text.SetupHardware,"ax",@progbits
.global	SetupHardware
	.type	SetupHardware, @function
SetupHardware:
.LFB86:
	.file 3 "Arduino-usbserial.c"
	.loc 3 140 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 3 142 0
	in r24,0x34
	andi r24,lo8(-9)
	out 0x34,r24
	.loc 3 143 0
	ldi r24,lo8(24)
/* #APP */
 ;  143 "Arduino-usbserial.c" 1
	in __tmp_reg__, __SREG__
	cli
	sts 96, r24
	sts 96, __zero_reg__
	out __SREG__,__tmp_reg__
	
 ;  0 "" 2
.LVL11:
/* #NOAPP */
.LBB45:
.LBB46:
	.file 4 "../../LUFA/Drivers/Peripheral/Serial.h"
	.loc 4 102 0
	ldi r24,lo8(103)
	ldi r25,0
	sts 204+1,r25
	sts 204,r24
	.loc 4 104 0
	ldi r24,lo8(6)
	sts 202,r24
	.loc 4 105 0
	sts 200,__zero_reg__
	.loc 4 106 0
	ldi r24,lo8(24)
	sts 201,r24
	.loc 4 108 0
	sbi 0xa,3
	.loc 4 109 0
	sbi 0xb,2
.LBE46:
.LBE45:
.LBB47:
.LBB48:
	.file 5 "./Board/LEDs.h"
	.loc 5 69 0
	in r24,0xa
	ori r24,lo8(96)
	out 0xa,r24
	.loc 5 70 0
	in r24,0xb
	ori r24,lo8(96)
	out 0xb,r24
.LBE48:
.LBE47:
	.loc 3 148 0
	call USB_Init
.LVL12:
	.loc 3 151 0
	in r24,0xa
	.loc 3 152 0
	in r24,0xb
	.loc 3 155 0
	ldi r24,lo8(4)
	out 0x25,r24
	.loc 3 158 0
	sbi 0xb,7
	.loc 3 159 0
	sbi 0xa,7
	ret
	.cfi_endproc
.LFE86:
	.size	SetupHardware, .-SetupHardware
	.section	.text.startup.main,"ax",@progbits
.global	main
	.type	main, @function
main:
.LFB85:
	.loc 3 81 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 3 82 0
	call SetupHardware
.LVL13:
.LBB100:
.LBB101:
	.loc 1 87 0
	in r18,__SREG__
.LVL14:
.LBB102:
.LBB103:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/local/CrossPack-AVR-20131216/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL15:
/* #NOAPP */
.LBE103:
.LBE102:
	.loc 1 89 0
	ldi r24,lo8(USBtoUSART_Buffer)
	ldi r25,hi8(USBtoUSART_Buffer)
	sts USBtoUSART_Buffer+128+1,r25
	sts USBtoUSART_Buffer+128,r24
	.loc 1 90 0
	sts USBtoUSART_Buffer+130+1,r25
	sts USBtoUSART_Buffer+130,r24
.LVL16:
.LBB104:
.LBB105:
	.loc 2 70 0
	out __SREG__,r18
	.loc 2 71 0
.LVL17:
.LBE105:
.LBE104:
.LBE101:
.LBE100:
.LBB106:
.LBB107:
	.loc 1 87 0
	in r18,__SREG__
.LVL18:
.LBB108:
.LBB109:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/local/CrossPack-AVR-20131216/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL19:
/* #NOAPP */
.LBE109:
.LBE108:
	.loc 1 89 0
	ldi r24,lo8(USARTtoUSB_Buffer)
	ldi r25,hi8(USARTtoUSB_Buffer)
	sts USARTtoUSB_Buffer+128+1,r25
	sts USARTtoUSB_Buffer+128,r24
	.loc 1 90 0
	sts USARTtoUSB_Buffer+130+1,r25
	sts USARTtoUSB_Buffer+130,r24
.LVL20:
.LBB110:
.LBB111:
	.loc 2 70 0
	out __SREG__,r18
.LVL21:
	.loc 2 71 0
.LBE111:
.LBE110:
.LBE107:
.LBE106:
	.loc 3 87 0
/* #APP */
 ;  87 "Arduino-usbserial.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.LBB112:
	.loc 3 109 0
	ldi r29,lo8(3)
.LVL22:
.L23:
.LBB113:
.LBB114:
.LBB115:
.LBB116:
	.loc 1 111 0
	in r25,__SREG__
.LVL23:
.LBB117:
.LBB118:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/local/CrossPack-AVR-20131216/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL24:
/* #NOAPP */
.LBE118:
.LBE117:
	.loc 1 113 0
	lds r24,USBtoUSART_Buffer+132
.LVL25:
.LBB119:
.LBB120:
	.loc 2 70 0
	out __SREG__,r25
	.loc 2 71 0
.LBE120:
.LBE119:
.LBE116:
.LBE115:
.LBE114:
.LBE113:
	.loc 3 92 0
	cpi r24,lo8(-128)
	breq .L9
.LBB121:
	.loc 3 94 0
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
.LVL26:
	call CDC_Device_ReceiveByte
.LVL27:
	.loc 3 97 0
	sbrc r25,7
	rjmp .L9
	.loc 3 98 0
	mov r22,r24
	ldi r24,lo8(USBtoUSART_Buffer)
	ldi r25,hi8(USBtoUSART_Buffer)
.LVL28:
	call RingBuffer_Insert
.LVL29:
.L9:
.LBE121:
.LBB122:
.LBB123:
.LBB124:
	.loc 1 111 0
	in r24,__SREG__
.LVL30:
.LBB125:
.LBB126:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/local/CrossPack-AVR-20131216/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL31:
/* #NOAPP */
.LBE126:
.LBE125:
	.loc 1 113 0
	lds r28,USARTtoUSB_Buffer+132
.LVL32:
.LBB127:
.LBB128:
	.loc 2 70 0
	out __SREG__,r24
	.loc 2 71 0
.LBE128:
.LBE127:
.LBE124:
.LBE123:
.LBE122:
	.loc 3 103 0
	sbic 0x15,0
	rjmp .L11
	.loc 3 103 0 is_stmt 0 discriminator 1
	cpi r28,lo8(97)
	brlo .L12
.L11:
	.loc 3 105 0 is_stmt 1
	sbi 0x15,0
	.loc 3 107 0
	lds r24,USARTtoUSB_Buffer+132
.LVL33:
	tst r24
	breq .L14
.LVL34:
.LBB129:
.LBB130:
	.loc 5 75 0
	cbi 0xb,5
.LBE130:
.LBE129:
	.loc 3 109 0
	sts PulseMSRemaining,r29
.LVL35:
.L14:
	.loc 3 113 0 discriminator 1
	tst r28
	breq .L33
	.loc 3 114 0
	ldi r24,lo8(USARTtoUSB_Buffer)
	ldi r25,hi8(USARTtoUSB_Buffer)
	call RingBuffer_Remove
.LVL36:
	mov r22,r24
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	call CDC_Device_SendByte
.LVL37:
	subi r28,lo8(-(-1))
.LVL38:
	rjmp .L14
.LVL39:
.L33:
	.loc 3 117 0
	lds r24,PulseMSRemaining
	tst r24
	breq .L17
	.loc 3 117 0 is_stmt 0 discriminator 1
	lds r24,PulseMSRemaining
	subi r24,lo8(-(-1))
	sts PulseMSRemaining,r24
	cpse r24,__zero_reg__
	rjmp .L17
.LVL40:
.LBB131:
.LBB132:
	.loc 5 80 0 is_stmt 1
	sbi 0xb,5
.LVL41:
.L17:
.LBE132:
.LBE131:
	.loc 3 121 0
	lds r24,PulseMSRemaining+1
	tst r24
	breq .L12
	.loc 3 121 0 is_stmt 0 discriminator 1
	lds r24,PulseMSRemaining+1
	subi r24,lo8(-(-1))
	sts PulseMSRemaining+1,r24
	cpse r24,__zero_reg__
	rjmp .L12
.LVL42:
.LBB133:
.LBB134:
	.loc 5 80 0 is_stmt 1
	sbi 0xb,6
.LVL43:
.L12:
.LBE134:
.LBE133:
.LBB135:
.LBB136:
.LBB137:
.LBB138:
	.loc 1 111 0
	in r25,__SREG__
.LVL44:
.LBB139:
.LBB140:
	.loc 2 50 0
/* #APP */
 ;  50 "/usr/local/CrossPack-AVR-20131216/avr/include/util/atomic.h" 1
	cli
 ;  0 "" 2
.LVL45:
/* #NOAPP */
.LBE140:
.LBE139:
	.loc 1 113 0
	lds r24,USBtoUSART_Buffer+132
.LVL46:
.LBB141:
.LBB142:
	.loc 2 70 0
	out __SREG__,r25
	.loc 2 71 0
.LBE142:
.LBE141:
.LBE138:
.LBE137:
.LBE136:
.LBE135:
	.loc 3 126 0
	tst r24
	breq .L20
	.loc 3 127 0
	ldi r24,lo8(USBtoUSART_Buffer)
	ldi r25,hi8(USBtoUSART_Buffer)
.LVL47:
	call RingBuffer_Remove
.LVL48:
.L22:
.LBB143:
.LBB144:
	.loc 4 142 0
	lds r25,200
	sbrs r25,5
	rjmp .L22
	.loc 4 143 0
	sts 206,r24
.LVL49:
.LBE144:
.LBE143:
.LBB145:
.LBB146:
	.loc 5 75 0
	cbi 0xb,6
.LBE146:
.LBE145:
	.loc 3 130 0
	sts PulseMSRemaining+1,r29
.LVL50:
.L20:
	.loc 3 133 0
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	call CDC_Device_USBTask
.LVL51:
	.loc 3 134 0
	call USB_USBTask
.LVL52:
.LBE112:
	.loc 3 135 0
	rjmp .L23
	.cfi_endproc
.LFE85:
	.size	main, .-main
	.section	.text.EVENT_USB_Device_ConfigurationChanged,"ax",@progbits
.global	EVENT_USB_Device_ConfigurationChanged
	.type	EVENT_USB_Device_ConfigurationChanged, @function
EVENT_USB_Device_ConfigurationChanged:
.LFB87:
	.loc 3 164 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 3 165 0
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	jmp CDC_Device_ConfigureEndpoints
.LVL53:
	.cfi_endproc
.LFE87:
	.size	EVENT_USB_Device_ConfigurationChanged, .-EVENT_USB_Device_ConfigurationChanged
	.section	.text.EVENT_USB_Device_UnhandledControlRequest,"ax",@progbits
.global	EVENT_USB_Device_UnhandledControlRequest
	.type	EVENT_USB_Device_UnhandledControlRequest, @function
EVENT_USB_Device_UnhandledControlRequest:
.LFB88:
	.loc 3 170 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 3 171 0
	ldi r24,lo8(VirtualSerial_CDC_Interface)
	ldi r25,hi8(VirtualSerial_CDC_Interface)
	jmp CDC_Device_ProcessControlRequest
.LVL54:
	.cfi_endproc
.LFE88:
	.size	EVENT_USB_Device_UnhandledControlRequest, .-EVENT_USB_Device_UnhandledControlRequest
	.section	.text.EVENT_CDC_Device_LineEncodingChanged,"ax",@progbits
.global	EVENT_CDC_Device_LineEncodingChanged
	.type	EVENT_CDC_Device_LineEncodingChanged, @function
EVENT_CDC_Device_LineEncodingChanged:
.LFB89:
	.loc 3 179 0
	.cfi_startproc
.LVL55:
	push r17
.LCFI0:
	.cfi_def_cfa_offset 3
	.cfi_offset 17, -2
	push r28
.LCFI1:
	.cfi_def_cfa_offset 4
	.cfi_offset 28, -3
	push r29
.LCFI2:
	.cfi_def_cfa_offset 5
	.cfi_offset 29, -4
/* prologue: function */
/* frame size = 0 */
/* stack size = 3 */
.L__stack_usage = 3
	movw r28,r24
.LVL56:
	.loc 3 182 0
	ldd r24,Y+20
.LVL57:
	cpi r24,lo8(1)
	breq .L47
	cpi r24,lo8(2)
	breq .L39
	.loc 3 180 0
	ldi r17,0
	rjmp .L38
.L39:
.LVL58:
	.loc 3 188 0
	ldi r17,lo8(32)
	.loc 3 189 0
	rjmp .L38
.LVL59:
.L47:
	.loc 3 185 0
	ldi r17,lo8(48)
.LVL60:
.L38:
	.loc 3 192 0
	ldd r24,Y+19
	cpi r24,lo8(2)
	brne .L40
	.loc 3 193 0
	ori r17,lo8(8)
.LVL61:
.L40:
	.loc 3 195 0
	ldd r24,Y+21
	cpi r24,lo8(7)
	breq .L42
	cpi r24,lo8(8)
	breq .L43
	cpi r24,lo8(6)
	brne .L41
	.loc 3 198 0
	ori r17,lo8(2)
.LVL62:
	.loc 3 199 0
	rjmp .L41
.L42:
	.loc 3 201 0
	ori r17,lo8(4)
.LVL63:
	.loc 3 202 0
	rjmp .L41
.L43:
	.loc 3 204 0
	ori r17,lo8(6)
.LVL64:
.L41:
	.loc 3 209 0
	sts 201,__zero_reg__
	.loc 3 210 0
	sts 200,__zero_reg__
	.loc 3 211 0
	sts 202,__zero_reg__
	.loc 3 214 0
	ldd r18,Y+15
	ldd r19,Y+16
	ldd r20,Y+17
	ldd r21,Y+18
	cp r18,__zero_reg__
	ldi r24,-31
	cpc r19,r24
	cpc r20,__zero_reg__
	cpc r21,__zero_reg__
	breq .L48
	.loc 3 216 0 discriminator 1
	movw r24,r20
	movw r22,r18
	lsr r25
	ror r24
	ror r23
	ror r22
	subi r22,-128
	sbci r23,123
	sbci r24,-31
	sbci r25,-1
	call __udivmodsi4
	.loc 3 214 0 discriminator 1
	subi r18,1
	sbc r19,__zero_reg__
	rjmp .L45
.L48:
	.loc 3 214 0 is_stmt 0
	ldi r18,lo8(16)
	ldi r19,0
.L45:
	.loc 3 214 0 discriminator 2
	sts 204+1,r19
	sts 204,r18
	.loc 3 218 0 is_stmt 1 discriminator 2
	sts 202,r17
	.loc 3 219 0 discriminator 2
	ldd r24,Y+15
	ldd r25,Y+16
	ldd r26,Y+17
	ldd r27,Y+18
	cp r24,__zero_reg__
	sbci r25,-31
	cpc r26,__zero_reg__
	cpc r27,__zero_reg__
	brne .L49
	.loc 3 219 0 is_stmt 0
	ldi r24,0
	rjmp .L46
.L49:
	ldi r24,lo8(2)
.L46:
	.loc 3 219 0 discriminator 3
	sts 200,r24
	.loc 3 220 0 is_stmt 1 discriminator 3
	ldi r24,lo8(-104)
	sts 201,r24
/* epilogue start */
	.loc 3 221 0 discriminator 3
	pop r29
	pop r28
.LVL65:
	pop r17
.LVL66:
	ret
	.cfi_endproc
.LFE89:
	.size	EVENT_CDC_Device_LineEncodingChanged, .-EVENT_CDC_Device_LineEncodingChanged
	.section	.text.__vector_23,"ax",@progbits
.global	__vector_23
	.type	__vector_23, @function
__vector_23:
.LFB90:
	.loc 3 227 0
	.cfi_startproc
	push r1
.LCFI3:
	.cfi_def_cfa_offset 3
	.cfi_offset 1, -2
	push r0
.LCFI4:
	.cfi_def_cfa_offset 4
	.cfi_offset 0, -3
	in r0,__SREG__
	push r0
	clr __zero_reg__
	push r18
.LCFI5:
	.cfi_def_cfa_offset 5
	.cfi_offset 18, -4
	push r19
.LCFI6:
	.cfi_def_cfa_offset 6
	.cfi_offset 19, -5
	push r20
.LCFI7:
	.cfi_def_cfa_offset 7
	.cfi_offset 20, -6
	push r21
.LCFI8:
	.cfi_def_cfa_offset 8
	.cfi_offset 21, -7
	push r22
.LCFI9:
	.cfi_def_cfa_offset 9
	.cfi_offset 22, -8
	push r23
.LCFI10:
	.cfi_def_cfa_offset 10
	.cfi_offset 23, -9
	push r24
.LCFI11:
	.cfi_def_cfa_offset 11
	.cfi_offset 24, -10
	push r25
.LCFI12:
	.cfi_def_cfa_offset 12
	.cfi_offset 25, -11
	push r26
.LCFI13:
	.cfi_def_cfa_offset 13
	.cfi_offset 26, -12
	push r27
.LCFI14:
	.cfi_def_cfa_offset 14
	.cfi_offset 27, -13
	push r30
.LCFI15:
	.cfi_def_cfa_offset 15
	.cfi_offset 30, -14
	push r31
.LCFI16:
	.cfi_def_cfa_offset 16
	.cfi_offset 31, -15
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 15 */
.L__stack_usage = 15
	.loc 3 228 0
	lds r22,206
.LVL67:
	.loc 3 230 0
	in r24,0x1e
	cpi r24,lo8(4)
	brne .L50
	.loc 3 231 0
	ldi r24,lo8(USARTtoUSB_Buffer)
	ldi r25,hi8(USARTtoUSB_Buffer)
	call RingBuffer_Insert
.LVL68:
.L50:
/* epilogue start */
	.loc 3 232 0
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
.LFE90:
	.size	__vector_23, .-__vector_23
	.section	.text.EVENT_CDC_Device_ControLineStateChanged,"ax",@progbits
.global	EVENT_CDC_Device_ControLineStateChanged
	.type	EVENT_CDC_Device_ControLineStateChanged, @function
EVENT_CDC_Device_ControLineStateChanged:
.LFB91:
	.loc 3 239 0
	.cfi_startproc
.LVL69:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 3 240 0
	movw r30,r24
	ldd r24,Z+13
.LVL70:
	.loc 3 242 0
	sbrs r24,0
	rjmp .L53
	.loc 3 243 0
	cbi 0xb,7
	ret
.L53:
	.loc 3 245 0
	sbi 0xb,7
	ret
	.cfi_endproc
.LFE91:
	.size	EVENT_CDC_Device_ControLineStateChanged, .-EVENT_CDC_Device_ControLineStateChanged
.global	VirtualSerial_CDC_Interface
	.data
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
	.comm	PulseMSRemaining,3,1
	.comm	USARTtoUSB_Buffer,133,1
	.comm	USBtoUSART_Buffer,133,1
	.text
.Letext0:
	.file 6 "/usr/local/CrossPack-AVR-20131216/avr/include/stdint.h"
	.file 7 "../../LUFA/Drivers/USB/HighLevel/../LowLevel/Device.h"
	.file 8 "../../LUFA/Drivers/USB/Class/Device/../Common/CDC.h"
	.file 9 "../../LUFA/Drivers/USB/Class/Device/CDC.h"
	.file 10 "../../LUFA/Drivers/USB/HighLevel/../LowLevel/USBController.h"
	.file 11 "../../LUFA/Drivers/USB/HighLevel/USBTask.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xbc8
	.word	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF94
	.byte	0x1
	.long	.LASF95
	.long	.LASF96
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
	.byte	0x6
	.byte	0x7a
	.long	0x3b
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x3
	.long	.LASF3
	.byte	0x6
	.byte	0x7b
	.long	0x4d
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.long	.LASF4
	.byte	0x6
	.byte	0x7c
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
	.byte	0x6
	.byte	0x7e
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
	.byte	0x7
	.byte	0x72
	.long	0xc5
	.uleb128 0x6
	.long	.LASF12
	.sleb128 0
	.uleb128 0x6
	.long	.LASF13
	.sleb128 1
	.uleb128 0x6
	.long	.LASF14
	.sleb128 2
	.uleb128 0x6
	.long	.LASF15
	.sleb128 3
	.uleb128 0x6
	.long	.LASF16
	.sleb128 4
	.uleb128 0x6
	.long	.LASF17
	.sleb128 5
	.byte	0
	.uleb128 0x5
	.long	.LASF19
	.byte	0x1
	.byte	0x8
	.byte	0x9b
	.long	0xe4
	.uleb128 0x6
	.long	.LASF20
	.sleb128 0
	.uleb128 0x6
	.long	.LASF21
	.sleb128 1
	.uleb128 0x6
	.long	.LASF22
	.sleb128 2
	.byte	0
	.uleb128 0x5
	.long	.LASF23
	.byte	0x1
	.byte	0x8
	.byte	0xa3
	.long	0x10f
	.uleb128 0x6
	.long	.LASF24
	.sleb128 0
	.uleb128 0x6
	.long	.LASF25
	.sleb128 1
	.uleb128 0x6
	.long	.LASF26
	.sleb128 2
	.uleb128 0x6
	.long	.LASF27
	.sleb128 3
	.uleb128 0x6
	.long	.LASF28
	.sleb128 4
	.byte	0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF29
	.uleb128 0x7
	.byte	0xd
	.byte	0x9
	.byte	0x64
	.long	0x1ab
	.uleb128 0x8
	.long	.LASF30
	.byte	0x9
	.byte	0x66
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF31
	.byte	0x9
	.byte	0x68
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x8
	.long	.LASF32
	.byte	0x9
	.byte	0x69
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x8
	.long	.LASF33
	.byte	0x9
	.byte	0x6a
	.long	0x1ab
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.long	.LASF34
	.byte	0x9
	.byte	0x6c
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x5
	.uleb128 0x8
	.long	.LASF35
	.byte	0x9
	.byte	0x6d
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.uleb128 0x8
	.long	.LASF36
	.byte	0x9
	.byte	0x6e
	.long	0x1ab
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x8
	.long	.LASF37
	.byte	0x9
	.byte	0x70
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x9
	.uleb128 0x8
	.long	.LASF38
	.byte	0x9
	.byte	0x71
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0xa
	.uleb128 0x8
	.long	.LASF39
	.byte	0x9
	.byte	0x72
	.long	0x1ab
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
	.byte	0x9
	.byte	0x78
	.long	0x1d7
	.uleb128 0x8
	.long	.LASF41
	.byte	0x9
	.byte	0x7a
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF42
	.byte	0x9
	.byte	0x7d
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.byte	0
	.uleb128 0x7
	.byte	0x7
	.byte	0x9
	.byte	0x83
	.long	0x218
	.uleb128 0x8
	.long	.LASF43
	.byte	0x9
	.byte	0x85
	.long	0x6d
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF44
	.byte	0x9
	.byte	0x86
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.long	.LASF45
	.byte	0x9
	.byte	0x89
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x5
	.uleb128 0x8
	.long	.LASF46
	.byte	0x9
	.byte	0x8c
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.byte	0
	.uleb128 0x7
	.byte	0x9
	.byte	0x9
	.byte	0x76
	.long	0x23d
	.uleb128 0x8
	.long	.LASF47
	.byte	0x9
	.byte	0x81
	.long	0x1b2
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF48
	.byte	0x9
	.byte	0x8d
	.long	0x1d7
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.byte	0
	.uleb128 0x7
	.byte	0x16
	.byte	0x9
	.byte	0x62
	.long	0x262
	.uleb128 0x8
	.long	.LASF49
	.byte	0x9
	.byte	0x73
	.long	0x262
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF50
	.byte	0x9
	.byte	0x90
	.long	0x218
	.byte	0x2
	.byte	0x23
	.uleb128 0xd
	.byte	0
	.uleb128 0x9
	.long	0x116
	.uleb128 0x3
	.long	.LASF51
	.byte	0x9
	.byte	0x93
	.long	0x23d
	.uleb128 0x7
	.byte	0x85
	.byte	0x1
	.byte	0x46
	.long	0x2b5
	.uleb128 0x8
	.long	.LASF52
	.byte	0x1
	.byte	0x48
	.long	0x2b5
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xa
	.string	"In"
	.byte	0x1
	.byte	0x49
	.long	0x2c5
	.byte	0x3
	.byte	0x23
	.uleb128 0x80
	.uleb128 0xa
	.string	"Out"
	.byte	0x1
	.byte	0x4a
	.long	0x2c5
	.byte	0x3
	.byte	0x23
	.uleb128 0x82
	.uleb128 0x8
	.long	.LASF53
	.byte	0x1
	.byte	0x4b
	.long	0x30
	.byte	0x3
	.byte	0x23
	.uleb128 0x84
	.byte	0
	.uleb128 0xb
	.long	0x30
	.long	0x2c5
	.uleb128 0xc
	.long	0x8d
	.byte	0x7f
	.byte	0
	.uleb128 0xd
	.byte	0x2
	.long	0x30
	.uleb128 0x3
	.long	.LASF54
	.byte	0x1
	.byte	0x4c
	.long	0x272
	.uleb128 0x7
	.byte	0x3
	.byte	0x3
	.byte	0x2e
	.long	0x309
	.uleb128 0x8
	.long	.LASF55
	.byte	0x3
	.byte	0x30
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF56
	.byte	0x3
	.byte	0x31
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x8
	.long	.LASF57
	.byte	0x3
	.byte	0x32
	.long	0x30
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.byte	0
	.uleb128 0xe
	.long	.LASF60
	.byte	0x2
	.byte	0x44
	.byte	0x1
	.byte	0x3
	.long	0x322
	.uleb128 0xf
	.string	"__s"
	.byte	0x2
	.byte	0x44
	.long	0x322
	.byte	0
	.uleb128 0xd
	.byte	0x2
	.long	0x328
	.uleb128 0x9
	.long	0x30
	.uleb128 0x10
	.long	.LASF97
	.byte	0x2
	.byte	0x30
	.byte	0x1
	.long	0x30
	.byte	0x3
	.uleb128 0x11
	.long	.LASF63
	.byte	0x1
	.byte	0x6b
	.byte	0x1
	.long	0x30
	.byte	0x3
	.long	0x37a
	.uleb128 0x12
	.long	.LASF52
	.byte	0x1
	.byte	0x6b
	.long	0x37a
	.uleb128 0x13
	.long	.LASF53
	.byte	0x1
	.byte	0x6d
	.long	0x30
	.uleb128 0x14
	.uleb128 0x13
	.long	.LASF58
	.byte	0x1
	.byte	0x6f
	.long	0x30
	.uleb128 0x13
	.long	.LASF59
	.byte	0x1
	.byte	0x6f
	.long	0x30
	.byte	0
	.byte	0
	.uleb128 0x9
	.long	0x37f
	.uleb128 0xd
	.byte	0x2
	.long	0x2cb
	.uleb128 0xe
	.long	.LASF61
	.byte	0x4
	.byte	0x8c
	.byte	0x1
	.byte	0x3
	.long	0x39e
	.uleb128 0x12
	.long	.LASF62
	.byte	0x4
	.byte	0x8c
	.long	0x39e
	.byte	0
	.uleb128 0x9
	.long	0x10f
	.uleb128 0x11
	.long	.LASF64
	.byte	0x1
	.byte	0x7f
	.byte	0x1
	.long	0x1ab
	.byte	0x3
	.long	0x3c0
	.uleb128 0x12
	.long	.LASF52
	.byte	0x1
	.byte	0x7f
	.long	0x37a
	.byte	0
	.uleb128 0x11
	.long	.LASF65
	.byte	0x1
	.byte	0x90
	.byte	0x1
	.long	0x1ab
	.byte	0x3
	.long	0x3dd
	.uleb128 0x12
	.long	.LASF52
	.byte	0x1
	.byte	0x90
	.long	0x37a
	.byte	0
	.uleb128 0xe
	.long	.LASF66
	.byte	0x4
	.byte	0x63
	.byte	0x1
	.byte	0x3
	.long	0x401
	.uleb128 0x12
	.long	.LASF67
	.byte	0x4
	.byte	0x63
	.long	0x401
	.uleb128 0x12
	.long	.LASF68
	.byte	0x4
	.byte	0x64
	.long	0x406
	.byte	0
	.uleb128 0x9
	.long	0x6d
	.uleb128 0x9
	.long	0x1ab
	.uleb128 0x15
	.long	.LASF98
	.byte	0x1
	.byte	0x9e
	.byte	0x1
	.long	.LFB71
	.long	.LFE71
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x492
	.uleb128 0x16
	.long	.LASF52
	.byte	0x1
	.byte	0x9e
	.long	0x37a
	.long	.LLST0
	.uleb128 0x17
	.long	.LASF69
	.byte	0x1
	.byte	0x9f
	.long	0x328
	.byte	0x1
	.byte	0x66
	.uleb128 0x18
	.long	.LBB31
	.long	.LBE31
	.uleb128 0x19
	.long	.LASF58
	.byte	0x1
	.byte	0xa6
	.long	0x30
	.byte	0x1
	.byte	0x62
	.uleb128 0x1a
	.long	.LASF59
	.byte	0x1
	.byte	0xa6
	.long	0x30
	.long	.LLST1
	.uleb128 0x1b
	.long	0x32d
	.long	.LBB32
	.long	.LBE32
	.byte	0x1
	.byte	0xa6
	.uleb128 0x1c
	.long	0x309
	.long	.LBB34
	.long	.LBE34
	.byte	0x1
	.byte	0xa6
	.uleb128 0x1d
	.long	0x316
	.byte	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1097
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1e
	.long	.LASF99
	.byte	0x1
	.byte	0xb6
	.byte	0x1
	.long	0x30
	.long	.LFB72
	.long	.LFE72
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x51d
	.uleb128 0x16
	.long	.LASF52
	.byte	0x1
	.byte	0xb6
	.long	0x37a
	.long	.LLST2
	.uleb128 0x19
	.long	.LASF69
	.byte	0x1
	.byte	0xb8
	.long	0x30
	.byte	0x1
	.byte	0x64
	.uleb128 0x18
	.long	.LBB36
	.long	.LBE36
	.uleb128 0x19
	.long	.LASF58
	.byte	0x1
	.byte	0xbd
	.long	0x30
	.byte	0x1
	.byte	0x62
	.uleb128 0x1a
	.long	.LASF59
	.byte	0x1
	.byte	0xbd
	.long	0x30
	.long	.LLST3
	.uleb128 0x1b
	.long	0x32d
	.long	.LBB37
	.long	.LBE37
	.byte	0x1
	.byte	0xbd
	.uleb128 0x1c
	.long	0x309
	.long	.LBB39
	.long	.LBE39
	.byte	0x1
	.byte	0xbd
	.uleb128 0x1d
	.long	0x316
	.byte	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1236
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1f
	.long	.LASF100
	.byte	0x5
	.byte	0x43
	.byte	0x1
	.byte	0x3
	.uleb128 0x20
	.byte	0x1
	.long	.LASF76
	.byte	0x3
	.byte	0x8b
	.byte	0x1
	.long	.LFB86
	.long	.LFE86
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x57a
	.uleb128 0x21
	.long	0x3dd
	.long	.LBB45
	.long	.LBE45
	.byte	0x3
	.byte	0x92
	.long	0x561
	.uleb128 0x22
	.long	0x3ea
	.word	0x2580
	.uleb128 0x23
	.long	0x3f5
	.byte	0
	.byte	0
	.uleb128 0x1b
	.long	0x51d
	.long	.LBB47
	.long	.LBE47
	.byte	0x3
	.byte	0x93
	.uleb128 0x24
	.long	.LVL12
	.long	0xb44
	.byte	0
	.uleb128 0xe
	.long	.LASF70
	.byte	0x1
	.byte	0x55
	.byte	0x1
	.byte	0x3
	.long	0x5ab
	.uleb128 0x12
	.long	.LASF52
	.byte	0x1
	.byte	0x55
	.long	0x37a
	.uleb128 0x14
	.uleb128 0x13
	.long	.LASF58
	.byte	0x1
	.byte	0x57
	.long	0x30
	.uleb128 0x13
	.long	.LASF59
	.byte	0x1
	.byte	0x57
	.long	0x30
	.byte	0
	.byte	0
	.uleb128 0xe
	.long	.LASF71
	.byte	0x5
	.byte	0x49
	.byte	0x1
	.byte	0x3
	.long	0x5c4
	.uleb128 0x12
	.long	.LASF72
	.byte	0x5
	.byte	0x49
	.long	0x328
	.byte	0
	.uleb128 0xe
	.long	.LASF73
	.byte	0x5
	.byte	0x4e
	.byte	0x1
	.byte	0x3
	.long	0x5dd
	.uleb128 0x12
	.long	.LASF72
	.byte	0x5
	.byte	0x4e
	.long	0x328
	.byte	0
	.uleb128 0x25
	.byte	0x1
	.long	.LASF101
	.byte	0x3
	.byte	0x50
	.byte	0x1
	.long	0x4d
	.long	.LFB85
	.long	.LFE85
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x9d0
	.uleb128 0x21
	.long	0x57a
	.long	.LBB100
	.long	.LBE100
	.byte	0x3
	.byte	0x54
	.long	0x65f
	.uleb128 0x1d
	.long	0x587
	.byte	0x6
	.byte	0x3
	.long	USBtoUSART_Buffer
	.byte	0x9f
	.uleb128 0x18
	.long	.LBB101
	.long	.LBE101
	.uleb128 0x26
	.long	0x593
	.long	.LLST4
	.uleb128 0x26
	.long	0x59e
	.long	.LLST5
	.uleb128 0x1b
	.long	0x32d
	.long	.LBB102
	.long	.LBE102
	.byte	0x1
	.byte	0x57
	.uleb128 0x1c
	.long	0x309
	.long	.LBB104
	.long	.LBE104
	.byte	0x1
	.byte	0x57
	.uleb128 0x27
	.long	0x316
	.long	.LLST6
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x21
	.long	0x57a
	.long	.LBB106
	.long	.LBE106
	.byte	0x3
	.byte	0x55
	.long	0x6c3
	.uleb128 0x1d
	.long	0x587
	.byte	0x6
	.byte	0x3
	.long	USARTtoUSB_Buffer
	.byte	0x9f
	.uleb128 0x18
	.long	.LBB107
	.long	.LBE107
	.uleb128 0x26
	.long	0x593
	.long	.LLST7
	.uleb128 0x26
	.long	0x59e
	.long	.LLST8
	.uleb128 0x1b
	.long	0x32d
	.long	.LBB108
	.long	.LBE108
	.byte	0x1
	.byte	0x57
	.uleb128 0x1c
	.long	0x309
	.long	.LBB110
	.long	.LBE110
	.byte	0x1
	.byte	0x57
	.uleb128 0x27
	.long	0x316
	.long	.LLST9
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x28
	.long	.LBB112
	.long	.LBE112
	.long	0x9c6
	.uleb128 0x1a
	.long	.LASF74
	.byte	0x3
	.byte	0x66
	.long	0x30
	.long	.LLST10
	.uleb128 0x21
	.long	0x3a3
	.long	.LBB113
	.long	.LBE113
	.byte	0x3
	.byte	0x5c
	.long	0x76b
	.uleb128 0x1d
	.long	0x3b4
	.byte	0x6
	.byte	0x3
	.long	USBtoUSART_Buffer
	.byte	0x9f
	.uleb128 0x1c
	.long	0x33a
	.long	.LBB114
	.long	.LBE114
	.byte	0x1
	.byte	0x81
	.uleb128 0x29
	.long	0x34b
	.uleb128 0x18
	.long	.LBB115
	.long	.LBE115
	.uleb128 0x26
	.long	0x356
	.long	.LLST11
	.uleb128 0x18
	.long	.LBB116
	.long	.LBE116
	.uleb128 0x26
	.long	0x362
	.long	.LLST12
	.uleb128 0x26
	.long	0x36d
	.long	.LLST13
	.uleb128 0x1b
	.long	0x32d
	.long	.LBB117
	.long	.LBE117
	.byte	0x1
	.byte	0x6f
	.uleb128 0x1c
	.long	0x309
	.long	.LBB119
	.long	.LBE119
	.byte	0x1
	.byte	0x6f
	.uleb128 0x27
	.long	0x316
	.long	.LLST14
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x28
	.long	.LBB121
	.long	.LBE121
	.long	0x7bc
	.uleb128 0x1a
	.long	.LASF75
	.byte	0x3
	.byte	0x5e
	.long	0x42
	.long	.LLST15
	.uleb128 0x2a
	.long	.LVL27
	.long	0xb4f
	.long	0x7a3
	.uleb128 0x2b
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
	.long	.LVL29
	.long	0x40b
	.uleb128 0x2b
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
	.uleb128 0x21
	.long	0x33a
	.long	.LBB122
	.long	.LBE122
	.byte	0x3
	.byte	0x66
	.long	0x82c
	.uleb128 0x29
	.long	0x34b
	.uleb128 0x18
	.long	.LBB123
	.long	.LBE123
	.uleb128 0x26
	.long	0x356
	.long	.LLST16
	.uleb128 0x18
	.long	.LBB124
	.long	.LBE124
	.uleb128 0x26
	.long	0x362
	.long	.LLST17
	.uleb128 0x26
	.long	0x36d
	.long	.LLST18
	.uleb128 0x1b
	.long	0x32d
	.long	.LBB125
	.long	.LBE125
	.byte	0x1
	.byte	0x6f
	.uleb128 0x1c
	.long	0x309
	.long	.LBB127
	.long	.LBE127
	.byte	0x1
	.byte	0x6f
	.uleb128 0x27
	.long	0x316
	.long	.LLST19
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x21
	.long	0x5ab
	.long	.LBB129
	.long	.LBE129
	.byte	0x3
	.byte	0x6c
	.long	0x849
	.uleb128 0x27
	.long	0x5b8
	.long	.LLST20
	.byte	0
	.uleb128 0x21
	.long	0x5c4
	.long	.LBB131
	.long	.LBE131
	.byte	0x3
	.byte	0x76
	.long	0x866
	.uleb128 0x27
	.long	0x5d1
	.long	.LLST21
	.byte	0
	.uleb128 0x21
	.long	0x5c4
	.long	.LBB133
	.long	.LBE133
	.byte	0x3
	.byte	0x7a
	.long	0x883
	.uleb128 0x27
	.long	0x5d1
	.long	.LLST22
	.byte	0
	.uleb128 0x21
	.long	0x3c0
	.long	.LBB135
	.long	.LBE135
	.byte	0x3
	.byte	0x7e
	.long	0x912
	.uleb128 0x1d
	.long	0x3d1
	.byte	0x6
	.byte	0x3
	.long	USBtoUSART_Buffer
	.byte	0x9f
	.uleb128 0x1c
	.long	0x33a
	.long	.LBB136
	.long	.LBE136
	.byte	0x1
	.byte	0x92
	.uleb128 0x29
	.long	0x34b
	.uleb128 0x18
	.long	.LBB137
	.long	.LBE137
	.uleb128 0x26
	.long	0x356
	.long	.LLST23
	.uleb128 0x18
	.long	.LBB138
	.long	.LBE138
	.uleb128 0x26
	.long	0x362
	.long	.LLST24
	.uleb128 0x26
	.long	0x36d
	.long	.LLST25
	.uleb128 0x1b
	.long	0x32d
	.long	.LBB139
	.long	.LBE139
	.byte	0x1
	.byte	0x6f
	.uleb128 0x1c
	.long	0x309
	.long	.LBB141
	.long	.LBE141
	.byte	0x1
	.byte	0x6f
	.uleb128 0x1d
	.long	0x316
	.byte	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2257
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x21
	.long	0x385
	.long	.LBB143
	.long	.LBE143
	.byte	0x3
	.byte	0x7f
	.long	0x92f
	.uleb128 0x27
	.long	0x392
	.long	.LLST26
	.byte	0
	.uleb128 0x21
	.long	0x5ab
	.long	.LBB145
	.long	.LBE145
	.byte	0x3
	.byte	0x81
	.long	0x94c
	.uleb128 0x27
	.long	0x5b8
	.long	.LLST27
	.byte	0
	.uleb128 0x2a
	.long	.LVL36
	.long	0x492
	.long	0x968
	.uleb128 0x2b
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
	.uleb128 0x2a
	.long	.LVL37
	.long	0xb68
	.long	0x984
	.uleb128 0x2b
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
	.uleb128 0x2a
	.long	.LVL48
	.long	0x492
	.long	0x9a0
	.uleb128 0x2b
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
	.uleb128 0x2a
	.long	.LVL51
	.long	0xb85
	.long	0x9bc
	.uleb128 0x2b
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
	.uleb128 0x24
	.long	.LVL52
	.long	0xb99
	.byte	0
	.uleb128 0x24
	.long	.LVL13
	.long	0x526
	.byte	0
	.uleb128 0x20
	.byte	0x1
	.long	.LASF77
	.byte	0x3
	.byte	0xa3
	.byte	0x1
	.long	.LFB87
	.long	.LFE87
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xa04
	.uleb128 0x2d
	.long	.LVL53
	.byte	0x1
	.long	0xba3
	.uleb128 0x2b
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
	.uleb128 0x20
	.byte	0x1
	.long	.LASF78
	.byte	0x3
	.byte	0xa9
	.byte	0x1
	.long	.LFB88
	.long	.LFE88
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xa38
	.uleb128 0x2d
	.long	.LVL54
	.byte	0x1
	.long	0xbbb
	.uleb128 0x2b
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
	.uleb128 0x2e
	.byte	0x1
	.long	.LASF79
	.byte	0x3
	.byte	0xb2
	.byte	0x1
	.long	.LFB89
	.long	.LFE89
	.long	.LLST28
	.byte	0x1
	.long	0xa71
	.uleb128 0x16
	.long	.LASF80
	.byte	0x3
	.byte	0xb2
	.long	0xa71
	.long	.LLST29
	.uleb128 0x1a
	.long	.LASF81
	.byte	0x3
	.byte	0xb4
	.long	0x30
	.long	.LLST30
	.byte	0
	.uleb128 0x9
	.long	0xa76
	.uleb128 0xd
	.byte	0x2
	.long	0x267
	.uleb128 0x2e
	.byte	0x1
	.long	.LASF82
	.byte	0x3
	.byte	0xe2
	.byte	0x1
	.long	.LFB90
	.long	.LFE90
	.long	.LLST31
	.byte	0x1
	.long	0xabe
	.uleb128 0x1a
	.long	.LASF75
	.byte	0x3
	.byte	0xe4
	.long	0x30
	.long	.LLST32
	.uleb128 0x2c
	.long	.LVL68
	.long	0x40b
	.uleb128 0x2b
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
	.uleb128 0x20
	.byte	0x1
	.long	.LASF83
	.byte	0x3
	.byte	0xee
	.byte	0x1
	.long	.LFB91
	.long	.LFE91
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xaf7
	.uleb128 0x16
	.long	.LASF80
	.byte	0x3
	.byte	0xee
	.long	0xa71
	.long	.LLST33
	.uleb128 0x1a
	.long	.LASF84
	.byte	0x3
	.byte	0xf0
	.long	0x1ab
	.long	.LLST34
	.byte	0
	.uleb128 0x2f
	.long	.LASF85
	.byte	0x3
	.byte	0x28
	.long	0x2cb
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	USBtoUSART_Buffer
	.uleb128 0x2f
	.long	.LASF86
	.byte	0x3
	.byte	0x2b
	.long	0x2cb
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	USARTtoUSB_Buffer
	.uleb128 0x2f
	.long	.LASF87
	.byte	0x3
	.byte	0x33
	.long	0xb2d
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	PulseMSRemaining
	.uleb128 0x30
	.long	0x2d6
	.uleb128 0x2f
	.long	.LASF88
	.byte	0x3
	.byte	0x39
	.long	0x267
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	VirtualSerial_CDC_Interface
	.uleb128 0x31
	.byte	0x1
	.long	.LASF91
	.byte	0xa
	.word	0x123
	.byte	0x1
	.byte	0x1
	.uleb128 0x32
	.byte	0x1
	.long	.LASF89
	.byte	0x9
	.word	0x106
	.byte	0x1
	.long	0x42
	.byte	0x1
	.long	0xb68
	.uleb128 0x33
	.long	0xa71
	.byte	0
	.uleb128 0x34
	.byte	0x1
	.long	.LASF90
	.byte	0x9
	.byte	0xe9
	.byte	0x1
	.long	0x30
	.byte	0x1
	.long	0xb85
	.uleb128 0x33
	.long	0xa71
	.uleb128 0x33
	.long	0x328
	.byte	0
	.uleb128 0x35
	.byte	0x1
	.long	.LASF102
	.byte	0x9
	.byte	0xac
	.byte	0x1
	.byte	0x1
	.long	0xb99
	.uleb128 0x33
	.long	0xa71
	.byte	0
	.uleb128 0x36
	.byte	0x1
	.long	.LASF92
	.byte	0xb
	.byte	0xb2
	.byte	0x1
	.byte	0x1
	.uleb128 0x34
	.byte	0x1
	.long	.LASF93
	.byte	0x9
	.byte	0x9e
	.byte	0x1
	.long	0x1ab
	.byte	0x1
	.long	0xbbb
	.uleb128 0x33
	.long	0xa71
	.byte	0
	.uleb128 0x37
	.byte	0x1
	.long	.LASF103
	.byte	0x9
	.byte	0xa5
	.byte	0x1
	.byte	0x1
	.uleb128 0x33
	.long	0xa71
	.byte	0
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
	.uleb128 0xd
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
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
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
	.uleb128 0xf
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
	.uleb128 0x10
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
	.uleb128 0x11
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
	.uleb128 0x12
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
	.uleb128 0x13
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
	.uleb128 0x14
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x18
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x19
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
	.uleb128 0x1a
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
	.uleb128 0x1b
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
	.uleb128 0x1c
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
	.uleb128 0x1d
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1e
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
	.uleb128 0x1f
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
	.uleb128 0x20
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
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
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
	.uleb128 0x22
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
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
	.uleb128 0x26
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x28
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
	.uleb128 0x29
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2a
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
	.uleb128 0x2b
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x4109
	.byte	0x1
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
	.uleb128 0x2115
	.uleb128 0xc
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2e
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
	.uleb128 0x2f
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
	.uleb128 0x30
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x31
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
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x32
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x33
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x34
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
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x35
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
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x36
	.uleb128 0x2e
	.byte	0
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
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x37
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
	.uleb128 0x3c
	.uleb128 0xc
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
	.long	.LFE71
	.word	0x4
	.byte	0x8e
	.sleb128 -132
	.byte	0x9f
	.long	0
	.long	0
.LLST1:
	.long	.LVL2
	.long	.LVL4
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL4
	.long	.LFE71
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST2:
	.long	.LVL5
	.long	.LVL10
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL10
	.long	.LFE72
	.word	0x4
	.byte	0x8e
	.sleb128 -132
	.byte	0x9f
	.long	0
	.long	0
.LLST3:
	.long	.LVL8
	.long	.LVL9
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL9
	.long	.LFE72
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST4:
	.long	.LVL14
	.long	.LVL18
	.word	0x1
	.byte	0x62
	.long	.LVL18
	.long	.LVL21
	.word	0x2
	.byte	0x8
	.byte	0x5f
	.long	0
	.long	0
.LLST5:
	.long	.LVL15
	.long	.LVL16
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL16
	.long	.LFE85
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST6:
	.long	.LVL16
	.long	.LVL20
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1571
	.sleb128 0
	.long	.LVL20
	.long	.LVL22
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1671
	.sleb128 0
	.long	.LVL25
	.long	.LVL32
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1837
	.sleb128 0
	.long	.LVL32
	.long	.LVL46
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2031
	.sleb128 0
	.long	.LVL46
	.long	.LFE85
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2257
	.sleb128 0
	.long	0
	.long	0
.LLST7:
	.long	.LVL18
	.long	.LVL22
	.word	0x1
	.byte	0x62
	.long	0
	.long	0
.LLST8:
	.long	.LVL19
	.long	.LVL20
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL20
	.long	.LFE85
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST9:
	.long	.LVL20
	.long	.LVL22
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1671
	.sleb128 0
	.long	.LVL25
	.long	.LVL32
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1837
	.sleb128 0
	.long	.LVL32
	.long	.LVL46
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2031
	.sleb128 0
	.long	.LVL46
	.long	.LFE85
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2257
	.sleb128 0
	.long	0
	.long	0
.LLST10:
	.long	.LVL35
	.long	.LVL38
	.word	0x3
	.byte	0x8c
	.sleb128 -1
	.byte	0x9f
	.long	.LVL38
	.long	.LVL39
	.word	0x1
	.byte	0x6c
	.long	.LVL39
	.long	.LVL43
	.word	0x3
	.byte	0x8c
	.sleb128 -1
	.byte	0x9f
	.long	0
	.long	0
.LLST11:
	.long	.LVL25
	.long	.LVL26
	.word	0x1
	.byte	0x68
	.long	.LVL26
	.long	.LVL27-1
	.word	0x5
	.byte	0x3
	.long	USBtoUSART_Buffer+132
	.long	0
	.long	0
.LLST12:
	.long	.LVL23
	.long	.LVL27-1
	.word	0x1
	.byte	0x69
	.long	0
	.long	0
.LLST13:
	.long	.LVL24
	.long	.LVL25
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL25
	.long	.LFE85
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST14:
	.long	.LVL25
	.long	.LVL32
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+1837
	.sleb128 0
	.long	.LVL32
	.long	.LVL46
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2031
	.sleb128 0
	.long	.LVL46
	.long	.LFE85
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2257
	.sleb128 0
	.long	0
	.long	0
.LLST15:
	.long	.LVL27
	.long	.LVL28
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST16:
	.long	.LVL32
	.long	.LVL35
	.word	0x1
	.byte	0x6c
	.long	0
	.long	0
.LLST17:
	.long	.LVL30
	.long	.LVL33
	.word	0x1
	.byte	0x68
	.long	.LVL33
	.long	.LVL35
	.word	0x2
	.byte	0x8
	.byte	0x5f
	.long	0
	.long	0
.LLST18:
	.long	.LVL31
	.long	.LVL32
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL32
	.long	.LFE85
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST19:
	.long	.LVL32
	.long	.LVL46
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2031
	.sleb128 0
	.long	.LVL46
	.long	.LFE85
	.word	0x6
	.byte	0xf2
	.long	.Ldebug_info0+2257
	.sleb128 0
	.long	0
	.long	0
.LLST20:
	.long	.LVL34
	.long	.LVL35
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	0
	.long	0
.LLST21:
	.long	.LVL40
	.long	.LVL41
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	0
	.long	0
.LLST22:
	.long	.LVL42
	.long	.LVL43
	.word	0x3
	.byte	0x8
	.byte	0x40
	.byte	0x9f
	.long	0
	.long	0
.LLST23:
	.long	.LVL46
	.long	.LVL47
	.word	0x1
	.byte	0x68
	.long	.LVL47
	.long	.LVL48-1
	.word	0x5
	.byte	0x3
	.long	USBtoUSART_Buffer+132
	.long	0
	.long	0
.LLST24:
	.long	.LVL44
	.long	.LVL48-1
	.word	0x1
	.byte	0x69
	.long	0
	.long	0
.LLST25:
	.long	.LVL45
	.long	.LVL46
	.word	0x2
	.byte	0x31
	.byte	0x9f
	.long	.LVL46
	.long	.LFE85
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
.LLST26:
	.long	.LVL48
	.long	.LVL50
	.word	0x1
	.byte	0x68
	.long	0
	.long	0
.LLST27:
	.long	.LVL49
	.long	.LVL50
	.word	0x3
	.byte	0x8
	.byte	0x40
	.byte	0x9f
	.long	0
	.long	0
.LLST28:
	.long	.LFB89
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
	.long	.LCFI2
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI2
	.long	.LFE89
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	0
	.long	0
.LLST29:
	.long	.LVL55
	.long	.LVL57
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL57
	.long	.LVL65
	.word	0x6
	.byte	0x6c
	.byte	0x93
	.uleb128 0x1
	.byte	0x6d
	.byte	0x93
	.uleb128 0x1
	.long	.LVL65
	.long	.LFE89
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST30:
	.long	.LVL56
	.long	.LVL58
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL58
	.long	.LVL59
	.word	0x3
	.byte	0x8
	.byte	0x20
	.byte	0x9f
	.long	.LVL59
	.long	.LVL60
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL60
	.long	.LVL66
	.word	0x1
	.byte	0x61
	.long	0
	.long	0
.LLST31:
	.long	.LFB90
	.long	.LCFI3
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI3
	.long	.LCFI4
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI4
	.long	.LCFI5
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI5
	.long	.LCFI6
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI6
	.long	.LCFI7
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	.LCFI7
	.long	.LCFI8
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 7
	.long	.LCFI8
	.long	.LCFI9
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 8
	.long	.LCFI9
	.long	.LCFI10
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 9
	.long	.LCFI10
	.long	.LCFI11
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 10
	.long	.LCFI11
	.long	.LCFI12
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 11
	.long	.LCFI12
	.long	.LCFI13
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 12
	.long	.LCFI13
	.long	.LCFI14
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 13
	.long	.LCFI14
	.long	.LCFI15
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 14
	.long	.LCFI15
	.long	.LCFI16
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 15
	.long	.LCFI16
	.long	.LFE90
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 16
	.long	0
	.long	0
.LLST32:
	.long	.LVL67
	.long	.LVL68-1
	.word	0x1
	.byte	0x66
	.long	0
	.long	0
.LLST33:
	.long	.LVL69
	.long	.LVL70
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL70
	.long	.LFE91
	.word	0x6
	.byte	0x6e
	.byte	0x93
	.uleb128 0x1
	.byte	0x6f
	.byte	0x93
	.uleb128 0x1
	.long	0
	.long	0
.LLST34:
	.long	.LVL69
	.long	.LVL70
	.word	0x7
	.byte	0x88
	.sleb128 13
	.byte	0x94
	.byte	0x1
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.long	.LVL70
	.long	.LFE91
	.word	0x5
	.byte	0x88
	.sleb128 0
	.byte	0x31
	.byte	0x1a
	.byte	0x9f
	.long	0
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0x5c
	.word	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.word	0
	.word	0
	.long	.LFB71
	.long	.LFE71-.LFB71
	.long	.LFB72
	.long	.LFE72-.LFB72
	.long	.LFB86
	.long	.LFE86-.LFB86
	.long	.LFB85
	.long	.LFE85-.LFB85
	.long	.LFB87
	.long	.LFE87-.LFB87
	.long	.LFB88
	.long	.LFE88-.LFB88
	.long	.LFB89
	.long	.LFE89-.LFB89
	.long	.LFB90
	.long	.LFE90-.LFB90
	.long	.LFB91
	.long	.LFE91-.LFB91
	.long	0
	.long	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.long	.LFB71
	.long	.LFE71
	.long	.LFB72
	.long	.LFE72
	.long	.LFB86
	.long	.LFE86
	.long	.LFB85
	.long	.LFE85
	.long	.LFB87
	.long	.LFE87
	.long	.LFB88
	.long	.LFE88
	.long	.LFB89
	.long	.LFE89
	.long	.LFB90
	.long	.LFE90
	.long	.LFB91
	.long	.LFE91
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF99:
	.string	"RingBuffer_Remove"
.LASF88:
	.string	"VirtualSerial_CDC_Interface"
.LASF100:
	.string	"LEDs_Init"
.LASF97:
	.string	"__iCliRetVal"
.LASF82:
	.string	"__vector_23"
.LASF96:
	.string	"/Users/alessandrochelli/Downloads/LUFA 100807/Projects/arduino-usbserial"
.LASF65:
	.string	"RingBuffer_IsEmpty"
.LASF12:
	.string	"DEVICE_STATE_Unattached"
.LASF14:
	.string	"DEVICE_STATE_Default"
.LASF3:
	.string	"int16_t"
.LASF9:
	.string	"long long int"
.LASF0:
	.string	"signed char"
.LASF43:
	.string	"BaudRateBPS"
.LASF89:
	.string	"CDC_Device_ReceiveByte"
.LASF67:
	.string	"BaudRate"
.LASF10:
	.string	"long long unsigned int"
.LASF24:
	.string	"CDC_PARITY_None"
.LASF66:
	.string	"Serial_Init"
.LASF6:
	.string	"long int"
.LASF56:
	.string	"RxLEDPulse"
.LASF55:
	.string	"TxLEDPulse"
.LASF44:
	.string	"CharFormat"
.LASF36:
	.string	"DataOUTEndpointDoubleBank"
.LASF4:
	.string	"uint16_t"
.LASF18:
	.string	"USB_Device_States_t"
.LASF31:
	.string	"DataINEndpointNumber"
.LASF72:
	.string	"LEDMask"
.LASF42:
	.string	"DeviceToHost"
.LASF59:
	.string	"__ToDo"
.LASF5:
	.string	"unsigned int"
.LASF86:
	.string	"USARTtoUSB_Buffer"
.LASF90:
	.string	"CDC_Device_SendByte"
.LASF28:
	.string	"CDC_PARITY_Space"
.LASF8:
	.string	"long unsigned int"
.LASF19:
	.string	"CDC_LineEncodingFormats_t"
.LASF27:
	.string	"CDC_PARITY_Mark"
.LASF58:
	.string	"sreg_save"
.LASF20:
	.string	"CDC_LINEENCODING_OneStopBit"
.LASF71:
	.string	"LEDs_TurnOnLEDs"
.LASF16:
	.string	"DEVICE_STATE_Configured"
.LASF23:
	.string	"CDC_LineEncodingParity_t"
.LASF49:
	.string	"Config"
.LASF78:
	.string	"EVENT_USB_Device_UnhandledControlRequest"
.LASF98:
	.string	"RingBuffer_Insert"
.LASF35:
	.string	"DataOUTEndpointSize"
.LASF17:
	.string	"DEVICE_STATE_Suspended"
.LASF30:
	.string	"ControlInterfaceNumber"
.LASF25:
	.string	"CDC_PARITY_Odd"
.LASF64:
	.string	"RingBuffer_IsFull"
.LASF32:
	.string	"DataINEndpointSize"
.LASF103:
	.string	"CDC_Device_ProcessControlRequest"
.LASF11:
	.string	"sizetype"
.LASF34:
	.string	"DataOUTEndpointNumber"
.LASF53:
	.string	"Count"
.LASF22:
	.string	"CDC_LINEENCODING_TwoStopBits"
.LASF91:
	.string	"USB_Init"
.LASF37:
	.string	"NotificationEndpointNumber"
.LASF15:
	.string	"DEVICE_STATE_Addressed"
.LASF13:
	.string	"DEVICE_STATE_Powered"
.LASF33:
	.string	"DataINEndpointDoubleBank"
.LASF75:
	.string	"ReceivedByte"
.LASF81:
	.string	"ConfigMask"
.LASF76:
	.string	"SetupHardware"
.LASF102:
	.string	"CDC_Device_USBTask"
.LASF74:
	.string	"BufferCount"
.LASF40:
	.string	"_Bool"
.LASF1:
	.string	"unsigned char"
.LASF68:
	.string	"DoubleSpeed"
.LASF94:
	.string	"GNU C 4.8.1 -mmcu=atmega16u2 -gdwarf-2 -Os -std=gnu99 -funsigned-char -funsigned-bitfields -ffunction-sections -fno-inline-small-functions -fpack-struct -fshort-enums -fno-strict-aliasing"
.LASF38:
	.string	"NotificationEndpointSize"
.LASF63:
	.string	"RingBuffer_GetCount"
.LASF73:
	.string	"LEDs_TurnOffLEDs"
.LASF7:
	.string	"uint32_t"
.LASF26:
	.string	"CDC_PARITY_Even"
.LASF92:
	.string	"USB_USBTask"
.LASF29:
	.string	"char"
.LASF93:
	.string	"CDC_Device_ConfigureEndpoints"
.LASF50:
	.string	"State"
.LASF84:
	.string	"CurrentDTRState"
.LASF85:
	.string	"USBtoUSART_Buffer"
.LASF21:
	.string	"CDC_LINEENCODING_OneAndAHalfStopBits"
.LASF83:
	.string	"EVENT_CDC_Device_ControLineStateChanged"
.LASF57:
	.string	"PingPongLEDPulse"
.LASF47:
	.string	"ControlLineStates"
.LASF87:
	.string	"PulseMSRemaining"
.LASF60:
	.string	"__iRestore"
.LASF70:
	.string	"RingBuffer_InitBuffer"
.LASF54:
	.string	"RingBuff_t"
.LASF95:
	.string	"Arduino-usbserial.c"
.LASF48:
	.string	"LineEncoding"
.LASF52:
	.string	"Buffer"
.LASF46:
	.string	"DataBits"
.LASF2:
	.string	"uint8_t"
.LASF69:
	.string	"Data"
.LASF39:
	.string	"NotificationEndpointDoubleBank"
.LASF77:
	.string	"EVENT_USB_Device_ConfigurationChanged"
.LASF80:
	.string	"CDCInterfaceInfo"
.LASF45:
	.string	"ParityType"
.LASF79:
	.string	"EVENT_CDC_Device_LineEncodingChanged"
.LASF62:
	.string	"DataByte"
.LASF101:
	.string	"main"
.LASF61:
	.string	"Serial_TxByte"
.LASF51:
	.string	"USB_ClassInfo_CDC_Device_t"
.LASF41:
	.string	"HostToDevice"
	.ident	"GCC: (GNU) 4.8.1"
.global __do_copy_data
.global __do_clear_bss
