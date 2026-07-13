/*
 * Entry: 0049cc94
 * Name: HoverCraft::PackTempState
 * Namespace: HoverCraft
 * Signature: void PackTempState(HoverCraft * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HoverCraft::PackTempState(HoverCraft *this,void *param_1,uint *param_2)

{
  int *piVar1;
  int iVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  uchar uVar5;
  REDUCED_VEC RVar6;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined2 uStack_8;
  
  *param_2 = *param_2 + 0x12;
  VVar3.y = (float)this->_padding_;
  VVar3.x = (float)&local_c;
  VVar3.z = (float)this->_padding_;
  RVar6 = NetUtil_ReduceVector(VVar3);
  *(undefined4 *)param_1 = *RVar6._0_4_;
  *(undefined2 *)((int)param_1 + 4) = *(undefined2 *)(RVar6._0_4_ + 1);
  VVar4.y = (float)this->_padding_;
  VVar4.x = (float)local_14;
  VVar4.z = (float)this->_padding_;
  RVar6 = NetUtil_ReduceVector(VVar4);
  local_c = *RVar6._0_4_;
  uStack_8 = *(undefined2 *)(RVar6._0_4_ + 1);
  *(undefined4 *)((int)param_1 + 6) = local_c;
  *(undefined2 *)((int)param_1 + 10) = uStack_8;
  uVar5 = NetUtil_ReduceSmallFloat(*(float *)(this->_padding_ + 0xc4));
  *(uchar *)((int)param_1 + 0xc) = uVar5;
  uVar5 = NetUtil_ReduceSmallFloat(*(float *)(this->_padding_ + 200));
  *(uchar *)((int)param_1 + 0xd) = uVar5;
  uVar5 = NetUtil_ReduceSmallFloat(*(float *)(this->_padding_ + 0xcc));
  *(uchar *)((int)param_1 + 0xe) = uVar5;
  uVar5 = NetUtil_ReduceSmallFloat(*(float *)(this->_padding_ + 0xd0));
  *(uchar *)((int)param_1 + 0xf) = uVar5;
  *(undefined1 *)((int)param_1 + 0x10) = 0;
  if (*(int *)(this->_padding_ + 0xd8) != 0) {
    *(undefined1 *)((int)param_1 + 0x10) = 1;
  }
  if (*(int *)(this->_padding_ + 0xd4) != 0) {
    *(byte *)((int)param_1 + 0x10) = *(byte *)((int)param_1 + 0x10) | 2;
  }
  if (*(int *)(this->_padding_ + 0xdc) != 0) {
    *(byte *)((int)param_1 + 0x10) = *(byte *)((int)param_1 + 0x10) | 4;
  }
  piVar1 = &this->_padding_;
  if ((*(byte *)(*piVar1 + 0x14) & 1) != 0) {
    *(byte *)((int)param_1 + 0x10) = *(byte *)((int)param_1 + 0x10) | 8;
  }
  if ((*(uint *)(*piVar1 + 0x14) & 0x400) != 0) {
    *(byte *)((int)param_1 + 0x10) = *(byte *)((int)param_1 + 0x10) | 0x10;
  }
  if (((*(byte *)(*piVar1 + 0x14) & 0x10) != 0) && ((UserProfilePtr->playOption & 0x10) != 0)) {
    *(byte *)((int)param_1 + 0x10) = *(byte *)((int)param_1 + 0x10) | 0x40;
  }
  Craft::PackTempState((Craft *)this,(void *)((int)param_1 + 0x12),param_2);
  iVar2 = this->_padding_;
  this->lastThrot = *(float *)(iVar2 + 0xcc);
  this->soundThrust = *(_gas_object **)(iVar2 + 0xc4);
  this->soundTurbo = *(_gas_object **)(iVar2 + 200);
  this->lastFly = *(float *)(iVar2 + 0xd0);
  (this->omegaEye).x = *(float *)(iVar2 + 0xd8);
  (this->omegaEye).y = *(float *)(iVar2 + 0xd4);
  (this->omegaEye).z = *(float *)(iVar2 + 0xdc);
  return;
}
