/*
 * Entry: 0049f95d
 * Name: HowitzerClass::BuildClass
 * Namespace: HowitzerClass
 * Signature: GameObjectClass * BuildClass(HowitzerClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall HowitzerClass::BuildClass(HowitzerClass *this,long64 param_1)

{
  HowitzerClass *pHVar1;
  undefined4 unaff_ESI;
  
  pHVar1 = operator_new(0x3d0);
  if (pHVar1 == (HowitzerClass *)0x0) {
    pHVar1 = (HowitzerClass *)0x0;
  }
  else {
    pHVar1 = HowitzerClass(pHVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pHVar1;
}
