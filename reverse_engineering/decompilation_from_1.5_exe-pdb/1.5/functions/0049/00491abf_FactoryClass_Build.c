/*
 * Entry: 00491abf
 * Name: FactoryClass::Build
 * Namespace: FactoryClass
 * Signature: GameObject * Build(FactoryClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall FactoryClass::Build(FactoryClass *this,_OBJ76 *param_1)

{
  Factory *pFVar1;
  
  pFVar1 = GameObject::operator_new(0x318);
  if (pFVar1 == (Factory *)0x0) {
    pFVar1 = (Factory *)0x0;
  }
  else {
    pFVar1 = Factory::Factory(pFVar1,param_1,this);
  }
  return (GameObject *)pFVar1;
}
