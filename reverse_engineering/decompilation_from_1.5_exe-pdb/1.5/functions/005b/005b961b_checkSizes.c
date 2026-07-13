/*
 * Entry: 005b961b
 * Name: checkSizes
 * Namespace: Global
 * Signature: void checkSizes(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl checkSizes(lua_State *param_1)

{
  global_State *pgVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  lua_State *unaff_EBX;
  uint uVar5;
  
  pgVar1 = unaff_EBX->l_G;
  iVar2 = (pgVar1->strt).size;
  if (((pgVar1->strt).nuse < (uint)((int)(iVar2 + (iVar2 >> 0x1f & 3U)) >> 2)) && (0x40 < iVar2)) {
    luaS_resize(unaff_EBX,iVar2 / 2);
  }
  uVar3 = (pgVar1->buff).buffsize;
  if (0x40 < uVar3) {
    uVar5 = uVar3 >> 1;
    if (uVar5 + 1 < 0xfffffffe) {
      pcVar4 = luaM_realloc_(unaff_EBX,(pgVar1->buff).buffer,uVar3,uVar5);
    }
    else {
      pcVar4 = luaM_toobig(unaff_EBX);
    }
    (pgVar1->buff).buffsize = uVar5;
    (pgVar1->buff).buffer = pcVar4;
  }
  return;
}
