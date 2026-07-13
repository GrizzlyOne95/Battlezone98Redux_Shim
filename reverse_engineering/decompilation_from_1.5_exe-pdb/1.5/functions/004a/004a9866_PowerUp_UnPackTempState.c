/*
 * Entry: 004a9866
 * Name: PowerUp::UnPackTempState
 * Namespace: PowerUp
 * Signature: void UnPackTempState(PowerUp * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PowerUp::UnPackTempState(PowerUp *this,void *param_1,uint *param_2)

{
  uint *puVar1;
  int iVar2;
  VECTOR_3D VVar3;
  REDUCED_VEC RVar4;
  REDUCED_VEC RVar5;
  VECTOR_3D *pVVar6;
  float fVar7;
  VECTOR_3D local_1c;
  float local_10;
  float fStack_c;
  float fStack_8;
  
  RVar4.z._1_1_ = (char)((ushort)*(undefined2 *)((int)param_1 + 4) >> 8);
  RVar4._0_5_ = *(undefined5 *)param_1;
  pVVar6 = NetUtil_ExpandVector(&local_1c,RVar4);
  local_10 = pVVar6->x;
  fStack_c = pVVar6->y;
  fStack_8 = pVVar6->z;
  iVar2 = this->_padding_;
  *(float *)(iVar2 + 0x1c) = local_10;
  *(float *)(iVar2 + 0x20) = fStack_c;
  *(float *)(iVar2 + 0x24) = fStack_8;
  iVar2 = this->_padding_;
  this->_padding_ = *(int *)(iVar2 + 0x1c);
  this->_padding_ = *(int *)(iVar2 + 0x20);
  this->_padding_ = *(int *)(iVar2 + 0x24);
  RVar5.z._1_1_ = (char)((ushort)*(undefined2 *)((int)param_1 + 10) >> 8);
  RVar5._0_5_ = *(undefined5 *)((int)param_1 + 6);
  pVVar6 = NetUtil_ExpandVector(&local_1c,RVar5);
  local_10 = pVVar6->x;
  fStack_c = pVVar6->y;
  fStack_8 = pVVar6->z;
  iVar2 = this->_padding_;
  *(float *)(iVar2 + 0x28) = local_10;
  *(float *)(iVar2 + 0x2c) = fStack_c;
  *(float *)(iVar2 + 0x30) = fStack_8;
  iVar2 = this->_padding_;
  this->_padding_ = *(int *)(iVar2 + 0x28);
  this->_padding_ = *(int *)(iVar2 + 0x2c);
  this->_padding_ = *(int *)(iVar2 + 0x30);
  VVar3.z._1_1_ = (char)((uint)this->_padding_ >> 8);
  VVar3._0_9_ = *(unkbyte9 *)&this->_padding_;
  VVar3.z._2_2_ = (short)((uint)this->_padding_ >> 0x10);
  fVar7 = VecLen(VVar3);
  *(float *)(this->_padding_ + 0xc) = fVar7;
  iVar2 = this->_padding_;
  if (*(float *)(iVar2 + 0xc) <= 0.0) {
    fVar7 = 1e+30;
  }
  else {
    fVar7 = 1.0 / *(float *)(iVar2 + 0xc);
  }
  *(float *)(iVar2 + 0x10) = fVar7;
  this->_padding_ = *(int *)(this->_padding_ + 0xc);
  this->_padding_ = *(int *)(this->_padding_ + 0x10);
  fVar7 = NetUtil_ExpandSmallFloat(*(uchar *)((int)param_1 + 0xc));
  *(float *)(this->_padding_ + 0xd0) = fVar7;
  fVar7 = NetUtil_ExpandSmallFloat(*(uchar *)((int)param_1 + 0xd));
  *(float *)(this->_padding_ + 0xc4) = fVar7;
  fVar7 = NetUtil_ExpandSmallFloat(*(uchar *)((int)param_1 + 0xe));
  *(float *)(this->_padding_ + 200) = fVar7;
  fVar7 = NetUtil_ExpandSmallFloat(*(uchar *)((int)param_1 + 0xf));
  *(float *)(this->_padding_ + 0xcc) = fVar7;
  *(uint *)(this->_padding_ + 0xd4) = *(byte *)((int)param_1 + 0x10) & 1;
  *(undefined4 *)(this->_padding_ + 0x10c) = 0;
  if ((*(byte *)((int)param_1 + 0x10) & 2) != 0) {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 | 0x8000;
  }
  if ((*(byte *)((int)param_1 + 0x10) & 4) != 0) {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 | 0x20;
  }
  if ((*(byte *)((int)param_1 + 0x10) & 8) != 0) {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 | 1;
  }
  if ((*(byte *)((int)param_1 + 0x10) & 0x10) != 0) {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 | 4;
  }
  if ((*(byte *)((int)param_1 + 0x10) & 0x20) != 0) {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 | 8;
  }
  fVar7 = (float)*(byte *)((int)param_1 + 0x11) * 0.003921569;
  this->_padding_ = (int)fVar7;
  GameObject::SetCurHealth((GameObject *)&this[-1]._padding_,fVar7 * (float)this->_padding_);
  if ((*(byte *)((int)param_1 + 0x10) & 0x80) != 0) {
    obj_set_flag((_OBJ76 *)this->_padding_,0x1000080);
    DistributedObject::SetLocal((DistributedObject *)this);
  }
  *param_2 = *param_2 - 0x12;
  return;
}
