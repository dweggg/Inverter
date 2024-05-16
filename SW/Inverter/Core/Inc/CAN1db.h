/*
 *  @formatter:off
 *  CAN1db.h
 *
 *  Created on: mayo 16, 2024 18:10:49 :: Software Version: 0.5beta 
 *		Author: Valentin Felsner
 *		Copyright by IMED Ltd :: http://www.imed.co.nz.
 *
 *		This is a .dbc to .h C header converter.
 *		It converts a Vector CANdb++ .dbc file to CAN message and signal structs to make them
 *		more easily human readable during development and support auto-completion in eclipse-based IDEs.
 *
 *		This software is a beta version and provided "as is" - neither IMED Ltd nor the author
 *		take any responsibility for the results. It may be used free of charge but it is not permitted
 *		to redistribute the software nor to decompile and/or modify the original converter source code.
 *		Please send us an email to contact@imed.co.nz if you have any feature requests or bug reports, thank you.
 *		And if you or your business do find this software useful, come to New Zealand and join us for a beer some time!
 */

#ifndef DBC_CAN1DB_H
#define DBC_CAN1DB_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Only define if not using STM Cube */
#ifndef USE_HAL_DRIVER
	#ifndef CAN_ID_STD
	#define CAN_ID_STD		((uint32_t)0x00000000U)  /*!< Standard Id */
	#endif
	#ifndef CAN_ID_EXT
	#define CAN_ID_EXT		((uint32_t)0x00000004U)  /*!< Extended Id as per STM32 HAL*/
	#endif
#endif
#include "stdint.h"

/*
 * ---------------------------------------------------------------------------------------------------------------------
 * Helper function to link a converter struct pointer to a CAN message array (uint_8t[8])
 * This converter struct acts like a "getSigVal()" function.
 * Usage example: 
 * DBC_linkMsgConverter(DBC_IMED_HELMBUS_MSG_BTN_STATUS, RxMessage);
 * 
 * -> DBC_IMED_HELMBUS_MSG_BTN_STATUS is a generated CANdb message struct.
 * -> RxMessage is an uint8_t array[8] as received or sent by the can peripheral.
 * 
 * Now, the message data can be accessed like this:
 * uint32_t uid = DBC_IMED_HELMBUS_MSG_BTN_STATUS.getSigVal->Board_UID;
 * 
 * -> or whatever signals are defined in that message.
 * ---------------------------------------------------------------------------------------------------------------------
 */
#ifndef DBC_linkMsgConverter
#define DBC_linkMsgConverter(dbc, arr) (dbc).getSigVal = (typeof((dbc).getSigVal)) &(arr)
#define DBC_setup(dbc, MSG)  \
do { \
	(MSG).DLC = (dbc).DLC; \
	(MSG).IDE = (dbc).IDE; \
	(MSG).RTR = 0; \
	(MSG).ExtId = (MSG).IDE > 0 ? (dbc).ID : 0; \
	(MSG).StdId = (MSG).IDE > 0 ? 0 : (dbc).ID; \
} while (0)

/*
 * ---------------------------------------------------------------------------------------------------------------------
 *	Type definitions
 * ---------------------------------------------------------------------------------------------------------------------
 */

/**
 * Data value types are defined here. Same list as is available in Vector CANdb++ for signal data types.
 */
typedef enum dbc_valueType {
	dbc_valueType_unsigned = 0, dbc_valueType_signed, dbc_valueType_float, dbc_valueType_double, dbc_valueType_void
} dbc_valueType;

/*
 * ---------------------------------------------------------------------------------------------------------------------
 *	ValueTables
 * ---------------------------------------------------------------------------------------------------------------------
 */

typedef enum DBC_VT_TC_WARNING {
	DBC_VT_TC_WARNING_For input string: "No" = 9999, DBC_VT_TC_WARNING_Value descriptions must not contain spaces! = 9999, DBC_VT_TC_WARNING_For input string: "TC" = 9999, DBC_VT_TC_WARNING_Value descriptions must not contain spaces! = 9999, DBC_VT_TC_WARNING_For input string: "TC_Warning" = 9999, DBC_VT_TC_WARNING_Value descriptions must not contain spaces! = 9999
} DBC_VT_TC_WARNING;

typedef enum DBC_VT_REGENERATIVE_ENABLE {
	DBC_VT_REGENERATIVE_ENABLE_For input string: "Not" = 9999, DBC_VT_REGENERATIVE_ENABLE_Value descriptions must not contain spaces! = 9999, DBC_VT_REGENERATIVE_ENABLE_For input string: "Enabled" = 9999, DBC_VT_REGENERATIVE_ENABLE_Value descriptions must not contain spaces! = 9999, DBC_VT_REGENERATIVE_ENABLE_For input string: "Regenerative_Enable" = 9999, DBC_VT_REGENERATIVE_ENABLE_Value descriptions must not contain spaces! = 9999
} DBC_VT_REGENERATIVE_ENABLE;

typedef enum DBC_VT_SHUTDOWN_PACKAGEINTCK {
	DBC_VT_SHUTDOWN_PACKAGEINTCK_OPENED = 0, DBC_VT_SHUTDOWN_PACKAGEINTCK_OK = 1
} DBC_VT_SHUTDOWN_PACKAGEINTCK;

typedef enum DBC_VT_SHUTDOWN_IMD {
	DBC_VT_SHUTDOWN_IMD_OPENED = 0, DBC_VT_SHUTDOWN_IMD_OPEN = 1
} DBC_VT_SHUTDOWN_IMD;

typedef enum DBC_VT_SHUTDOWN_BMS {
	DBC_VT_SHUTDOWN_BMS_OPENED = 0, DBC_VT_SHUTDOWN_BMS_OK = 1
} DBC_VT_SHUTDOWN_BMS;

typedef enum DBC_VT_CURRENTSENSOR_ERROR {
	DBC_VT_CURRENTSENSOR_ERROR_OK = 0, DBC_VT_CURRENTSENSOR_ERROR_ERROR = 1
} DBC_VT_CURRENTSENSOR_ERROR;

typedef enum DBC_VT_BMSERROR_OVERCURRENT {
	DBC_VT_BMSERROR_OVERCURRENT_ERROR = 0, DBC_VT_BMSERROR_OVERCURRENT_OK = 1
} DBC_VT_BMSERROR_OVERCURRENT;

typedef enum DBC_VT_STATE_PRECHARGERELAY {
	DBC_VT_STATE_PRECHARGERELAY_OPENED = 0, DBC_VT_STATE_PRECHARGERELAY_CLOSED = 1
} DBC_VT_STATE_PRECHARGERELAY;

typedef enum DBC_VT_STATE_DIVIDECURRENT {
	DBC_VT_STATE_DIVIDECURRENT_OFF = 0, DBC_VT_STATE_DIVIDECURRENT_ON = 1
} DBC_VT_STATE_DIVIDECURRENT;

typedef enum DBC_VT_STATE_BALANCING {
	DBC_VT_STATE_BALANCING_OFF = 0, DBC_VT_STATE_BALANCING_ON = 1
} DBC_VT_STATE_BALANCING;

typedef enum DBC_VT_STATE_AIR_PLUS {
	DBC_VT_STATE_AIR_PLUS_OPENED = 0, DBC_VT_STATE_AIR_PLUS_CLOSED = 1
} DBC_VT_STATE_AIR_PLUS;

typedef enum DBC_VT_STATE_AIR_MINUS {
	DBC_VT_STATE_AIR_MINUS_OPENED = 0, DBC_VT_STATE_AIR_MINUS_CLOSED = 1
} DBC_VT_STATE_AIR_MINUS;

typedef enum DBC_VT_STATE_ACCUMULATORFANS {
	DBC_VT_STATE_ACCUMULATORFANS_OFF = 0, DBC_VT_STATE_ACCUMULATORFANS_ON = 1
} DBC_VT_STATE_ACCUMULATORFANS;

typedef enum DBC_VT_BMSERROR_VOLTAGEDISCONNECTION {
	DBC_VT_BMSERROR_VOLTAGEDISCONNECTION_ERROR = 0, DBC_VT_BMSERROR_VOLTAGEDISCONNECTION_OK = 1
} DBC_VT_BMSERROR_VOLTAGEDISCONNECTION;

typedef enum DBC_VT_BMSERROR_UNDERVOLTAGE {
	DBC_VT_BMSERROR_UNDERVOLTAGE_ERROR = 0, DBC_VT_BMSERROR_UNDERVOLTAGE_OK = 1
} DBC_VT_BMSERROR_UNDERVOLTAGE;

