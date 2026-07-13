/*
 * Entry: 0059f350
 * Name: _ov_64_seek_lap
 * Namespace: Global
 * Signature: int _ov_64_seek_lap(OggVorbis_File * param_1, long64 param_2, _func___cdecl_int_OggVorbis_File_ptr_long64 * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

int __cdecl
_ov_64_seek_lap(OggVorbis_File *param_1,long64 param_2,
               _func___cdecl_int_OggVorbis_File_ptr_long64 *param_3)

{
  int iVar1;
  undefined1 **ppuVar2;
  int *piVar3;
  undefined4 in_stack_00000008;
  undefined1 *local_40 [2];
  uint local_38;
  float *local_34;
  int local_30;
  int local_2c;
  int local_28;
  undefined1 *local_24;
  int local_20;
  int local_1c;
  float *local_18;
  vorbis_info *local_14;
  int local_10;
  int local_c;
  undefined4 local_8;
  
  local_38 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_1->ready_state < 2) {
    local_20 = -0x83;
  }
  else {
    local_20 = _ov_initset(param_1);
    if (local_20 == 0) {
      local_14 = ov_info(param_1,-1);
      local_c = ov_halfrate_p(param_1);
      local_28 = local_14->channels;
      local_1c = vorbis_info_blocksize(local_14,0);
      local_1c = local_1c >> ((char)local_c + 1U & 0x1f);
      local_18 = vorbis_window(&param_1->vd,0);
      local_40[1] = (undefined1 *)(local_40 + -local_28);
      local_24 = (undefined1 *)(local_40 + -local_28);
      ppuVar2 = local_40 + -local_28;
      for (local_10 = 0; iVar1 = local_1c, local_10 < local_28; local_10 = local_10 + 1) {
        *(undefined4 *)((int)ppuVar2 + -4) = 0x59f422;
        iVar1 = iVar1 * -4;
        local_40[0] = (undefined1 *)((int)ppuVar2 + iVar1);
        *(undefined1 **)(local_24 + local_10 * 4) = (undefined1 *)((int)ppuVar2 + iVar1);
        ppuVar2 = (undefined1 **)((int)ppuVar2 + iVar1);
      }
      *(int *)((int)ppuVar2 + -4) = local_1c;
      *(undefined1 **)((int)ppuVar2 + -8) = local_24;
      *(vorbis_dsp_state **)((int)ppuVar2 + -0xc) = &param_1->vd;
      *(vorbis_info **)((int)ppuVar2 + -0x10) = local_14;
      *(OggVorbis_File **)((int)ppuVar2 + -0x14) = param_1;
      *(undefined4 *)((int)ppuVar2 + -0x18) = 0x59f452;
      _ov_getlap(*(OggVorbis_File **)((int)ppuVar2 + -0x14),*(vorbis_info **)((int)ppuVar2 + -0x10),
                 *(vorbis_dsp_state **)((int)ppuVar2 + -0xc),*(float ***)((int)ppuVar2 + -8),
                 *(int *)((int)ppuVar2 + -4));
      *(undefined4 *)((int)ppuVar2 + -4) = (undefined4)param_2;
      *(undefined4 *)((int)ppuVar2 + -8) = in_stack_00000008;
      *(OggVorbis_File **)((int)ppuVar2 + -0xc) = param_1;
      piVar3 = (int *)((int)ppuVar2 + -0x10);
      *(undefined4 *)((int)ppuVar2 + -0x10) = 0x59f464;
      local_20 = (*param_2._4_4_)();
      if (local_20 == 0) {
        piVar3[2] = (int)param_1;
        piVar3[1] = 0x59f481;
        local_20 = _ov_initprime((OggVorbis_File *)piVar3[2]);
        if (local_20 == 0) {
          piVar3[2] = 0xffffffff;
          piVar3[1] = (int)param_1;
          *piVar3 = 0x59f4a0;
          local_14 = ov_info((OggVorbis_File *)piVar3[1],piVar3[2]);
          local_2c = local_14->channels;
          piVar3[2] = 0;
          piVar3[1] = (int)local_14;
          *piVar3 = 0x59f4ba;
          iVar1 = vorbis_info_blocksize((vorbis_info *)piVar3[1],piVar3[2]);
          local_30 = iVar1 >> ((char)local_c + 1U & 0x1f);
          piVar3[2] = 0;
          piVar3[1] = (int)&param_1->vd;
          *piVar3 = 0x59f4d8;
          local_34 = vorbis_window((vorbis_dsp_state *)piVar3[1],piVar3[2]);
          piVar3[2] = (int)&local_8;
          piVar3[1] = (int)&param_1->vd;
          *piVar3 = 0x59f4f1;
          vorbis_synthesis_lapout((vorbis_dsp_state *)piVar3[1],(float ***)piVar3[2]);
          piVar3[2] = (int)local_34;
          piVar3[1] = (int)local_18;
          *piVar3 = local_2c;
          piVar3[-1] = local_28;
          piVar3[-2] = local_30;
          piVar3[-3] = local_1c;
          piVar3[-4] = (int)local_24;
          piVar3[-5] = local_8;
          piVar3[-6] = 0x59f519;
          _ov_splice((float **)piVar3[-5],(float **)piVar3[-4],piVar3[-3],piVar3[-2],piVar3[-1],
                     *piVar3,(float *)piVar3[1],(float *)piVar3[2]);
          local_20 = 0;
        }
      }
    }
  }
  return local_20;
}
