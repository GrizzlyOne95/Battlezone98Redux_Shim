/*
 * Entry: 005a2800
 * Name: vorbis_analysis_init
 * Namespace: Global
 * Signature: int vorbis_analysis_init(vorbis_dsp_state * param_1, vorbis_info * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_analysis_init(vorbis_dsp_state *param_1,vorbis_info *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  vorbis_look_psy_global *pvVar3;
  envelope_lookup *peVar4;
  
  iVar2 = _vds_shared_init(param_1,param_2,1);
  if (iVar2 != 0) {
    return 1;
  }
  puVar1 = param_1->backend_state;
  pvVar3 = _vp_global_look(param_2);
  puVar1[0xf] = pvVar3;
  peVar4 = calloc(1,0xb4);
  *puVar1 = peVar4;
  _ve_envelope_init(peVar4,param_2);
  vorbis_bitrate_init(param_2,(bitrate_manager_state *)(puVar1 + 0x14));
  *(undefined4 *)&param_1->sequence = 3;
  *(undefined4 *)((int)&param_1->sequence + 4) = 0;
  return 0;
}
