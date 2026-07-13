/*
 * Entry: 004a7fdb
 * Name: PersonClass::BuildClass
 * Namespace: PersonClass
 * Signature: GameObjectClass * BuildClass(PersonClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall PersonClass::BuildClass(PersonClass *this,long64 param_1)

{
  PersonClass *pPVar1;
  undefined4 unaff_ESI;
  
  pPVar1 = operator_new(0x4b0);
  if (pPVar1 == (PersonClass *)0x0) {
    pPVar1 = (PersonClass *)0x0;
  }
  else {
    pPVar1 = PersonClass(pPVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pPVar1;
}
