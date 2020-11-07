#pragma once
#include "pch.h"

#define MAX_TIMERS		2048
#define	MAX_PLAYERS		100
#define MAX_VEHICLES	1000
#define MAX_OBJECTS		3000
#define MAX_PICKUPS		2000
#define MAX_CHECKPOINTS 2000

typedef enum {
	Normal = 1,
	NormalRelative = 2,
	Turn = 3,
	TurnRelative = 4
} vcmpVehicleSpeed;

#define SKIN_ID_UNKNOWN 				-1
#define SKIN_ID_TOMMY_VERCETTI 			0
#define SKIN_ID_COP 					1
#define SKIN_ID_SWAT 					2
#define SKIN_ID_FBI 					3
#define SKIN_ID_ARMY 					4
#define SKIN_ID_PARAMEDIC 				5
#define SKIN_ID_FIREMAN 				6
#define SKIN_ID_GOLF_GUY_A 				7
#define SKIN_ID_BUM_LADY_A 				9
#define SKIN_ID_BUM_LADY_B 				10
#define SKIN_ID_PUNK_A 					11
#define SKIN_ID_LAWYER 					12
#define SKIN_ID_SPANISH_LADY_A 			13
#define SKIN_ID_SPANISH_LADY_B 			14
#define SKIN_ID_COOL_GUY_A 				15
#define SKIN_ID_ARABIC_GUY 				16
#define SKIN_ID_BEACH_LADY_A 			17
#define SKIN_ID_BEACH_LADY_B 			18
#define SKIN_ID_BEACH_GUY_A 			19
#define SKIN_ID_BEACH_GUY_B 			20
#define SKIN_ID_OFFICE_LADY_A 			21
#define SKIN_ID_WAITRESS_A 				22
#define SKIN_ID_FOOD_LADY 				23
#define SKIN_ID_PROSTITUTE_A 			24
#define SKIN_ID_BUM_LADY_C 				25
#define SKIN_ID_BUM_GUY_A 				26
#define SKIN_ID_GARBAGEMAN_A 			27
#define SKIN_ID_TAXI_DRIVER_A 			28
#define SKIN_ID_HATIAN_A 				29
#define SKIN_ID_CRIMINAL_A 				30
#define SKIN_ID_HOOD_LADY 				31
#define SKIN_ID_GRANNY_A 				32
#define SKIN_ID_BUSINESS_MAN_A 			33
#define SKIN_ID_CHURCH_GUY 				34
#define SKIN_ID_CLUB_LADY 				35
#define SKIN_ID_CHURCH_LADY 			36
#define SKIN_ID_PIMP 					37
#define SKIN_ID_BEACH_LADY_C 			38
#define SKIN_ID_BEACH_GUY_C 			39
#define SKIN_ID_BEACH_LADY_D 			40
#define SKIN_ID_BEACH_GUY_D 			41
#define SKIN_ID_BUSINESS_MAN_B 			42
#define SKIN_ID_PROSTITUTE_B 			43
#define SKIN_ID_BUM_LADY_D 				44
#define SKIN_ID_BUM_GUY_B 				45
#define SKIN_ID_HATIAN_B 				46
#define SKIN_ID_CONSTRUCTION_WORKER_A 	47
#define SKIN_ID_PUNK_B 					48
#define SKIN_ID_PROSTITUTE_C 			49
#define SKIN_ID_GRANNY_B 				50
#define SKIN_ID_PUNK_C 					51
#define SKIN_ID_BUSINESS_MAN_C 			52
#define SKIN_ID_SPANISH_LADY_C 			53
#define SKIN_ID_SPANISH_LADY_D 			54
#define SKIN_ID_COOL_GUY_B 				55
#define SKIN_ID_BUSINESS_MAN_D 			56
#define SKIN_ID_BEACH_LADY_E 			57
#define SKIN_ID_BEACH_GUY_E 			58
#define SKIN_ID_BEACH_LADY_F 			59
#define SKIN_ID_BEACH_GUY_F 			60
#define SKIN_ID_CONSTRUCTION_WORKER_B 	61
#define SKIN_ID_GOLF_GUY_B 				62
#define SKIN_ID_GOLF_LADY 				63
#define SKIN_ID_GOLF_GUY_C 				64
#define SKIN_ID_BEACH_LADY_G 			65
#define SKIN_ID_BEACH_GUY_G 			66
#define SKIN_ID_OFFICE_LADY_B 			67
#define SKIN_ID_BUSINESS_MAN_E 			68
#define SKIN_ID_BUSINESS_MAN_F 			69
#define SKIN_ID_PROSTITUTE_D 			70
#define SKIN_ID_BUM_LADY_E 				71
#define SKIN_ID_BUM_GUY_C 				72
#define SKIN_ID_SPANISH_GUY 			73
#define SKIN_ID_TAXI_DRIVER_B 			74
#define SKIN_ID_GYM_LADY 				75
#define SKIN_ID_GYM_GUY 				76
#define SKIN_ID_SKATE_LADY 				77
#define SKIN_ID_SKATE_GUY 				78
#define SKIN_ID_SHOPPER_A 				79
#define SKIN_ID_SHOPPER_B 				80
#define SKIN_ID_TOURIST_A 				81
#define SKIN_ID_TOURIST_B 				82
#define SKIN_ID_CUBAN_A 				83
#define SKIN_ID_CUBAN_B 				84
#define SKIN_ID_HATIAN_C 				85
#define SKIN_ID_HATIAN_D 				86
#define SKIN_ID_SHARK_A 				87
#define SKIN_ID_SHARK_B 				88
#define SKIN_ID_DIAZ_GUY_A 				89
#define SKIN_ID_DIAZ_GUY_B 				90
#define SKIN_ID_DBP_SECURITY_A 			91
#define SKIN_ID_DBP_SECURITY_B 			92
#define SKIN_ID_BIKER_A 				93
#define SKIN_ID_BIKER_B 				94
#define SKIN_ID_VERCETTI_GUY_A 			95
#define SKIN_ID_VERCETTI_GUY_B 			96
#define SKIN_ID_UNDERCOVER_COP_A 		97
#define SKIN_ID_UNDERCOVER_COP_B 		98
#define SKIN_ID_UNDERCOVER_COP_C 		99
#define SKIN_ID_UNDERCOVER_COP_D 		100
#define SKIN_ID_UNDERCOVER_COP_E 		101
#define SKIN_ID_UNDERCOVER_COP_F 		102
#define SKIN_ID_RICH_GUY 				103
#define SKIN_ID_COOL_GUY_C 				104
#define SKIN_ID_PROSTITUTE_E 			105
#define SKIN_ID_PROSTITUTE_F 			106
#define SKIN_ID_LOVE_FIST_A 			107
#define SKIN_ID_KEN_ROSENBURG 			108
#define SKIN_ID_CANDY_SUXX 				109
#define SKIN_ID_HILARY 					110
#define SKIN_ID_LOVE_FIST_B 			111
#define SKIN_ID_PHIL 					112
#define SKIN_ID_ROCKSTAR_GUY 			113
#define SKIN_ID_SONNY 					114
#define SKIN_ID_LANCE_A 				115
#define SKIN_ID_MERCADES_A 				116
#define SKIN_ID_LOVE_FIST_C 			117
#define SKIN_ID_ALEX_SRUB 				118
#define SKIN_ID_LANCE_COP 				119
#define SKIN_ID_LANCE_B 				120
#define SKIN_ID_CORTEZ 					121
#define SKIN_ID_LOVE_FIST_D 			122
#define SKIN_ID_COLUMBIAN_GUY_A 		123
#define SKIN_ID_HILARY_ROBBER 			124
#define SKIN_ID_MERCADES_B 				125
#define SKIN_ID_CAM 					126
#define SKIN_ID_CAM_ROBBER 				127
#define SKIN_ID_PHIL_ONE_ARM 			128
#define SKIN_ID_PHIL_ROBBER 			129
#define SKIN_ID_COOL_GUY_D 				130
#define SKIN_ID_PIZZAMAN 				131
#define SKIN_ID_TAXI_DRIVER_C 			132
#define SKIN_ID_TAXI_DRIVER_D 			133
#define SKIN_ID_SAILOR_A 				134
#define SKIN_ID_SAILOR_B 				135
#define SKIN_ID_SAILOR_C 				136
#define SKIN_ID_CHEF 					137
#define SKIN_ID_CRIMINAL_B 				138
#define SKIN_ID_FRENCH_GUY 				139
#define SKIN_ID_GARBAGEMAN_B 			140
#define SKIN_ID_HATIAN_E 				141
#define SKIN_ID_WAITRESS_B 				142
#define SKIN_ID_SONNY_GUY_A 			143
#define SKIN_ID_SONNY_GUY_B 			144
#define SKIN_ID_SONNY_GUY_C 			145
#define SKIN_ID_COLUMBIAN_GUY_B 		146
#define SKIN_ID_THUG_A 					147
#define SKIN_ID_BEACH_GUY_H 			148
#define SKIN_ID_GARBAGEMAN_C 			149
#define SKIN_ID_GARBAGEMAN_D 			150
#define SKIN_ID_GARBAGEMAN_E 			151
#define SKIN_ID_TRANNY 					152
#define SKIN_ID_THUG_B 					153
#define SKIN_ID_SPANDEX_GUY_A 			154
#define SKIN_ID_SPANDEX_GUY_B 			155
#define SKIN_ID_STRIPPER_A 				156
#define SKIN_ID_STRIPPER_B 				157
#define SKIN_ID_STRIPPER_C 				158
#define SKIN_ID_STORE_CLERK 			159