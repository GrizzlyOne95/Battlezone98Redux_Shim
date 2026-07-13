/*
 * Entry: 004810cd
 * Name: VolumeBump
 * Namespace: Global
 * Signature: int VolumeBump(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl VolumeBump(_gas_object *param_1)

{
  uint uVar1;
  
  uVar1 = (param_1->gc).flags;
  if ((((uVar1 & 2) == 0) || (GM->masterVolume1 != 0)) &&
     (((uVar1 & 4) == 0 || (GM->masterVolume2 != 0)))) {
    return 0;
  }
  return 1;
}
