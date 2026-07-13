/*
 * Entry: 00510ee2
 * Name: IParse_Get_New_Variable
 * Namespace: Global
 * Signature: _variable_struct * IParse_Get_New_Variable(int param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_variable_struct * __cdecl IParse_Get_New_Variable(int param_1,char *param_2)

{
  char cVar1;
  _variable_struct *p_Var2;
  char *pcVar3;
  int iVar4;
  
  p_Var2 = calloc(1,0x28);
  pcVar3 = param_2;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  pcVar3 = calloc(1,(size_t)(pcVar3 + (1 - (int)(param_2 + 1))));
  iVar4 = (int)pcVar3 - (int)param_2;
  do {
    cVar1 = *param_2;
    param_2[iVar4] = cVar1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  p_Var2->variable_type = param_1;
  p_Var2->variable_name = pcVar3;
  p_Var2->the_struct_el = (_struct_list_element *)0x0;
  p_Var2->string_value = (char *)0x0;
  p_Var2->next_array_variable = (_variable_struct *)0x0;
  p_Var2->next_variable = (_variable_struct *)0x0;
  p_Var2->struct_element_count = 0;
  return p_Var2;
}
