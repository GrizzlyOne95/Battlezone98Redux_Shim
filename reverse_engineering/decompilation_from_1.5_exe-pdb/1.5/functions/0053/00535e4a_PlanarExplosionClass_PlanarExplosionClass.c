/*
 * Entry: 00535e4a
 * Name: PlanarExplosionClass::PlanarExplosionClass
 * Namespace: PlanarExplosionClass
 * Signature: PlanarExplosionClass * PlanarExplosionClass(PlanarExplosionClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PlanarExplosionClass * __thiscall
PlanarExplosionClass::PlanarExplosionClass(PlanarExplosionClass *this)

{
  ExplosionClass::ExplosionClass((ExplosionClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x8 = 0x504c4e58;
  *(char **)&this->field_0xc = "planarexpl";
  return this;
}
