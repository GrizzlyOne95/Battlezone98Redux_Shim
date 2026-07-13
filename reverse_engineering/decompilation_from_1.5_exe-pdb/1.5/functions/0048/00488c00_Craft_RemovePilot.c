/*
 * Entry: 00488c00
 * Name: Craft::RemovePilot
 * Namespace: Craft
 * Signature: void RemovePilot(Craft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::RemovePilot(Craft *this)

{
  undefined4 *puVar1;
  int iVar2;
  VHCL_CONTROL *pVVar3;
  
  if ((this->_padding_ != 0) && (*(int *)(this->_padding_ + 0xac) != 4)) {
    this->_padding_ = 0;
    puVar1 = (undefined4 *)this->_padding_;
    if (puVar1 != (undefined4 *)0x0) {
      (**(code **)*puVar1)(1);
      this->_padding_ = 0;
    }
    pVVar3 = &this->vhcl->control;
    for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
      pVVar3->steer = 0.0;
      pVVar3 = (VHCL_CONTROL *)&pVVar3->pitch;
    }
    if ((Carrier *)this->_padding_ != (Carrier *)0x0) {
      Carrier::UnTriggerAll((Carrier *)this->_padding_);
      return;
    }
  }
  return;
}
