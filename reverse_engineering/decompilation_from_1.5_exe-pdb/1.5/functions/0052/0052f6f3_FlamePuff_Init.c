/*
 * Entry: 0052f6f3
 * Name: FlamePuff::Init
 * Namespace: FlamePuff
 * Signature: void Init(FlamePuff * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FlamePuff::Init(FlamePuff *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  int iVar1;
  
  Bullet::Init((Bullet *)this,param_1,param_2);
  iVar1 = *(int *)(this->_padding_ + 0x78);
  this->frameTimer = 0.0;
  this->flameIndex = iVar1;
  return;
}
