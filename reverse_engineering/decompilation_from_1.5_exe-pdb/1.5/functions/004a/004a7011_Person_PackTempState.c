/*
 * Entry: 004a7011
 * Name: Person::PackTempState
 * Namespace: Person
 * Signature: void PackTempState(Person * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Person::PackTempState(Person *this,void *param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  void *pvVar5;
  Person *pPVar6;
  undefined1 extraout_AL;
  undefined1 extraout_AL_00;
  uchar uVar7;
  Weapon *pWVar8;
  float10 fVar9;
  float10 extraout_ST0;
  float10 fVar10;
  float10 extraout_ST1;
  REDUCED_VEC RVar11;
  undefined1 local_18 [10];
  undefined4 local_e;
  undefined2 uStack_a;
  Person *local_8;
  
  pvVar5 = param_1;
  fVar10 = (float10)0;
  *param_2 = *param_2 + 0x14;
  fVar9 = (float10)255.0;
  local_8 = this;
  if (fVar10 < (float10)(float)this->_padding_) {
    _ftol2();
    *(undefined1 *)((int)param_1 + 1) = extraout_AL;
    fVar9 = extraout_ST0;
    fVar10 = extraout_ST1;
  }
  else {
    *(undefined1 *)((int)param_1 + 1) = 0;
  }
  if (fVar10 < (float10)(float)this->_padding_) {
    fVar10 = (float10)(float)this->_padding_;
    if ((float10)1 < fVar10) {
      fVar10 = (float10)1;
    }
    ceil((double)(fVar10 * fVar9));
    _ftol2();
    *(undefined1 *)param_1 = extraout_AL_00;
  }
  else {
    *(undefined1 *)param_1 = 0;
  }
  VVar3.y = (float)this->_padding_;
  VVar3.x = (float)local_18;
  VVar3.z = (float)this->_padding_;
  RVar11 = NetUtil_ReduceVector(VVar3);
  local_e = *RVar11._0_4_;
  uStack_a = *(undefined2 *)(RVar11._0_4_ + 1);
  *(undefined4 *)((int)param_1 + 2) = local_e;
  *(undefined2 *)((int)param_1 + 6) = uStack_a;
  VVar4.y = (float)local_8->_padding_;
  VVar4.x = (float)local_18;
  VVar4.z = (float)local_8->_padding_;
  RVar11 = NetUtil_ReduceVector(VVar4);
  pPVar6 = local_8;
  local_e = *RVar11._0_4_;
  uStack_a = *(undefined2 *)(RVar11._0_4_ + 1);
  *(undefined4 *)((int)param_1 + 8) = local_e;
  *(undefined2 *)((int)param_1 + 0xc) = uStack_a;
  uVar7 = NetUtil_ReduceSmallFloat(*(float *)(local_8->_padding_ + 0xc4));
  *(uchar *)((int)param_1 + 0xe) = uVar7;
  uVar7 = NetUtil_ReduceSmallFloat(*(float *)(pPVar6->_padding_ + 200));
  *(uchar *)((int)param_1 + 0xf) = uVar7;
  uVar7 = NetUtil_ReduceSmallFloat(*(float *)(pPVar6->_padding_ + 0xcc));
  *(uchar *)((int)param_1 + 0x10) = uVar7;
  uVar7 = NetUtil_ReduceSmallFloat(*(float *)(pPVar6->_padding_ + 0xd0));
  *(uchar *)((int)param_1 + 0x11) = uVar7;
  *(undefined1 *)((int)param_1 + 0x12) = 0;
  if (*(int *)(pPVar6->_padding_ + 0xd8) != 0) {
    *(undefined1 *)((int)param_1 + 0x12) = 1;
  }
  if (*(int *)(pPVar6->_padding_ + 0xd4) != 0) {
    *(byte *)((int)param_1 + 0x12) = *(byte *)((int)param_1 + 0x12) | 2;
  }
  if (*(int *)(pPVar6->_padding_ + 0xdc) != 0) {
    *(byte *)((int)param_1 + 0x12) = *(byte *)((int)param_1 + 0x12) | 4;
  }
  if ((*(byte *)(pPVar6->_padding_ + 0x10c) & 0x80) != 0) {
    *(byte *)((int)param_1 + 0x12) = *(byte *)((int)param_1 + 0x12) | 8;
  }
  if ((*(byte *)(pPVar6->_padding_ + 0x10c) & 4) != 0) {
    *(byte *)((int)param_1 + 0x12) = *(byte *)((int)param_1 + 0x12) | 0x10;
  }
  if ((char)pPVar6->_padding_ != '\0') {
    *(byte *)((int)param_1 + 0x12) = *(byte *)((int)param_1 + 0x12) | 0x20;
  }
  if (((*(byte *)(pPVar6->_padding_ + 0x14) & 0x10) != 0) &&
     ((UserProfilePtr->playOption & 0x10) != 0)) {
    *(byte *)((int)param_1 + 0x12) = *(byte *)((int)param_1 + 0x12) | 0x40;
  }
  if ((float)pPVar6->_padding_ < 0.0) {
    *(byte *)((int)param_1 + 0x12) = *(byte *)((int)param_1 + 0x12) | 0x80;
  }
  *(undefined1 *)((int)param_1 + 0x13) = 0;
  iVar1 = pPVar6->_padding_;
  if (iVar1 == 2) {
    *(undefined1 *)((int)param_1 + 0x13) = 0;
  }
  else if (iVar1 == 0) {
    *(undefined1 *)((int)param_1 + 0x13) = 1;
  }
  else if (iVar1 == 1) {
    *(undefined1 *)((int)param_1 + 0x13) = 2;
  }
  else if (iVar1 == 3) {
    *(undefined1 *)((int)param_1 + 0x13) = 3;
  }
  if (pPVar6->_padding_ == 0) {
    *(byte *)((int)param_1 + 0x13) = *(byte *)((int)param_1 + 0x13) | 4;
  }
  if (pPVar6->_padding_ != 0) {
    uVar2 = *(uint *)(pPVar6->_padding_ + 0x30);
    param_1 = (void *)0x0;
    do {
      if ((((uVar2 & 1 << ((byte)param_1 & 0x1f)) != 0) &&
          (pWVar8 = Carrier::GetWeapon((Carrier *)pPVar6->_padding_,(int)param_1),
          pWVar8 != (Weapon *)0x0)) && (pWVar8->weaponClass->sig == 0x534e4950)) {
        *(byte *)((int)pvVar5 + 0x13) = *(byte *)((int)pvVar5 + 0x13) | 8;
      }
      param_1 = (void *)((int)param_1 + 1);
    } while ((int)param_1 < 5);
  }
  return;
}
