/*
 * Entry: 00532baa
 * Name: ObjectLobberClass::BuildClass
 * Namespace: ObjectLobberClass
 * Signature: WeaponClass * BuildClass(ObjectLobberClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass * __thiscall ObjectLobberClass::BuildClass(ObjectLobberClass *this,long64 param_1)

{
  ObjectLobberClass *pOVar1;
  undefined4 unaff_ESI;
  
  pOVar1 = operator_new(0x80);
  if (pOVar1 == (ObjectLobberClass *)0x0) {
    pOVar1 = (ObjectLobberClass *)0x0;
  }
  else {
    pOVar1 = ObjectLobberClass(pOVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (WeaponClass *)pOVar1;
}
