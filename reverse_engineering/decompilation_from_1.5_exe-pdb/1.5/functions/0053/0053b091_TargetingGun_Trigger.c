/*
 * Entry: 0053b091
 * Name: TargetingGun::Trigger
 * Namespace: TargetingGun
 * Signature: void Trigger(TargetingGun * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TargetingGun::Trigger(TargetingGun *this)

{
  float fVar1;
  
  this->triggered = true;
  fVar1 = Get_Time();
  this->_padding_ = (int)fVar1;
  return;
}
