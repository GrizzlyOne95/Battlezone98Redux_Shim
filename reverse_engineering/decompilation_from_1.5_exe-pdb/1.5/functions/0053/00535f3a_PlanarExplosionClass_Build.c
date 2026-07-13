/*
 * Entry: 00535f3a
 * Name: PlanarExplosionClass::Build
 * Namespace: PlanarExplosionClass
 * Signature: Explosion * Build(PlanarExplosionClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Explosion * __thiscall PlanarExplosionClass::Build(PlanarExplosionClass *this,_OBJ76 *param_1)

{
  PlanarExplosion *pPVar1;
  
  pPVar1 = operator_new(0x3c);
  if (pPVar1 == (PlanarExplosion *)0x0) {
    pPVar1 = (PlanarExplosion *)0x0;
  }
  else {
    pPVar1 = PlanarExplosion::PlanarExplosion(pPVar1,param_1,this);
  }
  return (Explosion *)pPVar1;
}
