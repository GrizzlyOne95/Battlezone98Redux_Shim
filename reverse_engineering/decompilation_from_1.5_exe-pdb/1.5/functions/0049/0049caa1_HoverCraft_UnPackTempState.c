/*
 * Entry: 0049caa1
 * Name: HoverCraft::UnPackTempState
 * Namespace: HoverCraft
 * Signature: void UnPackTempState(HoverCraft * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HoverCraft::UnPackTempState(HoverCraft *this,void *param_1,uint *param_2)

{
  uint *puVar1;
  int *piVar2;
  int iVar3;
  VECTOR_3D VVar4;
  REDUCED_VEC RVar5;
  REDUCED_VEC RVar6;
  VECTOR_3D *pVVar7;
  float fVar8;
  VECTOR_3D local_1c;
  float local_10;
  float fStack_c;
  float fStack_8;
  
  RVar5.z._1_1_ = (char)((ushort)*(undefined2 *)((int)param_1 + 4) >> 8);
  RVar5._0_5_ = *(undefined5 *)param_1;
  pVVar7 = NetUtil_ExpandVector(&local_1c,RVar5);
  local_10 = pVVar7->x;
  fStack_c = pVVar7->y;
  fStack_8 = pVVar7->z;
  iVar3 = this->_padding_;
  *(float *)(iVar3 + 0x1c) = local_10;
  *(float *)(iVar3 + 0x20) = fStack_c;
  *(float *)(iVar3 + 0x24) = fStack_8;
  iVar3 = this->_padding_;
  this->_padding_ = *(int *)(iVar3 + 0x1c);
  this->_padding_ = *(int *)(iVar3 + 0x20);
  this->_padding_ = *(int *)(iVar3 + 0x24);
  RVar6.z._1_1_ = (char)((ushort)*(undefined2 *)((int)param_1 + 10) >> 8);
  RVar6._0_5_ = *(undefined5 *)((int)param_1 + 6);
  pVVar7 = NetUtil_ExpandVector(&local_1c,RVar6);
  local_10 = pVVar7->x;
  fStack_c = pVVar7->y;
  fStack_8 = pVVar7->z;
  iVar3 = this->_padding_;
  *(float *)(iVar3 + 0x28) = local_10;
  *(float *)(iVar3 + 0x2c) = fStack_c;
  *(float *)(iVar3 + 0x30) = fStack_8;
  iVar3 = this->_padding_;
  this->_padding_ = *(int *)(iVar3 + 0x28);
  this->_padding_ = *(int *)(iVar3 + 0x2c);
  this->_padding_ = *(int *)(iVar3 + 0x30);
  VVar4.z._1_1_ = (char)((uint)this->_padding_ >> 8);
  VVar4._0_9_ = *(unkbyte9 *)&this->_padding_;
  VVar4.z._2_2_ = (short)((uint)this->_padding_ >> 0x10);
  fVar8 = VecLen(VVar4);
  *(float *)(this->_padding_ + 0xc) = fVar8;
  iVar3 = this->_padding_;
  if (*(float *)(iVar3 + 0xc) <= 0.0) {
    fVar8 = 1e+30;
  }
  else {
    fVar8 = 1.0 / *(float *)(iVar3 + 0xc);
  }
  *(float *)(iVar3 + 0x10) = fVar8;
  iVar3 = this->_padding_;
  this->_padding_ = *(int *)(iVar3 + 0xc);
  this->_padding_ = *(int *)(iVar3 + 0x10);
  *(uint *)(iVar3 + 0xd8) = *(byte *)((int)param_1 + 0x10) & 1;
  *(uint *)(this->_padding_ + 0xd4) = *(byte *)((int)param_1 + 0x10) >> 1 & 1;
  *(uint *)(this->_padding_ + 0xdc) = *(byte *)((int)param_1 + 0x10) >> 2 & 1;
  if ((*(byte *)((int)param_1 + 0x10) & 8) == 0) {
    piVar2 = &this->_padding_;
    if ((*(byte *)((int)param_1 + 0x10) & 0x10) == 0) {
      obj_clear_flag((_OBJ76 *)*piVar2,1);
      *(uint *)(*piVar2 + 0x14) = *(uint *)(*piVar2 + 0x14) & 0xfffffbff;
    }
    else {
      obj_set_flag((_OBJ76 *)*piVar2,1);
      *(uint *)(*piVar2 + 0x14) = *(uint *)(*piVar2 + 0x14) & 0xfffffffe;
      *(uint *)(*piVar2 + 0x14) = *(uint *)(*piVar2 + 0x14) | 0x400;
    }
  }
  else {
    puVar1 = (uint *)(this->_padding_ + 0x14);
    *puVar1 = *puVar1 | 1;
  }
  if ((*(byte *)((int)param_1 + 0x10) & 0x40) == 0) {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 & 0xffffefff;
  }
  else {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 | 0x1000;
  }
  fVar8 = NetUtil_ExpandSmallFloat(*(uchar *)((int)param_1 + 0xc));
  *(float *)(this->_padding_ + 0xc4) = fVar8;
  fVar8 = NetUtil_ExpandSmallFloat(*(uchar *)((int)param_1 + 0xd));
  *(float *)(this->_padding_ + 200) = fVar8;
  fVar8 = NetUtil_ExpandSmallFloat(*(uchar *)((int)param_1 + 0xe));
  *(float *)(this->_padding_ + 0xcc) = fVar8;
  fVar8 = NetUtil_ExpandSmallFloat(*(uchar *)((int)param_1 + 0xf));
  *(float *)(this->_padding_ + 0xd0) = fVar8;
  *param_2 = *param_2 - 0x12;
  Craft::UnPackTempState((Craft *)this,(void *)((int)param_1 + 0x12),param_2);
  return;
}
