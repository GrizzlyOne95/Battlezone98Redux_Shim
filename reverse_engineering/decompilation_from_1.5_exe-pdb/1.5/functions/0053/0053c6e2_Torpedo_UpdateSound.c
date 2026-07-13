/*
 * Entry: 0053c6e2
 * Name: Torpedo::UpdateSound
 * Namespace: Torpedo
 * Signature: void UpdateSound(Torpedo * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Torpedo::UpdateSound(Torpedo *this,float param_1)

{
  char *pcVar1;
  _gas_object *p_Var2;
  GAS_PREP_INFO local_50;
  GAS_CTRL local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pcVar1 = (char *)(this->_padding_ + 0x19c);
  if ((*pcVar1 != '\0') && (this->soundThrust == (_gas_object *)0x0)) {
    InitGASCtrl(&local_34);
    local_34.flags = 0x2001;
    InitGASPrep(&local_50);
    local_50.loopMode = 1;
    local_50.pri = (-(uint)((((_OBJ76 *)this->_padding_)->flags & 0x10) != 0) & 0x14) + 0x2d;
    p_Var2 = StartGASEvent(pcVar1,(_OBJ76 *)this->_padding_,&local_34,&local_50);
    this->soundThrust = p_Var2;
  }
  return;
}
