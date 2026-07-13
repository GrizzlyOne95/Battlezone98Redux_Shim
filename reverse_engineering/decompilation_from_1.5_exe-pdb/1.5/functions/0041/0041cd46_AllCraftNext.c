/*
 * Entry: 0041cd46
 * Name: AllCraftNext
 * Namespace: Global
 * Signature: int AllCraftNext(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AllCraftNext(lua_State *param_1)

{
  Craft *this;
  uint uVar1;
  Craft **ppCVar2;
  int iVar3;
  
  uVar1 = lua_tointeger(param_1,-0x2713);
  do {
    if ((uint)((int)Craft::craftList._Mylast - (int)Craft::craftList._Myfirst >> 2) <= uVar1) {
      return 0;
    }
    ppCVar2 = std::vector<Craft_*,std::allocator<Craft_*>_>::at(&Craft::craftList,uVar1);
    this = *ppCVar2;
    uVar1 = uVar1 + 1;
    iVar3 = (**(code **)(this->_padding_ + 0x30))();
  } while ((*(uint *)(iVar3 + 0x14) & 0x200) != 0);
  lua_pushinteger(param_1,uVar1);
  lua_replace(param_1,-0x2713);
  iVar3 = GameObject::GetHandle((GameObject *)this);
  PushHandle(param_1,iVar3);
  return 1;
}
