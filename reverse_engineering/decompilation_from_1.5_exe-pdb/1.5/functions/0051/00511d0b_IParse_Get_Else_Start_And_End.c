/*
 * Entry: 00511d0b
 * Name: IParse_Get_Else_Start_And_End
 * Namespace: Global
 * Signature: int IParse_Get_Else_Start_And_End(char * param_1, int * param_2, int param_3, _domain * param_4, int * param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl
IParse_Get_Else_Start_And_End
          (char *param_1,int *param_2,int param_3,_domain *param_4,int *param_5,int *param_6)

{
  void *_Memory;
  int iVar1;
  char local_d0 [108];
  undefined1 local_64 [92];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_64;
  _Memory = calloc(1,1);
  iVar1 = IParse_Search_For_Next_Declaration(param_1,param_2,param_3,param_4,local_d0);
  free(_Memory);
  if (iVar1 == 0xe) {
    IParse_Get_Next_Statement_Start_And_End(param_1,param_2,param_3,param_4,param_5,param_6);
  }
  return (uint)(iVar1 == 0xe);
}
