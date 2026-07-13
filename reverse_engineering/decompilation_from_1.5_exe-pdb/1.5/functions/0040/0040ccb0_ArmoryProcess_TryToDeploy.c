/*
 * Entry: 0040ccb0
 * Name: ArmoryProcess::TryToDeploy
 * Namespace: ArmoryProcess
 * Signature: bool TryToDeploy(ArmoryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ArmoryProcess::TryToDeploy(ArmoryProcess *this)

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
