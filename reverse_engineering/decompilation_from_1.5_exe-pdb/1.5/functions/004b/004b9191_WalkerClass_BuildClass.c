/*
 * Entry: 004b9191
 * Name: WalkerClass::BuildClass
 * Namespace: WalkerClass
 * Signature: GameObjectClass * BuildClass(WalkerClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall WalkerClass::BuildClass(WalkerClass *this,long64 param_1)

{
  WalkerClass *pWVar1;
  undefined4 unaff_ESI;
  
  pWVar1 = operator_new(0x3d0);
  if (pWVar1 == (WalkerClass *)0x0) {
    pWVar1 = (WalkerClass *)0x0;
  }
  else {
    pWVar1 = WalkerClass(pWVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pWVar1;
}
