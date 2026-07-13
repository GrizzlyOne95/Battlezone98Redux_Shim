/*
 * Entry: 005a2870
 * Name: vorbis_synthesis_init
 * Namespace: Global
 * Signature: int vorbis_synthesis_init(vorbis_dsp_state * param_1, vorbis_info * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_synthesis_init(vorbis_dsp_state *param_1,vorbis_info *param_2)

{
  int iVar1;
  
  iVar1 = _vds_shared_init(param_1,param_2,0);
  if (iVar1 != 0) {
    vorbis_dsp_clear(param_1);
    return 1;
  }
  vorbis_synthesis_restart(param_1);
  return 0;
}
