/*
 * Entry: 0059d7c0
 * Name: ov_pcm_seek
 * Namespace: Global
 * Signature: int ov_pcm_seek(OggVorbis_File * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ov_pcm_seek(OggVorbis_File *param_1,long64 param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  long lVar5;
  uint extraout_EAX;
  uint extraout_EAX_00;
  int iVar6;
  int extraout_EDX;
  int extraout_EDX_00;
  undefined4 unaff_ESI;
  long64 lVar7;
  uint in_stack_00000008;
  int local_74;
  uint local_58;
  int local_50;
  int local_48;
  ogg_packet local_44;
  ogg_page local_24;
  int local_14;
  long local_10;
  long local_c;
  int local_8;
  
  local_10 = 0;
  local_8 = ov_pcm_seek_page(param_1,CONCAT44(unaff_ESI,(int)param_2));
  if ((local_8 < 0) || (local_8 = _make_decode_ready(param_1), local_8 != 0)) {
    return local_8;
  }
LAB_0059d813:
  while (local_14 = ogg_stream_packetpeek(&param_1->os,&local_44), 0 < local_14) {
    local_c = vorbis_packet_blocksize(param_1->vi + param_1->current_link,&local_44);
    if (local_c < 0) {
      ogg_stream_packetout(&param_1->os,0);
    }
    else {
      if (local_10 != 0) {
        uVar3 = local_10 + local_c >> 2;
        lVar7 = param_1->pcm_offset;
        iVar4 = *(int *)((int)&param_1->pcm_offset + 4);
        *(uint *)&param_1->pcm_offset = uVar3 + (int)param_1->pcm_offset;
        *(uint *)((int)&param_1->pcm_offset + 4) =
             iVar4 + (local_10 + local_c >> 0x1f) + (uint)CARRY4(uVar3,(uint)lVar7);
      }
      iVar4 = vorbis_info_blocksize(param_1->vi,1);
      uVar3 = iVar4 + local_c >> 2;
      iVar4 = *(int *)((int)&param_1->pcm_offset + 4) + (iVar4 + local_c >> 0x1f) +
              (uint)CARRY4(uVar3,(uint)param_1->pcm_offset);
      if (((int)param_2 <= iVar4) &&
         (((int)param_2 < iVar4 || (in_stack_00000008 <= uVar3 + (int)param_1->pcm_offset))))
      goto LAB_0059dafe;
      ogg_stream_packetout(&param_1->os,0);
      vorbis_synthesis_trackonly(&param_1->vb,&local_44);
      vorbis_synthesis_blockin(&param_1->vd,&param_1->vb);
      if ((-2 < (int)local_44.granulepos._4_4_) && (local_44.granulepos._4_4_ < 0x80000000)) {
        puVar1 = (uint *)(param_1->pcmlengths + param_1->current_link * 2);
        uVar3 = *puVar1;
        iVar4 = *(int *)((int)param_1->pcmlengths + param_1->current_link * 0x10 + 4);
        *(uint *)&param_1->pcm_offset = (uint)local_44.granulepos - *puVar1;
        *(uint *)((int)&param_1->pcm_offset + 4) =
             (local_44.granulepos._4_4_ - iVar4) - (uint)((uint)local_44.granulepos < uVar3);
        iVar4 = *(int *)((int)&param_1->pcm_offset + 4);
        if ((iVar4 < 1) && (iVar4 < 0)) {
          *(undefined4 *)&param_1->pcm_offset = 0;
          *(undefined4 *)((int)&param_1->pcm_offset + 4) = 0;
        }
        for (local_48 = 0; local_48 < param_1->current_link; local_48 = local_48 + 1) {
          uVar3 = (uint)param_1->pcm_offset;
          puVar1 = (uint *)(param_1->pcmlengths + local_48 * 2 + 1);
          uVar2 = *puVar1;
          iVar4 = *(int *)((int)&param_1->pcm_offset + 4);
          iVar6 = *(int *)((int)param_1->pcmlengths + local_48 * 0x10 + 0xc);
          *(uint *)&param_1->pcm_offset = uVar3 + *puVar1;
          *(uint *)((int)&param_1->pcm_offset + 4) = iVar4 + iVar6 + (uint)CARRY4(uVar3,uVar2);
        }
      }
      local_10 = local_c;
    }
  }
  if ((local_14 < 0) && (local_14 != -3)) goto LAB_0059dafe;
  lVar7 = _get_next_page(param_1,&local_24,-1);
  local_74 = (int)((ulonglong)lVar7 >> 0x20);
  if ((local_74 < 1) && (lVar7 < 0)) {
LAB_0059dafe:
    param_1->bittrack = 0.0;
    param_1->samptrack = 0.0;
    iVar4 = vorbis_synthesis_halfrate_p(param_1->vi);
    while( true ) {
      _allshr();
      _allshl();
      iVar6 = *(int *)((int)&param_1->pcm_offset + 4);
      if ((extraout_EDX < iVar6) ||
         ((extraout_EDX <= iVar6 && (extraout_EAX <= (uint)param_1->pcm_offset)))) break;
      _allshr();
      local_58 = vorbis_synthesis_pcmout(&param_1->vd,(float ***)0x0);
      if ((extraout_EDX_00 <= (int)local_58 >> 0x1f) &&
         ((extraout_EDX_00 < (int)local_58 >> 0x1f || (extraout_EAX_00 < local_58)))) {
        local_58 = extraout_EAX_00;
      }
      vorbis_synthesis_read(&param_1->vd,local_58);
      uVar3 = local_58 << ((byte)iVar4 & 0x1f);
      lVar7 = param_1->pcm_offset;
      iVar6 = *(int *)((int)&param_1->pcm_offset + 4);
      *(uint *)&param_1->pcm_offset = uVar3 + (int)param_1->pcm_offset;
      *(uint *)((int)&param_1->pcm_offset + 4) =
           iVar6 + ((int)uVar3 >> 0x1f) + (uint)CARRY4(uVar3,(uint)lVar7);
      if (((int)local_58 >> 0x1f <= extraout_EDX_00) &&
         ((((int)local_58 >> 0x1f < extraout_EDX_00 || (local_58 < extraout_EAX_00)) &&
          (iVar6 = _fetch_and_process_packet(param_1,(ogg_packet *)0x0,1,1), iVar6 < 1)))) {
        lVar7 = ov_pcm_total(param_1,-1);
        param_1->pcm_offset = lVar7;
      }
    }
    return 0;
  }
  iVar4 = ogg_page_bos(&local_24);
  if (iVar4 != 0) {
    _decode_clear(param_1);
  }
  if (param_1->ready_state < 3) {
    iVar4 = ogg_page_serialno(&local_24);
    for (local_50 = 0; (local_50 < param_1->links && (param_1->serialnos[local_50] != iVar4));
        local_50 = local_50 + 1) {
    }
    if (local_50 == param_1->links) goto LAB_0059d813;
    param_1->current_link = local_50;
    param_1->ready_state = 3;
    lVar5 = ogg_page_serialno(&local_24);
    param_1->current_serialno = lVar5;
    ogg_stream_reset_serialno(&param_1->os,iVar4);
    iVar4 = _make_decode_ready(param_1);
    if (iVar4 != 0) {
      return iVar4;
    }
    local_10 = 0;
    local_14 = 0;
  }
  ogg_stream_pagein(&param_1->os,&local_24);
  goto LAB_0059d813;
}
