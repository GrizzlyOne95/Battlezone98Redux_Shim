/*
 * Entry: 00535e6a
 * Name: PlanarExplosionClass::PlanarExplosionClass
 * Namespace: PlanarExplosionClass
 * Signature: PlanarExplosionClass * PlanarExplosionClass(PlanarExplosionClass * this, PlanarExplosionClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PlanarExplosionClass * __thiscall
PlanarExplosionClass::PlanarExplosionClass
          (PlanarExplosionClass *this,PlanarExplosionClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  ExplosionClass::ExplosionClass
            ((ExplosionClass *)this,(ExplosionClass *)param_1,
             CONCAT44(unaff_ESI,(undefined4)param_2));
  *(undefined ***)this = &_vftable_;
  return this;
}
