/*
 * Entry: 00410311
 * Name: IsAlive
 * Namespace: Global
 * Signature: int IsAlive(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsAlive(_OBJ76 *param_1,_OBJ76 *param_2)

{
  VEHICLE *pVVar1;
  
  if ((param_1->flags & 0x200) == 0) {
    pVVar1 = get_obj_vhcl(param_1);
    if ((pVVar1->flags & 0x20) == 0) {
      return 1;
    }
  }
  return 0;
}
