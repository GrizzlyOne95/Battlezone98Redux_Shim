/*
 * Entry: 0053ab77
 * Name: SprayBombClass::Build
 * Namespace: SprayBombClass
 * Signature: Ordnance * Build(SprayBombClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall SprayBombClass::Build(SprayBombClass *this,_OBJ76 *param_1)

{
  SprayBomb *pSVar1;
  
  pSVar1 = operator_new(0xe8);
  if (pSVar1 == (SprayBomb *)0x0) {
    pSVar1 = (SprayBomb *)0x0;
  }
  else {
    pSVar1 = SprayBomb::SprayBomb(pSVar1,param_1,this);
  }
  return (Ordnance *)pSVar1;
}
