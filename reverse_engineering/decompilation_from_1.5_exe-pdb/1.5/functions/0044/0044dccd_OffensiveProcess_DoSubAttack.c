/*
 * Entry: 0044dccd
 * Name: OffensiveProcess::DoSubAttack
 * Namespace: OffensiveProcess
 * Signature: void DoSubAttack(OffensiveProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OffensiveProcess::DoSubAttack(OffensiveProcess *this)

{
  char cVar1;
  
  cVar1 = (**(code **)(*(int *)this->_padding_ + 0x18))();
  if (cVar1 != '\0') {
    this->_padding_ = 3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0044dceb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)this->_padding_ + 0x1c))();
  return;
}
