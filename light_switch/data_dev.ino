 String millis2time(){ // преобразование миллисекунд в вид д/ч/м/с
  
         int times =(millis()/1000);
         int days =  (times/3600)/24;
         int timehour =(((times)  % 86400L) / 3600); // часы
        if ( ((times % 3600) / 60) < 10 ) {
         int timehour = 0;
               }
         int timeminuts=((times  % 3600) / 60); // минуты
         if ( (times % 60) < 10 ) {
         int timeminuts = 0;
             }
         int timeseconds=(times % 60); // секунды
       String Time= String(days)+":"+String(twoDigits(timehour))+":"+String(twoDigits(timeminuts))+":"+String(twoDigits(timeseconds));
       return Time;
     }

 String twoDigits(int digits){
             if(digits < 10) {
          String i = '0'+String(digits);
          return i;
         }
          else {
        return String(digits);
         }
      }

void time_work(){
   if (captivePortal()) {  
    return;
  }
  if (validateToken()){
       DynamicJsonDocument doc(1024);
       doc["time"] = millis2time();
       if(digitalRead(channel1)){ doc["c1"] = "On"; } else { doc["c1"] = "Off"; }
       if(digitalRead(channel2)){ doc["c2"] = "On"; } else { doc["c2"] = "Off"; }
       if(digitalRead(channel3)){ doc["c3"] = "On"; } else { doc["c3"] = "Off"; }
       doc["MQTT"] = MQTT_status();
       String json;
       serializeJson(doc, json);
          
     server.send(200, "text", json);   
  }   
}



String JSON_DATA(){
       DynamicJsonDocument doc(1024);
       String json;
       if(digitalRead(channel1)){ doc["c1"] = "On1"; } else { doc["c1"] = "Off1"; }
       if(digitalRead(channel2)){ doc["c2"] = "On2"; } else { doc["c2"] = "Off2"; }
       if(digitalRead(channel3)){ doc["c3"] = "On3"; } else { doc["c3"] = "Off3"; }
       serializeJson(doc, json);
     return json;
}

void status_sw(){
 if(server.hasArg("apikey")){  
       if(server.arg("apikey") == String(settings.API_key)){
          server.send(200, "text/json", JSON_DATA());
       }
  }else{
    server.send(200, "text/json", "no valide key");
  }
}
