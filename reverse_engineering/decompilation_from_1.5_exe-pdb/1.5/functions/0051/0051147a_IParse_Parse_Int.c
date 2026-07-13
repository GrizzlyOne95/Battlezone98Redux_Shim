/*
 * Entry: 0051147a
 * Name: IParse_Parse_Int
 * Namespace: Global
 * Signature: int IParse_Parse_Int(_domain * param_1, int param_2, int * param_3, double * param_4, char[80] * param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
IParse_Parse_Int(_domain *param_1,int param_2,int *param_3,double *param_4,char (*param_5) [80],
                int *param_6)

{
  char (*pacVar1) [80];
  _variable_struct *p_Var2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  bool bVar6;
  double dVar7;
  int local_8;
  
  pacVar1 = param_5;
  local_8 = 0;
  iVar3 = 2;
  bVar6 = true;
  pcVar4 = param_5[1];
  pcVar5 = "=";
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *pcVar4 == *pcVar5;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    p_Var2 = IParse_Get_New_Variable(1,*param_5);
    dVar7 = expression(param_1,2,param_2 + -1,param_3,param_4,pacVar1,param_6,(int *)&param_5,
                       &p_Var2->int_value,&local_8);
    p_Var2->double_value = dVar7;
  }
  else {
    if (param_2 != 1) {
      return -1;
    }
    p_Var2 = IParse_Get_New_Variable(1,*param_5);
  }
  p_Var2->next_variable = param_1->variables;
  param_1->number_of_variables = param_1->number_of_variables + 1;
  param_1->variables = p_Var2;
  return local_8;
}
