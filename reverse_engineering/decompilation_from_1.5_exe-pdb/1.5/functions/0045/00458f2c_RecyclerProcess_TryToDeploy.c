/*
 * Entry: 00458f2c
 * Name: RecyclerProcess::TryToDeploy
 * Namespace: RecyclerProcess
 * Signature: bool TryToDeploy(RecyclerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall RecyclerProcess::TryToDeploy(RecyclerProcess *this)

{
  bool bVar1;
  
  bVar1 = Producer::HasPower((Producer *)this->craft);
  if (bVar1) {
    (**(code **)(this->craft->_padding_ + 0x5c))();
    this->nextState = DEPLOY;
    return true;
  }
  this->nextState = WAIT;
  return false;
}
