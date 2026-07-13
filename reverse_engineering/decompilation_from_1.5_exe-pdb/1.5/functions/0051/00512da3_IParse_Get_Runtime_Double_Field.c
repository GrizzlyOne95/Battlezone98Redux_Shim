/*
 * Entry: 00512da3
 * Name: IParse_Get_Runtime_Double_Field
 * Namespace: Global
 * Signature: double IParse_Get_Runtime_Double_Field(void * param_1, char * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

double __cdecl IParse_Get_Runtime_Double_Field(void *param_1,char *param_2,int *param_3)

{
  double dVar1;
  double *pdVar2;
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pdVar2 = (double *)IParse_Get_Runtime_Struct_Field(param_1,param_2);
  if (pdVar2 == (double *)0x0) {
    *param_3 = -1;
    sprintf(local_108,"Config or AIP double parameter \'%s\' not found.",param_2);
    dVar1 = -1.0;
  }
  else {
    dVar1 = *pdVar2;
    *param_3 = 0;
  }
  return dVar1;
}
