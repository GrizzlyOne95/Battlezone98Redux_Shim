/*
 * Entry: 00405d7d
 * Name: get_obj_vhcl
 * Namespace: Global
 * Signature: VEHICLE * get_obj_vhcl(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VEHICLE * __cdecl get_obj_vhcl(_OBJ76 *param_1)

{
  int iVar1;
  
  iVar1 = is_vhcl(param_1);
  if (iVar1 != 0) {
    return param_1->class_ptr;
  }
  return (VEHICLE *)0x0;
}
