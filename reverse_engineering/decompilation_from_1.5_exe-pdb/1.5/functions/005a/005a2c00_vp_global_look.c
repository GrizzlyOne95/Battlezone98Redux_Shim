/*
 * Entry: 005a2c00
 * Name: _vp_global_look
 * Namespace: Global
 * Signature: vorbis_look_psy_global * _vp_global_look(vorbis_info * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vorbis_look_psy_global * __cdecl _vp_global_look(vorbis_info *param_1)

{
  void *pvVar1;
  int iVar2;
  vorbis_look_psy_global *pvVar3;
  
  pvVar1 = param_1->codec_setup;
  pvVar3 = calloc(1,0x24);
  iVar2 = param_1->channels;
  pvVar3->ampmax = -9999.0;
  pvVar3->gi = (vorbis_info_psy_global *)((int)pvVar1 + 0xb34);
  pvVar3->channels = iVar2;
  return pvVar3;
}
