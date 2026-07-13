/*
 * Entry: 0041b997
 * Name: GetClassSig
 * Namespace: Global
 * Signature: int GetClassSig(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetClassSig(lua_State *param_1)

{
  undefined4 uVar1;
  int iVar2;
  GameObject *pGVar3;
  char local_8;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  iVar2 = GetHandle(param_1,1);
  pGVar3 = GameObjectHandle::GetObj(iVar2);
  if (pGVar3 != (GameObject *)0x0) {
    iVar2 = (**(code **)pGVar3->_padding_)();
    uVar1 = *(undefined4 *)(iVar2 + 0x20);
    _local_8 = CONCAT13((char)uVar1,
                        CONCAT12((char)((uint)uVar1 >> 8),
                                 CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))))
    ;
    lua_pushlstring(param_1,&local_8,4);
    return 1;
  }
  return 0;
}
