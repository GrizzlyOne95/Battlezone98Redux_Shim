/*
 * Entry: 004ed18f
 * Name: is_structure
 * Namespace: Global
 * Signature: int is_structure(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl is_structure(_OBJ76 *param_1)

{
  int iVar1;
  
  iVar1 = is_structure_class(param_1->class_id);
  return iVar1;
}