typedef enum DBC_VT_BMSERROR_UNDERTEMPERATURE {
	DBC_VT_BMSERROR_UNDERTEMPERATURE_ERROR = 0, DBC_VT_BMSERROR_UNDERTEMPERATURE_OK = 1
} DBC_VT_BMSERROR_UNDERTEMPERATURE;

typedef enum DBC_VT_BMSERROR_OVERVOLTAGE {
	DBC_VT_BMSERROR_OVERVOLTAGE_ERROR = 0, DBC_VT_BMSERROR_OVERVOLTAGE_OK = 1
} DBC_VT_BMSERROR_OVERVOLTAGE;

typedef enum DBC_VT_BMSERROR_OVERTEMPERATURE {
	DBC_VT_BMSERROR_OVERTEMPERATURE_ERROR = 0, DBC_VT_BMSERROR_OVERTEMPERATURE_OK = 1
} DBC_VT_BMSERROR_OVERTEMPERATURE;

typedef enum DBC_VT_BMSERROR_NTCDISCONNECTION {
	DBC_VT_BMSERROR_NTCDISCONNECTION_ERROR = 0, DBC_VT_BMSERROR_NTCDISCONNECTION_ON = 1
} DBC_VT_BMSERROR_NTCDISCONNECTION;

typedef enum DBC_VT_BMSERROR_SLAVEDISCONNECTION {
	DBC_VT_BMSERROR_SLAVEDISCONNECTION_ERROR = 0, DBC_VT_BMSERROR_SLAVEDISCONNECTION_OK = 1
} DBC_VT_BMSERROR_SLAVEDISCONNECTION;

typedef enum DBC_VT_CUSTOMMODE_IDENTIFIER {
	DBC_VT_CUSTOMMODE_IDENTIFIER_SKF_Initial = 1, DBC_VT_CUSTOMMODE_IDENTIFIER_CKF_Initial = 2, DBC_VT_CUSTOMMODE_IDENTIFIER_Cte_SKF = 3, DBC_VT_CUSTOMMODE_IDENTIFIER_Cte_CKF = 4, DBC_VT_CUSTOMMODE_IDENTIFIER_APPS_Sat_Down = 5, DBC_VT_CUSTOMMODE_IDENTIFIER_APPS_Sat_Up = 6, DBC_VT_CUSTOMMODE_IDENTIFIER_Max_Regenerative_Torque = 7, DBC_VT_CUSTOMMODE_IDENTIFIER_Power_Limit = 8, DBC_VT_CUSTOMMODE_IDENTIFIER_K_Reduction_P = 9, DBC_VT_CUSTOMMODE_IDENTIFIER_K_Reduction_Temperature = 10
} DBC_VT_CUSTOMMODE_IDENTIFIER;

typedef enum DBC_VT_RACINGMODE {
	DBC_VT_RACINGMODE_WorkShop_Test = 1, DBC_VT_RACINGMODE_Custom_Dash = 11, DBC_VT_RACINGMODE_Custom_Experiment_Enviroment = 12, DBC_VT_RACINGMODE_Acceleration_RUN1 = 21, DBC_VT_RACINGMODE_Acceleration_RUN2 = 22, DBC_VT_RACINGMODE_Skidpad_RUN1 = 31, DBC_VT_RACINGMODE_Skidpad_RUN2 = 32, DBC_VT_RACINGMODE_AutoX_RUN1 = 41, DBC_VT_RACINGMODE_AutoX_RUN2 = 42, DBC_VT_RACINGMODE_Endurance_RUN1 = 51, DBC_VT_RACINGMODE_Endurance_RUN2 = 52
} DBC_VT_RACINGMODE;

typedef enum DBC_VT_AIRS_STATE {
	DBC_VT_AIRS_STATE_OPEN = 0, DBC_VT_AIRS_STATE_CLOSE = 3, DBC_VT_AIRS_STATE_Precharge = 6, DBC_VT_AIRS_STATE_Charger = 9
} DBC_VT_AIRS_STATE;

typedef enum DBC_VT_TORQUE_LOCKON {
	DBC_VT_TORQUE_LOCKON_UNLOCKED = 0, DBC_VT_TORQUE_LOCKON_LOCKED = 1
} DBC_VT_TORQUE_LOCKON;

typedef enum DBC_VT_ENABLEDRIVE_ORDER {
	DBC_VT_ENABLEDRIVE_ORDER_OFF = 0, DBC_VT_ENABLEDRIVE_ORDER_ON = 1
} DBC_VT_ENABLEDRIVE_ORDER;

typedef enum DBC_VT_CAR_STATE {
	DBC_VT_CAR_STATE_INIT = 0, DBC_VT_CAR_STATE_STANDBY = 3, DBC_VT_CAR_STATE_PRECHARGE = 9, DBC_VT_CAR_STATE_LOCKED = 13, DBC_VT_CAR_STATE_OPEN = 21, DBC_VT_CAR_STATE_For input string: "PRECHARGE" = 9999, DBC_VT_CAR_STATE_Value descriptions must not contain spaces! = 9999, DBC_VT_CAR_STATE_For input string: "DONE" = 9999, DBC_VT_CAR_STATE_Value descriptions must not contain spaces! = 9999, DBC_VT_CAR_STATE_For input string: "TS" = 9999, DBC_VT_CAR_STATE_Value descriptions must not contain spaces! = 9999, DBC_VT_CAR_STATE_For input string: "RTD" = 9999, DBC_VT_CAR_STATE_Value descriptions must not contain spaces! = 9999, DBC_VT_CAR_STATE_For input string: "AIRs" = 9999, DBC_VT_CAR_STATE_Value descriptions must not contain spaces! = 9999, DBC_VT_CAR_STATE_For input string: "ENABLE" = 9999, DBC_VT_CAR_STATE_Value descriptions must not contain spaces! = 9999, DBC_VT_CAR_STATE_For input string: "Car_State" = 9999, DBC_VT_CAR_STATE_Value descriptions must not contain spaces! = 9999
} DBC_VT_CAR_STATE;

typedef enum DBC_VT_AIRS_REQUEST {
	DBC_VT_AIRS_REQUEST_OPEN = 0, DBC_VT_AIRS_REQUEST_CLOSE = 3, DBC_VT_AIRS_REQUEST_PRECHARGE = 6
} DBC_VT_AIRS_REQUEST;

typedef enum DBC_VT_CRITICALDISCONNECTION {
	DBC_VT_CRITICALDISCONNECTION_OK = 0, DBC_VT_CRITICALDISCONNECTION_ERROR = 1
} DBC_VT_CRITICALDISCONNECTION;

typedef enum DBC_VT_CURRENTPATHDISCONNECTIONFLAG {
	DBC_VT_CURRENTPATHDISCONNECTIONFLAG_CONNECTED = 0, DBC_VT_CURRENTPATHDISCONNECTIONFLAG_DISCONNECTED = 1
} DBC_VT_CURRENTPATHDISCONNECTIONFLAG;

typedef enum DBC_VT_CRITICAL_SIGNAL_DISCONNECTION {
	DBC_VT_CRITICAL_SIGNAL_DISCONNECTION_OK = 0, DBC_VT_CRITICAL_SIGNAL_DISCONNECTION_ERROR = 1
} DBC_VT_CRITICAL_SIGNAL_DISCONNECTION;

typedef enum DBC_VT_CRITICAL_CAN_DISCONNECTION {
	DBC_VT_CRITICAL_CAN_DISCONNECTION_OK = 0, DBC_VT_CRITICAL_CAN_DISCONNECTION_ERROR = 1
} DBC_VT_CRITICAL_CAN_DISCONNECTION;

typedef enum DBC_VT_APPS_IMPLAUSIBILITY {
	DBC_VT_APPS_IMPLAUSIBILITY_OK = 0, DBC_VT_APPS_IMPLAUSIBILITY_ERROR = 1
} DBC_VT_APPS_IMPLAUSIBILITY;

typedef enum DBC_VT_DISCONNECTION_PITOT {
	DBC_VT_DISCONNECTION_PITOT_CONNECTION = 0, DBC_VT_DISCONNECTION_PITOT_DISCONNECTION = 1
} DBC_VT_DISCONNECTION_PITOT;

typedef enum DBC_VT_DISCONNECTION_BRAKEPRESSURE {
	DBC_VT_DISCONNECTION_BRAKEPRESSURE_CONNECTION = 0, DBC_VT_DISCONNECTION_BRAKEPRESSURE_DISCONNECTION = 1
} DBC_VT_DISCONNECTION_BRAKEPRESSURE;

