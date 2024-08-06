void hard_sw() {                       // Обработка нажатия выключателя

   if(!digitalRead(switch_hard) && !switch_h){
       sw_count++;
      switch(sw_count){
        case 1: 
            digitalWrite(channel1, HIGH);
            digitalWrite(channel2, HIGH);
            digitalWrite(channel3, HIGH);
            break;
        case 2: 
            digitalWrite(channel1, HIGH);
            digitalWrite(channel2, LOW);
            digitalWrite(channel3, LOW);
            break;
        case 3: 
            digitalWrite(channel1, LOW);
            digitalWrite(channel2, HIGH);
            digitalWrite(channel3, LOW);
            break;
        case 4: 
            digitalWrite(channel1, HIGH);
            digitalWrite(channel2, HIGH);
            digitalWrite(channel3, LOW);
            break;
        case 5: 
            digitalWrite(channel1, LOW);
            digitalWrite(channel2, LOW);
            digitalWrite(channel3, HIGH);
            break;
        case 6: 
            digitalWrite(channel1, LOW);
            digitalWrite(channel2, LOW);
            digitalWrite(channel3, LOW);
            sw_count = 0;
            break;
      
    }
    
    MQTT_send_data("jsondata", JSON_DATA());
    switch_h = true;
   }
   if(digitalRead(switch_hard) && switch_h){
       switch_h = false;
   }
}

void powerS(){
   if (!validateToken()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  if (server.hasArg("switch")){ 
    int channell = 0;
    String chan = server.arg("switch");
  if(chan == "1"){ channell = channel1; }
  if(chan == "2"){ channell = channel2; }
  if(chan == "3"){ channell = channel3; }
  
  String response_message ="";
  if(digitalRead(channell)){
      digitalWrite(channell, LOW);
      response_message += "<center><a href=\"#\" class=\"btn_off\" onclick=\"on_off("+chan+")\">Включить канал "+chan+"</a></center>";
   }else{
      digitalWrite(channell, HIGH);
      response_message  += "<center><a href=\"#\" class=\"btn_on\" onclick=\"on_off("+chan+")\">Выключить канал "+chan+"</a></center>";
  }
      
     server.send(200, "text/html", response_message + "0 ytn" );
     if(settings.mqtt_en){ MQTT_send_data("jsondata", JSON_DATA());}
     if(settings.auto_on){
        if(chan == "1"){ settings._channel1 = digitalRead(channell); }
        if(chan == "2"){ settings._channel2 = digitalRead(channell); }
        if(chan == "3"){ settings._channel3 = digitalRead(channell); }
        save_config();
     }
    }
}

void powerAPI(){
if(server.hasArg("apikey")){
  if (server.hasArg("switch") && server.arg("apikey") == String(settings.API_key)){ 
    int channell = 0;
    String chan = server.arg("switch");
  if(chan == "1"){ channell = channel1; }
  if(chan == "2"){ channell = channel2; }
  if(chan == "3"){ channell = channel3; }
  
  String response_message ="";
  if(digitalRead(channell)){
      digitalWrite(channell, LOW);
      response_message += chan+"Off";
   }else{
      digitalWrite(channell, HIGH);
      response_message  += chan+"On";
  }
      
     server.send(200, "text/html", response_message );
     if(settings.mqtt_en){ MQTT_send_data("jsondata", JSON_DATA());}
     if(settings.auto_on){
        if(chan == "1"){ settings._channel1 = digitalRead(channell); }
        if(chan == "2"){ settings._channel2 = digitalRead(channell); }
        if(chan == "3"){ settings._channel3 = digitalRead(channell); }
        save_config();
      }
    }
  }
}

 void powerS2(int channell){
  if(digitalRead(channell)){
      digitalWrite(channell, LOW);
   }else{
      digitalWrite(channell, HIGH);
  }

     if(settings.mqtt_en){ MQTT_send_data("jsondata", JSON_DATA());}
    
}    



      

void callback(char* topic, byte* payload, unsigned int length) {
           String message;
         for (int i = 0; i < length; i++) 
           {
           message = message + (char)payload[i];
          }
          if(message == "On1" && !digitalRead(channel1)){
             powerS2(channel1);         
           }
          if(message == "On2" && !digitalRead(channel2)){
             powerS2(channel2);         
           }
           if(message == "On3" && !digitalRead(channel3)){
             powerS2(channel3);         
           }
            if(message == "Off1" && digitalRead(channel1)){
             powerS2(channel1);         
           }
          if(message == "Off2" && digitalRead(channel2)){
             powerS2(channel2);         
           }
           if(message == "Off3" && digitalRead(channel3)){
             powerS2(channel3);         
           }
 }
