/*
 * Entry: 0052aea8
 * Name: BoltClass::BuildClass
 * Namespace: BoltClass
 * Signature: OrdnanceClass * BuildClass(BoltClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall BoltClass::BuildClass(BoltClass *this,long64 param_1)

{
  BoltClass *pBVar1;
  undefined4 unaff_ESI;
  
  pBVar1 = operator_new(0x88);
  if (pBVar1 == (BoltClass *)0x0) {
    pBVar1 = (BoltClass *)0x0;
  }
  else {
    pBVar1 = BoltClass(pBVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pBVar1;
}
