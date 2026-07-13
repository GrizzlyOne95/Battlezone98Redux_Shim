/*
 * Entry: 0041bf78
 * Name: SelectedObjectsNext
 * Namespace: Global
 * Signature: int SelectedObjectsNext(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SelectedObjectsNext(lua_State *param_1)

{
  int iVar1;
  int iVar2;
  GameObject *pGVar3;
  int iVar4;
  
  iVar2 = lua_tointeger(param_1,-0x2713);
  do {
    if (controlPanel.selectNum <= iVar2) {
      return 0;
    }
    iVar1 = controlPanel.selectList[iVar2];
    iVar2 = iVar2 + 1;
    pGVar3 = GameObjectHandle::GetObj(iVar1);
  } while ((pGVar3 == (GameObject *)0x0) ||
          (iVar4 = (**(code **)(pGVar3->_padding_ + 0x30))(), (*(uint *)(iVar4 + 0x14) & 0x200) != 0
          ));
  lua_pushinteger(param_1,iVar2);
  lua_replace(param_1,-0x2713);
  PushHandle(param_1,iVar1);
  return 1;
}
