/*
 * Entry: 005366f2
 * Name: PopperGun::Trigger
 * Namespace: PopperGun
 * Signature: void Trigger(PopperGun * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PopperGun::Trigger(PopperGun *this)

{
  float fVar1;
  
  this->triggered = true;
  fVar1 = Get_Time();
  this->_padding_ = (int)fVar1;
  return;
}
