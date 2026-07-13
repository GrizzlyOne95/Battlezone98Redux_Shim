/*
 * Entry: 0046f873
 * Name: Carrier::TriggerSpecial
 * Namespace: Carrier
 * Signature: void TriggerSpecial(Carrier * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Carrier::TriggerSpecial(Carrier *this)

{
  int iVar1;
  
  iVar1 = this->special;
  if ((-1 < iVar1) && ((this->enabled & 1 << ((byte)iVar1 & 0x1f)) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x0046f88e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->weapon[iVar1]->_padding_ + 8))();
    return;
  }
  return;
}
