// Функция отправки данных по протоколу MQTT
void MQTT_send(){
   client.loop();
   uint32_t nows = millis();
  if (nows - lastMsg > 30000 && settings.mqtt_en) {
    if(WiFi.status() == WL_CONNECTED) {
        MQTT_send_data("jsondata", JSON_DATA());
     }
   lastMsg = nows; 
  }
 }
void MQTT_send_data(String topic, String data){
         String root = settings.mqtt_topic;
         String top  = root +"/"+ topic;
         String subscr = root +"/control";
         String input = settings.mqtt_serv;
         int colonIndex = input.indexOf(':');
         String ipAddress;
         String port;
         IPAddress Remote_MQTT_IP;

        if (colonIndex != -1) {
             ipAddress = input.substring(0, colonIndex);
             port = input.substring(colonIndex + 1);
             WiFi.hostByName(ipAddress.c_str(), Remote_MQTT_IP);
          }
      
      client.setServer(Remote_MQTT_IP, port.toInt());
      client.setCallback(callback);
           if(client.connected()){                                                                                    // Вторичная отправка данных при подключенном брокере 
          count_rf = 0;
          send_mqtt(top, data, subscr);
           }else{
              count_rf++;
              String ch_id = String(ESP.getChipId());
              if (client.connect(ch_id.c_str(), settings.mqtt_user, settings.mqtt_passw)){                             // Первичная отправка данных, выполняестя попытка подключения к брокеру 
                    send_mqtt(top, data, subscr);          
                }else{
                  if(count_rf > 2){                                                                                    // Если были неудачные попытки подключения, то переподключаем Wi-fi
                     WiFi.disconnect();
                     WiFi.begin(settings.mySSID, settings.myPW);
                     count_rf = 0;
                }
            }
        }
     
}

void send_mqtt(String tops, String data, String subscr){
     // Анонсируем объекты для Home Assistant [auto-discovery ]
     // Анонсируем объекты один раз при успешном подуключении и при запуске устройства
    // if(!annonce_mqtt_discovery){
           mqqt_d_annonce("CL1", "c1", "On1", "Off1");
           mqqt_d_annonce("CL2", "c2", "On2", "Off2");
           mqqt_d_annonce("CL3", "c3", "On3", "Off3");

           annonce_mqtt_discovery = true;
    // }
    // Отправляем данные 
    client.publish(tops.c_str(), data.c_str());
    client.subscribe(subscr.c_str());
}

void mqqt_d_annonce(String namec, String cn, String on_d, String off_d){

          String top      = String(settings.mqtt_topic) +"/jsondata";
          String control  = String(settings.mqtt_topic) +"/control";
          char jsonBuffer[1024] = {0};
          
          DynamicJsonDocument chan1(1024);
                              chan1["name"]                 = namec;
                              chan1["state_topic"]          = top;
                              chan1["command_topic"]        = control;
                              chan1["payload_on"]           = on_d;
                              chan1["payload_off"]          = off_d;
                              chan1["state_value_template"] = "{{ value_json."+cn+" }}";
                              
           serializeJson(chan1, jsonBuffer, sizeof(jsonBuffer));
           String top_to = "homeassistant/light/"+cn+"/config";
           client.publish(top_to.c_str(), jsonBuffer, true);
}

String MQTT_status(){
    String response_message = "";
    if(client.connected()){
         response_message = "подключен";
      }else{
         response_message = "отключен";
    }
    return response_message;
} 
