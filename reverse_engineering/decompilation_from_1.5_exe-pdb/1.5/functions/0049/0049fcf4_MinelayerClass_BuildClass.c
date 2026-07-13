/*
 * Entry: 0049fcf4
 * Name: MinelayerClass::BuildClass
 * Namespace: MinelayerClass
 * Signature: GameObjectClass * BuildClass(MinelayerClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall MinelayerClass::BuildClass(MinelayerClass *this,long64 param_1)

{
  MinelayerClass *pMVar1;
  undefined4 unaff_ESI;
  
  pMVar1 = operator_new(0x3d0);
  if (pMVar1 == (MinelayerClass *)0x0) {
    pMVar1 = (MinelayerClass *)0x0;
  }
  else {
    pMVar1 = MinelayerClass(pMVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pMVar1;
}
