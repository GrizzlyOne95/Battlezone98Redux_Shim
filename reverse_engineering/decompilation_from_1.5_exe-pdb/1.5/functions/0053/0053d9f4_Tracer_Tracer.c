/*
 * Entry: 0053d9f4
 * Name: Tracer::Tracer
 * Namespace: Tracer
 * Signature: Tracer * Tracer(Tracer * this, _OBJ76 * param_1, TracerClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Tracer * __thiscall Tracer::Tracer(Tracer *this,_OBJ76 *param_1,TracerClass *param_2)

{
  Bullet::Bullet((Bullet *)this,param_1,(BulletClass *)param_2);
  this->shotDistance = 0.0;
  this->_padding_ = (int)&_vftable_;
  return this;
}
