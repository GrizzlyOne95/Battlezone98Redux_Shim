/*
 * Entry: 004b3d7f
 * Name: TurretCraft::PackTempState
 * Namespace: TurretCraft
 * Signature: void PackTempState(TurretCraft * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretCraft::PackTempState(TurretCraft *this,void *param_1,uint *param_2)

{
  VECTOR_3D VVar1;
  uchar uVar2;
  REDUCED_VEC RVar3;
  TurretCraft *local_c;
  TurretCraft *pTStack_8;
  
  *param_2 = *param_2 + 10;
  VVar1.y = (float)this->_padding_;
  VVar1.x = (float)&local_c;
  VVar1.z = (float)this->_padding_;
  local_c = this;
  pTStack_8 = this;
  RVar3 = NetUtil_ReduceVector(VVar1);
  *(undefined4 *)param_1 = *RVar3._0_4_;
  *(undefined2 *)((int)param_1 + 4) = *(undefined2 *)(RVar3._0_4_ + 1);
  uVar2 = NetUtil_ReduceSmallFloat(*(float *)(this->_padding_ + 0xc4));
  *(uchar *)((int)param_1 + 6) = uVar2;
  uVar2 = NetUtil_ReduceSmallFloat(*(float *)(this->_padding_ + 200));
  *(uchar *)((int)param_1 + 7) = uVar2;
  *(undefined1 *)((int)param_1 + 8) = 0;
  if (*(int *)(this->_padding_ + 0xd8) != 0) {
    *(undefined1 *)((int)param_1 + 8) = 1;
  }
  if (*(int *)(this->_padding_ + 0xd4) != 0) {
    *(byte *)((int)param_1 + 8) = *(byte *)((int)param_1 + 8) | 2;
  }
  if (*(int *)(this->_padding_ + 0xdc) != 0) {
    *(byte *)((int)param_1 + 8) = *(byte *)((int)param_1 + 8) | 4;
  }
  if ((*(byte *)(this->_padding_ + 0x10c) & 0x20) != 0) {
    *(byte *)((int)param_1 + 8) = *(byte *)((int)param_1 + 8) | 8;
  }
  if (((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) &&
     ((UserProfilePtr->playOption & 0x10) != 0)) {
    *(byte *)((int)param_1 + 8) = *(byte *)((int)param_1 + 8) | 0x40;
  }
  Craft::PackTempState((Craft *)this,(void *)((int)param_1 + 10),param_2);
  return;
}
