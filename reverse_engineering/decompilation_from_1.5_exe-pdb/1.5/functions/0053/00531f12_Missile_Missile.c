/*
 * Entry: 00531f12
 * Name: Missile::Missile
 * Namespace: Missile
 * Signature: Missile * Missile(Missile * this, _OBJ76 * param_1, MissileClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Missile * __thiscall Missile::Missile(Missile *this,_OBJ76 *param_1,MissileClass *param_2)

{
  Rocket::Rocket((Rocket *)this,param_1,(RocketClass *)param_2);
  this->targetHandle = 0;
  this->_padding_ = (int)&_vftable_;
  return this;
}
