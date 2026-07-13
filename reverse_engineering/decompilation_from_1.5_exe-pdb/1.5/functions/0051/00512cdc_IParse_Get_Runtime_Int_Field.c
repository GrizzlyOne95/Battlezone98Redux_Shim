/*
 * Entry: 00512cdc
 * Name: IParse_Get_Runtime_Int_Field
 * Namespace: Global
 * Signature: int IParse_Get_Runtime_Int_Field(void * param_1, char * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl IParse_Get_Runtime_Int_Field(void *param_1,char *param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  piVar1 = (int *)IParse_Get_Runtime_Struct_Field(param_1,param_2);
  if (piVar1 == (int *)0x0) {
    *param_3 = -1;
    sprintf(local_108,"Config or AIP int parameter \'%s\' not found.",param_2);
    iVar2 = -1;
  }
  else {
    iVar2 = *piVar1;
    *param_3 = 0;
  }
  return iVar2;
}
