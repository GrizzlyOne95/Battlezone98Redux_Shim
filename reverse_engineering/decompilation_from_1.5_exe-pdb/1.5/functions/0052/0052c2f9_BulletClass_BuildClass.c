/*
 * Entry: 0052c2f9
 * Name: BulletClass::BuildClass
 * Namespace: BulletClass
 * Signature: OrdnanceClass * BuildClass(BulletClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall BulletClass::BuildClass(BulletClass *this,long64 param_1)

{
  BulletClass *this_00;
  OrdnanceClass *pOVar1;
  undefined4 unaff_ESI;
  
  this_00 = operator_new(0x70);
  if (this_00 == (BulletClass *)0x0) {
    pOVar1 = (OrdnanceClass *)0x0;
  }
  else {
    pOVar1 = (OrdnanceClass *)BulletClass(this_00,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return pOVar1;
}
