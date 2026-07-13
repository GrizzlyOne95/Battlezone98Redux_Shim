/*
 * Entry: 0041c004
 * Name: ObjectiveObjectsNext
 * Namespace: Global
 * Signature: int ObjectiveObjectsNext(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ObjectiveObjectsNext(lua_State *param_1)

{
  GameObject *this;
  int iVar1;
  int iVar2;
  
  iVar1 = lua_tointeger(param_1,-0x2713);
  do {
    if (GameObject::objectiveCount <= iVar1) {
      return 0;
    }
    this = GameObject::objectiveList[iVar1];
  } while ((this == (GameObject *)0x0) ||
          (iVar2 = (**(code **)(this->_padding_ + 0x30))(), (*(uint *)(iVar2 + 0x14) & 0x200) != 0))
  ;
  lua_pushinteger(param_1,iVar1);
  lua_replace(param_1,-0x2713);
  iVar1 = GameObject::GetHandle(this);
  PushHandle(param_1,iVar1);
  return 1;
}
