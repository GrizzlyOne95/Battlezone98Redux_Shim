/*
 * Entry: 004ad374
 * Name: SAV::CleanupSound
 * Namespace: SAV
 * Signature: void CleanupSound(SAV * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SAV::CleanupSound(SAV *this)

{
  _gas_object *p_Var1;
  
  if (this->_padding_ != 0) {
    p_Var1 = FindGASObject((char *)(this->_padding_ + 0x36c),(_OBJ76 *)this->_padding_);
    if (p_Var1 != (_gas_object *)0x0) {
      this->_padding_ = (int)p_Var1;
      StopGASEvent(p_Var1);
    }
    this->_padding_ = 0;
  }
  return;
}
