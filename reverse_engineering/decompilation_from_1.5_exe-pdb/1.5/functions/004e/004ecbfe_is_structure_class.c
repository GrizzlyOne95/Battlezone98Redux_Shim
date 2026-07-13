/*
 * Entry: 004ecbfe
 * Name: is_structure_class
 * Namespace: Global
 * Signature: int is_structure_class(OBJECT_CLASS_T param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl is_structure_class(OBJECT_CLASS_T param_1)

{
  if (((param_1 != CLASS_ID_STRUCTURE1) && (param_1 != CLASS_ID_SIGN)) &&
     (((int)param_1 < 7 || ((8 < (int)param_1 && (param_1 != CLASS_ID_STRUCTURE2)))))) {
    return 0;
  }
  return 1;
}
