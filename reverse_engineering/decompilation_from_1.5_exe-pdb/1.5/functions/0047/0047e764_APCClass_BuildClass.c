/*
 * Entry: 0047e764
 * Name: APCClass::BuildClass
 * Namespace: APCClass
 * Signature: GameObjectClass * BuildClass(APCClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall APCClass::BuildClass(APCClass *this,long64 param_1)

{
  APCClass *pAVar1;
  undefined4 unaff_ESI;
  
  pAVar1 = operator_new(0x3e0);
  if (pAVar1 == (APCClass *)0x0) {
    pAVar1 = (APCClass *)0x0;
  }
  else {
    pAVar1 = APCClass(pAVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pAVar1;
}
