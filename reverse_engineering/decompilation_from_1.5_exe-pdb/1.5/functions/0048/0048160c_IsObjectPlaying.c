/*
 * Entry: 0048160c
 * Name: IsObjectPlaying
 * Namespace: Global
 * Signature: int IsObjectPlaying(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsObjectPlaying(_gas_object *param_1)

{
  if (param_1->dsb == (IDirectSoundBuffer *)0x0) {
    return 0;
  }
  (**(code **)((int)*param_1->dsb + 0x24))(param_1->dsb,&param_1);
  return (uint)param_1 & 1;
}
