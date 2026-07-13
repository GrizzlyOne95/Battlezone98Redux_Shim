/*
 * Entry: 005129db
 * Name: IParse_Get_Runtime_Char
 * Namespace: Global
 * Signature: schar IParse_Get_Runtime_Char(void * param_1, char * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

schar __cdecl IParse_Get_Runtime_Char(void *param_1,char *param_2,int *param_3)

{
  schar sVar1;
  _variable_struct *p_Var2;
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  p_Var2 = IParse_Which_Variable(param_1,param_2);
  if (p_Var2 == (_variable_struct *)0x0) {
    *param_3 = -1;
    sprintf(local_108,"Config or AIP char parameter \'%s\' not found.",param_2);
    sVar1 = -1;
  }
  else {
    *param_3 = 0;
    sVar1 = (schar)p_Var2->int_value;
  }
  return sVar1;
}
