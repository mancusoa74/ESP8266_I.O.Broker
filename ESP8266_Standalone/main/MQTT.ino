void MQTTsend()
{
MQTTclient.publish(topicName1, temp01);
delay(50);
MQTTclient.publish(topicName2, temp02);
delay(50);
MQTTclient.publish(topicName3, temp03);
delay(50);
MQTTclient.publish(topicName4, temp04);
delay(50);
MQTTclient.publish(topicName5, temp05);
delay(50);
MQTTclient.publish(topicName6, temp06);
delay(50);
MQTTclient.publish(topicName7, temp07);
delay(50);
MQTTclient.publish(topicName8, temp08);
delay(50);
MQTTclient.publish(topicName9, temp09);
delay(50);
MQTTclient.publish(topicName10, temp10);
delay(50);
MQTTclient.publish(topicName11, temp11);
delay(50);
MQTTclient.publish(topicName12, temp12);
delay(50);
MQTTclient.publish(topicName13, temp13);
delay(50);
MQTTclient.publish(topicName14, temp14);
delay(50);
MQTTclient.publish(topicName15, temp15);
delay(50);
Serial.println("All MQTT topics publish!");
}

