/*
 * Entry: 0059c0f0
 * Name: ov_bitrate
 * Namespace: Global
 * Signature: long ov_bitrate(OggVorbis_File * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl ov_bitrate(OggVorbis_File *param_1,int param_2)

{
  long lVar1;
  uint extraout_EAX;
  long extraout_EAX_00;
  undefined4 extraout_EAX_01;
  long extraout_EAX_02;
  int extraout_EDX;
  undefined4 extraout_EDX_00;
  bool bVar2;
  double dVar3;
  uint local_14;
  int iStack_10;
  int local_c;
  
  if (param_1->ready_state < 2) {
    lVar1 = -0x83;
  }
  else if (param_2 < param_1->links) {
    if ((param_1->seekable == 0) && (param_2 != 0)) {
      lVar1 = ov_bitrate(param_1,0);
    }
    else if (param_2 < 0) {
      local_14 = 0;
      iStack_10 = 0;
      for (local_c = 0; local_c < param_1->links; local_c = local_c + 1) {
        _allmul();
        bVar2 = CARRY4(extraout_EAX,local_14);
        local_14 = extraout_EAX + local_14;
        iStack_10 = iStack_10 + extraout_EDX + (uint)bVar2;
      }
      dVar3 = ov_time_total(param_1,-1);
      floor((double)((float)((float10)CONCAT44(iStack_10,local_14) / (float10)dVar3) + 0.5));
      _ftol2_sse();
      lVar1 = extraout_EAX_00;
    }
    else if (param_1->seekable == 0) {
      if (param_1->vi[param_2].bitrate_nominal < 1) {
        if (param_1->vi[param_2].bitrate_upper < 1) {
          lVar1 = -1;
        }
        else if (param_1->vi[param_2].bitrate_lower < 1) {
          lVar1 = param_1->vi[param_2].bitrate_upper;
        }
        else {
          lVar1 = (param_1->vi[param_2].bitrate_upper + param_1->vi[param_2].bitrate_lower) / 2;
        }
      }
      else {
        lVar1 = param_1->vi[param_2].bitrate_nominal;
      }
    }
    else {
      _allmul();
      dVar3 = ov_time_total(param_1,param_2);
      floor((double)CONCAT44(extraout_EDX_00,extraout_EAX_01) / dVar3 + 0.5);
      _ftol2_sse();
      lVar1 = extraout_EAX_02;
    }
  }
  else {
    lVar1 = -0x83;
  }
  return lVar1;
}