typedef enum DBC_VT_DISCONNECTION_DASHBOARD {
	DBC_VT_DISCONNECTION_DASHBOARD_CONNECTED = 0, DBC_VT_DISCONNECTION_DASHBOARD_DISCONNECTED = 1
} DBC_VT_DISCONNECTION_DASHBOARD;

typedef enum DBC_VT_DISCONNECTION_BMS {
	DBC_VT_DISCONNECTION_BMS_CONNECTED = 0, DBC_VT_DISCONNECTION_BMS_DISCONNECTED = 1
} DBC_VT_DISCONNECTION_BMS;

typedef enum DBC_VT_DISCONNECTION_FRONT {
	DBC_VT_DISCONNECTION_FRONT_CONNECTED = 0, DBC_VT_DISCONNECTION_FRONT_DISCONNECTED = 1
} DBC_VT_DISCONNECTION_FRONT;

typedef enum DBC_VT_DISCONNECTION_REAR {
	DBC_VT_DISCONNECTION_REAR_CONNECTED = 0, DBC_VT_DISCONNECTION_REAR_DISCONNECTED = 1
} DBC_VT_DISCONNECTION_REAR;

typedef enum DBC_VT_DISCONNECTION_STEERINGSENSOR {
	DBC_VT_DISCONNECTION_STEERINGSENSOR_CONNECTED = 0, DBC_VT_DISCONNECTION_STEERINGSENSOR_DISCONNECTED = 1
} DBC_VT_DISCONNECTION_STEERINGSENSOR;

typedef enum DBC_VT_DISCONNECTION_SUSP_R_R {
	DBC_VT_DISCONNECTION_SUSP_R_R_CONNECTION = 0, DBC_VT_DISCONNECTION_SUSP_R_R_DISCONNECTION = 1
} DBC_VT_DISCONNECTION_SUSP_R_R;

typedef enum DBC_VT_DISCONNECTION_SUSP_R_L {
	DBC_VT_DISCONNECTION_SUSP_R_L_CONNECTION = 0, DBC_VT_DISCONNECTION_SUSP_R_L_DISCONNECTION = 1
} DBC_VT_DISCONNECTION_SUSP_R_L;

typedef enum DBC_VT_DISCONNECTION_SUSP_F_R {
	DBC_VT_DISCONNECTION_SUSP_F_R_CONNECTION = 0, DBC_VT_DISCONNECTION_SUSP_F_R_DISCONNECTION = 1
} DBC_VT_DISCONNECTION_SUSP_F_R;

typedef enum DBC_VT_DISCONNECTION_SUSP_F_L {
	DBC_VT_DISCONNECTION_SUSP_F_L_CONNECTION = 0, DBC_VT_DISCONNECTION_SUSP_F_L_DISCONNECTION = 1
} DBC_VT_DISCONNECTION_SUSP_F_L;

typedef enum DBC_VT_DISCONNECTION_BRAKEPEDAL {
	DBC_VT_DISCONNECTION_BRAKEPEDAL_CONNECTION = 0, DBC_VT_DISCONNECTION_BRAKEPEDAL_DISCONNECTION = 1
} DBC_VT_DISCONNECTION_BRAKEPEDAL;

typedef enum DBC_VT_DISCONNECTION_APPS2 {
	DBC_VT_DISCONNECTION_APPS2_CONNECTION = 0, DBC_VT_DISCONNECTION_APPS2_DISCONNECTION = 1
} DBC_VT_DISCONNECTION_APPS2;

typedef enum DBC_VT_DISCONNECTION_APPS1 {
	DBC_VT_DISCONNECTION_APPS1_CONNECTION = 0, DBC_VT_DISCONNECTION_APPS1_DISCONNECTION = 1
} DBC_VT_DISCONNECTION_APPS1;

typedef enum DBC_VT_DISCONNECTION_ELLIPSE {
	DBC_VT_DISCONNECTION_ELLIPSE_CONNECTED = 0, DBC_VT_DISCONNECTION_ELLIPSE_DISCONNECTED = 1
} DBC_VT_DISCONNECTION_ELLIPSE;



/**
 * Signals map CAN data to physical signals and provide units, conversion factors and data types.
 * The same as used in CANdb++.
 */
typedef struct signal {
	const char* name;
	const char* unit;
	const dbc_valueType valueType;
	const uint8_t lengthBits;
	const float factor, offset, min, max;
} signal;

/**
 * Each message contains a struct of type signal_positioned to indicate the signal's position in the can frame
 * and to allow access of the signals properties using a pointer.
 */
typedef struct signal_positioned {
	const uint8_t position;
	const signal* attributes;
} signal_positioned;
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"


/*
 * ---------------------------------------------------------------------------------------------------------------------
 *	Signals
 * ---------------------------------------------------------------------------------------------------------------------
 */

