/*
 * Entry: 00531742
 * Name: MagnetMineClass::BuildClass
 * Namespace: MagnetMineClass
 * Signature: GameObjectClass * BuildClass(MagnetMineClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall MagnetMineClass::BuildClass(MagnetMineClass *this,long64 param_1)

{
  MagnetMineClass *pMVar1;
  undefined4 unaff_ESI;
  
  pMVar1 = operator_new(0x188);
  if (pMVar1 == (MagnetMineClass *)0x0) {
    pMVar1 = (MagnetMineClass *)0x0;
  }
  else {
    pMVar1 = MagnetMineClass(pMVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pMVar1;
}
