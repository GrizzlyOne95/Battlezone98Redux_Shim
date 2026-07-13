/*
 * Entry: 0052d5bb
 * Name: DayWreckerClass::BuildClass
 * Namespace: DayWreckerClass
 * Signature: GameObjectClass * BuildClass(DayWreckerClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall DayWreckerClass::BuildClass(DayWreckerClass *this,long64 param_1)

{
  DayWreckerClass *pDVar1;
  undefined4 unaff_ESI;
  
  pDVar1 = operator_new(0x180);
  if (pDVar1 == (DayWreckerClass *)0x0) {
    pDVar1 = (DayWreckerClass *)0x0;
  }
  else {
    pDVar1 = DayWreckerClass(pDVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pDVar1;
}
