/*
 * Entry: 0053d989
 * Name: TorpedoClass::BuildClass
 * Namespace: TorpedoClass
 * Signature: GameObjectClass * BuildClass(TorpedoClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall TorpedoClass::BuildClass(TorpedoClass *this,long64 param_1)

{
  TorpedoClass *pTVar1;
  undefined4 unaff_ESI;
  
  pTVar1 = operator_new(0x1b0);
  if (pTVar1 == (TorpedoClass *)0x0) {
    pTVar1 = (TorpedoClass *)0x0;
  }
  else {
    pTVar1 = TorpedoClass(pTVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pTVar1;
}
