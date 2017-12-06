

Ticker restartTimer;

void setup_restart(){
  restartTimer.once(RESTART_TIME, restart_system);
}

void restart_system(){
  #ifdef DEBUG
  Serial.println("RESTART!");
  #endif
  write_restart();
  ESP.restart();
}
