/*
 *  @formatter:off
 *  Inverters.h
 *
 *  Created on: mayo 12, 2024 22:01:14 :: Software Version: 0.5beta 
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

#ifndef DBC_INVERTERS_H
#define DBC_INVERTERS_H

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
 * Name: 	Enable_Inv_R
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_Enable_Inv_R = {
	.name = "Enable_Inv_R",
	.unit = "-",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 1,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 1.0f
};

/**
 * Name: 	TotalPower
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_TotalPower = {
	.name = "TotalPower",
	.unit = "kW",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	Power_RR
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_Power_RR = {
	.name = "Power_RR",
	.unit = "kW",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	Power_RL
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_Power_RL = {
	.name = "Power_RL",
	.unit = "kW",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	TorqueReal_RR
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_TorqueReal_RR = {
	.name = "TorqueReal_RR",
	.unit = "Nm",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	TorqueReal_RL
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_TorqueReal_RL = {
	.name = "TorqueReal_RL",
	.unit = "Nm",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	SpeedMotor_RR
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_SpeedMotor_RR = {
	.name = "SpeedMotor_RR",
	.unit = "rpm",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	SpeedMotor_RL
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_SpeedMotor_RL = {
	.name = "SpeedMotor_RL",
	.unit = "rpm",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	DCBus_RR
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_DCBus_RR = {
	.name = "DCBus_RR",
	.unit = "V",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	DCBus_RL
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_DCBus_RL = {
	.name = "DCBus_RL",
	.unit = "V",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	Iq_RR
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_Iq_RR = {
	.name = "Iq_RR",
	.unit = "A",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	Icmd_RR
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_Icmd_RR = {
	.name = "Icmd_RR",
	.unit = "A",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	Iactual_RR
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_Iactual_RR = {
	.name = "Iactual_RR",
	.unit = "A",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	Iq_RL
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_Iq_RL = {
	.name = "Iq_RL",
	.unit = "A",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	Icmd_RL
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_Icmd_RL = {
	.name = "Icmd_RL",
	.unit = "A",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	Iactual_RL
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_Iactual_RL = {
	.name = "Iactual_RL",
	.unit = "A",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	TempMotor_RR
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_TempMotor_RR = {
	.name = "TempMotor_RR",
	.unit = "ºC",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	TempMotor_RL
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_TempMotor_RL = {
	.name = "TempMotor_RL",
	.unit = "ºC",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	TempIGBT_RR
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_TempIGBT_RR = {
	.name = "TempIGBT_RR",
	.unit = "ºC",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};

/**
 * Name: 	TempIGBT_RL
 * Comment:	<<empty>>
 */
static const signal DBC_INVERTERS_SIG_TempIGBT_RL = {
	.name = "TempIGBT_RL",
	.unit = "ºC",
	.valueType = dbc_valueType_unsigned,
	.lengthBits = 16,
	.factor = 1.0f, .offset = 0.0f, .min = 0.0f, .max = 65535.0f
};


/*
 * ---------------------------------------------------------------------------------------------------------------------
 * 				Messages
 * ---------------------------------------------------------------------------------------------------------------------
 */

/**
 * Name: 	AP_ETAS_EnableInv
 * Comment:	<<empty>>
 */
