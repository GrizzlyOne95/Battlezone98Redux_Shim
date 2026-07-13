/*
 * Entry: 00482948
 * Name: BarracksClass::BuildClass
 * Namespace: BarracksClass
 * Signature: GameObjectClass * BuildClass(BarracksClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall BarracksClass::BuildClass(BarracksClass *this,long64 param_1)

{
  BarracksClass *pBVar1;
  undefined4 unaff_ESI;
  
  pBVar1 = operator_new(0x168);
  if (pBVar1 == (BarracksClass *)0x0) {
    pBVar1 = (BarracksClass *)0x0;
  }
  else {
    pBVar1 = BarracksClass(pBVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pBVar1;
}
