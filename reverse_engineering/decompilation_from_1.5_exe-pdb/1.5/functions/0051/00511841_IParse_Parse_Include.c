/*
 * Entry: 00511841
 * Name: IParse_Parse_Include
 * Namespace: Global
 * Signature: int IParse_Parse_Include(_domain * param_1, int param_2, int * param_3, double * param_4, char[80] * param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl
IParse_Parse_Include
          (_domain *param_1,int param_2,int *param_3,double *param_4,char (*param_5) [80],
          int *param_6)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_2 == 1) {
    pcVar1 = *param_5 + 1;
    pcVar4 = *param_5;
    do {
      cVar2 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar2 != '\0');
    if (((*param_5)[0] == '\"') && ((pcVar4 + (-1 - (int)pcVar1))[(int)*param_5] == '\"')) {
      strncpy(local_58,*param_5 + 1,(size_t)(pcVar4 + (-2 - (int)pcVar1)));
      pcVar4[(int)(local_58 + (-2 - (int)pcVar1))] = '\0';
      iVar3 = IParse_Parse_File(local_58,param_1);
    }
    else {
      iVar3 = -1;
    }
  }
  else {
    iVar3 = -1;
  }
  return iVar3;
}
