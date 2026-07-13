/*
 * Entry: 00511b98
 * Name: IParse_Parse_Struct_Array
 * Namespace: Global
 * Signature: int IParse_Parse_Struct_Array(_domain * param_1, char * param_2, int param_3, int * param_4, double * param_5, char[80] * param_6, int * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
IParse_Parse_Struct_Array
          (_domain *param_1,char *param_2,int param_3,int *param_4,double *param_5,
          char (*param_6) [80],int *param_7)

{
  _struct_list_element *p_Var1;
  char (*pacVar2) [80];
  _variable_struct *p_Var3;
  int iVar4;
  int local_18;
  char *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = 0;
  iVar4 = 3;
  p_Var1 = IParse_Which_Struct(param_1,param_2);
  for (pacVar2 = param_6 + 3; (*pacVar2)[0] != ']'; pacVar2 = pacVar2 + 1) {
    iVar4 = iVar4 + 1;
  }
  expression(param_1,2,iVar4 + -1,param_4,param_5,param_6,param_7,&local_18,&local_10,&local_c);
  p_Var3 = IParse_Get_New_Variable(8,*param_6);
  p_Var3->the_struct_el = p_Var1;
  local_14 = calloc(1,p_Var1->struct_length * local_10);
  p_Var3->string_value = local_14;
  local_8 = iVar4 + 4;
  while (local_8 < param_3 + -1) {
    IParse_Fill_All_Fields(param_1,p_Var1,&local_14,param_4,param_5,param_6,param_7,&local_8);
    p_Var3->struct_element_count = p_Var3->struct_element_count + 1;
  }
  p_Var3->next_variable = param_1->variables;
  param_1->number_of_variables = param_1->number_of_variables + 1;
  param_1->variables = p_Var3;
  return local_c;
}
