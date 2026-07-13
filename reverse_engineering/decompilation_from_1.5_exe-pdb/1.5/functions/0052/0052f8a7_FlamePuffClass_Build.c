/*
 * Entry: 0052f8a7
 * Name: FlamePuffClass::Build
 * Namespace: FlamePuffClass
 * Signature: Ordnance * Build(FlamePuffClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall FlamePuffClass::Build(FlamePuffClass *this,_OBJ76 *param_1)

{
  FlamePuff *pFVar1;
  
  pFVar1 = operator_new(0xe8);
  if (pFVar1 == (FlamePuff *)0x0) {
    pFVar1 = (FlamePuff *)0x0;
  }
  else {
    pFVar1 = FlamePuff::FlamePuff(pFVar1,param_1,this);
  }
  return (Ordnance *)pFVar1;
}
