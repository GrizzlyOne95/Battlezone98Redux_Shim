/*
 * Entry: 004ad460
 * Name: SAV::Simulate
 * Namespace: SAV
 * Signature: void Simulate(SAV * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SAV::Simulate(SAV *this,float param_1)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  _OBJ76 *p_Var4;
  float fVar5;
  bool bVar6;
  VECTOR_3D *pVVar7;
  int *piVar8;
  float fVar9;
  float fVar10;
  VECTOR_3D local_44;
  undefined8 local_38;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  MAT_3D *local_10;
  float local_c;
  float local_8;
  
  iVar2 = this->_padding_;
  iVar3 = this->_padding_;
  if (*(int *)(iVar3 + 0xd4) == 0) {
    local_8 = *(float *)(iVar3 + 0xd0);
  }
  else {
    local_8 = 2.0;
  }
  local_38 = (double)CONCAT44(*(undefined4 *)(iVar3 + 0xcc),(undefined4)local_38);
  local_18 = *(float *)(iVar3 + 0xc4);
  local_10 = (MAT_3D *)(iVar2 + 0x20);
  fVar9 = GetPerformance((float)this->_padding_);
  iVar3 = this->_padding_;
  local_24 = *(float *)(iVar3 + 0x334) * fVar9;
  local_20 = *(float *)(iVar3 + 0x338) * fVar9;
  local_28 = *(float *)(iVar3 + 0x300) * fVar9;
  local_2c = *(float *)(iVar3 + 0x304) * fVar9;
  local_14 = *(float *)(iVar3 + 0x308) * fVar9;
  local_30 = *(float *)(iVar3 + 0x30c) * fVar9;
  fVar10 = *(float *)(iVar3 + 0x314) * fVar9;
  local_c = *(float *)(iVar3 + 0x31c) * fVar9;
  local_1c = *(float *)(iVar3 + 800) * fVar9;
  fVar5 = local_8 * local_8;
  if (1.0 < fVar5) {
    fVar5 = 1.0;
  }
  fVar10 = (*(float *)(iVar3 + 0x318) * fVar9 - fVar10) * fVar5 + fVar10;
  if (0.0 < fVar10) {
    fVar10 = Clamp(local_18 - (float)this->_padding_ / fVar10,-1.0,1.0);
    this->_padding_ = (int)(fVar10 * local_c * param_1 + (float)this->_padding_);
  }
  fVar5 = (float)this->_padding_ - (float)this->_padding_ * local_20 * param_1;
  this->_padding_ = (int)fVar5;
  fVar10 = (float)this->_padding_ - (float)this->_padding_ * local_20 * param_1;
  this->_padding_ = (int)fVar10;
  this->_padding_ = (int)(fVar5 - local_24 * param_1 * *(float *)(iVar2 + 0x3c));
  this->_padding_ = (int)(fVar10 + *(float *)(iVar2 + 0x24) * local_24 * param_1);
  pVVar7 = Vector_Unrotate(&local_44,(VECTOR_3D *)&this->_padding_,(MAT_3D *)(iVar2 + 0x20));
  this->_padding_ = (int)pVVar7->x;
  this->_padding_ = (int)pVVar7->y;
  this->_padding_ = (int)pVVar7->z;
  local_c = local_2c;
  if (0.0 < local_8) {
    local_c = local_28;
  }
  local_18 = local_30 * param_1;
  if (0.0 < local_14) {
    piVar8 = &this->_padding_;
    fVar10 = Clamp(local_38._4_4_ - (float)*piVar8 / local_14,-1.0,1.0);
    *piVar8 = (int)(fVar10 * local_18 + (float)*piVar8);
  }
  if (0.0 < local_c) {
    fVar10 = Clamp(local_8 - (float)this->_padding_ / local_c,-1.0,1.0);
    this->_padding_ = (int)(fVar10 * local_18 + (float)this->_padding_);
  }
  if ((*(uint *)(this->_padding_ + 0x14) & 0x200) == 0) {
    fVar10 = SQRT(local_1c * 0.025) * (float)this->_padding_ * param_1;
    this->_padding_ = (int)((float)this->_padding_ - (fVar10 + fVar10));
  }
  pVVar7 = Vector_Rotate(&local_44,(VECTOR_3D *)&this->_padding_,local_10);
  this->_padding_ = (int)pVVar7->x;
  this->_padding_ = (int)pVVar7->y;
  this->_padding_ = (int)pVVar7->z;
  local_38 = (double)((float)local_10->posit_y - this->setAltitude);
  fVar10 = Terrain_FindFloor(local_10->posit_x,local_10->posit_z);
  fVar10 = (float)local_38 - fVar10;
  p_Var4 = (_OBJ76 *)this->_padding_;
  local_38._4_4_ = fVar10;
  if ((p_Var4->flags & 0x200) == 0) {
    fVar10 = Clamp(fVar10 * -0.025,-1.0,1.0);
    this->_padding_ = (int)(fVar10 * local_1c * param_1 + (float)this->_padding_);
  }
  else {
    this->_padding_ = (int)((float)this->_padding_ - param_1 * 9.8);
  }
  iVar2 = this->_padding_;
  if (iVar2 == 0) {
LAB_004ad86b:
    piVar8 = (int *)(this->_padding_ + 0xe0);
    if (*piVar8 != 0) {
      *piVar8 = 0;
      this->_padding_ = 1;
      DoAudioNew((char *)(this->_padding_ + 0x39c),(_OBJ76 *)this->_padding_,(GAS_CTRL *)0x0);
      this->setAltitude = *(float *)(this->_padding_ + 0x3c0);
      this->_padding_ = 3;
    }
  }
  else {
    if (iVar2 == 1) {
      if ((-40.0 < local_38._4_4_) && (local_38._4_4_ < 1.0)) {
        this->_padding_ = 2;
        p_Var4->flags = p_Var4->flags | 1;
      }
      if (*(int *)(this->_padding_ + 0xe0) == 0) goto LAB_004ad8c1;
    }
    else if (iVar2 != 2) {
      if (iVar2 != 3) goto LAB_004ad8c1;
      if ((-1.0 < local_38._4_4_) && (local_38._4_4_ < 40.0)) {
        this->_padding_ = 0;
        DoAudioNew((char *)(this->_padding_ + 0x3ac),p_Var4,(GAS_CTRL *)0x0);
        this->_padding_ = 0;
      }
      if (*(int *)(this->_padding_ + 0xe0) == 0) goto LAB_004ad8c1;
      goto LAB_004ad86b;
    }
    piVar8 = (int *)(this->_padding_ + 0xe0);
    if (*piVar8 != 0) {
      *piVar8 = 0;
      this->_padding_ = 3;
      this->setAltitude = *(float *)(this->_padding_ + 0x324);
      puVar1 = (uint *)(this->_padding_ + 0x14);
      *puVar1 = *puVar1 & 0xfffffffe;
    }
  }
LAB_004ad8c1:
  this->_padding_ = (int)(*(float *)(this->_padding_ + 200) * 0.5);
  if ((((*(byte *)(this->_padding_ + 0x14) & 0x10) != 0) &&
      ((UserProfilePtr->playOption & 0x10) != 0)) ||
     ((bVar6 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_), bVar6 &&
      ((*(uint *)(this->_padding_ + 0x10c) & 0x1000) != 0)))) {
    this->_padding_ = (int)((float)this->_padding_ - local_10->front_y);
  }
  (**(code **)(this->_padding_ + 0x98))(param_1);
  Craft::Simulate((Craft *)this,param_1);
  return;
}
