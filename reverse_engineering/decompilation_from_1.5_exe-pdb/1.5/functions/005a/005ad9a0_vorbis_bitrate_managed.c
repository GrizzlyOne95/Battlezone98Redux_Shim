/*
 * Entry: 005ad9a0
 * Name: vorbis_bitrate_managed
 * Namespace: Global
 * Signature: int vorbis_bitrate_managed(vorbis_block * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_bitrate_managed(vorbis_block *param_1)

{
  int *piVar1;
  
  piVar1 = (int *)((int)param_1->vd->backend_state + 0x50);
  if ((piVar1 != (int *)0x0) && (*piVar1 != 0)) {
    return 1;
  }
  return 0;
}
