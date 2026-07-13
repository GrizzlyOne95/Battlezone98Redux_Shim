/*
 * Entry: 0049f62c
 * Name: Howitzer::Save
 * Namespace: Howitzer
 * Signature: bool Save(Howitzer * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Howitzer::Save(Howitzer *this,_iobuf *param_1)

{
  bool bVar1;
  float fStack_c;
  undefined4 uStack_8;
  
  fStack_c = 0.0;
  uStack_8 = (uint)this & 0xffffff;
  bVar1 = ::out(param_1,(float *)(*(int *)&this->field_0xec + 0x3c0),4,"undeffloat");
  if ((((bVar1) && (bVar1 = ::out(param_1,&fStack_c,4,"undeffloat"), bVar1)) &&
      (bVar1 = ::out(param_1,(float *)(*(int *)&this->field_0xec + 0x3c4),4,"undeffloat"), bVar1))
     && (((bVar1 = ::out(param_1,(float *)(*(int *)&this->field_0xec + 0x3c8),4,"undeffloat"), bVar1
          && (bVar1 = ::out(param_1,&this->field_0x220,4,"undefraw"), bVar1)) &&
         ((bVar1 = ::out(param_1,(float *)&this->field_0x2c8,4,"undeffloat"), bVar1 &&
          (bVar1 = ::out(param_1,(bool *)((int)&uStack_8 + 3),1,"undefbool"), bVar1)))))) {
    bVar1 = HoverCraft::Save((HoverCraft *)this,param_1);
    return bVar1;
  }
  return false;
}
