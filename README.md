This is an example on how to create an IoT Device with the Raspberry PI Pico WiFi. 

In order to be able to build this code, 2 modifications have to be made in order to avoid "PANIC": 

1. The LWIP_NUM_SYS_TIMEOUT has to increased by 1 as mentioned in this thread: https://github.com/raspberrypi/pico-sdk/issues/1281

![image](https://github.com/user-attachments/assets/54ed6c50-0b6a-4e08-b52c-0f31f9a93609)

2. The MQTT_OUTPUT_RINGBUF_SIZE has also to be increased, otherwise a memory execption will be triggered.

   ![image](https://github.com/user-attachments/assets/c6b0dcfa-408c-4985-ab4d-0392cc3e8dd0)


How the Code works:

The MQTT library takes care of the basic functionality for the mqtt to work (connect, publish, subscribe, etc.)

The IoT device library gives all the function that enable the user to define and update in a easy way the different entities for home assistant.

In order to configure the Device have first a look in the "IoT_device_confih.h", from here it is possible to configure all the entities details.

![image](https://github.com/user-attachments/assets/c893a263-d859-4d33-b64f-de3fa3465b7b)

Then move to the "IoT_device.c", here two functions are defined in order to initialize and update the status of all the entities in home assistant.

The IoT_device_config_pub_init gives the flexibility to instanciate a generic entity, given the proper configuration function as parameter.

In this example 3 voltage sensors and one output switch are being configured.

![image](https://github.com/user-attachments/assets/08eb0c34-1545-489d-b6ca-0136470014e6)

In order to update the status of the entities, customize the "IoT_device_state_update_pub" function, by adding all the entities status by using the functions provided by the parson library

![image](https://github.com/user-attachments/assets/c45d831e-a68c-406d-9775-649201a0b133)

In your main function just call the "IoT_device_config_pub_init(mqtt->mqtt_client_inst, mqtt);" upon connection and the "IoT_device_config_pub_init(mqtt->mqtt_client_inst, mqtt);" every time there is need to update the status of the sensors.

![image](https://github.com/user-attachments/assets/d5e586b9-38e7-409f-8b21-2f37201e8601)

The configuration of the MQTT broker are defined in the "mqttExample.h" file