static struct DBC_INVERTERS_MSG_AP_ETAS_EnableInv {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned Enable_Inv_R;
	} getSig;
	 struct __attribute__((packed)) DBC_INVERTERS_MSG_AP_ETAS_EnableInv_getSigVal {
		uint8_t Enable_Inv_R	: 1;
	} *getSigVal;
} DBC_INVERTERS_MSG_AP_ETAS_EnableInv __attribute__((unused)) = {
	.ID = 0xB1,
	.IDE = CAN_ID_STD,
	.DLC = 8,
	.getSig  = {
		.Enable_Inv_R = {
			.position = 0,
			.attributes = &DBC_INVERTERS_SIG_Enable_Inv_R
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	TBD_Inv_R_Power
 * Comment:	<<empty>>
 */
static struct DBC_INVERTERS_MSG_TBD_Inv_R_Power {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned TotalPower;
		signal_positioned Power_RL;
		signal_positioned Power_RR;
	} getSig;
	 struct __attribute__((packed)) DBC_INVERTERS_MSG_TBD_Inv_R_Power_getSigVal {
		uint16_t TotalPower	: 16;
		uint16_t Power_RL	: 16;
		uint16_t Power_RR	: 16;
	} *getSigVal;
} DBC_INVERTERS_MSG_TBD_Inv_R_Power __attribute__((unused)) = {
	.ID = 0xB4,
	.IDE = CAN_ID_STD,
	.DLC = 6,
	.getSig  = {
		.TotalPower = {
			.position = 7,
			.attributes = &DBC_INVERTERS_SIG_TotalPower
		},
		.Power_RL = {
			.position = 23,
			.attributes = &DBC_INVERTERS_SIG_Power_RL
		},
		.Power_RR = {
			.position = 39,
			.attributes = &DBC_INVERTERS_SIG_Power_RR
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	TBD_Inv_R_Torque
 * Comment:	<<empty>>
 */
static struct DBC_INVERTERS_MSG_TBD_Inv_R_Torque {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned TorqueReal_RL;
		signal_positioned TorqueReal_RR;
	} getSig;
	 struct __attribute__((packed)) DBC_INVERTERS_MSG_TBD_Inv_R_Torque_getSigVal {
		uint16_t TorqueReal_RL	: 16;
		uint16_t TorqueReal_RR	: 16;
	} *getSigVal;
} DBC_INVERTERS_MSG_TBD_Inv_R_Torque __attribute__((unused)) = {
	.ID = 0xC7,
	.IDE = CAN_ID_STD,
	.DLC = 4,
	.getSig  = {
		.TorqueReal_RL = {
			.position = 7,
			.attributes = &DBC_INVERTERS_SIG_TorqueReal_RL
		},
		.TorqueReal_RR = {
			.position = 23,
			.attributes = &DBC_INVERTERS_SIG_TorqueReal_RR
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_Inv_R_Error
 * Comment:	<<empty>>
 */
static struct DBC_INVERTERS_MSG_AP_Inv_R_Error {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
} DBC_INVERTERS_MSG_AP_Inv_R_Error __attribute__((unused)) = {
	.ID = 0xB0,
	.IDE = CAN_ID_STD,
	.DLC = 8
};


/**
 * Name: 	AP_Inv_R_Speed
 * Comment:	<<empty>>
 */
static struct DBC_INVERTERS_MSG_AP_Inv_R_Speed {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned SpeedMotor_RL;
		signal_positioned SpeedMotor_RR;
	} getSig;
	 struct __attribute__((packed)) DBC_INVERTERS_MSG_AP_Inv_R_Speed_getSigVal {
		uint16_t SpeedMotor_RL	: 16;
		uint16_t SpeedMotor_RR	: 16;
	} *getSigVal;
} DBC_INVERTERS_MSG_AP_Inv_R_Speed __attribute__((unused)) = {
	.ID = 0xB5,
	.IDE = CAN_ID_STD,
	.DLC = 4,
	.getSig  = {
		.SpeedMotor_RL = {
			.position = 7,
			.attributes = &DBC_INVERTERS_SIG_SpeedMotor_RL
		},
		.SpeedMotor_RR = {
			.position = 23,
			.attributes = &DBC_INVERTERS_SIG_SpeedMotor_RR
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_Inv_R_DCBus
 * Comment:	<<empty>>
 */
static struct DBC_INVERTERS_MSG_AP_Inv_R_DCBus {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned DCBus_RL;
		signal_positioned DCBus_RR;
	} getSig;
	 struct __attribute__((packed)) DBC_INVERTERS_MSG_AP_Inv_R_DCBus_getSigVal {
		uint16_t DCBus_RL	: 16;
		uint16_t DCBus_RR	: 16;
	} *getSigVal;
} DBC_INVERTERS_MSG_AP_Inv_R_DCBus __attribute__((unused)) = {
	.ID = 0xB3,
	.IDE = CAN_ID_STD,
	.DLC = 4,
	.getSig  = {
		.DCBus_RL = {
			.position = 7,
			.attributes = &DBC_INVERTERS_SIG_DCBus_RL
		},
		.DCBus_RR = {
			.position = 23,
			.attributes = &DBC_INVERTERS_SIG_DCBus_RR
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	MEAS_Inv_R_Currents_R
 * Comment:	<<empty>>
 */
static struct DBC_INVERTERS_MSG_MEAS_Inv_R_Currents_R {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned Iactual_RR;
		signal_positioned Icmd_RR;
		signal_positioned Iq_RR;
	} getSig;
	 struct __attribute__((packed)) DBC_INVERTERS_MSG_MEAS_Inv_R_Currents_R_getSigVal {
		uint16_t Iactual_RR	: 16;
		uint16_t Icmd_RR	: 16;
		uint16_t Iq_RR	: 16;
	} *getSigVal;
} DBC_INVERTERS_MSG_MEAS_Inv_R_Currents_R __attribute__((unused)) = {
	.ID = 0xC9,
	.IDE = CAN_ID_STD,
	.DLC = 6,
	.getSig  = {
		.Iactual_RR = {
			.position = 7,
			.attributes = &DBC_INVERTERS_SIG_Iactual_RR
		},
		.Icmd_RR = {
			.position = 23,
			.attributes = &DBC_INVERTERS_SIG_Icmd_RR
		},
		.Iq_RR = {
			.position = 39,
			.attributes = &DBC_INVERTERS_SIG_Iq_RR
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	MEAS_Inv_R_Currents_L
 * Comment:	<<empty>>
 */
static struct DBC_INVERTERS_MSG_MEAS_Inv_R_Currents_L {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned Iactual_RL;
		signal_positioned Icmd_RL;
		signal_positioned Iq_RL;
	} getSig;
	 struct __attribute__((packed)) DBC_INVERTERS_MSG_MEAS_Inv_R_Currents_L_getSigVal {
		uint16_t Iactual_RL	: 16;
		uint16_t Icmd_RL	: 16;
		uint16_t Iq_RL	: 16;
	} *getSigVal;
} DBC_INVERTERS_MSG_MEAS_Inv_R_Currents_L __attribute__((unused)) = {
	.ID = 0xC8,
	.IDE = CAN_ID_STD,
	.DLC = 6,
	.getSig  = {
		.Iactual_RL = {
			.position = 7,
			.attributes = &DBC_INVERTERS_SIG_Iactual_RL
		},
		.Icmd_RL = {
			.position = 23,
			.attributes = &DBC_INVERTERS_SIG_Icmd_RL
		},
		.Iq_RL = {
			.position = 39,
			.attributes = &DBC_INVERTERS_SIG_Iq_RL
		}
	},
	.getSigVal = 0
};


/**
 * Name: 	AP_Inv_R_Temperatures
 * Comment:	<<empty>>
 */
static struct DBC_INVERTERS_MSG_AP_Inv_R_Temperatures {
	const uint32_t ID;
	const uint8_t IDE;
	const uint8_t DLC;
	 const struct {
		signal_positioned TempIGBT_RL;
		signal_positioned TempIGBT_RR;
		signal_positioned TempMotor_RL;
		signal_positioned TempMotor_RR;
	} getSig;
	 struct __attribute__((packed)) DBC_INVERTERS_MSG_AP_Inv_R_Temperatures_getSigVal {
		uint16_t TempIGBT_RL	: 16;
		uint16_t TempIGBT_RR	: 16;
		uint16_t TempMotor_RL	: 16;
		uint16_t TempMotor_RR	: 16;
	} *getSigVal;
} DBC_INVERTERS_MSG_AP_Inv_R_Temperatures __attribute__((unused)) = {
	.ID = 0xB2,
	.IDE = CAN_ID_STD,
	.DLC = 8,
	.getSig  = {
		.TempIGBT_RL = {
			.position = 7,
			.attributes = &DBC_INVERTERS_SIG_TempIGBT_RL
		},
		.TempIGBT_RR = {
			.position = 23,
			.attributes = &DBC_INVERTERS_SIG_TempIGBT_RR
		},
		.TempMotor_RL = {
			.position = 39,
			.attributes = &DBC_INVERTERS_SIG_TempMotor_RL
		},
		.TempMotor_RR = {
			.position = 55,
			.attributes = &DBC_INVERTERS_SIG_TempMotor_RR
		}
	},
	.getSigVal = 0
};




/*
 * Nodes List:
 * 	Inverters_Front
 * 	Inverters_Rear
 */

/*
 * Functions
 */


#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif

#endif /* DBC_INVERTERS_H */
/* @formatter:on */
