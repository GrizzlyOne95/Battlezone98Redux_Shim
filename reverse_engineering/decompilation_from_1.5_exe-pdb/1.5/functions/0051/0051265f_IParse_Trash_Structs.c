/*
 * Entry: 0051265f
 * Name: IParse_Trash_Structs
 * Namespace: Global
 * Signature: void IParse_Trash_Structs(_struct_list_element * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl IParse_Trash_Structs(_struct_list_element *param_1)

{
  if (param_1 != (_struct_list_element *)0x0) {
    IParse_Trash_Structs(param_1->next_struct);
    if (param_1->struct_name != (char *)0x0) {
      free(param_1->struct_name);
    }
    if (param_1->the_definition != (_field_def *)0x0) {
      IParse_Trash_Field_Definitions(param_1->the_definition);
    }
    free(param_1);
  }
  return;
}
