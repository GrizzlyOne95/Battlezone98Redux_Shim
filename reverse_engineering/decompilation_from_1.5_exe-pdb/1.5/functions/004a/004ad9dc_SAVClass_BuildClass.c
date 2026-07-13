/*
 * Entry: 004ad9dc
 * Name: SAVClass::BuildClass
 * Namespace: SAVClass
 * Signature: GameObjectClass * BuildClass(SAVClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall SAVClass::BuildClass(SAVClass *this,long64 param_1)

{
  SAVClass *pSVar1;
  undefined4 unaff_ESI;
  
  pSVar1 = operator_new(0x3c8);
  if (pSVar1 == (SAVClass *)0x0) {
    pSVar1 = (SAVClass *)0x0;
  }
  else {
    pSVar1 = SAVClass(pSVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pSVar1;
}
