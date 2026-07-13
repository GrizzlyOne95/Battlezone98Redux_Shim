/*
 * Entry: 004b3b77
 * Name: TugClass::BuildClass
 * Namespace: TugClass
 * Signature: GameObjectClass * BuildClass(TugClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall TugClass::BuildClass(TugClass *this,long64 param_1)

{
  TugClass *pTVar1;
  undefined4 unaff_ESI;
  
  pTVar1 = operator_new(0x3c8);
  if (pTVar1 == (TugClass *)0x0) {
    pTVar1 = (TugClass *)0x0;
  }
  else {
    pTVar1 = TugClass(pTVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pTVar1;
}
