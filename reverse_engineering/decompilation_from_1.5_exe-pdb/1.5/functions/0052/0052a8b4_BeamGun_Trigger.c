/*
 * Entry: 0052a8b4
 * Name: BeamGun::Trigger
 * Namespace: BeamGun
 * Signature: void Trigger(BeamGun * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BeamGun::Trigger(BeamGun *this)

{
  float fVar1;
  
  this->triggered = true;
  fVar1 = Get_Time();
  this->_padding_ = (int)fVar1;
  return;
}
