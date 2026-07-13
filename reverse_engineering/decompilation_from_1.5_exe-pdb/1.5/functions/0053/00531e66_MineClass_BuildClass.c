/*
 * Entry: 00531e66
 * Name: MineClass::BuildClass
 * Namespace: MineClass
 * Signature: GameObjectClass * BuildClass(MineClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall MineClass::BuildClass(MineClass *this,long64 param_1)

{
  MineClass *pMVar1;
  undefined4 unaff_ESI;
  
  pMVar1 = operator_new(0x168);
  if (pMVar1 == (MineClass *)0x0) {
    pMVar1 = (MineClass *)0x0;
  }
  else {
    pMVar1 = MineClass(pMVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pMVar1;
}
