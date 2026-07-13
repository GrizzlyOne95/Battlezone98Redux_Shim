/*
 * Entry: 004afdfc
 * Name: ScrapFieldClass::Build
 * Namespace: ScrapFieldClass
 * Signature: GameObject * Build(ScrapFieldClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall ScrapFieldClass::Build(ScrapFieldClass *this,_OBJ76 *param_1)

{
  ScrapField *pSVar1;
  
  pSVar1 = GameObject::operator_new(0x230);
  if (pSVar1 == (ScrapField *)0x0) {
    pSVar1 = (ScrapField *)0x0;
  }
  else {
    pSVar1 = ScrapField::ScrapField(pSVar1,param_1,this);
  }
  return (GameObject *)pSVar1;
}
