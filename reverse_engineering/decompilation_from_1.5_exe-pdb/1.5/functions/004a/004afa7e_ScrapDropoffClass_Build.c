/*
 * Entry: 004afa7e
 * Name: ScrapDropoffClass::Build
 * Namespace: ScrapDropoffClass
 * Signature: GameObject * Build(ScrapDropoffClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall ScrapDropoffClass::Build(ScrapDropoffClass *this,_OBJ76 *param_1)

{
  ScrapDropoff *pSVar1;
  
  pSVar1 = GameObject::operator_new(0x228);
  if (pSVar1 == (ScrapDropoff *)0x0) {
    pSVar1 = (ScrapDropoff *)0x0;
  }
  else {
    pSVar1 = ScrapDropoff::ScrapDropoff(pSVar1,param_1,this);
  }
  return (GameObject *)pSVar1;
}
