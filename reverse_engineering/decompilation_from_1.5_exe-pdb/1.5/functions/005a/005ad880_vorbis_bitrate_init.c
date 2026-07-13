/*
 * Entry: 005ad880
 * Name: vorbis_bitrate_init
 * Namespace: Global
 * Signature: void vorbis_bitrate_init(vorbis_info * param_1, bitrate_manager_state * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl vorbis_bitrate_init(vorbis_info *param_1,bitrate_manager_state *param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  long extraout_EAX;
  long extraout_EAX_00;
  long extraout_EAX_01;
  long extraout_EAX_02;
  
  piVar1 = param_1->codec_setup;
  memset(param_2,0,0x30);
  if ((piVar1 + 0x348 != (int *)0x0) && (0 < piVar1[0x34b])) {
    iVar2 = *piVar1;
    iVar3 = piVar1[1];
    dVar4 = (double)(iVar2 >> 1);
    dVar5 = (double)param_1->rate;
    param_2->managed = 1;
    param_2->short_per_long = iVar3 / iVar2;
    floor(((double)piVar1[0x348] * dVar4) / dVar5 + 0.5);
    _ftol2_sse();
    param_2->avg_bitsper = extraout_EAX;
    floor(((double)piVar1[0x349] * dVar4) / dVar5 + 0.5);
    _ftol2_sse();
    param_2->min_bitsper = extraout_EAX_00;
    floor(((double)piVar1[0x34a] * dVar4) / dVar5 + 0.5);
    _ftol2_sse();
    param_2->avgfloat = 7.0;
    param_2->max_bitsper = extraout_EAX_01;
    _ftol2_sse();
    param_2->minmax_reservoir = extraout_EAX_02;
    param_2->avg_reservoir = extraout_EAX_02;
  }
  return;
}
