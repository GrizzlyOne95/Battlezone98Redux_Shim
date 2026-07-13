/*
 * Entry: 0052bb66
 * Name: Bullet::Init
 * Namespace: Bullet
 * Signature: void Init(Bullet * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Bullet::Init(Bullet *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  VECTOR_3D *pVVar4;
  VECTOR_3D local_1c;
  float local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  Ordnance::Init((Ordnance *)this,param_1,param_2);
  iVar3 = this->_padding_;
  local_10 = ((VECTOR_3D *)(iVar3 + 0x38))->x;
  local_c = *(undefined4 *)(iVar3 + 0x3c);
  local_8 = *(undefined4 *)(iVar3 + 0x40);
  pVVar4 = ScaleVector(&local_1c,*(float *)(this->_padding_ + 0x50),*(VECTOR_3D *)(iVar3 + 0x38));
  fVar1 = pVVar4->y;
  fVar2 = pVVar4->z;
  this->_padding_ = (int)pVVar4->x;
  this->_padding_ = (int)fVar1;
  this->_padding_ = (int)fVar2;
  fVar1 = *(float *)(this->_padding_ + 0x50);
  this->_padding_ = (int)fVar1;
  if (fVar1 <= 0.0) {
    fVar1 = 1e+30;
  }
  else {
    fVar1 = 1.0 / fVar1;
  }
  this->_padding_ = (int)fVar1;
  this->noHitOwner = true;
  return;
}
