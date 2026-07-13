/*
 * Entry: 0041ccb2
 * Name: AllObjectsNext
 * Namespace: Global
 * Signature: int AllObjectsNext(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AllObjectsNext(lua_State *param_1)

{
  GameObject *this;
  uint uVar1;
  GameObject **ppGVar2;
  int iVar3;
  
  uVar1 = lua_tointeger(param_1,-0x2713);
  do {
    if ((uint)((int)GameObject::objectList->_Mylast - (int)GameObject::objectList->_Myfirst >> 2) <=
        uVar1) {
      return 0;
    }
    ppGVar2 = std::vector<GameObject_*,std::allocator<GameObject_*>_>::at
                        (GameObject::objectList,uVar1);
    this = *ppGVar2;
    uVar1 = uVar1 + 1;
    iVar3 = (**(code **)(this->_padding_ + 0x30))();
  } while ((*(uint *)(iVar3 + 0x14) & 0x200) != 0);
  lua_pushinteger(param_1,uVar1);
  lua_replace(param_1,-0x2713);
  iVar3 = GameObject::GetHandle(this);
  PushHandle(param_1,iVar3);
  return 1;
}
