/*
 * Entry: 00512c81
 * Name: IParse_Get_Runtime_Char_Field
 * Namespace: Global
 * Signature: schar IParse_Get_Runtime_Char_Field(void * param_1, char * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

schar __cdecl IParse_Get_Runtime_Char_Field(void *param_1,char *param_2,int *param_3)

{
  schar sVar1;
  char *pcVar2;
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pcVar2 = IParse_Get_Runtime_Struct_Field(param_1,param_2);
  if (pcVar2 == (char *)0x0) {
    *param_3 = -1;
    sprintf(local_108,"Config or AIP char parameter \'%s\' not found.",param_2);
    sVar1 = -1;
  }
  else {
    *param_3 = 0;
    sVar1 = *pcVar2;
  }
  return sVar1;
}
