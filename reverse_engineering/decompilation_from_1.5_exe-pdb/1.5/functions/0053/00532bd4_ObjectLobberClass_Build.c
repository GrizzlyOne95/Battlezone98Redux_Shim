/*
 * Entry: 00532bd4
 * Name: ObjectLobberClass::Build
 * Namespace: ObjectLobberClass
 * Signature: Weapon * Build(ObjectLobberClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall ObjectLobberClass::Build(ObjectLobberClass *this,_OBJ76 *param_1)

{
  ObjectLobber *pOVar1;
  
  pOVar1 = operator_new(0xc0);
  if (pOVar1 == (ObjectLobber *)0x0) {
    pOVar1 = (ObjectLobber *)0x0;
  }
  else {
    pOVar1 = ObjectLobber::ObjectLobber(pOVar1,param_1,this);
  }
  return (Weapon *)pOVar1;
}
