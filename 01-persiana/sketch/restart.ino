

Ticker restartTimer;

void setup_restart(){
  mqttReconnectTimer.once(RESTART_TIME, restart_system);
}

void restart_system(){
  #ifdef DEBUG
  Serial.println("RESTART!");
  #endif
  ESP.restart();
}

