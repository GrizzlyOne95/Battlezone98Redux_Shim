/*
 * Entry: 0051236b
 * Name: do_parse
 * Namespace: Global
 * Signature: int do_parse(char * param_1, int * param_2, int param_3, _domain * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl do_parse(char *param_1,int *param_2,int param_3,_domain *param_4)

{
  int iVar1;
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar1 = 0;
  while( true ) {
    if (iVar1 != 0) {
      return iVar1;
    }
    iVar1 = IParse_Search_For_Next_Declaration(param_1,param_2,param_3,param_4,local_58);
    if (iVar1 == -1) break;
    iVar1 = IParse_Complete_Declaration(param_1,param_2,param_3,param_4,iVar1,local_58);
  }
  return 0;
}
