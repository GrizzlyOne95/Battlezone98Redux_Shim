/*
 * Entry: 004b9664
 * Name: WingmanClass::BuildClass
 * Namespace: WingmanClass
 * Signature: GameObjectClass * BuildClass(WingmanClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall WingmanClass::BuildClass(WingmanClass *this,long64 param_1)

{
  WingmanClass *pWVar1;
  undefined4 unaff_ESI;
  
  pWVar1 = operator_new(0x3c0);
  if (pWVar1 == (WingmanClass *)0x0) {
    pWVar1 = (WingmanClass *)0x0;
  }
  else {
    pWVar1 = WingmanClass(pWVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pWVar1;
}
