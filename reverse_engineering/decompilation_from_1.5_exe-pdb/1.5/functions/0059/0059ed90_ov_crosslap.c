/*
 * Entry: 0059ed90
 * Name: ov_crosslap
 * Namespace: Global
 * Signature: int ov_crosslap(OggVorbis_File * param_1, OggVorbis_File * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

int __cdecl ov_crosslap(OggVorbis_File *param_1,OggVorbis_File *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 **ppuVar4;
  undefined4 uStackY_4c;
  undefined1 *local_40 [2];
  uint local_38;
  float *local_34;
  int local_30;
  int local_2c;
  vorbis_info *local_28;
  undefined1 *local_24;
  int local_20;
  int local_1c;
  float *local_18;
  int local_14;
  vorbis_info *local_10;
  int local_c;
  undefined4 local_8;
  
  local_38 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_1 == param_2) {
    local_20 = 0;
  }
  else if (param_1->ready_state < 2) {
    local_20 = -0x83;
  }
  else if (param_2->ready_state < 2) {
    local_20 = -0x83;
  }
  else {
    local_20 = _ov_initset(param_1);
    if ((local_20 == 0) && (local_20 = _ov_initprime(param_2), local_20 == 0)) {
      uStackY_4c = 0x59ee1a;
      local_10 = ov_info(param_1,-1);
      uStackY_4c = 0x59ee2b;
      local_28 = ov_info(param_2,-1);
      local_c = ov_halfrate_p(param_1);
      local_2c = ov_halfrate_p(param_2);
      iVar1 = local_10->channels;
      iVar2 = iVar1 * -4;
      local_40[1] = (undefined1 *)(local_40 + -iVar1);
      local_24 = (undefined1 *)(local_40 + -iVar1);
      *(undefined4 *)(&stack0xffffffbc + iVar2) = 0;
      *(vorbis_info **)(&stack0xffffffb8 + iVar2) = local_10;
      (&uStackY_4c)[-iVar1] = 0x59ee71;
      iVar3 = vorbis_info_blocksize
                        (*(vorbis_info **)(&stack0xffffffb8 + iVar2),
                         *(int *)(&stack0xffffffbc + iVar2));
      local_1c = iVar3 >> ((char)local_c + 1U & 0x1f);
      *(undefined4 *)(&stack0xffffffbc + iVar2) = 0;
      *(vorbis_info **)(&stack0xffffffb8 + iVar2) = local_28;
      (&uStackY_4c)[-iVar1] = 0x59ee8a;
      iVar3 = vorbis_info_blocksize
                        (*(vorbis_info **)(&stack0xffffffb8 + iVar2),
                         *(int *)(&stack0xffffffbc + iVar2));
      local_30 = iVar3 >> ((char)local_2c + 1U & 0x1f);
      *(undefined4 *)(&stack0xffffffbc + iVar2) = 0;
      *(vorbis_dsp_state **)(&stack0xffffffb8 + iVar2) = &param_1->vd;
      (&uStackY_4c)[-iVar1] = 0x59eea9;
      local_18 = vorbis_window(*(vorbis_dsp_state **)(&stack0xffffffb8 + iVar2),
                               *(int *)(&stack0xffffffbc + iVar2));
      *(undefined4 *)(&stack0xffffffbc + iVar2) = 0;
      *(vorbis_dsp_state **)(&stack0xffffffb8 + iVar2) = &param_2->vd;
      (&uStackY_4c)[-iVar1] = 0x59eec0;
      local_34 = vorbis_window(*(vorbis_dsp_state **)(&stack0xffffffb8 + iVar2),
                               *(int *)(&stack0xffffffbc + iVar2));
      ppuVar4 = local_40 + -iVar1;
      for (local_14 = 0; iVar1 = local_1c, local_14 < local_10->channels; local_14 = local_14 + 1) {
        *(undefined4 *)((int)ppuVar4 + -4) = 0x59eeee;
        iVar1 = iVar1 * -4;
        local_40[0] = (undefined1 *)((int)ppuVar4 + iVar1);
        *(undefined1 **)(local_24 + local_14 * 4) = (undefined1 *)((int)ppuVar4 + iVar1);
        ppuVar4 = (undefined1 **)((int)ppuVar4 + iVar1);
      }
      *(int *)((int)ppuVar4 + -4) = local_1c;
      *(undefined1 **)((int)ppuVar4 + -8) = local_24;
      *(vorbis_dsp_state **)((int)ppuVar4 + -0xc) = &param_1->vd;
      *(vorbis_info **)((int)ppuVar4 + -0x10) = local_10;
      *(OggVorbis_File **)((int)ppuVar4 + -0x14) = param_1;
      *(undefined4 *)((int)ppuVar4 + -0x18) = 0x59ef1e;
      _ov_getlap(*(OggVorbis_File **)((int)ppuVar4 + -0x14),*(vorbis_info **)((int)ppuVar4 + -0x10),
                 *(vorbis_dsp_state **)((int)ppuVar4 + -0xc),*(float ***)((int)ppuVar4 + -8),
                 *(int *)((int)ppuVar4 + -4));
      *(undefined4 **)((int)ppuVar4 + -4) = &local_8;
      *(vorbis_dsp_state **)((int)ppuVar4 + -8) = &param_2->vd;
      *(undefined4 *)((int)ppuVar4 + -0xc) = 0x59ef33;
      vorbis_synthesis_lapout
                (*(vorbis_dsp_state **)((int)ppuVar4 + -8),*(float ****)((int)ppuVar4 + -4));
      *(float **)((int)ppuVar4 + -4) = local_34;
      *(float **)((int)ppuVar4 + -8) = local_18;
      *(int *)((int)ppuVar4 + -0xc) = local_28->channels;
      *(int *)((int)ppuVar4 + -0x10) = local_10->channels;
      *(int *)((int)ppuVar4 + -0x14) = local_30;
      *(int *)((int)ppuVar4 + -0x18) = local_1c;
      *(undefined1 **)((int)ppuVar4 + -0x1c) = local_24;
      *(undefined4 *)((int)ppuVar4 + -0x20) = local_8;
      *(undefined4 *)((int)ppuVar4 + -0x24) = 0x59ef61;
      _ov_splice(*(float ***)((int)ppuVar4 + -0x20),*(float ***)((int)ppuVar4 + -0x1c),
                 *(int *)((int)ppuVar4 + -0x18),*(int *)((int)ppuVar4 + -0x14),
                 *(int *)((int)ppuVar4 + -0x10),*(int *)((int)ppuVar4 + -0xc),
                 *(float **)((int)ppuVar4 + -8),*(float **)((int)ppuVar4 + -4));
      local_20 = 0;
    }
  }
  return local_20;
}
