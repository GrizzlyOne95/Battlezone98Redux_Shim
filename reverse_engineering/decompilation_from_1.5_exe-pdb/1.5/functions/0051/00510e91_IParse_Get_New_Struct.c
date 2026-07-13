/*
 * Entry: 00510e91
 * Name: IParse_Get_New_Struct
 * Namespace: Global
 * Signature: _struct_list_element * IParse_Get_New_Struct(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_struct_list_element * __cdecl IParse_Get_New_Struct(char *param_1)

{
  char cVar1;
  _struct_list_element *p_Var2;
  char *pcVar3;
  int iVar4;
  
  p_Var2 = calloc(1,0x10);
  pcVar3 = param_1;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  pcVar3 = calloc(1,(size_t)(pcVar3 + (1 - (int)(param_1 + 1))));
  iVar4 = (int)pcVar3 - (int)param_1;
  do {
    cVar1 = *param_1;
    param_1[iVar4] = cVar1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  p_Var2->struct_length = 0;
  p_Var2->the_definition = (_field_def *)0x0;
  p_Var2->next_struct = (_struct_list_element *)0x0;
  p_Var2->struct_name = pcVar3;
  return p_Var2;
}
