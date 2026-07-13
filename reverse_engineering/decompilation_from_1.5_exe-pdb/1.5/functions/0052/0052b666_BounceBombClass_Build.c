/*
 * Entry: 0052b666
 * Name: BounceBombClass::Build
 * Namespace: BounceBombClass
 * Signature: Ordnance * Build(BounceBombClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance * __thiscall BounceBombClass::Build(BounceBombClass *this,_OBJ76 *param_1)

{
  BounceBomb *pBVar1;
  
  pBVar1 = operator_new(0xe8);
  if (pBVar1 == (BounceBomb *)0x0) {
    pBVar1 = (BounceBomb *)0x0;
  }
  else {
    pBVar1 = BounceBomb::BounceBomb(pBVar1,param_1,this);
  }
  return (Ordnance *)pBVar1;
}
