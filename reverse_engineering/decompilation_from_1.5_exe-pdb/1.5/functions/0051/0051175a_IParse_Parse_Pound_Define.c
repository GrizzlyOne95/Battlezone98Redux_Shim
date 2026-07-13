/*
 * Entry: 0051175a
 * Name: IParse_Parse_Pound_Define
 * Namespace: Global
 * Signature: int IParse_Parse_Pound_Define(_domain * param_1, int param_2, int * param_3, double * param_4, char[80] * param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
IParse_Parse_Pound_Define
          (_domain *param_1,int param_2,int *param_3,double *param_4,char (*param_5) [80],
          int *param_6)

{
  char cVar1;
  _variable_struct *p_Var2;
  char *pcVar3;
  char *_Dest;
  char *pcVar4;
  double dVar5;
  int local_c;
  int local_8;
  
  local_8 = 0;
  pcVar4 = param_5[1];
  if (*pcVar4 == '\"') {
    p_Var2 = IParse_Get_New_Variable(10,*param_5);
    pcVar3 = pcVar4;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    _Dest = calloc(1,(size_t)(pcVar3 + (-2 - (int)(param_5[1] + 1))));
    p_Var2->string_value = _Dest;
    pcVar3 = pcVar4;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    p_Var2->int_value = (int)(pcVar3 + (-2 - (int)(param_5[1] + 1)));
    pcVar3 = pcVar4;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    strncpy(_Dest,param_5[1] + 1,(size_t)(pcVar3 + (-2 - (int)(param_5[1] + 1))));
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    p_Var2->string_value[(int)(pcVar4 + (-3 - (int)(param_5[1] + 1)))] = '\0';
  }
  else {
    p_Var2 = IParse_Get_New_Variable(3,*param_5);
    dVar5 = expression(param_1,1,param_2 + -1,param_3,param_4,param_5,param_6,&local_c,
                       &p_Var2->int_value,&local_8);
    p_Var2->double_value = dVar5;
    if (local_c != 0) {
      p_Var2->variable_type = 1;
    }
  }
  p_Var2->next_variable = param_1->variables;
  param_1->number_of_variables = param_1->number_of_variables + 1;
  param_1->variables = p_Var2;
  return local_8;
}
