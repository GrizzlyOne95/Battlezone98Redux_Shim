/*
 * Entry: 0052e7ee
 * Name: ExplosionClass::Build
 * Namespace: ExplosionClass
 * Signature: Explosion * Build(ExplosionClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Explosion * __thiscall ExplosionClass::Build(ExplosionClass *this,_OBJ76 *param_1)

{
  Explosion *pEVar1;
  
  pEVar1 = operator_new(0x38);
  if (pEVar1 == (Explosion *)0x0) {
    pEVar1 = (Explosion *)0x0;
  }
  else {
    pEVar1 = Explosion::Explosion(pEVar1,param_1,this);
  }
  return pEVar1;
}
