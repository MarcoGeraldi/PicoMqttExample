/* -------------------------------------------------------------------------- */
/*                                Include Files                               */
/* -------------------------------------------------------------------------- */

#include "IoT_device.h"
#include <ctype.h> 
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>


/* ----------------------- Initialize all the entities ---------------------- */
err_t IoT_device_config_pub_init(mqtt_client_t *client, void *arg){
    
    err_t err;
    
    /* ---------------------- Entity Voltage L1 Definition ---------------------- */
    IoT_device_config_pub_generic((IoT_entityDeclaration_t) IoT_entity_sensor_definition, client, arg, &(EntityParams){
                                                                                                            .enableByDefault = DEVICE_GRID_U_ENABLE_DEFAULT,
                                                                                                            .category = DEVICE_GRID_U_ENTITY_CATEGORY,
                                                                                                            .icon = DEVICE_GRID_U_ICON,
                                                                                                            .entityName = DEVICE_GRID_U1_ENTITY_NAME,
                                                                                                            .stateClass = DEVICE_GRID_U_STATE_CLASS,
                                                                                                            .stateTopic = DEVICE_STATE_TOPIC,
                                                                                                            .unit = DEVICE_GRID_U_UNIT,
                                                                                                            .entityType = DEVICE_GRID_U_ENTITY_TYPE
                                                                                                        });    
    /* ---------------------- Entity Voltage L2 Definition ---------------------- */
    IoT_device_config_pub_generic((IoT_entityDeclaration_t) IoT_entity_sensor_definition, client, arg, &(EntityParams){
                                                                                                            .enableByDefault = DEVICE_GRID_U_ENABLE_DEFAULT,
                                                                                                            .category = DEVICE_GRID_U_ENTITY_CATEGORY,
                                                                                                            .icon = DEVICE_GRID_U_ICON,
                                                                                                            .entityName = DEVICE_GRID_U2_ENTITY_NAME,
                                                                                                            .stateClass = DEVICE_GRID_U_STATE_CLASS,
                                                                                                            .stateTopic = DEVICE_STATE_TOPIC,
                                                                                                            .unit = DEVICE_GRID_U_UNIT,
                                                                                                            .entityType = DEVICE_GRID_U_ENTITY_TYPE
                                                                                                        });
    /* ---------------------- Entity Voltage L3 Definition ---------------------- */
    IoT_device_config_pub_generic((IoT_entityDeclaration_t) IoT_entity_sensor_definition, client, arg, &(EntityParams){
                                                                                                            .enableByDefault = DEVICE_GRID_U_ENABLE_DEFAULT,
                                                                                                            .category = DEVICE_GRID_U_ENTITY_CATEGORY,
                                                                                                            .icon = DEVICE_GRID_U_ICON,
                                                                                                            .entityName = DEVICE_GRID_U3_ENTITY_NAME,
                                                                                                            .stateClass = DEVICE_GRID_U_STATE_CLASS,
                                                                                                            .stateTopic = DEVICE_STATE_TOPIC,
                                                                                                            .unit = DEVICE_GRID_U_UNIT,
                                                                                                            .entityType = DEVICE_GRID_U_ENTITY_TYPE
                                                                                                        });

    /* ------------------------- Entity Out1 Definition ------------------------- */
    IoT_device_config_pub_generic((IoT_entityDeclaration_t) IoT_entity_switch_definition, client, arg, &(EntityParams){
                                                                                                            .entityName = DEVICE_OUT1_ENTITY_NAME,
                                                                                                            .stateTopic = DEVICE_STATE_TOPIC, 
                                                                                                            .command_topic = DEVICE_OUT1_COMMAND_TOPIC,
                                                                                                            .entityType = ENTITY_TYPE_SWITCH
                                                                                                        });
    return err;
}

/* -------------------------- Update entity status -------------------------- */
err_t IoT_device_state_update_pub(mqtt_client_t *client, void *arg){
    err_t err; 
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    char publishTopic[128];
    char *serialized_string = NULL;

    /* ------------------------- Add all entities status ------------------------ */
    json_object_set_number(root_object, stringSnakeCase (DEVICE_GRID_U1_ENTITY_NAME), rand()); //Voltage L1
    json_object_set_number(root_object, stringSnakeCase (DEVICE_GRID_U2_ENTITY_NAME), rand()); //Voltage L2
    json_object_set_number(root_object, stringSnakeCase (DEVICE_GRID_U3_ENTITY_NAME), rand()); //Voltage L3
 
    json_object_set_string(root_object, stringSnakeCase (DEVICE_OUT1_ENTITY_NAME), IoT_entity_output1_state_value); //Voltage L3
 
    /* ---------------------- Convert JSON Object to string --------------------- */
    serialized_string = json_serialize_to_string_pretty(root_value);

    /* ---------------------- Publish Entity Configuration ---------------------- */
    mqtt_publish(client, DEVICE_STATE_TOPIC, serialized_string, strlen(serialized_string), 2, 0, mqtt_pub_request_cb, arg);
    
    return err;
}

