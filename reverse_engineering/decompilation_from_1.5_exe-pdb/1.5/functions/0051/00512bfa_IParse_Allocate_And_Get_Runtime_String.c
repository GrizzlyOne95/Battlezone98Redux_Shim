/*
 * Entry: 00512bfa
 * Name: IParse_Allocate_And_Get_Runtime_String
 * Namespace: Global
 * Signature: char * IParse_Allocate_And_Get_Runtime_String(void * param_1, char * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

char * __cdecl IParse_Allocate_And_Get_Runtime_String(void *param_1,char *param_2,int *param_3)

{
  char cVar1;
  _variable_struct *p_Var2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  p_Var2 = IParse_Which_Variable(param_1,param_2);
  if (p_Var2 == (_variable_struct *)0x0) {
    *param_3 = -1;
    sprintf(local_108,"Config or AIP string parameter \'%s\' not found.",param_2);
    pcVar3 = (char *)0x0;
  }
  else {
    *param_3 = 0;
    pcVar4 = p_Var2->string_value;
    pcVar5 = pcVar4 + 1;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    pcVar3 = calloc(1,(size_t)(pcVar4 + (1 - (int)pcVar5)));
    pcVar5 = p_Var2->string_value;
    pcVar4 = pcVar3;
    do {
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
      *pcVar4 = cVar1;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
  }
  return pcVar3;
}
