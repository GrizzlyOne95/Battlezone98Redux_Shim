/*
 * Entry: 005b952f
 * Name: freeobj
 * Namespace: Global
 * Signature: void freeobj(lua_State * param_1, GCObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl freeobj(lua_State *param_1,GCObject *param_2)

{
  uint *puVar1;
  uchar uVar2;
  Closure *in_EAX;
  code *pcVar3;
  lua_State *in_EDX;
  
  uVar2 = (in_EAX->c).tt;
  if (uVar2 == '\x04') {
    puVar1 = &(in_EDX->l_G->strt).nuse;
    *puVar1 = *puVar1 - 1;
    pcVar3 = (code *)((int)&((in_EAX->c).env)->node + 1);
  }
  else {
    if (uVar2 == '\x05') {
      luaH_free(in_EDX,(Table *)&in_EAX->c);
      return;
    }
    if (uVar2 == '\x06') {
      luaF_freeclosure(in_EDX,in_EAX);
      return;
    }
    if (uVar2 != '\a') {
      if (uVar2 == '\b') {
        luaE_freethread(in_EDX,(lua_State *)&in_EAX->c);
        return;
      }
      if (uVar2 != '\t') {
        if (uVar2 != '\n') {
          return;
        }
        luaF_freeupval(in_EDX,(UpVal *)&in_EAX->c);
        return;
      }
      luaF_freeproto(in_EDX,(Proto *)&in_EAX->c);
      return;
    }
    pcVar3 = (in_EAX->c).f + 0x18;
  }
  luaM_realloc_(in_EDX,in_EAX,(uint)pcVar3,0);
  return;
}
