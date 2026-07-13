/*
 * Entry: 0052fd49
 * Name: FlareMineClass::BuildClass
 * Namespace: FlareMineClass
 * Signature: GameObjectClass * BuildClass(FlareMineClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall FlareMineClass::BuildClass(FlareMineClass *this,long64 param_1)

{
  FlareMineClass *pFVar1;
  undefined4 unaff_ESI;
  
  pFVar1 = operator_new(0x188);
  if (pFVar1 == (FlareMineClass *)0x0) {
    pFVar1 = (FlareMineClass *)0x0;
  }
  else {
    pFVar1 = FlareMineClass(pFVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pFVar1;
}
