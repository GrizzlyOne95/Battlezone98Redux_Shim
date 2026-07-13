/*
 * Entry: 0049f5af
 * Name: HoverCraftClass::BuildClass
 * Namespace: HoverCraftClass
 * Signature: GameObjectClass * BuildClass(HoverCraftClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall HoverCraftClass::BuildClass(HoverCraftClass *this,long64 param_1)

{
  HoverCraftClass *pHVar1;
  undefined4 unaff_ESI;
  
  pHVar1 = operator_new(0x3c0);
  if (pHVar1 == (HoverCraftClass *)0x0) {
    pHVar1 = (HoverCraftClass *)0x0;
  }
  else {
    pHVar1 = HoverCraftClass(pHVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pHVar1;
}
