/*
 * Entry: 0040c5e7
 * Name: Producer::CanBuild
 * Namespace: Producer
 * Signature: bool CanBuild(Producer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Producer::CanBuild(Producer *this)

{
  char cVar1;
  
  if (this->deployedBuilder != false) {
    cVar1 = (**(code **)(this->_padding_ + 100))();
    if (cVar1 == '\0') {
      return false;
    }
  }
  return true;
}
