/*
 * Entry: 005bc8e2
 * Name: resize
 * Namespace: Global
 * Signature: void resize(lua_State * param_1, Table * param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl resize(lua_State *param_1,Table *param_2,int param_3,int param_4)

{
  undefined4 *puVar1;
  byte bVar2;
  Node *pNVar3;
  Table *in_EAX;
  lua_TValue *plVar4;
  int iVar5;
  int unaff_ESI;
  Table *unaff_EDI;
  int *piVar6;
  uint local_c;
  Table *local_8;
  
  bVar2 = in_EAX->lsizenode;
  iVar5 = in_EAX->sizearray;
  pNVar3 = in_EAX->node;
  if (iVar5 < (int)param_2) {
    setarrayvector(param_1,unaff_EDI,unaff_ESI);
  }
  setnodevector(param_1,unaff_EDI,unaff_ESI);
  if ((int)param_2 < iVar5) {
    in_EAX->sizearray = (int)param_2;
    local_8 = param_2;
    local_c = (int)param_2 << 4;
    do {
      puVar1 = (undefined4 *)((int)&in_EAX->array->value + local_c);
      if (puVar1[2] != 0) {
        plVar4 = luaH_setnum(param_1,in_EAX,(int)((int)&local_8->next + 1));
        (plVar4->value).gc = (GCObject *)*puVar1;
        *(undefined4 *)((int)&plVar4->value + 4) = puVar1[1];
        plVar4->tt = puVar1[2];
      }
      local_8 = (Table *)((int)&local_8->next + 1);
      local_c = local_c + 0x10;
    } while ((int)local_8 < iVar5);
    if ((undefined1 *)((int)&param_2->next + 1U) < (undefined1 *)0x10000000) {
      plVar4 = luaM_realloc_(param_1,in_EAX->array,iVar5 << 4,(int)param_2 << 4);
    }
    else {
      plVar4 = luaM_toobig(param_1);
    }
    in_EAX->array = plVar4;
  }
  iVar5 = 1 << (bVar2 & 0x1f);
  local_8 = (Table *)(iVar5 + -1);
  if (-1 < (int)local_8) {
    piVar6 = &pNVar3[(int)local_8].i_val.tt;
    do {
      if (*piVar6 != 0) {
        plVar4 = luaH_set(param_1,in_EAX,(lua_TValue *)(piVar6 + 2));
        (plVar4->value).gc = (((lua_TValue *)(piVar6 + -2))->value).gc;
        *(int *)((int)&plVar4->value + 4) = piVar6[-1];
        plVar4->tt = *piVar6;
      }
      local_8 = (Table *)((int)local_8 + -1);
      piVar6 = piVar6 + -8;
    } while (-1 < (int)local_8);
  }
  if (pNVar3 != &dummynode_) {
    luaM_realloc_(param_1,pNVar3,iVar5 << 5,0);
  }
  return;
}
