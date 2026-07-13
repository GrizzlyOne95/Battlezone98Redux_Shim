/*
 * Entry: 005bc817
 * Name: unbound_search
 * Namespace: Global
 * Signature: int unbound_search(Table * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl unbound_search(Table *param_1,uint param_2)

{
  uint in_EAX;
  lua_TValue *plVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  uVar5 = in_EAX + 1;
  do {
    plVar1 = luaH_getnum(param_1,uVar5);
    if (plVar1->tt == 0) {
      while (uVar2 = in_EAX, 1 < uVar5 - uVar2) {
        uVar3 = uVar2 + uVar5 >> 1;
        plVar1 = luaH_getnum(param_1,uVar3);
        in_EAX = uVar3;
        if (plVar1->tt == 0) {
          in_EAX = uVar2;
          uVar5 = uVar3;
        }
      }
      return uVar2;
    }
    uVar2 = uVar5 * 2;
    in_EAX = uVar5;
    uVar5 = uVar2;
  } while (uVar2 < 0x7ffffffe);
  iVar4 = 1;
  while (plVar1 = luaH_getnum(param_1,iVar4), plVar1->tt != 0) {
    iVar4 = iVar4 + 1;
  }
  return iVar4 + -1;
}
