/***********************************************************************/
/*                                                                     */
/*  FILE        :vect.h                                                */
/*  DATE        :Mon, Mar 21, 2011                                     */
/*  DESCRIPTION :Definition of Vector                                  */
/*  CPU TYPE    :SH7045F                                               */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.18).    */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/***********************************************************************/
                  




//;<<VECTOR DATA START (POWER ON RESET)>>
//;0 Power On Reset PC
extern void PowerON_Reset_PC(void);                                                                                                                

//;<<VECTOR DATA END (POWER ON RESET)>>
// 1 Power On Reset SP

//;<<VECTOR DATA START (MANUAL RESET)>>
//;2 Manual Reset PC
extern void Manual_Reset_PC(void);                                                                                                                 

//;<<VECTOR DATA END (MANUAL RESET)>>
// 3 Manual Reset SP

// 4 Illegal code
#pragma interrupt INT_Illegal_code
extern void INT_Illegal_code(void);

// 5 Reserved

// 6 Illegal slot
#pragma interrupt INT_Illegal_slot
extern void INT_Illegal_slot(void);

// 7 Reserved

// 8 Reserved

// 9 CPU Address error
#pragma interrupt INT_CPU_Address
extern void INT_CPU_Address(void);

// 10 DMAC Address error
#pragma interrupt INT_DMAC_Address
extern void INT_DMAC_Address(void);

// 11 NMI
#pragma interrupt INT_NMI
extern void INT_NMI(void);

// 12 User breakpoint trap
#pragma interrupt INT_User_Break
extern void INT_User_Break(void);

// 13 Reserved

// 14 Reserved

// 15 Reserved

// 16 Reserved

// 17 Reserved

// 18 Reserved

// 19 Reserved

// 20 Reserved

// 21 Reserved

// 22 Reserved

// 23 Reserved

// 24 Reserved

// 25 Reserved

// 26 Reserved

// 27 Reserved

// 28 Reserved

// 29 Reserved

// 30 Reserved

// 31 Reserved

// 32 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA32
extern void INT_TRAPA32(void);

// 33 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA33
extern void INT_TRAPA33(void);

// 34 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA34
extern void INT_TRAPA34(void);

// 35 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA35
extern void INT_TRAPA35(void);

// 36 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA36
extern void INT_TRAPA36(void);

// 37 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA37
extern void INT_TRAPA37(void);

// 38 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA38
extern void INT_TRAPA38(void);

// 39 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA39
extern void INT_TRAPA39(void);

// 40 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA40
extern void INT_TRAPA40(void);

// 41 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA41
extern void INT_TRAPA41(void);

// 42 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA42
extern void INT_TRAPA42(void);

// 43 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA43
extern void INT_TRAPA43(void);

// 44 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA44
extern void INT_TRAPA44(void);

// 45 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA45
extern void INT_TRAPA45(void);

// 46 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA46
extern void INT_TRAPA46(void);

// 47 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA47
extern void INT_TRAPA47(void);

// 48 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA48
extern void INT_TRAPA48(void);

// 49 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA49
extern void INT_TRAPA49(void);

// 50 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA50
extern void INT_TRAPA50(void);

// 51 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA51
extern void INT_TRAPA51(void);

// 52 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA52
extern void INT_TRAPA52(void);

// 53 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA53
extern void INT_TRAPA53(void);

// 54 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA54
extern void INT_TRAPA54(void);

// 55 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA55
extern void INT_TRAPA55(void);

// 56 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA56
extern void INT_TRAPA56(void);

// 57 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA57
extern void INT_TRAPA57(void);

// 58 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA58
extern void INT_TRAPA58(void);

// 59 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA59
extern void INT_TRAPA59(void);

// 60 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA60
extern void INT_TRAPA60(void);

// 61 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA61
extern void INT_TRAPA61(void);

// 62 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA62
extern void INT_TRAPA62(void);

// 63 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA63
extern void INT_TRAPA63(void);

// 64 Interrupt IRQ0
#pragma interrupt INT_IRQ0
extern void INT_IRQ0(void);

// 65 Interrupt IRQ1
#pragma interrupt INT_IRQ1
extern void INT_IRQ1(void);

// 66 Interrupt IRQ2
#pragma interrupt INT_IRQ2
extern void INT_IRQ2(void);

// 67 Interrupt IRQ3
#pragma interrupt INT_IRQ3
extern void INT_IRQ3(void);

// 68 Interrupt IRQ4
#pragma interrupt INT_IRQ4
extern void INT_IRQ4(void);

// 69 Interrupt IRQ5
#pragma interrupt INT_IRQ5
extern void INT_IRQ5(void);

