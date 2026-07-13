/*
 * Entry: 00512d38
 * Name: IParse_Get_Runtime_Float_Field
 * Namespace: Global
 * Signature: double IParse_Get_Runtime_Float_Field(void * param_1, char * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

double __cdecl IParse_Get_Runtime_Float_Field(void *param_1,char *param_2,int *param_3)

{
  float fVar1;
  double dVar2;
  float *pfVar3;
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pfVar3 = (float *)IParse_Get_Runtime_Struct_Field(param_1,param_2);
  if (pfVar3 == (float *)0x0) {
    *param_3 = -1;
    sprintf(local_108,"Config or AIP float parameter \'%s\' not found.",param_2);
    dVar2 = -1.0;
  }
  else {
    fVar1 = *pfVar3;
    *param_3 = 0;
    dVar2 = (double)fVar1;
  }
  return dVar2;
}
