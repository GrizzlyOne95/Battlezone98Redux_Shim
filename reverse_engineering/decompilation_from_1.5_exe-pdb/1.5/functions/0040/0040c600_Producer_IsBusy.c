/*
 * Entry: 0040c600
 * Name: Producer::IsBusy
 * Namespace: Producer
 * Signature: bool IsBusy(Producer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Producer::IsBusy(Producer *this)

{
  char cVar1;
  
  if (this->deployedBuilder != false) {
    cVar1 = (**(code **)(this->_padding_ + 100))();
    if (cVar1 == '\0') {
      return false;
    }
  }
  return this->buildClass != (GameObjectClass *)0x0;
}
