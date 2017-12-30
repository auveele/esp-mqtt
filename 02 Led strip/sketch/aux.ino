
/*########################
##########################
 
  aux.ino

  Este archivo contiene ...

##########################
########################*/


// #################
// PRINT FREE MEMORY
// #################
void print_memory(){
  long mem = ESP.getFreeHeap();
  DEBUG_PRINT("freeMemory()=");
  DEBUG_PRINTLN(mem);
}
