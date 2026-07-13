/*
 * Entry: 004af73b
 * Name: ScrapClass::Build
 * Namespace: ScrapClass
 * Signature: GameObject * Build(ScrapClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall ScrapClass::Build(ScrapClass *this,_OBJ76 *param_1)

{
  Scrap *pSVar1;
  
  pSVar1 = GameObject::operator_new(0x238);
  if (pSVar1 == (Scrap *)0x0) {
    pSVar1 = (Scrap *)0x0;
  }
  else {
    pSVar1 = Scrap::Scrap(pSVar1,param_1,this);
  }
  return (GameObject *)pSVar1;
}
