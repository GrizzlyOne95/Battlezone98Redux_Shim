/*
 * Entry: 0052d6fa
 * Name: Dispenser::Trigger
 * Namespace: Dispenser
 * Signature: void Trigger(Dispenser * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Dispenser::Trigger(Dispenser *this)

{
  float fVar1;
  
  this->triggered = true;
  fVar1 = Get_Time();
  this->_padding_ = (int)fVar1;
  return;
}
