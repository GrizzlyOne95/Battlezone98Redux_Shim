/*
 * Entry: 0049c61f
 * Name: HoverCraft::CleanupSound
 * Namespace: HoverCraft
 * Signature: void CleanupSound(HoverCraft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HoverCraft::CleanupSound(HoverCraft *this)

{
  int iVar1;
  _gas_object *p_Var2;
  
  iVar1 = this->_padding_;
  if (this->soundTurbo != (_gas_object *)0x0) {
    p_Var2 = FindGASObject((char *)(iVar1 + 0x37c),(_OBJ76 *)this->_padding_);
    if (p_Var2 != (_gas_object *)0x0) {
      this->soundTurbo = p_Var2;
      StopGASEvent(p_Var2);
    }
    this->soundTurbo = (_gas_object *)0x0;
  }
  if (this->soundThrust != (_gas_object *)0x0) {
    p_Var2 = FindGASObject((char *)(iVar1 + 0x36c),(_OBJ76 *)this->_padding_);
    if (p_Var2 != (_gas_object *)0x0) {
      this->soundThrust = p_Var2;
      StopGASEvent(p_Var2);
    }
    this->soundThrust = (_gas_object *)0x0;
  }
  if (this->soundFly != (_gas_object *)0x0) {
    p_Var2 = FindGASObject((char *)(iVar1 + 0x38c),(_OBJ76 *)this->_padding_);
    if (p_Var2 != (_gas_object *)0x0) {
      this->soundFly = p_Var2;
      StopGASEvent(p_Var2);
    }
    this->soundFly = (_gas_object *)0x0;
  }
  return;
}
