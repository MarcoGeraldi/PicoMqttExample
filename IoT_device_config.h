#ifndef IoT_device_config_H
#define IoT_device_config_H


/* -------------------------------------------------------------------------- */
/*                         HassIO Entities definitions                        */
/* -------------------------------------------------------------------------- */
#define ENTITY_CATEGORY_DIAGNOSTIC "diagnostic"
#define ENTITY_TYPE_SWITCH "switch"
#define ENTITY_TYPE_SENSOR "sensor"

/* -------------------------------------------------------------------------- */
/*                             DEVICE DEFINITIONS                             */
/* -------------------------------------------------------------------------- */
#define DEVICE_IDENTIFIER "deviceIdentifier"
#define DEVICE_MANUFACTURER "deviceManufacturer"
#define DEVICE_MODEL "deviceModel"
#define DEVICE_NAME "deviceName"
#define DEVICE_ID "0x131asdf7692safd8127643asdf1"
#define DEVICE_SW_VERS "1.2.3"
#define DEVICE_STATE_TOPIC DEVICE_MODEL "/" DEVICE_NAME
/* -------------------------------------------------------------------------- */
/*                             ENTITY DEFINITIONS                             */
/* -------------------------------------------------------------------------- */

/* ------------------------------ Grid Voltage ------------------------------ */
#define DEVICE_GRID_U_ENABLE_DEFAULT true
#define DEVICE_GRID_U_ENTITY_TYPE ENTITY_TYPE_SENSOR
#define DEVICE_GRID_U_ENTITY_CATEGORY ENTITY_CATEGORY_DIAGNOSTIC
#define DEVICE_GRID_U_ICON "mdi:signal"
#define DEVICE_GRID_U_STATE_CLASS "measurement"
#define DEVICE_GRID_U1_ENTITY_NAME "Voltage_L1"
#define DEVICE_GRID_U2_ENTITY_NAME "Voltage_L2"
#define DEVICE_GRID_U3_ENTITY_NAME "Voltage_L3"
#define DEVICE_GRID_U_UNIT "V"
 





#endif