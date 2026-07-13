/*
 * Entry: 00511d8e
 * Name: IParse_Parse_Conditional_Code
 * Namespace: Global
 * Signature: int IParse_Parse_Conditional_Code(char * param_1, int * param_2, int param_3, _domain * param_4, int param_5, int * param_6, double * param_7, char[80] * param_8, int * param_9)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
IParse_Parse_Conditional_Code
          (char *param_1,int *param_2,int param_3,_domain *param_4,int param_5,int *param_6,
          double *param_7,char (*param_8) [80],int *param_9)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  bool bVar6;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_10 = 0;
  iVar3 = 2;
  bVar6 = true;
  pcVar4 = *param_8;
  pcVar5 = "(";
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *pcVar4 == *pcVar5;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    expression(param_4,1,param_5 + -1,param_6,param_7,param_8,param_9,&local_20,&local_14,&local_10)
    ;
    local_8 = *param_2;
    IParse_Get_Next_Statement_Start_And_End(param_1,&local_8,param_3,param_4,&local_18,&local_c);
    iVar3 = local_c;
    local_8 = local_c + 1;
    iVar1 = IParse_Get_Else_Start_And_End(param_1,&local_8,param_3,param_4,&local_1c,&local_c);
    if (iVar1 == 0) {
      local_c = iVar3;
    }
    if (local_14 == 0) {
      piVar2 = &local_1c;
      iVar3 = local_c;
    }
    else {
      piVar2 = &local_18;
    }
    do_parse(param_1,piVar2,iVar3,param_4);
    *param_2 = local_c + 1;
  }
  else {
    local_10 = -1;
  }
  return local_10;
}