/**
 * Name: 	InvRear_PowerError
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRear_PowerError = {
	.name = "InvRear_PowerError",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	SoC_Low
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_SoC_Low = {
	.name = "SoC_Low",
	.unit = "",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	SoC_High
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_SoC_High = {
	.name = "SoC_High",
	.unit = "",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	Disconnection_Pitot
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Disconnection_Pitot = {
	.name = "Disconnection_Pitot",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Disconnection_BrakePressure
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Disconnection_BrakePressure = {
	.name = "Disconnection_BrakePressure",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Disconnection_DashBoard
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Disconnection_DashBoard = {
	.name = "Disconnection_DashBoard",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Disconnection_BMS
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Disconnection_BMS = {
	.name = "Disconnection_BMS",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Disconnection_Front
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Disconnection_Front = {
	.name = "Disconnection_Front",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Disconnection_Rear
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Disconnection_Rear = {
	.name = "Disconnection_Rear",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Disconnection_SteeringSensor
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Disconnection_SteeringSensor = {
	.name = "Disconnection_SteeringSensor",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Disconnection_Susp_R_R
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Disconnection_Susp_R_R = {
	.name = "Disconnection_Susp_R_R",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Disconnection_Susp_R_L
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Disconnection_Susp_R_L = {
	.name = "Disconnection_Susp_R_L",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Disconnection_Susp_F_R
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Disconnection_Susp_F_R = {
	.name = "Disconnection_Susp_F_R",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Disconnection_Susp_F_L
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Disconnection_Susp_F_L = {
	.name = "Disconnection_Susp_F_L",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Disconnection_BrakePedal
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Disconnection_BrakePedal = {
	.name = "Disconnection_BrakePedal",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Disconnection_APPS2
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Disconnection_APPS2 = {
	.name = "Disconnection_APPS2",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Disconnection_APPS1
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Disconnection_APPS1 = {
	.name = "Disconnection_APPS1",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Disconnection_Ellipse
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Disconnection_Ellipse = {
	.name = "Disconnection_Ellipse",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRL_idMeas
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRL_idMeas = {
	.name = "InvRL_idMeas",
	.unit = "A",
	.valueType = dbc_valueType_signed,
	.lengthBits = 16,
	.factor = 0.1f, .offset = 0.0f, .min = -204.8f, .max = 204.7f
};

/**
 * Name: 	InvRL_iqMeas
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRL_iqMeas = {
	.name = "InvRL_iqMeas",
	.unit = "A",
	.valueType = dbc_valueType_signed,
	.lengthBits = 16,
	.factor = 0.1f, .offset = 0.0f, .min = -204.8f, .max = 204.7f
};

/**
 * Name: 	InvRR_idMeas
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRR_idMeas = {
	.name = "InvRR_idMeas",
	.unit = "A",
	.valueType = dbc_valueType_signed,
	.lengthBits = 16,
	.factor = 0.1f, .offset = 0.0f, .min = -204.8f, .max = 204.7f
};

/**
 * Name: 	InvRR_iqMeas
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRR_iqMeas = {
	.name = "InvRR_iqMeas",
	.unit = "A",
	.valueType = dbc_valueType_signed,
	.lengthBits = 16,
	.factor = 0.1f, .offset = 0.0f, .min = -204.8f, .max = 204.7f
};

/**
 * Name: 	InvRL_idRef
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRL_idRef = {
	.name = "InvRL_idRef",
	.unit = "A",
	.valueType = dbc_valueType_signed,
	.lengthBits = 16,
	.factor = 0.1f, .offset = 0.0f, .min = -204.8f, .max = 204.7f
};

/**
 * Name: 	InvRL_iqRef
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRL_iqRef = {
	.name = "InvRL_iqRef",
	.unit = "A",
	.valueType = dbc_valueType_signed,
	.lengthBits = 16,
	.factor = 0.1f, .offset = 0.0f, .min = -204.8f, .max = 204.7f
};

/**
 * Name: 	InvRR_idRef
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRR_idRef = {
	.name = "InvRR_idRef",
	.unit = "A",
	.valueType = dbc_valueType_signed,
	.lengthBits = 16,
	.factor = 0.1f, .offset = 0.0f, .min = -204.8f, .max = 204.7f
};

/**
 * Name: 	InvRR_iqRef
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRR_iqRef = {
	.name = "InvRR_iqRef",
	.unit = "A",
	.valueType = dbc_valueType_signed,
	.lengthBits = 16,
	.factor = 0.1f, .offset = 0.0f, .min = -204.8f, .max = 204.7f
};

/**
 * Name: 	MotRR_Power
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_MotRR_Power = {
	.name = "MotRR_Power",
	.unit = "W",
	.valueType = dbc_valueType_signed,
	.lengthBits = 16,
	.factor = 10.0f, .offset = 0.0f, .min = -50000.0f, .max = 50000.0f
};

/**
 * Name: 	MotRL_Power
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_MotRL_Power = {
	.name = "MotRL_Power",
	.unit = "W",
	.valueType = dbc_valueType_signed,
	.lengthBits = 16,
	.factor = 10.0f, .offset = 0.0f, .min = -50000.0f, .max = 50000.0f
};

/**
 * Name: 	InvRR_DCBus
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRR_DCBus = {
	.name = "InvRR_DCBus",
	.unit = "V",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 0.01f, .offset = 0.0f, .min = 0.0f, .max = 655.35f
};

/**
 * Name: 	InvRL_DCBus
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRL_DCBus = {
	.name = "InvRL_DCBus",
	.unit = "V",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 0.01f, .offset = 0.0f, .min = 0.0f, .max = 655.35f
};

/**
 * Name: 	InvRear_Alive
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRear_Alive = {
	.name = "InvRear_Alive",
	.unit = "",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 8,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 255.0f
};

/**
 * Name: 	MotRR_TorqueCalc
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_MotRR_TorqueCalc = {
	.name = "MotRR_TorqueCalc",
	.unit = "Nm",
	.valueType = dbc_valueType_signed,
	.lengthBits = 16,
	.factor = 0.01f, .offset = 0.0f, .min = -100.0f, .max = 100.0f
};

/**
 * Name: 	MotRR_Speed
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_MotRR_Speed = {
	.name = "MotRR_Speed",
	.unit = "RPM",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	MotRL_Speed
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_MotRL_Speed = {
	.name = "MotRL_Speed",
	.unit = "RPM",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	MotRL_TorqueCalc
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_MotRL_TorqueCalc = {
	.name = "MotRL_TorqueCalc",
	.unit = "Nm",
	.valueType = dbc_valueType_signed,
	.lengthBits = 16,
	.factor = 0.01f, .offset = 0.0f, .min = -100.0f, .max = 100.0f
};

/**
 * Name: 	MotRR_Temp
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_MotRR_Temp = {
	.name = "MotRR_Temp",
	.unit = "ºC",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 0.1f, .offset = 0.0f, .min = 0.0f, .max = 200.0f
};

/**
 * Name: 	InvRR_Temp
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRR_Temp = {
	.name = "InvRR_Temp",
	.unit = "ºC",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 0.1f, .offset = 0.0f, .min = 0.0f, .max = 200.0f
};

/**
 * Name: 	InvRL_Temp
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRL_Temp = {
	.name = "InvRL_Temp",
	.unit = "ºC",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 0.1f, .offset = 0.0f, .min = 0.0f, .max = 200.0f
};

/**
 * Name: 	MotRL_Temp
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_MotRL_Temp = {
	.name = "MotRL_Temp",
	.unit = "ºC",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 0.1f, .offset = 0.0f, .min = 0.0f, .max = 200.0f
};

/**
 * Name: 	MotRL_OverTemp_Error
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_MotRL_OverTemp_Error = {
	.name = "MotRL_OverTemp_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	MotRL_Encoder_Error
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_MotRL_Encoder_Error = {
	.name = "MotRL_Encoder_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRL_UnderVoltage_Error
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRL_UnderVoltage_Error = {
	.name = "InvRL_UnderVoltage_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRL_OverVoltage_Error
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRL_OverVoltage_Error = {
	.name = "InvRL_OverVoltage_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRL_OverTemp_Error
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRL_OverTemp_Error = {
	.name = "InvRL_OverTemp_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRL_OverSpeed_Error
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRL_OverSpeed_Error = {
	.name = "InvRL_OverSpeed_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRL_OverCurrent_Error
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRL_OverCurrent_Error = {
	.name = "InvRL_OverCurrent_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRL_HW_Warning
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRL_HW_Warning = {
	.name = "InvRL_HW_Warning",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRL_Control_Error
 * Comment:	Calculus error
 */
