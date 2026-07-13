/*
 * Entry: 0053da18
 * Name: Tracer::~Tracer
 * Namespace: Tracer
 * Signature: void ~Tracer(Tracer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tracer::~Tracer(Tracer *this)

{
  this->_padding_ = (int)&_vftable_;
  Bullet::~Bullet((Bullet *)this);
  return;
}
