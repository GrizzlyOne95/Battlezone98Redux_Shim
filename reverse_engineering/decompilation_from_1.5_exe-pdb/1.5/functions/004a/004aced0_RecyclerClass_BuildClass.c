/*
 * Entry: 004aced0
 * Name: RecyclerClass::BuildClass
 * Namespace: RecyclerClass
 * Signature: GameObjectClass * BuildClass(RecyclerClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall RecyclerClass::BuildClass(RecyclerClass *this,long64 param_1)

{
  RecyclerClass *pRVar1;
  undefined4 unaff_ESI;
  
  pRVar1 = operator_new(0x430);
  if (pRVar1 == (RecyclerClass *)0x0) {
    pRVar1 = (RecyclerClass *)0x0;
  }
  else {
    pRVar1 = RecyclerClass(pRVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pRVar1;
}
