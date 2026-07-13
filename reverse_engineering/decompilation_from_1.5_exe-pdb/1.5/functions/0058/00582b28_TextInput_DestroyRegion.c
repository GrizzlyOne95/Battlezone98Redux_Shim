/*
 * Entry: 00582b28
 * Name: TextInput_DestroyRegion
 * Namespace: Global
 * Signature: void TextInput_DestroyRegion(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TextInput_DestroyRegion(void *param_1)

{
  free(*(void **)((int)param_1 + 8));
  DeleteWrapper(&region_list,param_1);
  return;
}
