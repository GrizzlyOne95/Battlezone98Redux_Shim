/*
 * Entry: 00537dee
 * Name: Rocket::Rocket
 * Namespace: Rocket
 * Signature: Rocket * Rocket(Rocket * this, _OBJ76 * param_1, RocketClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Rocket * __thiscall Rocket::Rocket(Rocket *this,_OBJ76 *param_1,RocketClass *param_2)

{
  SmokeEmitter *pSVar1;
  
  Bullet::Bullet((Bullet *)this,param_1,(BulletClass *)param_2);
  this->_padding_ = (int)&_vftable_;
  if (param_2->smokeCount < 1) {
    this->smokeEmitter = (SmokeEmitter *)0x0;
  }
  else {
    pSVar1 = SmokeEffect::AddEmitter
                       (&smokeEffect,param_2->smokeIndex,param_2->smokeCount,param_2->smokeRate,
                        param_2->smokeRadius,1.0);
    this->smokeEmitter = pSVar1;
  }
  return this;
}
