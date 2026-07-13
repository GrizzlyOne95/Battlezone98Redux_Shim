/*
 * Entry: 0059c620
 * Name: ov_raw_seek
 * Namespace: Global
 * Signature: int ov_raw_seek(OggVorbis_File * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl ov_raw_seek(OggVorbis_File *param_1,long64 param_2)

{
  uint *puVar1;
  int iVar2;
  undefined4 unaff_ESI;
  bool bVar3;
  long64 lVar4;
  uint in_stack_00000008;
  int local_204;
  int local_1e0;
  uint local_1d4;
  int local_1d0;
  int local_1cc;
  ogg_packet local_1c4;
  long local_1a4;
  ogg_page local_1a0;
  int local_190;
  long local_18c;
  int local_188;
  undefined8 local_184;
  uint local_17c;
  int local_178;
  undefined1 local_174 [364];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_1->ready_state < 2) {
    return -0x83;
  }
  if (param_1->seekable == 0) {
    return -0x8a;
  }
  if (((int)param_2 < 0) ||
     ((iVar2 = *(int *)((int)&param_1->end + 4), iVar2 <= (int)param_2 &&
      ((iVar2 < (int)param_2 || ((uint)param_1->end < in_stack_00000008)))))) {
    return -0x83;
  }
  if (2 < param_1->ready_state) {
    iVar2 = *(int *)((int)param_1->offsets + param_1->current_link * 8 + 4);
    if ((iVar2 <= (int)param_2) &&
       ((iVar2 < (int)param_2 ||
        (*(uint *)(param_1->offsets + param_1->current_link) <= in_stack_00000008)))) {
      iVar2 = *(int *)((int)param_1->offsets + param_1->current_link * 8 + 0xc);
      if (((int)param_2 < iVar2) ||
         (((int)param_2 <= iVar2 &&
          (in_stack_00000008 < *(uint *)(param_1->offsets + param_1->current_link + 1)))))
      goto LAB_0059c739;
    }
    _decode_clear(param_1);
  }
LAB_0059c739:
  *(undefined4 *)&param_1->pcm_offset = 0xffffffff;
  *(undefined4 *)((int)&param_1->pcm_offset + 4) = 0xffffffff;
  ogg_stream_reset_serialno(&param_1->os,param_1->current_serialno);
  vorbis_synthesis_restart(&param_1->vd);
  local_178 = _seek_helper(param_1,CONCAT44(unaff_ESI,(int)param_2));
  if (local_178 != 0) {
    *(undefined4 *)&param_1->pcm_offset = 0xffffffff;
    *(undefined4 *)((int)&param_1->pcm_offset + 4) = 0xffffffff;
    ogg_stream_clear(local_174);
    _decode_clear(param_1);
    return -0x89;
  }
  local_1a4 = 0;
  local_17c = 0;
  local_18c = 0;
  local_188 = 0;
  local_190 = 0;
  local_184 = -1;
  ogg_stream_init(local_174,param_1->current_serialno);
  ogg_stream_reset(local_174);
LAB_0059c804:
  if ((2 < param_1->ready_state) && (iVar2 = ogg_stream_packetout(local_174,&local_1c4), 0 < iVar2))
  {
    if (param_1->vi[param_1->current_link].codec_setup != (void *)0x0) {
      local_18c = vorbis_packet_blocksize(param_1->vi + param_1->current_link,&local_1c4);
      if (local_18c < 0) {
        ogg_stream_packetout(&param_1->os,0);
        local_18c = 0;
      }
      else if ((local_188 == 0) || (local_190 != 0)) {
        if (local_1a4 != 0) {
          local_17c = (local_1a4 + local_18c >> 2) + local_17c;
        }
      }
      else {
        ogg_stream_packetout(&param_1->os,0);
      }
      if (((uint)local_1c4.granulepos & local_1c4.granulepos._4_4_) != 0xffffffff) {
        iVar2 = param_1->current_link;
        puVar1 = (uint *)(param_1->pcmlengths + iVar2 * 2);
        local_1d4 = (uint)local_1c4.granulepos - *puVar1;
        local_1d0 = (local_1c4.granulepos._4_4_ -
                    *(int *)((int)param_1->pcmlengths + iVar2 * 0x10 + 4)) -
                    (uint)((uint)local_1c4.granulepos < *puVar1);
        if ((local_1d0 < 1) && (local_1d0 < 0)) {
          local_1d4 = 0;
          local_1d0 = 0;
        }
        for (local_1cc = 0; local_1cc < iVar2; local_1cc = local_1cc + 1) {
          puVar1 = (uint *)(param_1->pcmlengths + local_1cc * 2 + 1);
          bVar3 = CARRY4(local_1d4,*puVar1);
          local_1d4 = local_1d4 + *puVar1;
          local_1d0 = local_1d0 + *(int *)((int)param_1->pcmlengths + local_1cc * 0x10 + 0xc) +
                      (uint)bVar3;
        }
        *(uint *)&param_1->pcm_offset = local_1d4 - local_17c;
        *(uint *)((int)&param_1->pcm_offset + 4) =
             (local_1d0 - ((int)local_17c >> 0x1f)) - (uint)(local_1d4 < local_17c);
        iVar2 = *(int *)((int)&param_1->pcm_offset + 4);
        if ((iVar2 < 1) && (iVar2 < 0)) {
          *(undefined4 *)&param_1->pcm_offset = 0;
          *(undefined4 *)((int)&param_1->pcm_offset + 4) = 0;
        }
LAB_0059cc7b:
        ogg_stream_clear(local_174);
        param_1->bittrack = 0.0;
        param_1->samptrack = 0.0;
        return 0;
      }
      local_1a4 = local_18c;
      goto LAB_0059c804;
    }
    ogg_stream_packetout(&param_1->os,0);
  }
  if (local_1a4 == 0) {
    lVar4 = _get_next_page(param_1,&local_1a0,-1);
    local_184._4_4_ = (int)((ulonglong)lVar4 >> 0x20);
    local_184 = lVar4;
    if ((0 < local_184._4_4_) || (-1 < lVar4)) {
      if (((2 < param_1->ready_state) &&
          (iVar2 = ogg_page_serialno(&local_1a0), param_1->current_serialno != iVar2)) &&
         (iVar2 = ogg_page_bos(&local_1a0), iVar2 != 0)) {
        _decode_clear(param_1);
        ogg_stream_clear(local_174);
      }
      if (param_1->ready_state < 3) goto code_r0x0059cb10;
      goto LAB_0059cc35;
    }
    lVar4 = ov_pcm_total(param_1,-1);
    param_1->pcm_offset = lVar4;
  }
  else {
    *(undefined4 *)&param_1->pcm_offset = 0xffffffff;
    *(undefined4 *)((int)&param_1->pcm_offset + 4) = 0xffffffff;
  }
  goto LAB_0059cc7b;
code_r0x0059cb10:
  iVar2 = ogg_page_serialno(&local_1a0);
  for (local_1e0 = 0; (local_1e0 < param_1->links && (param_1->serialnos[local_1e0] != iVar2));
      local_1e0 = local_1e0 + 1) {
  }
  if (local_1e0 != param_1->links) {
    param_1->current_link = local_1e0;
    param_1->current_serialno = iVar2;
    ogg_stream_reset_serialno(&param_1->os,iVar2);
    ogg_stream_reset_serialno(local_174,iVar2);
    param_1->ready_state = 3;
    iVar2 = *(int *)((int)param_1->dataoffsets + local_1e0 * 8 + 4);
    if ((iVar2 < local_184._4_4_) ||
       ((iVar2 <= local_184._4_4_ && (*(uint *)(param_1->dataoffsets + local_1e0) < (uint)local_184)
        ))) {
      local_204 = 0;
    }
    else {
      local_204 = 1;
    }
    local_190 = local_204;
LAB_0059cc35:
    ogg_stream_pagein(&param_1->os,&local_1a0);
    ogg_stream_pagein(local_174,&local_1a0);
    local_188 = ogg_page_eos(&local_1a0);
  }
  goto LAB_0059c804;
}
