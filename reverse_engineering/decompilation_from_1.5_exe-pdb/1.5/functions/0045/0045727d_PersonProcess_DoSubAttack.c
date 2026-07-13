/*
 * Entry: 0045727d
 * Name: PersonProcess::DoSubAttack
 * Namespace: PersonProcess
 * Signature: void DoSubAttack(PersonProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonProcess::DoSubAttack(PersonProcess *this)

{
  char cVar1;
  
  cVar1 = (**(code **)(*(int *)this->_padding_ + 0x18))();
  if (cVar1 != '\0') {
    this->_padding_ = 3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0045729b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)this->_padding_ + 0x1c))();
  return;
}
