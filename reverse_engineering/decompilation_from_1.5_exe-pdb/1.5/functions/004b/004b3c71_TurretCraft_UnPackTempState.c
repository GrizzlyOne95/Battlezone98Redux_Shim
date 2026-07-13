/*
 * Entry: 004b3c71
 * Name: TurretCraft::UnPackTempState
 * Namespace: TurretCraft
 * Signature: void UnPackTempState(TurretCraft * this, void * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretCraft::UnPackTempState(TurretCraft *this,void *param_1,uint *param_2)

{
  uint *puVar1;
  int iVar2;
  VECTOR_3D *pVVar3;
  float fVar4;
  VECTOR_3D local_1c;
  float local_10;
  float fStack_c;
  float fStack_8;
  
  pVVar3 = NetUtil_ExpandVector(&local_1c,*(REDUCED_VEC *)param_1);
  local_10 = pVVar3->x;
  fStack_c = pVVar3->y;
  fStack_8 = pVVar3->z;
  iVar2 = this->_padding_;
  *(float *)(iVar2 + 0x28) = local_10;
  *(float *)(iVar2 + 0x2c) = fStack_c;
  *(float *)(iVar2 + 0x30) = fStack_8;
  iVar2 = this->_padding_;
  this->_padding_ = *(int *)(iVar2 + 0x28);
  this->_padding_ = *(int *)(iVar2 + 0x2c);
  this->_padding_ = *(int *)(iVar2 + 0x30);
  fVar4 = NetUtil_ExpandSmallFloat(*(uchar *)((int)param_1 + 6));
  *(float *)(this->_padding_ + 0xc4) = fVar4;
  fVar4 = NetUtil_ExpandSmallFloat(*(uchar *)((int)param_1 + 7));
  *(float *)(this->_padding_ + 200) = fVar4;
  *(uint *)(this->_padding_ + 0xd8) = *(byte *)((int)param_1 + 8) & 1;
  *(uint *)(this->_padding_ + 0xd4) = *(byte *)((int)param_1 + 8) >> 1 & 1;
  *(uint *)(this->_padding_ + 0xdc) = *(byte *)((int)param_1 + 8) >> 2 & 1;
  if ((*(byte *)((int)param_1 + 8) & 8) == 0) {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 & 0xffffffdf;
  }
  else {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 | 0x20;
  }
  if ((*(byte *)((int)param_1 + 8) & 0x40) == 0) {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 & 0xffffefff;
  }
  else {
    puVar1 = (uint *)(this->_padding_ + 0x10c);
    *puVar1 = *puVar1 | 0x1000;
  }
  *param_2 = *param_2 - 10;
  Craft::UnPackTempState((Craft *)this,(void *)((int)param_1 + 10),param_2);
  return;
}