// 70 Interrupt IRQ6
#pragma interrupt INT_IRQ6
extern void INT_IRQ6(void);

// 71 Interrupt IRQ7
#pragma interrupt INT_IRQ7
extern void INT_IRQ7(void);

// 72 DMAC0 DEI0
#pragma interrupt INT_DMAC0_DEI0
extern void INT_DMAC0_DEI0(void);

// 73 Reserved

// 74 Reserved

// 75 Reserved

// 76 DMAC1 DEI1
#pragma interrupt INT_DMAC1_DEI1
extern void INT_DMAC1_DEI1(void);

// 77 Reserved

// 78 Reserved

// 79 Reserved

// 80 DMAC3 DEI2
#pragma interrupt INT_DMAC3_DEI2
extern void INT_DMAC3_DEI2(void);

// 81 Reserved

// 82 Reserved

// 83 Reserved

// 84 DMAC3 DEI3
#pragma interrupt INT_DMAC3_DEI3
extern void INT_DMAC3_DEI3(void);

// 85 ReservedB

// 86 Reserved

// 87 Reserved

// 88 MTU0 TGI0A
#pragma interrupt INT_MTU0_TGI0A
extern void INT_MTU0_TGI0A(void);

// 89 MTU0 TGI0B
#pragma interrupt INT_MTU0_TGI0B
extern void INT_MTU0_TGI0B(void);

// 90 MTU0 TGI0C
#pragma interrupt INT_MTU0_TGI0C
extern void INT_MTU0_TGI0C(void);

// 91 MTU0 TGI0D
#pragma interrupt INT_MTU0_TGI0D
extern void INT_MTU0_TGI0D(void);

// 92 MTU0 TCI0V
#pragma interrupt INT_MTU0_TCI0V
extern void INT_MTU0_TCI0V(void);

// 93 Reserved

// 94 Reserved

// 95 Reserved

// 96 MTU1 TGI1A
#pragma interrupt INT_MTU1_TGI1A
extern void INT_MTU1_TGI1A(void);

// 97 MTU1 TGI1B
#pragma interrupt INT_MTU1_TGI1B
extern void INT_MTU1_TGI1B(void);

// 98 Reserved

// 99 Reserved

// 100 MTU1 TCI1V
#pragma interrupt INT_MTU1_TCI1V
extern void INT_MTU1_TCI1V(void);

// 101 MTU1 TCI1U
#pragma interrupt INT_MTU1_TCI1U
extern void INT_MTU1_TCI1U(void);

// 102 Reserved

// 103 Reserved

// 104 MTU2 TGI2A
#pragma interrupt INT_MTU2_TGI2A
extern void INT_MTU2_TGI2A(void);

// 105 MTU2 TGI2B
#pragma interrupt INT_MTU2_TGI2B
extern void INT_MTU2_TGI2B(void);

// 106 Reserved

// 107 Reserved

// 108 MTU2 TCI2V
#pragma interrupt INT_MTU2_TCI2V
extern void INT_MTU2_TCI2V(void);

// 109 MTU2 TCI2U
#pragma interrupt INT_MTU2_TCI2U
extern void INT_MTU2_TCI2U(void);

// 110 Reserved

// 111 Reserved

// 112 MTU3 TGI3A
#pragma interrupt INT_MTU3_TGI3A
extern void INT_MTU3_TGI3A(void);

// 113 MTU3 TGI3B
#pragma interrupt INT_MTU3_TGI3B
extern void INT_MTU3_TGI3B(void);

// 114 MTU3 TGI3C
#pragma interrupt INT_MTU3_TGI3C
extern void INT_MTU3_TGI3C(void);

// 115 MTU3 TGI3D
#pragma interrupt INT_MTU3_TGI3D
extern void INT_MTU3_TGI3D(void);

// 116 MTU3 TCI3V
#pragma interrupt INT_MTU3_TCI3V
extern void INT_MTU3_TCI3V(void);

// 117 Reserved

// 118 Reserved

// 119 Reserved

// 120 MTU4 TGI4A
#pragma interrupt INT_MTU4_TGI4A
extern void INT_MTU4_TGI4A(void);

// 121 MTU4 TGI4B
#pragma interrupt INT_MTU4_TGI4B
extern void INT_MTU4_TGI4B(void);

// 122 MTU4 TGI4C
#pragma interrupt INT_MTU4_TGI4C
extern void INT_MTU4_TGI4C(void);

// 123 MTU4 TGI4D
#pragma interrupt INT_MTU4_TGI4D
extern void INT_MTU4_TGI4D(void);

// 124 MTU4 TCI4V
#pragma interrupt INT_MTU4_TCI4V
extern void INT_MTU4_TCI4V(void);

// 125 Reserved

// 126 Reserved

