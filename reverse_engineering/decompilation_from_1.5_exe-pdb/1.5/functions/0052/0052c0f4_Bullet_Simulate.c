/*
 * Entry: 0052c0f4
 * Name: Bullet::Simulate
 * Namespace: Bullet
 * Signature: void Simulate(Bullet * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Bullet::Simulate(Bullet *this,float param_1)

{
  uint *puVar1;
  float fVar2;
  VECTOR_3D_LONG VVar3;
  VECTOR_3D VVar4;
  _OBJ76 *p_Var5;
  int iVar6;
  VECTOR_3D_LONG local_48;
  double local_30;
  double local_28;
  double local_20;
  VECTOR_3D local_18;
  float local_c;
  bool local_5;
  
  if ((float)this->_padding_ < param_1) {
    param_1 = (float)this->_padding_;
  }
  fVar2 = (float)this->_padding_ - param_1;
  this->_padding_ = (int)fVar2;
  if (fVar2 <= 0.0) {
    puVar1 = (uint *)(this->_padding_ + 0x14);
    *puVar1 = *puVar1 | 0x200;
  }
  iVar6 = this->_padding_;
  local_30 = *(double *)(iVar6 + 0x48);
  local_28 = *(double *)(iVar6 + 0x50);
  local_20 = *(double *)(iVar6 + 0x58);
  Terrain_GetHeightAndNormal(local_30,local_20,&local_c,&local_18);
  if ((local_c <= (float)local_28) ||
     (0.0 <= (float)this->_padding_ * local_18.x +
             (float)this->_padding_ * local_18.z + (float)this->_padding_ * local_18.y)) {
    VVar4.x = (float)this->_padding_;
    VVar4.y = (float)this->_padding_;
    VVar4.z = (float)this->_padding_;
    VVar3.y = local_28;
    VVar3.x = local_30;
    VVar3.z._0_4_ = SUB84(local_20,0);
    VVar3.z._4_4_ = (int)((ulonglong)local_20 >> 0x20);
    iVar6 = Terrain_GetIntersection(VVar3,VVar4,&param_1,&local_18);
    local_5 = iVar6 != 0;
  }
  else {
    param_1 = 0.0;
    local_5 = true;
    local_28 = (double)local_c;
  }
  local_48.x = (double)(param_1 * (float)this->_padding_ + (float)local_30);
  local_48.y = (double)((float)this->_padding_ * param_1 + (float)local_28);
  local_48.z = (double)((float)this->_padding_ * param_1 + (float)local_20);
  p_Var5 = Collision(this,&param_1,&local_48,&local_18);
  *(double *)(this->_padding_ + 0x48) = local_48.x;
  *(double *)(this->_padding_ + 0x50) = local_48.y;
  *(double *)(this->_padding_ + 0x58) = local_48.z;
  if (p_Var5 == (_OBJ76 *)0x0) {
    if (local_5 == false) {
      iVar6 = Terrain_ValidPoint(local_48.x,local_48.z);
      if (iVar6 == 0) {
        puVar1 = (uint *)(this->_padding_ + 0x14);
        *puVar1 = *puVar1 | 0x200;
      }
    }
    else {
      (**(code **)(this->_padding_ + 0x14))(0,&local_18);
    }
  }
  else {
    (**(code **)(this->_padding_ + 0x14))(p_Var5->gameObj,&local_18);
  }
  return;
}
