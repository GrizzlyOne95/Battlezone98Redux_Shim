/*
 * Entry: 004a7355
 * Name: Person::UnPackTempState
 * Namespace: Person
 * Signature: void UnPackTempState(Person * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Person::UnPackTempState(Person *this,void *param_1,uint *param_2)

{
  uint *puVar1;
  undefined4 *puVar2;
  Carrier *this_00;
  VECTOR_3D VVar3;
  REDUCED_VEC RVar4;
  REDUCED_VEC RVar5;
  void *pvVar6;
  byte bVar7;
  long extraout_EAX;
  VECTOR_3D *pVVar8;
  Weapon *pWVar9;
  int iVar10;
  float fVar11;
  undefined1 uVar12;
  undefined1 uVar13;
  undefined2 uVar14;
  VECTOR_3D local_20;
  float local_14;
  float fStack_10;
  float fStack_c;
  uint local_8;
  
  pvVar6 = param_1;
  local_8 = this->_padding_ ^ 0x33333333;
  this->_padding_ = (int)((float)*(byte *)((int)param_1 + 1) * 0.003921569);
  _ftol2_sse();
  GameObject::SetCurAmmo((GameObject *)&this[-1]._padding_,extraout_EAX);
  local_8 = (uint)*(byte *)param_1;
  this->_padding_ = (int)((float)local_8 * 0.003921569);
  GameObject::SetCurHealth
            ((GameObject *)&this[-1]._padding_,(float)local_8 * 0.003921569 * (float)this->_padding_
            );
  RVar4.z._1_1_ = (char)((ushort)*(undefined2 *)((int)param_1 + 6) >> 8);
  RVar4._0_5_ = *(undefined5 *)((int)param_1 + 2);
  pVVar8 = NetUtil_ExpandVector(&local_20,RVar4);
  local_14 = pVVar8->x;
  fStack_10 = pVVar8->y;
  fStack_c = pVVar8->z;
  this->_padding_ = (int)local_14;
  this->_padding_ = (int)fStack_10;
  this->_padding_ = (int)fStack_c;
  iVar10 = this->_padding_;
  *(float *)(iVar10 + 0x1c) = local_14;
  *(float *)(iVar10 + 0x20) = fStack_10;
  *(float *)(iVar10 + 0x24) = fStack_c;
  RVar5.z._1_1_ = (char)((ushort)*(undefined2 *)((int)param_1 + 0xc) >> 8);
  RVar5._0_5_ = *(undefined5 *)((int)param_1 + 8);
  pVVar8 = NetUtil_ExpandVector(&local_20,RVar5);
  local_14 = pVVar8->x;
  fStack_10 = pVVar8->y;
  fStack_c = pVVar8->z;
  iVar10 = this->_padding_;
  *(float *)(iVar10 + 0x28) = local_14;
  *(float *)(iVar10 + 0x2c) = fStack_10;
  *(float *)(iVar10 + 0x30) = fStack_c;
  iVar10 = this->_padding_;
  this->_padding_ = *(int *)(iVar10 + 0x28);
  this->_padding_ = *(int *)(iVar10 + 0x2c);
  this->_padding_ = *(int *)(iVar10 + 0x30);
  VVar3.z._1_1_ = (char)((uint)this->_padding_ >> 8);
  VVar3._0_9_ = *(unkbyte9 *)&this->_padding_;
  VVar3.z._2_2_ = (short)((uint)this->_padding_ >> 0x10);
  fVar11 = VecLen(VVar3);
  *(float *)(this->_padding_ + 0xc) = fVar11;
  iVar10 = this->_padding_;
  if (*(float *)(iVar10 + 0xc) <= 0.0) {
    fVar11 = 1e+30;
  }
  else {
    fVar11 = 1.0 / *(float *)(iVar10 + 0xc);
  }
  *(float *)(iVar10 + 0x10) = fVar11;
  iVar10 = this->_padding_;
  this->_padding_ = *(int *)(iVar10 + 0xc);
  this->_padding_ = *(int *)(iVar10 + 0x10);
  *(uint *)(iVar10 + 0xd8) = *(byte *)((int)param_1 + 0x12) & 1;
  *(uint *)(this->_padding_ + 0xd4) = *(byte *)((int)param_1 + 0x12) & 2;
  *(uint *)(this->_padding_ + 0xdc) = *(byte *)((int)param_1 + 0x12) & 4;
  fVar11 = NetUtil_ExpandSmallFloat(*(uchar *)((int)param_1 + 0xe));
  *(float *)(this->_padding_ + 0xc4) = fVar11;
  fVar11 = NetUtil_ExpandSmallFloat(*(uchar *)((int)param_1 + 0xf));
  *(float *)(this->_padding_ + 200) = fVar11;
  fVar11 = NetUtil_ExpandSmallFloat(*(uchar *)((int)param_1 + 0x10));
  *(float *)(this->_padding_ + 0xcc) = fVar11;
  fVar11 = NetUtil_ExpandSmallFloat(*(uchar *)((int)param_1 + 0x11));
  *(float *)(this->_padding_ + 0xd0) = fVar11;
  if ((*(byte *)((int)param_1 + 0x12) & 8) == 0) {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 & 0xffffff7f;
  }
  else {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 | 0x80;
  }
  if ((*(byte *)((int)param_1 + 0x12) & 0x10) == 0) {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 & 0xfffffffb;
  }
  else {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 | 4;
  }
  if ((*(byte *)((int)param_1 + 0x12) & 0x40) == 0) {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 & 0xffffefff;
  }
  else {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 | 0x1000;
  }
  bVar7 = *(byte *)((int)param_1 + 0x13) & 3;
  if (bVar7 == 0) {
    this->_padding_ = 2;
  }
  else if (bVar7 == 1) {
    this->_padding_ = 0;
  }
  else if (bVar7 == 2) {
    this->_padding_ = 1;
  }
  else if (bVar7 == 3) {
    this->_padding_ = 3;
  }
  if ((*(byte *)((int)param_1 + 0x13) & 4) != 0) {
    puVar2 = (undefined4 *)this->_padding_;
    if (puVar2 != (undefined4 *)0x0) {
      (**(code **)*puVar2)(1);
    }
    this->_padding_ = 0;
  }
  if (this->_padding_ != 0) {
    param_1 = (void *)0x0;
    do {
      this_00 = (Carrier *)this->_padding_;
      pWVar9 = Carrier::GetWeapon(this_00,(int)param_1);
      if ((pWVar9 != (Weapon *)0x0) && (pWVar9->weaponClass->sig == 0x534e4950)) {
        if ((*(byte *)((int)pvVar6 + 0x13) & 8) == 0) {
          uVar12 = 0;
          uVar13 = 0;
          uVar14 = 0;
        }
        else {
          iVar10 = 1 << ((byte)param_1 & 0x1f);
          uVar12 = (undefined1)iVar10;
          uVar13 = (undefined1)((uint)iVar10 >> 8);
          uVar14 = (undefined2)((uint)iVar10 >> 0x10);
        }
        Carrier::SetSelected(this_00,CONCAT22(uVar14,CONCAT11(uVar13,uVar12)));
      }
      param_1 = (void *)((int)param_1 + 1);
    } while ((int)param_1 < 5);
  }
  GameObject::SetObjective
            ((GameObject *)&this[-1]._padding_,(bool)(*(byte *)((int)pvVar6 + 0x12) >> 5 & 1));
  if ((*(byte *)((int)pvVar6 + 0x12) & 0x80) != 0) {
    GameObject::SetCurHealth((GameObject *)&this[-1]._padding_,-1.0);
    AiMission::GetCurrent();
    obj_set_flag((_OBJ76 *)this->_padding_,0x1000080);
    DistributedObject::SetLocal((DistributedObject *)this);
  }
  *param_2 = *param_2 - 0x14;
  return;
}
