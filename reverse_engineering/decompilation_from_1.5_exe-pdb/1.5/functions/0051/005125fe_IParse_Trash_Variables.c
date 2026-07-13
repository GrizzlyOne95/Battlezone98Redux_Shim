/*
 * Entry: 005125fe
 * Name: IParse_Trash_Variables
 * Namespace: Global
 * Signature: void IParse_Trash_Variables(_variable_struct * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl IParse_Trash_Variables(_variable_struct *param_1)

{
  if (param_1 != (_variable_struct *)0x0) {
    IParse_Trash_Variables(param_1->next_variable);
    if (param_1->variable_name != (char *)0x0) {
      free(param_1->variable_name);
    }
    if (param_1->string_value != (char *)0x0) {
      free(param_1->string_value);
    }
    free(param_1);
  }
  return;
}
