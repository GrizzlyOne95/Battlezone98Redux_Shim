/*
 * Entry: 00535e8a
 * Name: PlanarExplosionClass::~PlanarExplosionClass
 * Namespace: PlanarExplosionClass
 * Signature: void ~PlanarExplosionClass(PlanarExplosionClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlanarExplosionClass::~PlanarExplosionClass(PlanarExplosionClass *this)

{
  *(undefined ***)this = &_vftable_;
  ExplosionClass::~ExplosionClass((ExplosionClass *)this);
  return;
}
