/*
 * Entry: 00489e81
 * Name: CraftClass::BuildClass
 * Namespace: CraftClass
 * Signature: GameObjectClass * BuildClass(CraftClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall CraftClass::BuildClass(CraftClass *this,long64 param_1)

{
  CraftClass *pCVar1;
  undefined4 unaff_ESI;
  
  pCVar1 = operator_new(0x300);
  if (pCVar1 == (CraftClass *)0x0) {
    pCVar1 = (CraftClass *)0x0;
  }
  else {
    pCVar1 = CraftClass(pCVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pCVar1;
}
