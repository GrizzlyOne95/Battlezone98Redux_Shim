/*
 * Entry: 004b6f65
 * Name: Walker::PackTempState
 * Namespace: Walker
 * Signature: void PackTempState(Walker * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Walker::PackTempState(Walker *this,void *param_1,uint *param_2)

{
  int iVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  uchar uVar4;
  REDUCED_VEC RVar5;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined2 uStack_8;
  
  *param_2 = *param_2 + 0x12;
  VVar2.y = (float)this->_padding_;
  VVar2.x = (float)&local_c;
  VVar2.z = (float)this->_padding_;
  RVar5 = NetUtil_ReduceVector(VVar2);
  *(undefined4 *)param_1 = *RVar5._0_4_;
  *(undefined2 *)((int)param_1 + 4) = *(undefined2 *)(RVar5._0_4_ + 1);
  VVar3.y = (float)this->_padding_;
  VVar3.x = (float)local_14;
  VVar3.z = (float)this->_padding_;
  RVar5 = NetUtil_ReduceVector(VVar3);
  local_c = *RVar5._0_4_;
  uStack_8 = *(undefined2 *)(RVar5._0_4_ + 1);
  *(undefined4 *)((int)param_1 + 6) = local_c;
  *(undefined2 *)((int)param_1 + 10) = uStack_8;
  uVar4 = NetUtil_ReduceSmallFloat(*(float *)(this->_padding_ + 0xc4));
  *(uchar *)((int)param_1 + 0xc) = uVar4;
  uVar4 = NetUtil_ReduceSmallFloat(*(float *)(this->_padding_ + 200));
  *(uchar *)((int)param_1 + 0xd) = uVar4;
  uVar4 = NetUtil_ReduceSmallFloat(*(float *)(this->_padding_ + 0xcc));
  *(uchar *)((int)param_1 + 0xe) = uVar4;
  uVar4 = NetUtil_ReduceSmallFloat(*(float *)(this->_padding_ + 0xd0));
  *(uchar *)((int)param_1 + 0xf) = uVar4;
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
  if (((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) &&
     ((UserProfilePtr->playOption & 0x10) != 0)) {
    *(byte *)((int)param_1 + 0x10) = *(byte *)((int)param_1 + 0x10) | 0x40;
  }
  Craft::PackTempState((Craft *)this,(void *)((int)param_1 + 0x12),param_2);
  iVar1 = this->_padding_;
  this->_padding_ = *(int *)(iVar1 + 0xcc);
  this->_padding_ = *(int *)(iVar1 + 0xc4);
  this->_padding_ = *(int *)(iVar1 + 200);
  this->_padding_ = *(int *)(iVar1 + 0xd0);
  this->curAnim = *(long *)(iVar1 + 0xd8);
  this->animHandle = *(int *)(iVar1 + 0xd4);
  *(undefined4 *)&this->cycleState = *(undefined4 *)(iVar1 + 0xdc);
  return;
}
