/*
 * Entry: 00510f91
 * Name: IParse_Insert_Variable
 * Namespace: Global
 * Signature: void IParse_Insert_Variable(_domain * param_1, _variable_struct * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl IParse_Insert_Variable(_domain *param_1,_variable_struct *param_2)

{
  param_2->next_variable = param_1->variables;
  param_1->number_of_variables = param_1->number_of_variables + 1;
  param_1->variables = param_2;
  return;
}
