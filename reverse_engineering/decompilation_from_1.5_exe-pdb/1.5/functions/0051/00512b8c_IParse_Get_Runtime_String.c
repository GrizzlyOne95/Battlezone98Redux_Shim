/*
 * Entry: 00512b8c
 * Name: IParse_Get_Runtime_String
 * Namespace: Global
 * Signature: char * IParse_Get_Runtime_String(void * param_1, char * param_2, int * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

char * __cdecl IParse_Get_Runtime_String(void *param_1,char *param_2,int *param_3,char *param_4)

{
  char cVar1;
  _variable_struct *p_Var2;
  char *pcVar3;
  char *pcVar4;
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  p_Var2 = IParse_Which_Variable(param_1,param_2);
  if (p_Var2 == (_variable_struct *)0x0) {
    *param_3 = -1;
    sprintf(local_108,"Config or AIP string parameter \'%s\' not found.",param_2);
    param_4 = (char *)0x0;
  }
  else {
    *param_3 = 0;
    pcVar3 = p_Var2->string_value;
    pcVar4 = param_4;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      *pcVar4 = cVar1;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
  }
  return param_4;
}
