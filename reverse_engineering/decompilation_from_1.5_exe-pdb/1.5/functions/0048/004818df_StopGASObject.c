/*
 * Entry: 004818df
 * Name: StopGASObject
 * Namespace: Global
 * Signature: int StopGASObject(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl StopGASObject(_gas_object *param_1)

{
  int iVar1;
  
  param_1->flags = param_1->flags & 0xfffffffb;
  iVar1 = IsObjectPlaying(param_1);
  if (iVar1 == 0) {
    return 0;
  }
  (**(code **)((int)*param_1->dsb + 0x48))(param_1->dsb);
  return 1;
}
