/*
 * Entry: 005c5a34
 * Name: luaU_undump
 * Namespace: Global
 * Signature: Proto * luaU_undump(lua_State * param_1, Zio * param_2, Mbuffer * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

Proto * __cdecl luaU_undump(lua_State *param_1,Zio *param_2,Mbuffer *param_3,char *param_4)

{
  char cVar1;
  TString *pTVar2;
  Proto *pPVar3;
  int iVar4;
  char *unaff_ESI;
  char **ppcVar5;
  LoadState *pLVar6;
  bool bVar7;
  LoadState local_30;
  LoadState local_20;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  cVar1 = *param_4;
  if ((cVar1 == '@') || (cVar1 == '=')) {
    local_30.name = param_4 + 1;
  }
  else {
    local_30.name = param_4;
    if (cVar1 == '\x1b') {
      local_30.name = "binary string";
    }
  }
  ppcVar5 = &local_20.name;
  local_30.L = param_1;
  local_30.Z = param_2;
  local_30.b = param_3;
  luaU_header((char *)ppcVar5);
  LoadBlock(&local_20,&DAT_0000000c,(uint)ppcVar5);
  iVar4 = 3;
  bVar7 = true;
  ppcVar5 = &local_20.name;
  pLVar6 = &local_20;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar7 = (lua_State *)*ppcVar5 == pLVar6->L;
    ppcVar5 = ppcVar5 + 1;
    pLVar6 = (LoadState *)&pLVar6->Z;
  } while (bVar7);
  if (!bVar7) {
    error((LoadState *)"bad header",unaff_ESI);
  }
  pTVar2 = luaS_newlstr(param_1,"=?",2);
  pPVar3 = LoadFunction(&local_30,pTVar2);
  return pPVar3;
}
