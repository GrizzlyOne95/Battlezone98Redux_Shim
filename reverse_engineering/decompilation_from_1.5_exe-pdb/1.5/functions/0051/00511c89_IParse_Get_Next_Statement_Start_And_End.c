/*
 * Entry: 00511c89
 * Name: IParse_Get_Next_Statement_Start_And_End
 * Namespace: Global
 * Signature: void IParse_Get_Next_Statement_Start_And_End(char * param_1, int * param_2, int param_3, _domain * param_4, int * param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl
IParse_Get_Next_Statement_Start_And_End
          (char *param_1,int *param_2,int param_3,_domain *param_4,int *param_5,int *param_6)

{
  int iVar1;
  void *_Memory;
  int iVar2;
  char local_d0 [108];
  undefined1 local_64 [92];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_64;
  _Memory = calloc(1,1);
  iVar2 = IParse_Search_For_Next_Declaration(param_1,param_2,param_3,param_4,local_d0);
  free(_Memory);
  iVar1 = *param_2;
  if (iVar2 == 0xd) {
    iVar2 = IParse_Find_Matched_Bracket(param_1,iVar1,param_3);
  }
  *param_5 = iVar1;
  *param_6 = iVar2;
  return;
}
