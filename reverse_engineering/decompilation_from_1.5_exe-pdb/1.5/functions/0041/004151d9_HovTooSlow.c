/*
 * Entry: 004151d9
 * Name: HovTooSlow
 * Namespace: Global
 * Signature: int HovTooSlow(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl HovTooSlow(_OBJ76 *param_1,_OBJ76 *param_2)

{
  VEHICLE *pVVar1;
  
  pVVar1 = get_obj_vhcl(param_1);
  if ((pVVar1->euler).v_mag < 5.0) {
    return 1;
  }
  return 0;
}