static const signal DBC_CAN1DB_SIG_InvRL_Control_Error = {
	.name = "InvRL_Control_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	MotRR_OverTemp_Error
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_MotRR_OverTemp_Error = {
	.name = "MotRR_OverTemp_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	MotRR_Encoder_Error
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_MotRR_Encoder_Error = {
	.name = "MotRR_Encoder_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRR_UnderVoltage_Error
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRR_UnderVoltage_Error = {
	.name = "InvRR_UnderVoltage_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRR_OverVoltage_Error
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRR_OverVoltage_Error = {
	.name = "InvRR_OverVoltage_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRR_OverTemp_Error
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRR_OverTemp_Error = {
	.name = "InvRR_OverTemp_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRR_OverSpeed_Error
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRR_OverSpeed_Error = {
	.name = "InvRR_OverSpeed_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRR_OverCurrent_Error
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRR_OverCurrent_Error = {
	.name = "InvRR_OverCurrent_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRR_HW_Warning
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRR_HW_Warning = {
	.name = "InvRR_HW_Warning",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRR_Control_Error
 * Comment:	Calculus error
 */
static const signal DBC_CAN1DB_SIG_InvRR_Control_Error = {
	.name = "InvRR_Control_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRR_PowerError
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRR_PowerError = {
	.name = "InvRR_PowerError",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRL_PowerError
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRL_PowerError = {
	.name = "InvRL_PowerError",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Torque_Ref_RR
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_Torque_Ref_RR = {
	.name = "Torque_Ref_RR",
	.unit = "Nm",
	.valueType = dbc_valueType_signed,
	.lengthBits = 16,
	.factor = 0.01f, .offset = 0.0f, .min = -100.0f, .max = 100.0f
};

/**
 * Name: 	Torque_Ref_RL
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_Torque_Ref_RL = {
	.name = "Torque_Ref_RL",
	.unit = "Nm",
	.valueType = dbc_valueType_signed,
	.lengthBits = 16,
	.factor = 0.01f, .offset = 0.0f, .min = -100.0f, .max = 100.0f
};

/**
 * Name: 	InvRR_Enable
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRR_Enable = {
	.name = "InvRR_Enable",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	InvRL_Enable
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_InvRL_Enable = {
	.name = "InvRL_Enable",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Shutdown_PackageIntck
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Shutdown_PackageIntck = {
	.name = "Shutdown_PackageIntck",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Shutdown_IMD
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Shutdown_IMD = {
	.name = "Shutdown_IMD",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Shutdown_BMS
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Shutdown_BMS = {
	.name = "Shutdown_BMS",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	ERROR
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_ERROR = {
	.name = "ERROR",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Accumulator_Current
 * Comment:	[-350 - 350]
 */
static const signal DBC_CAN1DB_SIG_Accumulator_Current = {
	.name = "Accumulator_Current",
	.unit = "A",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 32,
	.factor = -0.001f, .offset = 2147483.8f, .min = -350.0f, .max = 350.0f
};

/**
 * Name: 	Lowest_CellVoltage
 * Comment:	[2.8 - 4.2]
 */
static const signal DBC_CAN1DB_SIG_Lowest_CellVoltage = {
	.name = "Lowest_CellVoltage",
	.unit = "V",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 0.001f, .offset = 0.0f, .min = 0.0f, .max = 65.535f
};

/**
 * Name: 	Highest_CellVoltage
 * Comment:	[2.8 - 4.2]
 */
static const signal DBC_CAN1DB_SIG_Highest_CellVoltage = {
	.name = "Highest_CellVoltage",
	.unit = "V",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 0.001f, .offset = 0.0f, .min = 0.0f, .max = 65.535f
};

/**
 * Name: 	Accumulator_Voltage
 * Comment:	[0 - 588]
 */
static const signal DBC_CAN1DB_SIG_Accumulator_Voltage = {
	.name = "Accumulator_Voltage",
	.unit = "V",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 24,
	.factor = 0.001f, .offset = 0.0f, .min = 0.0f, .max = 16777.215f
};

/**
 * Name: 	Charger_MaxVoltage
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_Charger_MaxVoltage = {
	.name = "Charger_MaxVoltage",
	.unit = "",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 0.01f, .offset = 0.0f, .min = 0.0f, .max = 655.35f
};

/**
 * Name: 	Charger_MaxCurrent
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_Charger_MaxCurrent = {
	.name = "Charger_MaxCurrent",
	.unit = "",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 8,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 255.0f
};

/**
 * Name: 	Lowest_CellTemp
 * Comment:	[0, +60]
 */
static const signal DBC_CAN1DB_SIG_Lowest_CellTemp = {
	.name = "Lowest_CellTemp",
	.unit = "ºC",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 0.1f, .offset = 0.0f, .min = 0.0f, .max = 6553.5f
};

/**
 * Name: 	Highest_CellTemp
 * Comment:	[0, +60]
 */
static const signal DBC_CAN1DB_SIG_Highest_CellTemp = {
	.name = "Highest_CellTemp",
	.unit = "ºC",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 0.1f, .offset = 0.0f, .min = 0.0f, .max = 6553.5f
};

/**
 * Name: 	Average_CellTemp
 * Comment:	[0, +60]
 */
static const signal DBC_CAN1DB_SIG_Average_CellTemp = {
	.name = "Average_CellTemp",
	.unit = "ºC",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 0.1f, .offset = 0.0f, .min = 0.0f, .max = 6553.5f
};

/**
 * Name: 	RacingMode
 * Comment:	[1, 2, 3, 4, 5]
 */
static const signal DBC_CAN1DB_SIG_RacingMode = {
	.name = "RacingMode",
	.unit = "",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 3,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 7.0f
};

/**
 * Name: 	BMS_Alive
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_BMS_Alive = {
	.name = "BMS_Alive",
	.unit = "",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 8,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 255.0f
};

/**
 * Name: 	AIRs_State
 * Comment:	[0, 3, 6, 8, 9]
 */
static const signal DBC_CAN1DB_SIG_AIRs_State = {
	.name = "AIRs_State",
	.unit = "",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 4,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 15.0f
};

/**
 * Name: 	Dash_Alive
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_Dash_Alive = {
	.name = "Dash_Alive",
	.unit = "",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 8,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 255.0f
};

/**
 * Name: 	PrechargeRequest
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_PrechargeRequest = {
	.name = "PrechargeRequest",
	.unit = "",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	EnableDrive_Order
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_EnableDrive_Order = {
	.name = "EnableDrive_Order",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	SoC_Avg
 * Comment:	[0 - 1]
 */
static const signal DBC_CAN1DB_SIG_SoC_Avg = {
	.name = "SoC_Avg",
	.unit = "1%",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 8,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 255.0f
};

/**
 * Name: 	Speed
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_Speed = {
	.name = "Speed",
	.unit = "km/h",
	.valueType = dbc_valueType_signed,
	.lengthBits = 8,
	.factor = 1.0f, .offset = 0.0f, .min = -128.0f, .max = 127.0f
};

/**
 * Name: 	Precharge_Voltage
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_Precharge_Voltage = {
	.name = "Precharge_Voltage",
	.unit = "V",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 0.01f, .offset = 0.0f, .min = 0.0f, .max = 655.35f
};

/**
 * Name: 	Precharge_Percentage
 * Comment:	[0 - 100]
 */
static const signal DBC_CAN1DB_SIG_Precharge_Percentage = {
	.name = "Precharge_Percentage",
	.unit = "100%",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 8,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 100.0f
};

/**
 * Name: 	VDC_Max_Tyre_Slip
 * Comment:	[1 - 1.30]
 */
static const signal DBC_CAN1DB_SIG_VDC_Max_Tyre_Slip = {
	.name = "VDC_Max_Tyre_Slip",
	.unit = "-",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 8,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 255.0f
};

/**
 * Name: 	Car_State
 * Comment:	[0, 3, 6, 9, 12, 13, 14, 15, 21]
 */
static const signal DBC_CAN1DB_SIG_Car_State = {
	.name = "Car_State",
	.unit = "",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 5,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 21.0f
};

/**
 * Name: 	AIRs_Request
 * Comment:	[0, 3, 6, 8, 9]
 */
static const signal DBC_CAN1DB_SIG_AIRs_Request = {
	.name = "AIRs_Request",
	.unit = "",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 4,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 15.0f
};

/**
 * Name: 	TC_Warning
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_TC_Warning = {
	.name = "TC_Warning",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Regenerative_Enable
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Regenerative_Enable = {
	.name = "Regenerative_Enable",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	CriticalDisconnection
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_CriticalDisconnection = {
	.name = "CriticalDisconnection",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Relay_Error
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Relay_Error = {
	.name = "Relay_Error",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Car_OK
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Car_OK = {
	.name = "Car_OK",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Power
 * Comment:	[-115, +85]
 */
static const signal DBC_CAN1DB_SIG_Power = {
	.name = "Power",
	.unit = "kW",
	.valueType = dbc_valueType_signed,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = -32768.0f, .max = 32767.0f
};

/**
 * Name: 	Torque_OK
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Torque_OK = {
	.name = "Torque_OK",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	TV_Mode
 * Comment:	[1, 2, 3, 4]
 */
static const signal DBC_CAN1DB_SIG_TV_Mode = {
	.name = "TV_Mode",
	.unit = "",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 3,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 7.0f
};

/**
 * Name: 	Critical_Signal_Disconnection
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Critical_Signal_Disconnection = {
	.name = "Critical_Signal_Disconnection",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Critical_CAN_Disconnection
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_Critical_CAN_Disconnection = {
	.name = "Critical_CAN_Disconnection",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	APPS_Implausibility
 * Comment:	[0, 1]
 */
static const signal DBC_CAN1DB_SIG_APPS_Implausibility = {
	.name = "APPS_Implausibility",
	.unit = "Bit",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	Sync_CAN1
 * Comment:	<<empty>>
 */
static const signal DBC_CAN1DB_SIG_Sync_CAN1 = {
	.name = "Sync_CAN1",
	.unit = "",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 8,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 255.0f
};


/*
 * ---------------------------------------------------------------------------------------------------------------------
 * 				Messages
 * ---------------------------------------------------------------------------------------------------------------------
 */

/**
 * Name: 	VECTOR__INDEPENDENT_SIG_MSG
 * Comment:	This is a message for not used signals, created by Vector CANdb++ DBC OLE DB Provider.
 */
static struct DBC_CAN1DB_MSG_VECTOR__INDEPENDENT_SIG_MSG {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned InvRear_PowerError;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_VECTOR__INDEPENDENT_SIG_MSG_getSigVal {
		uint8_t InvRear_PowerError	: 1;
	} *getSigVal;
} DBC_CAN1DB_MSG_VECTOR__INDEPENDENT_SIG_MSG __attribute__((unused)) = {
	.ID = 0x40000000,
	.IDE = CAN_ID_EXT,
	.DLC = 0,
	.getSig  = {
		.InvRear_PowerError = {
			.position = 0,
			.attributes = &DBC_CAN1DB_SIG_InvRear_PowerError
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	MEAS_InvRear_CurrentsMeas
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_MEAS_InvRear_CurrentsMeas {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned InvRL_idMeas;
		signal_positioned InvRR_idMeas;
		signal_positioned InvRL_iqMeas;
		signal_positioned InvRR_iqMeas;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_MEAS_InvRear_CurrentsMeas_getSigVal {
		int16_t InvRL_idMeas	: 16;
		int16_t InvRR_idMeas	: 16;
		int16_t InvRL_iqMeas	: 16;
		int16_t InvRR_iqMeas	: 16;
	} *getSigVal;
} DBC_CAN1DB_MSG_MEAS_InvRear_CurrentsMeas __attribute__((unused)) = {
	.ID = 0xBA,
	.IDE = CAN_ID_STD,
	.DLC = 8,
	.getSig  = {
		.InvRL_idMeas = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_InvRL_idMeas
		},
		.InvRR_idMeas = {
			.position = 23,
			.attributes = &DBC_CAN1DB_SIG_InvRR_idMeas
		},
		.InvRL_iqMeas = {
			.position = 39,
			.attributes = &DBC_CAN1DB_SIG_InvRL_iqMeas
		},
		.InvRR_iqMeas = {
			.position = 55,
			.attributes = &DBC_CAN1DB_SIG_InvRR_iqMeas
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	MEAS_InvRear_CurrentsRef
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_MEAS_InvRear_CurrentsRef {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned InvRL_idRef;
		signal_positioned InvRR_idRef;
		signal_positioned InvRL_iqRef;
		signal_positioned InvRR_iqRef;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_MEAS_InvRear_CurrentsRef_getSigVal {
		int16_t InvRL_idRef	: 16;
		int16_t InvRR_idRef	: 16;
		int16_t InvRL_iqRef	: 16;
		int16_t InvRR_iqRef	: 16;
	} *getSigVal;
} DBC_CAN1DB_MSG_MEAS_InvRear_CurrentsRef __attribute__((unused)) = {
	.ID = 0xBC,
	.IDE = CAN_ID_STD,
	.DLC = 8,
	.getSig  = {
		.InvRL_idRef = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_InvRL_idRef
		},
		.InvRR_idRef = {
			.position = 23,
			.attributes = &DBC_CAN1DB_SIG_InvRR_idRef
		},
		.InvRL_iqRef = {
			.position = 39,
			.attributes = &DBC_CAN1DB_SIG_InvRL_iqRef
		},
		.InvRR_iqRef = {
			.position = 55,
			.attributes = &DBC_CAN1DB_SIG_InvRR_iqRef
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_InvRear_Electrical
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_InvRear_Electrical {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned InvRL_DCBus;
		signal_positioned InvRR_DCBus;
		signal_positioned MotRL_Power;
		signal_positioned MotRR_Power;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_InvRear_Electrical_getSigVal {
		uint16_t InvRL_DCBus	: 16;
		uint16_t InvRR_DCBus	: 16;
		int16_t MotRL_Power	: 16;
		int16_t MotRR_Power	: 16;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_InvRear_Electrical __attribute__((unused)) = {
	.ID = 0xB4,
	.IDE = CAN_ID_STD,
	.DLC = 8,
	.getSig  = {
		.InvRL_DCBus = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_InvRL_DCBus
		},
		.InvRR_DCBus = {
			.position = 23,
			.attributes = &DBC_CAN1DB_SIG_InvRR_DCBus
		},
		.MotRL_Power = {
			.position = 39,
			.attributes = &DBC_CAN1DB_SIG_MotRL_Power
		},
		.MotRR_Power = {
			.position = 55,
			.attributes = &DBC_CAN1DB_SIG_MotRR_Power
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	NM_InvRear_Keep_Alive
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_NM_InvRear_Keep_Alive {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned InvRear_Alive;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_NM_InvRear_Keep_Alive_getSigVal {
		uint8_t InvRear_Alive	: 8;
	} *getSigVal;
} DBC_CAN1DB_MSG_NM_InvRear_Keep_Alive __attribute__((unused)) = {
	.ID = 0xCC,
	.IDE = CAN_ID_STD,
	.DLC = 1,
	.getSig  = {
		.InvRear_Alive = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_InvRear_Alive
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_InvRear_Mechanical
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_InvRear_Mechanical {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned MotRL_TorqueCalc;
		signal_positioned MotRR_TorqueCalc;
		signal_positioned MotRL_Speed;
		signal_positioned MotRR_Speed;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_InvRear_Mechanical_getSigVal {
		int16_t MotRL_TorqueCalc	: 16;
		int16_t MotRR_TorqueCalc	: 16;
		uint16_t MotRL_Speed	: 16;
		uint16_t MotRR_Speed	: 16;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_InvRear_Mechanical __attribute__((unused)) = {
	.ID = 0xB6,
	.IDE = CAN_ID_STD,
	.DLC = 8,
	.getSig  = {
		.MotRL_TorqueCalc = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_MotRL_TorqueCalc
		},
		.MotRR_TorqueCalc = {
			.position = 23,
			.attributes = &DBC_CAN1DB_SIG_MotRR_TorqueCalc
		},
		.MotRL_Speed = {
			.position = 39,
			.attributes = &DBC_CAN1DB_SIG_MotRL_Speed
		},
		.MotRR_Speed = {
			.position = 55,
			.attributes = &DBC_CAN1DB_SIG_MotRR_Speed
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_InvRear_Temperatures
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_InvRear_Temperatures {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned InvRL_Temp;
		signal_positioned InvRR_Temp;
		signal_positioned MotRL_Temp;
		signal_positioned MotRR_Temp;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_InvRear_Temperatures_getSigVal {
		uint16_t InvRL_Temp	: 16;
		uint16_t InvRR_Temp	: 16;
		uint16_t MotRL_Temp	: 16;
		uint16_t MotRR_Temp	: 16;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_InvRear_Temperatures __attribute__((unused)) = {
	.ID = 0xB8,
	.IDE = CAN_ID_STD,
	.DLC = 8,
	.getSig  = {
		.InvRL_Temp = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_InvRL_Temp
		},
		.InvRR_Temp = {
			.position = 23,
			.attributes = &DBC_CAN1DB_SIG_InvRR_Temp
		},
		.MotRL_Temp = {
			.position = 39,
			.attributes = &DBC_CAN1DB_SIG_MotRL_Temp
		},
		.MotRR_Temp = {
			.position = 55,
			.attributes = &DBC_CAN1DB_SIG_MotRR_Temp
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_InvRear_Error
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_InvRear_Error {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned InvRL_PowerError;
		signal_positioned InvRL_OverTemp_Error;
		signal_positioned InvRL_OverVoltage_Error;
		signal_positioned InvRL_OverCurrent_Error;
		signal_positioned InvRL_OverSpeed_Error;
		signal_positioned InvRL_UnderVoltage_Error;
		signal_positioned InvRL_Control_Error;
		signal_positioned InvRL_HW_Warning;
		signal_positioned MotRL_OverTemp_Error;
		signal_positioned MotRL_Encoder_Error;
		signal_positioned InvRR_PowerError;
		signal_positioned InvRR_OverTemp_Error;
		signal_positioned InvRR_OverVoltage_Error;
		signal_positioned InvRR_OverCurrent_Error;
		signal_positioned InvRR_OverSpeed_Error;
		signal_positioned InvRR_UnderVoltage_Error;
		signal_positioned InvRR_Control_Error;
		signal_positioned InvRR_HW_Warning;
		signal_positioned MotRR_OverTemp_Error;
		signal_positioned MotRR_Encoder_Error;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_InvRear_Error_getSigVal {
		uint8_t InvRL_PowerError	: 1;
		uint8_t InvRL_OverTemp_Error	: 1;
		uint8_t InvRL_OverVoltage_Error	: 1;
		uint8_t InvRL_OverCurrent_Error	: 1;
		uint8_t InvRL_OverSpeed_Error	: 1;
		uint8_t InvRL_UnderVoltage_Error	: 1;
		uint8_t InvRL_Control_Error	: 1;
		uint8_t InvRL_HW_Warning	: 1;
		uint8_t MotRL_OverTemp_Error	: 1;
		uint8_t MotRL_Encoder_Error	: 1;
		uint8_t InvRR_PowerError	: 1;
		uint8_t InvRR_OverTemp_Error	: 1;
		uint8_t InvRR_OverVoltage_Error	: 1;
		uint8_t InvRR_OverCurrent_Error	: 1;
		uint8_t InvRR_OverSpeed_Error	: 1;
		uint8_t InvRR_UnderVoltage_Error	: 1;
		uint8_t InvRR_Control_Error	: 1;
		uint8_t InvRR_HW_Warning	: 1;
		uint8_t MotRR_OverTemp_Error	: 1;
		uint8_t MotRR_Encoder_Error	: 1;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_InvRear_Error __attribute__((unused)) = {
	.ID = 0xB0,
	.IDE = CAN_ID_STD,
	.DLC = 3,
	.getSig  = {
		.InvRL_PowerError = {
			.position = 0,
			.attributes = &DBC_CAN1DB_SIG_InvRL_PowerError
		},
		.InvRL_OverTemp_Error = {
			.position = 1,
			.attributes = &DBC_CAN1DB_SIG_InvRL_OverTemp_Error
		},
		.InvRL_OverVoltage_Error = {
			.position = 2,
			.attributes = &DBC_CAN1DB_SIG_InvRL_OverVoltage_Error
		},
		.InvRL_OverCurrent_Error = {
			.position = 3,
			.attributes = &DBC_CAN1DB_SIG_InvRL_OverCurrent_Error
		},
		.InvRL_OverSpeed_Error = {
			.position = 4,
			.attributes = &DBC_CAN1DB_SIG_InvRL_OverSpeed_Error
		},
		.InvRL_UnderVoltage_Error = {
			.position = 5,
			.attributes = &DBC_CAN1DB_SIG_InvRL_UnderVoltage_Error
		},
		.InvRL_Control_Error = {
			.position = 6,
			.attributes = &DBC_CAN1DB_SIG_InvRL_Control_Error
		},
		.InvRL_HW_Warning = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_InvRL_HW_Warning
		},
		.MotRL_OverTemp_Error = {
			.position = 8,
			.attributes = &DBC_CAN1DB_SIG_MotRL_OverTemp_Error
		},
		.MotRL_Encoder_Error = {
			.position = 9,
			.attributes = &DBC_CAN1DB_SIG_MotRL_Encoder_Error
		},
		.InvRR_PowerError = {
			.position = 10,
			.attributes = &DBC_CAN1DB_SIG_InvRR_PowerError
		},
		.InvRR_OverTemp_Error = {
			.position = 11,
			.attributes = &DBC_CAN1DB_SIG_InvRR_OverTemp_Error
		},
		.InvRR_OverVoltage_Error = {
			.position = 12,
			.attributes = &DBC_CAN1DB_SIG_InvRR_OverVoltage_Error
		},
		.InvRR_OverCurrent_Error = {
			.position = 13,
			.attributes = &DBC_CAN1DB_SIG_InvRR_OverCurrent_Error
		},
		.InvRR_OverSpeed_Error = {
			.position = 14,
			.attributes = &DBC_CAN1DB_SIG_InvRR_OverSpeed_Error
		},
		.InvRR_UnderVoltage_Error = {
			.position = 15,
			.attributes = &DBC_CAN1DB_SIG_InvRR_UnderVoltage_Error
		},
		.InvRR_Control_Error = {
			.position = 16,
			.attributes = &DBC_CAN1DB_SIG_InvRR_Control_Error
		},
		.InvRR_HW_Warning = {
			.position = 17,
			.attributes = &DBC_CAN1DB_SIG_InvRR_HW_Warning
		},
		.MotRR_OverTemp_Error = {
			.position = 18,
			.attributes = &DBC_CAN1DB_SIG_MotRR_OverTemp_Error
		},
		.MotRR_Encoder_Error = {
			.position = 19,
			.attributes = &DBC_CAN1DB_SIG_MotRR_Encoder_Error
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_ETAS_Torques
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_ETAS_Torques {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned Torque_Ref_RL;
		signal_positioned Torque_Ref_RR;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_ETAS_Torques_getSigVal {
		int16_t Torque_Ref_RL	: 16;
		int16_t Torque_Ref_RR	: 16;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_ETAS_Torques __attribute__((unused)) = {
	.ID = 0xB3,
	.IDE = CAN_ID_STD,
	.DLC = 4,
	.getSig  = {
		.Torque_Ref_RL = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_Torque_Ref_RL
		},
		.Torque_Ref_RR = {
			.position = 23,
			.attributes = &DBC_CAN1DB_SIG_Torque_Ref_RR
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_ETAS_EnableInv
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_ETAS_EnableInv {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned InvRL_Enable;
		signal_positioned InvRR_Enable;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_ETAS_EnableInv_getSigVal {
		uint8_t InvRL_Enable	: 1;
		uint8_t InvRR_Enable	: 1;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_ETAS_EnableInv __attribute__((unused)) = {
	.ID = 0xB2,
	.IDE = CAN_ID_STD,
	.DLC = 1,
	.getSig  = {
		.InvRL_Enable = {
			.position = 0,
			.attributes = &DBC_CAN1DB_SIG_InvRL_Enable
		},
		.InvRR_Enable = {
			.position = 1,
			.attributes = &DBC_CAN1DB_SIG_InvRR_Enable
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_BMS_SDC
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_BMS_SDC {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned Shutdown_PackageIntck;
		signal_positioned Shutdown_BMS;
		signal_positioned Shutdown_IMD;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_BMS_SDC_getSigVal {
		uint8_t Shutdown_PackageIntck	: 1;
		uint8_t Shutdown_BMS	: 1;
		uint8_t Shutdown_IMD	: 1;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_BMS_SDC __attribute__((unused)) = {
	.ID = 0x90,
	.IDE = CAN_ID_STD,
	.DLC = 1,
	.getSig  = {
		.Shutdown_PackageIntck = {
			.position = 0,
			.attributes = &DBC_CAN1DB_SIG_Shutdown_PackageIntck
		},
		.Shutdown_BMS = {
			.position = 1,
			.attributes = &DBC_CAN1DB_SIG_Shutdown_BMS
		},
		.Shutdown_IMD = {
			.position = 2,
			.attributes = &DBC_CAN1DB_SIG_Shutdown_IMD
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_CurrentSensor
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_CurrentSensor {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned Accumulator_Current;
		signal_positioned ERROR;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_CurrentSensor_getSigVal {
		uint32_t Accumulator_Current	: 32;
		uint8_t ERROR	: 1;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_CurrentSensor __attribute__((unused)) = {
	.ID = 0x3C2,
	.IDE = CAN_ID_STD,
	.DLC = 8,
	.getSig  = {
		.Accumulator_Current = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_Accumulator_Current
		},
		.ERROR = {
			.position = 32,
			.attributes = &DBC_CAN1DB_SIG_ERROR
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_BMS_Voltages
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_BMS_Voltages {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned Lowest_CellVoltage;
		signal_positioned Highest_CellVoltage;
		signal_positioned Accumulator_Voltage;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_BMS_Voltages_getSigVal {
		uint16_t Lowest_CellVoltage	: 16;
		uint16_t Highest_CellVoltage	: 16;
		uint32_t Accumulator_Voltage	: 24;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_BMS_Voltages __attribute__((unused)) = {
	.ID = 0x92,
	.IDE = CAN_ID_STD,
	.DLC = 7,
	.getSig  = {
		.Lowest_CellVoltage = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_Lowest_CellVoltage
		},
		.Highest_CellVoltage = {
			.position = 23,
			.attributes = &DBC_CAN1DB_SIG_Highest_CellVoltage
		},
		.Accumulator_Voltage = {
			.position = 39,
			.attributes = &DBC_CAN1DB_SIG_Accumulator_Voltage
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_BMS_ChargerParameters
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_BMS_ChargerParameters {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned Charger_MaxVoltage;
		signal_positioned Charger_MaxCurrent;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_BMS_ChargerParameters_getSigVal {
		uint16_t Charger_MaxVoltage	: 16;
		uint8_t Charger_MaxCurrent	: 8;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_BMS_ChargerParameters __attribute__((unused)) = {
	.ID = 0x9D,
	.IDE = CAN_ID_STD,
	.DLC = 3,
	.getSig  = {
		.Charger_MaxVoltage = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_Charger_MaxVoltage
		},
		.Charger_MaxCurrent = {
			.position = 23,
			.attributes = &DBC_CAN1DB_SIG_Charger_MaxCurrent
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_BMS_Temperatures
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_BMS_Temperatures {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned Lowest_CellTemp;
		signal_positioned Highest_CellTemp;
		signal_positioned Average_CellTemp;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_BMS_Temperatures_getSigVal {
		uint16_t Lowest_CellTemp	: 16;
		uint16_t Highest_CellTemp	: 16;
		uint16_t Average_CellTemp	: 16;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_BMS_Temperatures __attribute__((unused)) = {
	.ID = 0x93,
	.IDE = CAN_ID_STD,
	.DLC = 8,
	.getSig  = {
		.Lowest_CellTemp = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_Lowest_CellTemp
		},
		.Highest_CellTemp = {
			.position = 23,
			.attributes = &DBC_CAN1DB_SIG_Highest_CellTemp
		},
		.Average_CellTemp = {
			.position = 39,
			.attributes = &DBC_CAN1DB_SIG_Average_CellTemp
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_DASH_Mode
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_DASH_Mode {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned RacingMode;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_DASH_Mode_getSigVal {
		uint8_t RacingMode	: 3;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_DASH_Mode __attribute__((unused)) = {
	.ID = 0xA2,
	.IDE = CAN_ID_STD,
	.DLC = 1,
	.getSig  = {
		.RacingMode = {
			.position = 2,
			.attributes = &DBC_CAN1DB_SIG_RacingMode
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	NM_BMS_Keep_Alive
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_NM_BMS_Keep_Alive {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned BMS_Alive;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_NM_BMS_Keep_Alive_getSigVal {
		uint8_t BMS_Alive	: 8;
	} *getSigVal;
} DBC_CAN1DB_MSG_NM_BMS_Keep_Alive __attribute__((unused)) = {
	.ID = 0xCA,
	.IDE = CAN_ID_STD,
	.DLC = 1,
	.getSig  = {
		.BMS_Alive = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_BMS_Alive
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_BMS_AIRs_State
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_BMS_AIRs_State {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned AIRs_State;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_BMS_AIRs_State_getSigVal {
		uint8_t AIRs_State	: 4;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_BMS_AIRs_State __attribute__((unused)) = {
	.ID = 0x91,
	.IDE = CAN_ID_STD,
	.DLC = 1,
	.getSig  = {
		.AIRs_State = {
			.position = 3,
			.attributes = &DBC_CAN1DB_SIG_AIRs_State
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	NM_DASH_Keep_Alive
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_NM_DASH_Keep_Alive {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned Dash_Alive;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_NM_DASH_Keep_Alive_getSigVal {
		uint8_t Dash_Alive	: 8;
	} *getSigVal;
} DBC_CAN1DB_MSG_NM_DASH_Keep_Alive __attribute__((unused)) = {
	.ID = 0xCB,
	.IDE = CAN_ID_STD,
	.DLC = 1,
	.getSig  = {
		.Dash_Alive = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_Dash_Alive
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_DASH_PrechargeRequest
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_DASH_PrechargeRequest {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned PrechargeRequest;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_DASH_PrechargeRequest_getSigVal {
		uint8_t PrechargeRequest	: 1;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_DASH_PrechargeRequest __attribute__((unused)) = {
	.ID = 0xA0,
	.IDE = CAN_ID_STD,
	.DLC = 1,
	.getSig  = {
		.PrechargeRequest = {
			.position = 0,
			.attributes = &DBC_CAN1DB_SIG_PrechargeRequest
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_DASH_EnableDrive
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_DASH_EnableDrive {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned EnableDrive_Order;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_DASH_EnableDrive_getSigVal {
		uint8_t EnableDrive_Order	: 1;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_DASH_EnableDrive __attribute__((unused)) = {
	.ID = 0xA1,
	.IDE = CAN_ID_STD,
	.DLC = 1,
	.getSig  = {
		.EnableDrive_Order = {
			.position = 0,
			.attributes = &DBC_CAN1DB_SIG_EnableDrive_Order
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_ETAS_DashData
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_ETAS_DashData {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned Precharge_Voltage;
		signal_positioned Precharge_Percentage;
		signal_positioned Speed;
		signal_positioned SoC_Avg;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_ETAS_DashData_getSigVal {
		uint16_t Precharge_Voltage	: 16;
		uint8_t Precharge_Percentage	: 8;
		int8_t Speed	: 8;
		uint8_t SoC_Avg	: 8;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_ETAS_DashData __attribute__((unused)) = {
	.ID = 0x83,
	.IDE = CAN_ID_STD,
	.DLC = 5,
	.getSig  = {
		.Precharge_Voltage = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_Precharge_Voltage
		},
		.Precharge_Percentage = {
			.position = 23,
			.attributes = &DBC_CAN1DB_SIG_Precharge_Percentage
		},
		.Speed = {
			.position = 31,
			.attributes = &DBC_CAN1DB_SIG_Speed
		},
		.SoC_Avg = {
			.position = 39,
			.attributes = &DBC_CAN1DB_SIG_SoC_Avg
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_ETAS_VDCParams
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_ETAS_VDCParams {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned VDC_Max_Tyre_Slip;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_ETAS_VDCParams_getSigVal {
		uint8_t VDC_Max_Tyre_Slip	: 8;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_ETAS_VDCParams __attribute__((unused)) = {
	.ID = 0x8F,
	.IDE = CAN_ID_STD,
	.DLC = 1,
	.getSig  = {
		.VDC_Max_Tyre_Slip = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_VDC_Max_Tyre_Slip
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_ETAS_CarState
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_ETAS_CarState {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned Car_State;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_ETAS_CarState_getSigVal {
		uint8_t Car_State	: 5;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_ETAS_CarState __attribute__((unused)) = {
	.ID = 0x81,
	.IDE = CAN_ID_STD,
	.DLC = 1,
	.getSig  = {
		.Car_State = {
			.position = 4,
			.attributes = &DBC_CAN1DB_SIG_Car_State
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_ETAS_AIRsRequest
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_ETAS_AIRsRequest {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned AIRs_Request;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_ETAS_AIRsRequest_getSigVal {
		uint8_t AIRs_Request	: 4;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_ETAS_AIRsRequest __attribute__((unused)) = {
	.ID = 0x82,
	.IDE = CAN_ID_STD,
	.DLC = 1,
	.getSig  = {
		.AIRs_Request = {
			.position = 3,
			.attributes = &DBC_CAN1DB_SIG_AIRs_Request
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	MEAS_ETAS_InternalVars
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_MEAS_ETAS_InternalVars {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned Car_OK;
		signal_positioned Critical_Signal_Disconnection;
		signal_positioned Critical_CAN_Disconnection;
		signal_positioned CriticalDisconnection;
		signal_positioned APPS_Implausibility;
		signal_positioned Torque_OK;
		signal_positioned Relay_Error;
		signal_positioned TV_Mode;
		signal_positioned TC_Warning;
		signal_positioned Regenerative_Enable;
		signal_positioned Power;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_MEAS_ETAS_InternalVars_getSigVal {
		uint8_t Car_OK	: 1;
		uint8_t Critical_Signal_Disconnection	: 1;
		uint8_t Critical_CAN_Disconnection	: 1;
		uint8_t CriticalDisconnection	: 1;
		uint8_t APPS_Implausibility	: 1;
		uint8_t Torque_OK	: 1;
		uint8_t Relay_Error	: 1;
		uint8_t TV_Mode	: 3;
		uint8_t TC_Warning	: 1;
		uint8_t Regenerative_Enable	: 1;
		int16_t Power	: 16;
	} *getSigVal;
} DBC_CAN1DB_MSG_MEAS_ETAS_InternalVars __attribute__((unused)) = {
	.ID = 0xD0,
	.IDE = CAN_ID_STD,
	.DLC = 4,
	.getSig  = {
		.Car_OK = {
			.position = 0,
			.attributes = &DBC_CAN1DB_SIG_Car_OK
		},
		.Critical_Signal_Disconnection = {
			.position = 1,
			.attributes = &DBC_CAN1DB_SIG_Critical_Signal_Disconnection
		},
		.Critical_CAN_Disconnection = {
			.position = 2,
			.attributes = &DBC_CAN1DB_SIG_Critical_CAN_Disconnection
		},
		.CriticalDisconnection = {
			.position = 3,
			.attributes = &DBC_CAN1DB_SIG_CriticalDisconnection
		},
		.APPS_Implausibility = {
			.position = 4,
			.attributes = &DBC_CAN1DB_SIG_APPS_Implausibility
		},
		.Torque_OK = {
			.position = 5,
			.attributes = &DBC_CAN1DB_SIG_Torque_OK
		},
		.Relay_Error = {
			.position = 6,
			.attributes = &DBC_CAN1DB_SIG_Relay_Error
		},
		.TV_Mode = {
			.position = 10,
			.attributes = &DBC_CAN1DB_SIG_TV_Mode
		},
		.TC_Warning = {
			.position = 11,
			.attributes = &DBC_CAN1DB_SIG_TC_Warning
		},
		.Regenerative_Enable = {
			.position = 12,
			.attributes = &DBC_CAN1DB_SIG_Regenerative_Enable
		},
		.Power = {
			.position = 23,
			.attributes = &DBC_CAN1DB_SIG_Power
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_ETAS_Synchronism
 * Comment:	<<empty>>
 */
static struct DBC_CAN1DB_MSG_AP_ETAS_Synchronism {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned Sync_CAN1;
	} getSig;
	 struct __attribute__((packed)) DBC_CAN1DB_MSG_AP_ETAS_Synchronism_getSigVal {
		uint8_t Sync_CAN1	: 8;
	} *getSigVal;
} DBC_CAN1DB_MSG_AP_ETAS_Synchronism __attribute__((unused)) = {
	.ID = 0x80,
	.IDE = CAN_ID_STD,
	.DLC = 1,
	.getSig  = {
		.Sync_CAN1 = {
			.position = 7,
			.attributes = &DBC_CAN1DB_SIG_Sync_CAN1
		}
	},
	.getSigVal = 0
};




/*
 * Nodes List:
 * 	CurrentSensor
 * 	Inverter_Front
 * 	Inverter_Rear
 * 	DashBoard
 * 	BMS
 * 	ETAS_ES910
 */

/*
 * Functions
 */


#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif

#endif /* DBC_CAN1DB_H */
/* @formatter:on */
