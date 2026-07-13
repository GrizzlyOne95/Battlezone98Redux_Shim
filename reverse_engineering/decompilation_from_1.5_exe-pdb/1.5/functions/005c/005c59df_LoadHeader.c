/*
 * Entry: 005c59df
 * Name: LoadHeader
 * Namespace: Global
 * Signature: void LoadHeader(LoadState * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl LoadHeader(LoadState *param_1)

{
  int iVar1;
  int *piVar2;
  char *unaff_EDI;
  LoadState *pLVar3;
  bool bVar4;
  int local_20 [3];
  LoadState local_14;
  
  local_14.name = (char *)(__security_cookie ^ (uint)&stack0xfffffffc);
  piVar2 = local_20;
  luaU_header((char *)piVar2);
  LoadBlock(&local_14,&DAT_0000000c,(uint)piVar2);
  iVar1 = 3;
  bVar4 = true;
  piVar2 = local_20;
  pLVar3 = &local_14;
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar4 = (lua_State *)*piVar2 == pLVar3->L;
    piVar2 = piVar2 + 1;
    pLVar3 = (LoadState *)&pLVar3->Z;
  } while (bVar4);
  if (!bVar4) {
    error((LoadState *)"bad header",unaff_EDI);
  }
  return;
}
