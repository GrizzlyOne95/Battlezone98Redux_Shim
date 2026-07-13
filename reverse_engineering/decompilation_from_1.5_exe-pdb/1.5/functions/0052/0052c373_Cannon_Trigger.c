/*
 * Entry: 0052c373
 * Name: Cannon::Trigger
 * Namespace: Cannon
 * Signature: void Trigger(Cannon * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Cannon::Trigger(Cannon *this)

{
  float fVar1;
  
  this->triggered = true;
  fVar1 = Get_Time();
  this->_padding_ = (int)fVar1;
  return;
}
