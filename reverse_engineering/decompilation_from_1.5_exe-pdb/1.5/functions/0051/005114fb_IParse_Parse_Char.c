/*
 * Entry: 005114fb
 * Name: IParse_Parse_Char
 * Namespace: Global
 * Signature: int IParse_Parse_Char(_domain * param_1, int param_2, int * param_3, double * param_4, char[80] * param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
IParse_Parse_Char(_domain *param_1,int param_2,int *param_3,double *param_4,char (*param_5) [80],
                 int *param_6)

{
  char cVar1;
  _variable_struct *p_Var2;
  char *pcVar3;
  char *_Dest;
  int iVar4;
  char *pcVar5;
  bool bVar6;
  
  iVar4 = 2;
  bVar6 = true;
  pcVar3 = param_5[1];
  pcVar5 = "=";
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar6 = *pcVar3 == *pcVar5;
    pcVar3 = pcVar3 + 1;
    pcVar5 = pcVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    p_Var2 = IParse_Get_New_Variable(4,*param_5);
    iVar4 = (int)param_5[3][0];
  }
  else {
    if (param_2 == 1) {
      p_Var2 = IParse_Get_New_Variable(4,*param_5);
      goto LAB_005115fb;
    }
    iVar4 = 2;
    bVar6 = true;
    pcVar3 = param_5[1];
    pcVar5 = "[";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar6 = *pcVar3 == *pcVar5;
      pcVar3 = pcVar3 + 1;
      pcVar5 = pcVar5 + 1;
    } while (bVar6);
    if ((!bVar6) || (param_2 != 4)) {
      iVar4 = 2;
      bVar6 = true;
      pcVar3 = param_5[1];
      pcVar5 = "[";
      do {
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        bVar6 = *pcVar3 == *pcVar5;
        pcVar3 = pcVar3 + 1;
        pcVar5 = pcVar5 + 1;
      } while (bVar6);
      if ((!bVar6) || (param_2 != 6)) {
        return -1;
      }
      p_Var2 = IParse_Get_New_Variable(10,*param_5);
      _Dest = calloc(1,param_3[2]);
      p_Var2->string_value = _Dest;
      pcVar3 = param_5[5];
      p_Var2->int_value = param_3[2];
      pcVar5 = pcVar3;
      do {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      strncpy(_Dest,param_5[5] + 1,(size_t)(pcVar5 + (-2 - (int)(param_5[5] + 1))));
      do {
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      p_Var2->string_value[(int)(pcVar3 + (-2 - (int)(param_5[5] + 1)))] = '\0';
      goto LAB_005115fb;
    }
    p_Var2 = IParse_Get_New_Variable(10,*param_5);
    pcVar3 = calloc(1,param_3[2]);
    p_Var2->string_value = pcVar3;
    iVar4 = param_3[2];
  }
  p_Var2->int_value = iVar4;
LAB_005115fb:
  p_Var2->next_variable = param_1->variables;
  param_1->number_of_variables = param_1->number_of_variables + 1;
  param_1->variables = p_Var2;
  return 0;
}
