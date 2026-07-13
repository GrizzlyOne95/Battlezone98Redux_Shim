/*
 * Entry: 0052da19
 * Name: ExplosionFeature::ExplosionFeature
 * Namespace: ExplosionFeature
 * Signature: ExplosionFeature * ExplosionFeature(ExplosionFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionFeature * __thiscall ExplosionFeature::ExplosionFeature(ExplosionFeature *this)

{
  GameFeature::GameFeature((GameFeature *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
