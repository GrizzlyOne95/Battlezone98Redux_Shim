/*
 * Entry: 00485c82
 * Name: ConstructionRigClass::BuildClass
 * Namespace: ConstructionRigClass
 * Signature: GameObjectClass * BuildClass(ConstructionRigClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall
ConstructionRigClass::BuildClass(ConstructionRigClass *this,long64 param_1)

{
  ConstructionRigClass *pCVar1;
  undefined4 unaff_ESI;
  
  pCVar1 = operator_new(0x430);
  if (pCVar1 == (ConstructionRigClass *)0x0) {
    pCVar1 = (ConstructionRigClass *)0x0;
  }
  else {
    pCVar1 = ConstructionRigClass(pCVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pCVar1;
}
