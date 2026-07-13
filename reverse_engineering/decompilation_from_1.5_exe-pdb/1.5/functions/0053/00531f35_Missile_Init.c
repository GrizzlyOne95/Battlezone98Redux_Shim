/*
 * Entry: 00531f35
 * Name: Missile::Init
 * Namespace: Missile
 * Signature: void Init(Missile * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Missile::Init(Missile *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  Rocket::Init((Rocket *)this,param_1,param_2);
  if ((((_OBJ76 *)this->_padding_)->flags & 0x10) != 0) {
    userMissile = (_OBJ76 *)this->_padding_;
  }
  this->targetHandle = 0;
  return;
}
