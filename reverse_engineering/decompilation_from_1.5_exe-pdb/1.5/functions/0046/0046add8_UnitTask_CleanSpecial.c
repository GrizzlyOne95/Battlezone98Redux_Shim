/*
 * Entry: 0046add8
 * Name: UnitTask::CleanSpecial
 * Namespace: UnitTask
 * Signature: void CleanSpecial(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::CleanSpecial(UnitTask *this)

{
  Weapon **ppWVar1;
  char cVar2;
  
  ppWVar1 = &this->special;
  if (*ppWVar1 != (Weapon *)0x0) {
    cVar2 = (**(code **)((*ppWVar1)->_padding_ + 0x10))();
    if (cVar2 != '\0') {
                    /* WARNING: Could not recover jumptable at 0x0046adf4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)((*ppWVar1)->_padding_ + 0xc))();
      return;
    }
  }
  return;
}
