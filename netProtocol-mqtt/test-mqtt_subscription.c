#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>

#define BROKER_ADDRESS "localhost"  // 定义broker地址
#define PORT 1883                   // 定义broker端口号
#define KEEP_ALIVE 60               // 定义keepalive时间

struct mosquitto *mosq = NULL;

void on_connect(struct mosquitto *mosq, void *userdata, int rc) {
    if (rc) {
        printf("连接失败： %s\n", mosquitto_connack_string(rc));
    } else {
        printf("连接成功\n");
    }
}

void on_disconnect(struct mosquitto *mosq, void *userdata, int rc) {
    printf("断开连接\n");
}

void on_publish(struct mosquitto *mosq, void *userdata, int mid) {
    printf("消息发送成功，mid=%d\n", mid);
}

void on_subscribe(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos) {
    printf("订阅成功\n");
}

void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message) {
    printf("收到消息：\n");
    printf("主题： %s\n", message->topic);
    printf("消息： %s\n", (char*)message->payload);
}

int main(int argc, char *argv[]) {
    int rc = -1;
    char *topic01 = "test/Easy-Eai-01";
    char *topic02 = "test/Easy-Eai-02";
    int qos = 1;

    mosquitto_lib_init();   // 初始化mosquitto库

    mosq = mosquitto_new("subsrciption_cliend", true, NULL);   // 创建一个新的mosquitto客户端
    if (!mosq) {
        fprintf(stderr, "创建客户端失败\n");
        goto cleanup;
    }

    // 设置回调函数
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_disconnect_callback_set(mosq, on_disconnect);
    mosquitto_publish_callback_set(mosq, on_publish);
    mosquitto_subscribe_callback_set(mosq, on_subscribe);
    mosquitto_message_callback_set(mosq, on_message);

    // 连接到broker
    rc = mosquitto_connect(mosq, BROKER_ADDRESS, PORT, KEEP_ALIVE);
    if (rc != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "连接失败: %s\n", mosquitto_strerror(rc));
        goto cleanup;
    }

    // 订阅主题
    rc = mosquitto_subscribe(mosq, NULL, topic01, qos);
    if (rc != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "订阅失败: %s\n", mosquitto_strerror(rc));
        goto cleanup;
    }

    rc = mosquitto_subscribe(mosq, NULL, topic02, qos);
    if (rc != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "订阅失败: %s\n", mosquitto_strerror(rc));
        goto cleanup;
    }
    //循环回调接收消息
    mosquitto_loop_forever(mosq, -1, 1);

cleanup:
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return rc;

}

