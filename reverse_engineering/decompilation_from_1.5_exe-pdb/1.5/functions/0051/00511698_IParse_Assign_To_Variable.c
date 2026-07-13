/*
 * Entry: 00511698
 * Name: IParse_Assign_To_Variable
 * Namespace: Global
 * Signature: int IParse_Assign_To_Variable(_domain * param_1, char * param_2, int param_3, int * param_4, double * param_5, char[80] * param_6, int * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
IParse_Assign_To_Variable
          (_domain *param_1,char *param_2,int param_3,int *param_4,double *param_5,
          char (*param_6) [80],int *param_7)

{
  char cVar1;
  int iVar2;
  _variable_struct *p_Var3;
  char *pcVar4;
  char *pcVar5;
  double dVar6;
  int local_c;
  int local_8;
  
  local_8 = 0;
  p_Var3 = IParse_Which_Variable(param_1,param_2);
  if (p_Var3 == (_variable_struct *)0x0) {
    local_8 = -2;
  }
  else {
    iVar2 = p_Var3->variable_type;
    if (((iVar2 == 1) || (iVar2 == 2)) || (iVar2 == 3)) {
      dVar6 = expression(param_1,1,param_3 + -1,param_4,param_5,param_6,param_7,&local_c,
                         &p_Var3->int_value,&local_8);
      p_Var3->double_value = dVar6;
    }
    else if (iVar2 == 4) {
      p_Var3->int_value = (int)param_6[2][0];
    }
    else if (iVar2 == 10) {
      pcVar5 = param_6[1];
      pcVar4 = pcVar5;
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
      strncpy(p_Var3->string_value,param_6[1] + 1,(size_t)(pcVar4 + (-2 - (int)(param_6[1] + 1))));
      do {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      p_Var3->string_value[(int)(pcVar5 + (-2 - (int)(param_6[1] + 1)))] = '\0';
    }
    else {
      local_8 = -1;
    }
  }
  return local_8;
}
