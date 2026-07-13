/*
 * Entry: 004ada06
 * Name: SAVClass::Build
 * Namespace: SAVClass
 * Signature: GameObject * Build(SAVClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall SAVClass::Build(SAVClass *this,_OBJ76 *param_1)

{
  SAV *pSVar1;
  
  pSVar1 = GameObject::operator_new(0x2c8);
  if (pSVar1 == (SAV *)0x0) {
    pSVar1 = (SAV *)0x0;
  }
  else {
    pSVar1 = SAV::SAV(pSVar1,param_1,this);
  }
  return (GameObject *)pSVar1;
}
