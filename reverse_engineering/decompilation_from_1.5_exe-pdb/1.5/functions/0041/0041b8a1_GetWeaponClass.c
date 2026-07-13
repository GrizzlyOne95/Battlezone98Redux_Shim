/*
 * Entry: 0041b8a1
 * Name: GetWeaponClass
 * Namespace: Global
 * Signature: int GetWeaponClass(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetWeaponClass(lua_State *param_1)

{
  Carrier *this;
  int iVar1;
  GameObject *pGVar2;
  Weapon *pWVar3;
  
  iVar1 = GetHandle(param_1,1);
  pGVar2 = GameObjectHandle::GetObj(iVar1);
  if ((pGVar2 != (GameObject *)0x0) && (this = pGVar2->carrier, this != (Carrier *)0x0)) {
    iVar1 = luaL_checkinteger(param_1,2);
    pWVar3 = Carrier::GetWeapon(this,iVar1);
    if (pWVar3 != (Weapon *)0x0) {
      lua_pushlstring(param_1,(char *)&pWVar3->weaponClass->cfg,8);
      return 1;
    }
  }
  return 0;
}
