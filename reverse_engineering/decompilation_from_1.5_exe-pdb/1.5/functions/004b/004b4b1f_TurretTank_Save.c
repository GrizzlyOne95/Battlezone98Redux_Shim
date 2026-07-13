/*
 * Entry: 004b4b1f
 * Name: TurretTank::Save
 * Namespace: TurretTank
 * Signature: bool Save(TurretTank * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TurretTank::Save(TurretTank *this,_iobuf *param_1)

{
  bool bVar1;
  float local_c;
  undefined4 uStack_8;
  
  local_c = 0.0;
  uStack_8 = (uint)this & 0xffffff;
  bVar1 = ::out(param_1,(float *)(this->_padding_ + 0x3c0),4,"undeffloat");
  if ((((bVar1) && (bVar1 = ::out(param_1,&local_c,4,"undeffloat"), bVar1)) &&
      (bVar1 = ::out(param_1,(float *)(this->_padding_ + 0x3c4),4,"undeffloat"), bVar1)) &&
     (((bVar1 = ::out(param_1,(float *)(this->_padding_ + 0x3c8),4,"undeffloat"), bVar1 &&
       (bVar1 = ::out(param_1,&this->_padding_,4,"undefraw"), bVar1)) &&
      ((bVar1 = ::out(param_1,&this->delayTimer,4,"undeffloat"), bVar1 &&
       (bVar1 = ::out(param_1,(bool *)((int)&uStack_8 + 3),1,"undefbool"), bVar1)))))) {
    bVar1 = HoverCraft::Save((HoverCraft *)this,param_1);
    return bVar1;
  }
  return false;
}
