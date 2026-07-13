/*
 * Entry: 004af8b3
 * Name: ScrapDropoffClass::BuildClass
 * Namespace: ScrapDropoffClass
 * Signature: GameObjectClass * BuildClass(ScrapDropoffClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall ScrapDropoffClass::BuildClass(ScrapDropoffClass *this,long64 param_1)

{
  ScrapDropoffClass *pSVar1;
  undefined4 unaff_ESI;
  
  pSVar1 = operator_new(0x170);
  if (pSVar1 == (ScrapDropoffClass *)0x0) {
    pSVar1 = (ScrapDropoffClass *)0x0;
  }
  else {
    pSVar1 = ScrapDropoffClass(pSVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pSVar1;
}
