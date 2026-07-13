/*
 * Entry: 0053c6a3
 * Name: Torpedo::CleanupSound
 * Namespace: Torpedo
 * Signature: void CleanupSound(Torpedo * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Torpedo::CleanupSound(Torpedo *this)

{
  _gas_object *p_Var1;
  
  if (this->soundThrust != (_gas_object *)0x0) {
    p_Var1 = FindGASObject((char *)(this->_padding_ + 0x19c),(_OBJ76 *)this->_padding_);
    if (p_Var1 != (_gas_object *)0x0) {
      this->soundThrust = p_Var1;
      StopGASEvent(p_Var1);
    }
    this->soundThrust = (_gas_object *)0x0;
  }
  return;
}