void IoT_device_cb(MQTT_CLIENT_DATA_T* mqtt_client){
    printf("Topic: %s \n data: %s \n\r", mqtt_client->topic, mqtt_client->data);

    /* for this example, when the command "ON" is received, set the state to "ON" and vicecersa */
    if( 0 == strcmp(mqtt_client->topic, DEVICE_OUT1_COMMAND_TOPIC)) {
        if (0 == strcmp(mqtt_client->data, ENTITY_SWITCH_PAYLOAD_ON)) snprintf(IoT_entity_output1_state_value, sizeof(IoT_entity_output1_state_value), ENTITY_SWITCH_PAYLOAD_ON);
        if (0 == strcmp(mqtt_client->data, ENTITY_SWITCH_PAYLOAD_OFF)) snprintf(IoT_entity_output1_state_value, sizeof(IoT_entity_output1_state_value), ENTITY_SWITCH_PAYLOAD_OFF);
    }
}

/* ------------------------ Definition of the device ------------------------ */
JSON_Status IoT_deviceDeclaration(JSON_Object *object)
{
    JSON_Status JSON_Status = JSONSuccess;

    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_dotset_string(object, "device.identifiers", DEVICE_IDENTIFIER);

    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_dotset_string(object, "device.manufacturer", DEVICE_MANUFACTURER);

    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_dotset_string(object, "device.model", DEVICE_MODEL);

    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_dotset_string(object, "device.name", DEVICE_NAME);

    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_dotset_string(object, "device.sw_version", DEVICE_SW_VERS);

    return JSON_Status;
}

/* ----------------------- Initialize a generic entity ---------------------- */
err_t IoT_device_config_pub_generic(IoT_entityDeclaration_t IoT_entityDeclaration,mqtt_client_t *client, void *arg, EntityParams *params)
{
    err_t err;
    char *serialized_string = NULL;
    char publishTopic[128];

    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    
    /* ----------------------------- Add device info ---------------------------- */
    IoT_deviceDeclaration(root_object);

    /* ----------------------------- Declare Entity ----------------------------- */
    IoT_entityDeclaration(root_object, params);

    /* ---------------------- Convert JSON Object to string --------------------- */
    serialized_string = json_serialize_to_string_pretty(root_value);

    /* -------------------------- Calculate State Topic ------------------------- */
    snprintf(publishTopic, sizeof(publishTopic), "homeassistant/%s/%s/%s/config",params->entityType,DEVICE_ID,stringSnakeCase(params->entityName));
    
    /* ---------------------- Publish Entity Configuration ---------------------- */
    mqtt_publish(client, publishTopic, serialized_string, strlen(serialized_string), 2, 0, mqtt_pub_request_cb, arg);

    return err;
}


/* -------------------- Definition of Entity Type Sensor -------------------- */
JSON_Status IoT_entity_sensor_definition(JSON_Object *object, EntityParams *params){

    JSON_Status JSON_Status = JSONSuccess; 

    int length = strlen(stringSnakeCase(params->entityName)) + strlen(DEVICE_ID) +1 ;
    char *uniqueID = (char*)malloc((length + 1) * sizeof(char));
    sprintf(uniqueID, "%s_%s", DEVICE_ID, stringSnakeCase(params->entityName));

    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_number(object, "enabled_by_default",   params->enableByDefault);                                                                                                (object, "enabled_by_default",   DEVICE_GRID_U_ENABLE_DEFAULT);
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "entity_category",      params->category);
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "icon",                 params->icon);
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "name",                 params->entityName);
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "state_class",          params->stateClass);
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "state_topic",          params->stateTopic );
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "unit_of_measurement",  params->unit);
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "value_template",       stringValueTemplate(params->entityName));    
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "unique_id",            uniqueID);
        
    return JSON_Status;

}

/* ------------------- Definition of a Entity Type Switch ------------------- */
JSON_Status IoT_entity_switch_definition(JSON_Object *object, EntityParams *params){
    
    JSON_Status JSON_Status = JSONSuccess; 

    int length = strlen(stringSnakeCase(params->entityName)) + strlen(DEVICE_ID) + 1 ;
    char *uniqueID = (char*)malloc((length + 1) * sizeof(char));
    sprintf(uniqueID, "%s_%s", DEVICE_ID, stringSnakeCase(params->entityName));       

    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "name",                 params->entityName);
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "unique_id",            uniqueID);
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "state_topic",          params->stateTopic );
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "value_template",       stringValueTemplate(params->entityName));        
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "command_topic",        params->command_topic );
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "payload_off",          ENTITY_SWITCH_PAYLOAD_OFF );
    if (JSON_Status != JSONFailure)
        JSON_Status = json_object_set_string(object, "payload_on",           ENTITY_SWITCH_PAYLOAD_ON );

    
    return JSON_Status;
}

static char *stringSnakeCase (const char *entityName){
    int length = strlen(entityName);
    char *output = (char*)malloc((length + 1) * sizeof(char));

    for (int i = 0; i < length; i++) {
        output[i] = (entityName[i] == ' ') ? '_' : tolower(entityName[i]);
    }
    output[length] = '\0';

    return output;
}

static char *stringValueTemplate(const char *entityName){

    int length = strlen(entityName);
    char *output = (char*)malloc((length + strlen("{{value_json.}}") + 1) * sizeof(char));

    sprintf(output, "{{value_json.");
    for (int i = 0; i < length; i++) {
        output[i + strlen("{{value_json.")] = (entityName[i] == ' ') ? '_' : tolower(entityName[i]);
    }
    sprintf(output + strlen("{{value_json.") + length, "}}");

    return output;
}