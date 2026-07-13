/*
 * Entry: 00537e53
 * Name: Rocket::Init
 * Namespace: Rocket
 * Signature: void Init(Rocket * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Rocket::Init(Rocket *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  uint *puVar1;
  
  Bullet::Init((Bullet *)this,param_1,param_2);
  puVar1 = (uint *)(this->_padding_ + 0x14);
  *puVar1 = *puVar1 | 8;
  this->smokeTimer = 0.0;
  return;
}
