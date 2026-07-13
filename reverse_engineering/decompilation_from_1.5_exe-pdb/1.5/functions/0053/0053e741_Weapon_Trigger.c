/*
 * Entry: 0053e741
 * Name: Weapon::Trigger
 * Namespace: Weapon
 * Signature: void Trigger(Weapon * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Weapon::Trigger(Weapon *this)

{
  float fVar1;
  
  fVar1 = Get_Time();
  this->fLastTriggered = fVar1;
  return;
}
