/*
 * Entry: 004b552f
 * Name: TurretTank::UnPackTempState
 * Namespace: TurretTank
 * Signature: void UnPackTempState(TurretTank * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTank::UnPackTempState(TurretTank *this,void *param_1,uint *param_2)

{
  uint *puVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  undefined4 *puVar5;
  void *pvVar6;
  void *pvVar7;
  void *pvVar8;
  NetProcess *this_00;
  AiMission *pAVar9;
  long extraout_EAX;
  bool bVar10;
  double *pdVar11;
  
  pvVar8 = param_1;
  if ((*(byte *)((int)param_1 + 2) & 0x40) == 0) {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 & 0xffffefff;
  }
  else {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 | 0x1000;
  }
  if ((*(byte *)((int)param_1 + 2) & 0x80) == 0) {
    this->_padding_ = 0;
    puVar5 = (undefined4 *)this->_padding_;
    if (puVar5 != (undefined4 *)0x0) {
      (**(code **)*puVar5)(1);
      this->_padding_ = 0;
    }
  }
  else {
    this->_padding_ = this->_padding_;
    if (this->_padding_ == 0) {
      this_00 = operator_new(0x14);
      if (this_00 == (NetProcess *)0x0) {
        param_1 = (void *)0x0;
      }
      else {
        param_1 = NetProcess::NetProcess(this_00);
      }
      iVar4 = *(int *)param_1;
      pdVar11 = &this[-1].deployed_transform.posit_y;
      pAVar9 = AiMission::GetCurrent();
      (**(code **)(iVar4 + 0x18))(pAVar9,pdVar11);
    }
  }
  *(byte *)((int)pvVar8 + 2) = *(byte *)((int)pvVar8 + 2) & 3;
  cVar2 = *(char *)((int)pvVar8 + 2);
  if (cVar2 == '\0') {
    param_1 = (void *)0x3;
  }
  else if (cVar2 == '\x01') {
    param_1 = (void *)0x1;
  }
  else if (cVar2 == '\x02') {
    param_1 = (void *)0x2;
  }
  else if (cVar2 == '\x03') {
    param_1 = (void *)0x0;
  }
  pvVar6 = (void *)this->_padding_;
  if (pvVar6 == param_1) goto LAB_004b5637;
  if (pvVar6 == (void *)0x0) {
    bVar10 = param_1 == (void *)0x3;
LAB_004b562f:
    if (bVar10) goto LAB_004b5637;
  }
  else {
    if (pvVar6 == (void *)0x1) {
      pvVar7 = (void *)((int)param_1 + -2);
    }
    else {
      if (pvVar6 == (void *)0x2) {
        bVar10 = param_1 == (void *)0x1;
        goto LAB_004b562f;
      }
      pvVar7 = param_1;
      if (pvVar6 != (void *)0x3) goto LAB_004b5637;
    }
    if (pvVar7 == (void *)0x0) {
      this->_padding_ = 0;
      goto LAB_004b5637;
    }
  }
  this->_padding_ = 1;
LAB_004b5637:
  bVar3 = *(byte *)pvVar8;
  pdVar11 = &this[-1].deployed_transform.posit_y;
  this->_padding_ = (int)((float)bVar3 * 0.003921569);
  GameObject::SetCurHealth
            ((GameObject *)pdVar11,(float)bVar3 * 0.003921569 * (float)this->_padding_);
  (**(code **)(*(int *)pdVar11 + 0xa0))(this->_padding_);
  this->_padding_ = (int)((float)*(byte *)((int)pvVar8 + 1) * 0.003921569);
  _ftol2_sse();
  GameObject::SetCurAmmo((GameObject *)pdVar11,extraout_EAX);
  *param_2 = *param_2 - 3;
  if (param_1 == (void *)0x0) {
    HoverCraft::UnPackTempState((HoverCraft *)this,(void *)((int)pvVar8 + 3),param_2);
  }
  return;
}
