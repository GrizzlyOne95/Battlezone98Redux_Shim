/*
 * Entry: 0049afac
 * Name: GeizerClass::Build
 * Namespace: GeizerClass
 * Signature: GameObject * Build(GeizerClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall GeizerClass::Build(GeizerClass *this,_OBJ76 *param_1)

{
  Geizer *pGVar1;
  
  pGVar1 = GameObject::operator_new(0x240);
  if (pGVar1 == (Geizer *)0x0) {
    pGVar1 = (Geizer *)0x0;
  }
  else {
    pGVar1 = Geizer::Geizer(pGVar1,param_1,this);
  }
  return (GameObject *)pGVar1;
}
