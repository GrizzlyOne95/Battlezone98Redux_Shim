/*
 * Entry: 0053230a
 * Name: MissileClass::BuildClass
 * Namespace: MissileClass
 * Signature: OrdnanceClass * BuildClass(MissileClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall MissileClass::BuildClass(MissileClass *this,long64 param_1)

{
  MissileClass *pMVar1;
  undefined4 unaff_ESI;
  
  pMVar1 = operator_new(0xb8);
  if (pMVar1 == (MissileClass *)0x0) {
    pMVar1 = (MissileClass *)0x0;
  }
  else {
    pMVar1 = MissileClass(pMVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (OrdnanceClass *)pMVar1;
}
