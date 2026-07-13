/*
 * Entry: 004b0975
 * Name: ScrapSiloClass::Build
 * Namespace: ScrapSiloClass
 * Signature: GameObject * Build(ScrapSiloClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall ScrapSiloClass::Build(ScrapSiloClass *this,_OBJ76 *param_1)

{
  ScrapSilo *pSVar1;
  
  pSVar1 = GameObject::operator_new(0x238);
  if (pSVar1 == (ScrapSilo *)0x0) {
    pSVar1 = (ScrapSilo *)0x0;
  }
  else {
    pSVar1 = ScrapSilo::ScrapSilo(pSVar1,param_1,this);
  }
  return (GameObject *)pSVar1;
}
