/*
 * Entry: 00512aa6
 * Name: IParse_Get_Runtime_Float
 * Namespace: Global
 * Signature: double IParse_Get_Runtime_Float(void * param_1, char * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

double __cdecl IParse_Get_Runtime_Float(void *param_1,char *param_2,int *param_3)

{
  _variable_struct *p_Var1;
  char *_Format;
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  p_Var1 = IParse_Which_Variable(param_1,param_2);
  if (p_Var1 == (_variable_struct *)0x0) {
    _Format = "Config or AIP float parameter \'%s\' not found.";
  }
  else {
    if ((p_Var1->variable_type == 3) || (p_Var1->variable_type == 2)) {
      *param_3 = 0;
      return p_Var1->double_value;
    }
    _Format = "Config or AIP float parameter \'%s\' found but wrong type.";
  }
  *param_3 = -1;
  sprintf(local_108,_Format,param_2);
  return -1.0;
}
