/*
 * Entry: 0052f6bd
 * Name: FlamePuff::FlamePuff
 * Namespace: FlamePuff
 * Signature: FlamePuff * FlamePuff(FlamePuff * this, _OBJ76 * param_1, FlamePuffClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FlamePuff * __thiscall FlamePuff::FlamePuff(FlamePuff *this,_OBJ76 *param_1,FlamePuffClass *param_2)

{
  Bullet::Bullet((Bullet *)this,param_1,(BulletClass *)param_2);
  this->_padding_ = (int)&_vftable_;
  (param_1->bSphere).radius = param_2->flameRadius;
  return this;
}
