/*
 * Entry: 00537ad8
 * Name: RemoteDetonatorClass::BuildClass
 * Namespace: RemoteDetonatorClass
 * Signature: WeaponClass * BuildClass(RemoteDetonatorClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall RemoteDetonatorClass::BuildClass(RemoteDetonatorClass *this,long64 param_1)

{
  RemoteDetonatorClass *pRVar1;
  undefined4 unaff_ESI;
  
  pRVar1 = operator_new(0x88);
  if (pRVar1 == (RemoteDetonatorClass *)0x0) {
    pRVar1 = (RemoteDetonatorClass *)0x0;
  }
  else {
    pRVar1 = RemoteDetonatorClass(pRVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pRVar1;
}
