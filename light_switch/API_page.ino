void api_config_page(){
 if (!validateToken()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  String html = "<html><head><meta charset=\"UTF-8\"><title>Настройка API управления устройством</title>";
  html += "<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" />";
  html += "</head><body>";
  html += "<h2>Настройка API управления устройством</h2>";
  html += "<div class =\"frame\">";
  html += "<text>Текущий API ключ [apikey]:</text> <div class =\"live\" id=\"APIKEY\">"+key_return()+"</div>";
  html += "<div id=\"apibut\" ><center><a href=\"#\" class=\"btn_off\" onclick=\"api_genkey()\">Сгенерировать новый ключ</a></center></div><br>";
  html += "<text>Ссылка для получения статуса:</text> <div class =\"links\" id=\"status_link\">"+status_link()+"</div>";
  html += "<text>Ссылка для управления каналами:</text> <div class =\"links\" id=\"channel_link\">"+control_link()+"</div>";
  html += "<br></div>";
  html += "<center><br><a href=\"/\">Вернуться назад</a><br></center>";
  html += "<footer>© <b>CYBEREX TECH</b>, 2024. Версия микро ПО <b>"+version_code+"</b>.</footer></html>";
  html +=  api_js;
  html += "</body></html>";
  server.send(200, "text/html", html);
}

String key_return(){

       if(String(settings.API_key) == ""){                                 
           strncpy(settings.API_key, generateToken().c_str(), MAX_STRING_LENGTH); // Если  переменная settings.API_key пуста, то генерируем и сохраняем новый API ключ
           save_config();                                                         // Сохраняем в EEPROM
           }

     return String(settings.API_key);                                             // Возвращаем ключ
}

String status_link(){
    String sl = "http://"+String(myHostname)+".local/?page=status&apikey="+key_return();
  return sl;
}

String control_link(){
    String sl = "http://"+String(myHostname)+".local/?page=control&apikey="+key_return()+"&switch=3";
  return sl;
}
