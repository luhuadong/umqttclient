/*
 * @Author: jiejie
 * @Github: https://github.com/jiejieTop
 * @Date: 2019-12-11 21:53:07
 * @LastEditTime: 2020-06-08 20:40:47
 * @Description: the code belongs to jiejie, please keep the author information and source code according to the license.
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include "mqttclient.h"


#define ProductKey     "a1eubzkCwuz"
#define DeviceName     "wiot_01"
#define DeviceSecret   "56e89e401e0ed9b10e1e0e5725f362b4"

#define HOST           "a1eubzkCwuz.iot-as-mqtt.cn-shanghai.aliyuncs.com"
#define ADDRESS        "tcp://a1eubzkCwuz.iot-as-mqtt.cn-shanghai.aliyuncs.com"
#define CLIENTID       "a1eubzkCwuz.wiot_01|securemode=2,signmethod=hmacsha256,timestamp=1657691211776|"
#define USERNAME       "wiot_01&a1eubzkCwuz"
#define PASSWORD       "13ef429e9c6206d45ceefd3d73e4385ce5ac52de7d7c9b7c12b5d3fdfaf05f13"
#define PORT           "1883"

#define TOPIC          "/"ProductKey"/"DeviceName"/user/hello"
#define PROPERTY_TOPIC "/sys/"ProductKey"/"DeviceName"/thing/event/property/post"

#define PAYLOAD        "Hello, GetIoT.tech!"
#define QOS            1
#define TIMEOUT        10000L

static void topic1_handler(void* client, message_data_t* msg)
{
    (void) client;
    MQTT_LOG_I("-----------------------------------------------------------------------------------");
    MQTT_LOG_I("%s:%d %s()...\ntopic: %s\nmessage:%s", __FILE__, __LINE__, __FUNCTION__, msg->topic_name, (char*)msg->message->payload);
    MQTT_LOG_I("-----------------------------------------------------------------------------------");
}

void *mqtt_publish_thread(void *arg)
{
    mqtt_client_t *client = (mqtt_client_t *)arg;
    
    char buf[1024] = { 0 };
    mqtt_message_t msg;
    memset(&msg, 0, sizeof(msg));
    sprintf(buf, "welcome to mqttclient, this is a publish test...");

    sleep(2);

    mqtt_list_subscribe_topic(client);

    msg.payload = (void *) buf;
    msg.qos = 0;
    while(1) {
        time_t seconds = time((time_t*)NULL);
        float temp = random_number_range(200, 400)/10.0;
        sprintf(buf, "welcome to mqttclient, this is a publish test, a rand number: %d ...", random_number());

        //sprintf(buf, "{\"id\":\"123\",\"version\":\"1.0\",\"sys\":{\"ack\":0},\"params\":{\"Temperature\":{\"value\":%.1f,\"time\":%lu}},\"method\":\"thing.event.property.post\"}", temp, seconds);
        sprintf(buf, "{\"id\":\"123\",\"version\":\"1.0\",\"sys\":{\"ack\":0},\"params\":{\"Temperature\":{\"value\":%.1f}},\"method\":\"thing.event.property.post\"}", temp);
        printf("Publish >> %s\n", buf);
        
        mqtt_publish(client, PROPERTY_TOPIC, &msg);

        sleep(6);
    }
}

int main(void)
{
    int res;
    pthread_t thread1;
    mqtt_client_t *client = NULL;

    printf("%s\n", PROPERTY_TOPIC);
    
    printf("\nwelcome to mqttclient test...\n");

    mqtt_log_init();

    client = mqtt_lease();

    mqtt_set_port(client, PORT);
    mqtt_set_host(client, HOST);
    mqtt_set_client_id(client, CLIENTID);
    mqtt_set_user_name(client, USERNAME);
    mqtt_set_password(client, PASSWORD);
    mqtt_set_clean_session(client, 1);

    mqtt_connect(client);
    
    mqtt_subscribe(client, TOPIC, QOS0, topic1_handler);
    
    res = pthread_create(&thread1, NULL, mqtt_publish_thread, client);
    if(res != 0) {
        MQTT_LOG_E("create mqtt publish thread fail");
        exit(res);
    }

    while (1) {
        sleep(100);
    }
}