// 127 Reserved

// 128 SCI0 ERI0
#pragma interrupt INT_SCI0_ERI0
extern void INT_SCI0_ERI0(void);

// 129 SCI0 RXI0
#pragma interrupt INT_SCI0_RXI0
extern void INT_SCI0_RXI0(void);

// 130 SCI0 TXI0
#pragma interrupt INT_SCI0_TXI0
extern void INT_SCI0_TXI0(void);

// 131 SCI0 TEI0
#pragma interrupt INT_SCI0_TEI0
extern void INT_SCI0_TEI0(void);

// 132 SCI1 ERI1
#pragma interrupt INT_SCI1_ERI1
extern void INT_SCI1_ERI1(void);

// 133 SCI1 RXI1
#pragma interrupt INT_SCI1_RXI1
extern void INT_SCI1_RXI1(void);

// 134 SCI1 TXI1
#pragma interrupt INT_SCI1_TXI1
extern void INT_SCI1_TXI1(void);

// 135 SCI1 TEI1
#pragma interrupt INT_SCI1_TEI1
extern void INT_SCI1_TEI1(void);

// 136 A/D ADI0
#pragma interrupt INT_ADI0
extern void INT_ADI0(void);

// 137 A/D ADI0
#pragma interrupt INT_ADI1
extern void INT_ADI1(void);

// 138 Reserved

// 139 Reserved

// 140 DTC SWDTCE
#pragma interrupt INT_DTC_SWDTCE
extern void INT_DTC_SWDTCE(void);

// 141 Reserved

// 142 Reserved

// 143 Reserved

// 144 CMT0 CMI0
#pragma interrupt INT_CMT0_CMI0
extern void INT_CMT0_CMI0(void);

// 145 Reserved

// 146 Reserved

// 147 Reserved

// 148 CMT1 CMI1
#pragma interrupt INT_CMT1_CMI1
extern void INT_CMT1_CMI1(void);

// 149 Reserved

// 150 Reserved

// 151 Reserved

// 152 WDT ITI
#pragma interrupt INT_WDT_ITI
extern void INT_WDT_ITI(void);

// 153 BSC CMI
#pragma interrupt INT_BSC_CMI
extern void INT_BSC_CMI(void);

// 154 Reserved

// 155 Reserved

// 156 I/O OEI
#pragma interrupt INT_OEI
extern void INT_OEI(void);

// 157 Reserved

// 158 Reserved

// 159 Reserved

// 160 Reserved

// 161 Reserved

// 162 Reserved

// 163 Reserved

// 164 Reserved

// 165 Reserved

// 166 Reserved

// 167 Reserved

// 168 Reserved

// 169 Reserved

// 170 Reserved

// 171 Reserved

// 172 Reserved

// 173 Reserved

// 174 Reserved

// 175 Reserved

// 176 Reserved

// 177 Reserved

// 178 Reserved

// 179 Reserved

// 180 Reserved

// 181 Reserved

// 182 Reserved

// 183 Reserved

// 184 Reserved

// 185 Reserved

// 186 Reserved

// 187 Reserved

// 188 Reserved

// 189 Reserved

// 190 Reserved

// 191 Reserved

// 192 Reserved

// 193 Reserved

// 194 Reserved

// 195 Reserved

// 196 Reserved

// 197 Reserved

// 198 Reserved

// 199 Reserved

// 200 Reserved

// 201 Reserved

// 202 Reserved

// 203 Reserved

// 204 Reserved

// 205 Reserved

// 206 Reserved

// 207 Reserved

// 208 Reserved

// 209 Reserved

// 210 Reserved

// 211 Reserved

// 212 Reserved

// 213 Reserved

// 214 Reserved

// 215 Reserved

// 216 Reserved

// 217 Reserved

// 218 Reserved

// 219 Reserved

// 220 Reserved

// 221 Reserved

// 222 Reserved

// 223 Reserved

// 224 Reserved

// 225 Reserved

// 226 Reserved

// 227 Reserved

// 228 Reserved

// 229 Reserved

// 230 Reserved

// 231 Reserved

// 232 Reserved

// 233 Reserved

// 234 Reserved

// 235 Reserved

// 236 Reserved

// 237 Reserved

// 238 Reserved

// 239 Reserved

// 240 Reserved

// 241 Reserved

// 242 Reserved

// 243 Reserved

// 244 Reserved

// 245 Reserved

// 246 Reserved

// 247 Reserved

// 248 Reserved

// 249 Reserved

// 250 Reserved

// 251 Reserved

// 252 Reserved

// 253 Reserved

// 254 Reserved

// 255 Reserved

// Dummy
#pragma interrupt Dummy
extern void Dummy(void);