/*
 * Entry: 00529f7b
 * Name: Beam::Beam
 * Namespace: Beam
 * Signature: Beam * Beam(Beam * this, _OBJ76 * param_1, BeamClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Beam * __thiscall Beam::Beam(Beam *this,_OBJ76 *param_1,BeamClass *param_2)

{
  Bullet::Bullet((Bullet *)this,param_1,(BulletClass *)param_2);
  this->_padding_ = (int)&_vftable_;
  this->radius = SQRT(param_2->segmentLength * param_2->segmentLength * 0.25 +
                      param_2->segmentRadius * param_2->segmentRadius +
                      param_2->segmentVariance * param_2->segmentVariance);
  if (param_1->geom == (_GEOMETRY *)0x0) {
    (param_1->bSphere).radius = param_2->segmentRadius;
  }
  this->hardpoint = -1;
  return this;
}
