/*
 * Entry: 00510f41
 * Name: IParse_Get_New_Field
 * Namespace: Global
 * Signature: _field_def * IParse_Get_New_Field(int param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_field_def * __cdecl IParse_Get_New_Field(int param_1,char *param_2)

{
  char cVar1;
  _field_def *p_Var2;
  char *pcVar3;
  int iVar4;
  
  p_Var2 = calloc(1,0x10);
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
  p_Var2->next_field = (_field_def *)0x0;
  p_Var2->field_name = pcVar3;
  p_Var2->field_type = param_1;
  return p_Var2;
}
