void handleRoot() {
   if (captivePortal()) {  
    return;
  }
  String header;
  if (!validateToken()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  String html = "<html lang=\"ru\"><head><meta charset=\"UTF-8\"><title>Управление освещением</title>";
  html += "<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" />";
  html +=  js;
  html += "</head><body>";
  html += divcode;
  html += "<h2> Управление освещением</h2>";
  html += "<div class =\"frame\">";
  String content ="";
  if (server.hasHeader("User-Agent")) {
    content += "the user agent used is : " + server.header("User-Agent") + "<br><br>";
  }
  html += "<text>Время работы устройства:</text> <div class =\"live\" id=\"timew\">00:00:00:00</div>";
  html += "<text>Статус MQTT </text> <div class =\"live\" id=\"MQTT\">"+MQTT_status()+"</div>";
  html += "<text>Сохранять состояние каналов</text><div class =\"live\"><label class=\"switch\"><input onclick=\"switch_b(this.checked ? 'on' : 'off')\" type=\"checkbox\" id=\"switch_auto\" "+get_switch()+"><span class=\"slider round\"></span></label></div>";
  html += "<div id=\"pbut1\" >"+ bt_st() +"</div><br>";
  html += "<div id=\"pbut2\" >"+ bt_st2() +"</div><br>";
  html += "<div id=\"pbut3\" >"+ bt_st3() +"</div><br>";
  html += "<br></div></body>";
  html += "<center><br><a href=\"/?page=wlan_config\">Wi-Fi конфигурация</a><br>";
  html += "<a href=\"/?page=send_config\">Настройка передачи данных</a><br>";
  html += "<a href=\"/?page=api_config\">API доступ к устройству</a><br>";
  html += "<a href=\"/?page=changelp\">Изменение пароля устройства</a><br>";
  html += "<a href=\"/?page=update_fw\">Обновление прошивки</a><br>";
  html += "<a href=\"#\" onclick=\"rebootdev()\">Перезагрузить устройство</a><br>";
  html += "<a href=\"/login?DISCONNECT=YES\">Выход</a></center>";
  html += "<footer>© <b>CYBEREX TECH</b>, 2024. Версия микро ПО <b>"+version_code+"</b>.</footer>";
  html += "<script src=\"script.js\"></script>"; 
  html += "</html>";
  server.send(200, "text/html", html);
}
String bt_st(){
    String st;
  if(digitalRead(channel1)){
      st = "<center><a href=\"#\" class=\"btn_on\" onclick=\"on_off(1)\">Выключить канал 1</a></center>";
   }else{
      st = "<center><a href=\"#\" class=\"btn_off\" onclick=\"on_off(1)\">Включить канал 1</a></center>";
  }
  return st;
}
String bt_st2(){
    String st;
  if(digitalRead(channel2)){
      st = "<center><a href=\"#\" class=\"btn_on\" onclick=\"on_off(2)\">Выключить канал 2</a></center>";
   }else{
      st = "<center><a href=\"#\" class=\"btn_off\" onclick=\"on_off(2)\">Включить канал 2</a></center>";
  }
  return st;
}
String bt_st3(){
    String st;
  if(digitalRead(channel3)){
      st = "<center><a href=\"#\" class=\"btn_on\" onclick=\"on_off(3)\">Выключить канал 3</a></center>";
   }else{
      st = "<center><a href=\"#\" class=\"btn_off\" onclick=\"on_off(3)\">Включить канал 3</a></center>";
  }
  return st;
}

String get_switch(){
  String status_s; 
  if(settings.auto_on){
    status_s = "checked";
  }
  return status_s; 
}
