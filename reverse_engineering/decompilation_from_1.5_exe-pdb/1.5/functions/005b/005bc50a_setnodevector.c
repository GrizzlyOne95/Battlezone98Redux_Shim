/*
 * Entry: 005bc50a
 * Name: setnodevector
 * Namespace: Global
 * Signature: void setnodevector(lua_State * param_1, Table * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl setnodevector(lua_State *param_1,Table *param_2,int param_3)

{
  int in_EAX;
  void *pvVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int unaff_EDI;
  int local_8;
  
  if (in_EAX == 0) {
    *(Node **)(unaff_EDI + 0x10) = &dummynode_;
    local_8 = 0;
    iVar5 = 0;
  }
  else {
    local_8 = luaO_log2(in_EAX - 1);
    local_8 = local_8 + 1;
    if (0x1a < local_8) {
      luaG_runerror(param_1,"table overflow");
    }
    iVar5 = 1 << ((byte)local_8 & 0x1f);
    if (iVar5 + 1U < 0x8000000) {
      pvVar1 = luaM_realloc_(param_1,(void *)0x0,0,iVar5 << 5);
    }
    else {
      pvVar1 = luaM_toobig(param_1);
    }
    *(void **)(unaff_EDI + 0x10) = pvVar1;
    if (0 < iVar5) {
      iVar3 = 0;
      iVar4 = iVar5;
      do {
        iVar2 = *(int *)(unaff_EDI + 0x10) + iVar3;
        iVar3 = iVar3 + 0x20;
        iVar4 = iVar4 + -1;
        *(undefined4 *)(iVar2 + 0x1c) = 0;
        *(undefined4 *)(iVar2 + 0x18) = 0;
        *(undefined4 *)(iVar2 + 8) = 0;
      } while (iVar4 != 0);
    }
  }
  *(undefined1 *)(unaff_EDI + 7) = (undefined1)local_8;
  *(int *)(unaff_EDI + 0x14) = iVar5 * 0x20 + *(int *)(unaff_EDI + 0x10);
  return;
}
