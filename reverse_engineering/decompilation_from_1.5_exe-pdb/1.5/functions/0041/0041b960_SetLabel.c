/*
 * Entry: 0041b960
 * Name: SetLabel
 * Namespace: Global
 * Signature: int SetLabel(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetLabel(lua_State *param_1)

{
  int iVar1;
  GameObject *this;
  char *pcVar2;
  
  iVar1 = GetHandle(param_1,1);
  this = GameObjectHandle::GetObj(iVar1);
  if (this != (GameObject *)0x0) {
    pcVar2 = luaL_checklstring(param_1,2,(uint *)0x0);
    GameObject::SetLabel(this,pcVar2);
  }
  return 0;
}
