/*
 * Entry: 005122dc
 * Name: IParse_Complete_Declaration
 * Namespace: Global
 * Signature: int IParse_Complete_Declaration(char * param_1, int * param_2, int param_3, _domain * param_4, int param_5, char * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl
IParse_Complete_Declaration
          (char *param_1,int *param_2,int param_3,_domain *param_4,int param_5,char *param_6)

{
  char *pcVar1;
  char **ppcVar2;
  int local_60;
  char *local_5c;
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_5c = calloc(1,1);
  ppcVar2 = &local_5c;
  pcVar1 = IParse_Get_Termination_String(param_5,local_58);
  local_60 = IParse_Read_Until_String(param_1,param_2,param_3,pcVar1,ppcVar2);
  if (local_60 == 0) {
    local_60 = parse_declaration(param_1,param_2,param_3,param_4,param_5,param_6,&local_5c);
  }
  free(local_5c);
  return local_60;
}
