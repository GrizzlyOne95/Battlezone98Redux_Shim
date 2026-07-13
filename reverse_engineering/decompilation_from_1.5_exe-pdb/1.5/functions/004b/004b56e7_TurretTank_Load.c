/*
 * Entry: 004b56e7
 * Name: TurretTank::Load
 * Namespace: TurretTank
 * Signature: bool Load(TurretTank * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TurretTank::Load(TurretTank *this,_iobuf *param_1)

{
  _iobuf *p_Var1;
  bool bVar2;
  int iVar3;
  float local_10;
  float local_c;
  float local_8;
  
  p_Var1 = param_1;
  if (version < 0x3e9) {
LAB_004b57b9:
    bVar2 = HoverCraft::Load((HoverCraft *)this,p_Var1);
    param_1 = (_iobuf *)CONCAT13(bVar2,param_1._0_3_);
  }
  else {
    if (version == 0x412) {
LAB_004b5757:
      bVar2 = ::in(p_Var1,&this->_padding_,4);
      if (!bVar2) goto LAB_004b5785;
      bVar2 = ::in(p_Var1,&this->delayTimer,4);
      param_1 = (_iobuf *)CONCAT13(1,param_1._0_3_);
      if (!bVar2) goto LAB_004b5785;
    }
    else {
      bVar2 = ::in(param_1,(float *)&param_1,4);
      if (bVar2) {
        bVar2 = ::in(p_Var1,&local_8,4);
        if (bVar2) {
          bVar2 = ::in(p_Var1,&local_c,4);
          if (bVar2) {
            bVar2 = ::in(p_Var1,&local_10,4);
            if (bVar2) goto LAB_004b5757;
          }
        }
      }
LAB_004b5785:
      param_1 = (_iobuf *)((uint)param_1 & 0xffffff);
    }
    if (version != 0x412) {
      if (param_1._3_1_ != '\0') {
        bVar2 = ::in(p_Var1,(bool *)((int)&param_1 + 3),1);
        if (bVar2) goto LAB_004b57b9;
      }
      param_1 = (_iobuf *)((uint)param_1 & 0xffffff);
    }
    if (param_1._3_1_ != '\0') goto LAB_004b57b9;
  }
  iVar3 = this->_padding_;
  if ((iVar3 == 2) || (iVar3 == 1)) {
    iVar3 = 0;
  }
  else {
    if (iVar3 != 3) goto LAB_004b57fb;
    iVar3 = 1;
  }
  AnimObj_Start((void *)this->_padding_,iVar3,&this->animHandle);
LAB_004b57fb:
  if (this->_padding_ == 2) {
    SetHazard(this);
  }
  return (bool)param_1._3_1_;
}
