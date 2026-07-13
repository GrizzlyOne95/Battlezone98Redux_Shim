/*
 * Entry: 0052ad2a
 * Name: Bolt::Bolt
 * Namespace: Bolt
 * Signature: Bolt * Bolt(Bolt * this, _OBJ76 * param_1, BoltClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Bolt * __thiscall Bolt::Bolt(Bolt *this,_OBJ76 *param_1,BoltClass *param_2)

{
  Bullet::Bullet((Bullet *)this,param_1,(BulletClass *)param_2);
  this->_padding_ = (int)&_vftable_;
  this->radius = SQRT(param_2->segmentLength * param_2->segmentLength * 0.25 +
                      param_2->segmentRadius * param_2->segmentRadius +
                      param_2->segmentVariance * param_2->segmentVariance);
  if (param_1->geom == (_GEOMETRY *)0x0) {
    (param_1->bSphere).radius = param_2->segmentRadius;
  }
  return this;
}
