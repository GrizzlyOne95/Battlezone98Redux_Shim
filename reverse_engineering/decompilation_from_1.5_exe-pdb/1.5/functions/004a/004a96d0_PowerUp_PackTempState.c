/*
 * Entry: 004a96d0
 * Name: PowerUp::PackTempState
 * Namespace: PowerUp
 * Signature: void PackTempState(PowerUp * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PowerUp::PackTempState(PowerUp *this,void *param_1,uint *param_2)

{
  float fVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  PowerUp *pPVar4;
  uchar uVar5;
  undefined1 extraout_AL;
  REDUCED_VEC RVar6;
  undefined1 local_18 [8];
  undefined4 local_10;
  undefined2 uStack_c;
  PowerUp *local_8;
  
  *param_2 = *param_2 + 0x12;
  VVar2.y = (float)this->_padding_;
  VVar2.x = (float)&local_10;
  VVar2.z = (float)this->_padding_;
  local_8 = this;
  RVar6 = NetUtil_ReduceVector(VVar2);
  *(undefined4 *)param_1 = *RVar6._0_4_;
  *(undefined2 *)((int)param_1 + 4) = *(undefined2 *)(RVar6._0_4_ + 1);
  VVar3.y = (float)local_8->_padding_;
  VVar3.x = (float)local_18;
  VVar3.z = (float)local_8->_padding_;
  RVar6 = NetUtil_ReduceVector(VVar3);
  pPVar4 = local_8;
  local_10 = *RVar6._0_4_;
  uStack_c = *(undefined2 *)(RVar6._0_4_ + 1);
  *(undefined4 *)((int)param_1 + 6) = local_10;
  *(undefined2 *)((int)param_1 + 10) = uStack_c;
  uVar5 = NetUtil_ReduceSmallFloat(*(float *)(local_8->_padding_ + 0xd0));
  *(uchar *)((int)param_1 + 0xc) = uVar5;
  uVar5 = NetUtil_ReduceSmallFloat(*(float *)(pPVar4->_padding_ + 0xc4));
  *(uchar *)((int)param_1 + 0xd) = uVar5;
  uVar5 = NetUtil_ReduceSmallFloat(*(float *)(pPVar4->_padding_ + 200));
  *(uchar *)((int)param_1 + 0xe) = uVar5;
  uVar5 = NetUtil_ReduceSmallFloat(*(float *)(pPVar4->_padding_ + 0xcc));
  *(uchar *)((int)param_1 + 0xf) = uVar5;
  *(undefined1 *)((int)param_1 + 0x10) = 0;
  if (*(int *)(pPVar4->_padding_ + 0xd4) != 0) {
    *(undefined1 *)((int)param_1 + 0x10) = 1;
  }
  if ((*(uint *)(pPVar4->_padding_ + 0x10c) & 0x8000) != 0) {
    *(byte *)((int)param_1 + 0x10) = *(byte *)((int)param_1 + 0x10) | 2;
  }
  if ((*(byte *)(pPVar4->_padding_ + 0x10c) & 0x20) != 0) {
    *(byte *)((int)param_1 + 0x10) = *(byte *)((int)param_1 + 0x10) | 4;
  }
  if ((*(byte *)(pPVar4->_padding_ + 0x10c) & 1) != 0) {
    *(byte *)((int)param_1 + 0x10) = *(byte *)((int)param_1 + 0x10) | 8;
  }
  if ((*(byte *)(pPVar4->_padding_ + 0x10c) & 4) != 0) {
    *(byte *)((int)param_1 + 0x10) = *(byte *)((int)param_1 + 0x10) | 0x10;
  }
  if ((*(byte *)(pPVar4->_padding_ + 0x10c) & 8) != 0) {
    *(byte *)((int)param_1 + 0x10) = *(byte *)((int)param_1 + 0x10) | 0x20;
  }
  if ((float)pPVar4->_padding_ < 0.0) {
    *(byte *)((int)param_1 + 0x10) = *(byte *)((int)param_1 + 0x10) | 0x80;
  }
  if (0.0 < (float)pPVar4->_padding_) {
    fVar1 = (float)pPVar4->_padding_;
    if (1.0 < fVar1) {
      fVar1 = 1.0;
    }
    ceil((double)(fVar1 * 255.0));
    _ftol2();
    *(undefined1 *)((int)param_1 + 0x11) = extraout_AL;
  }
  else {
    *(undefined1 *)((int)param_1 + 0x11) = 0;
  }
  return;
}
