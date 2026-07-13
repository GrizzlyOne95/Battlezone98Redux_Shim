/*
 * Entry: 00512634
 * Name: IParse_Trash_Field_Definitions
 * Namespace: Global
 * Signature: void IParse_Trash_Field_Definitions(_field_def * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl IParse_Trash_Field_Definitions(_field_def *param_1)

{
  if (param_1 != (_field_def *)0x0) {
    IParse_Trash_Field_Definitions(param_1->next_field);
    if (param_1->field_name != (char *)0x0) {
      free(param_1->field_name);
    }
    free(param_1);
  }
  return;
}
