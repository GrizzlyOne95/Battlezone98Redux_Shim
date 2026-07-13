/*
 * Entry: 0059dd20
 * Name: _fetch_and_process_packet
 * Namespace: Global
 * Signature: int _fetch_and_process_packet(OggVorbis_File * param_1, ogg_packet * param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
_fetch_and_process_packet(OggVorbis_File *param_1,ogg_packet *param_2,int param_3,int param_4)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  long64 lVar5;
  int local_80;
  ogg_packet *local_74;
  int local_68;
  int local_60;
  int local_54;
  ogg_packet local_4c;
  int local_2c;
  ogg_packet *local_28;
  uint local_24;
  uint local_20;
  int local_1c;
  int local_18;
  ogg_page local_14;
  
  do {
    do {
      if ((param_1->ready_state == 3) && (local_18 = _make_decode_ready(param_1), local_18 < 0)) {
        return local_18;
      }
      if (param_1->ready_state == 4) {
        local_1c = vorbis_synthesis_halfrate_p(param_1->vi);
        while( true ) {
          if (param_2 == (ogg_packet *)0x0) {
            local_74 = &local_4c;
          }
          else {
            local_74 = param_2;
          }
          local_28 = local_74;
          local_2c = ogg_stream_packetout(&param_1->os,local_74);
          param_2 = (ogg_packet *)0x0;
          if (local_2c == -1) {
            return -3;
          }
          if (local_2c < 1) break;
          local_24 = (uint)local_28->granulepos;
          local_20 = *(uint *)((int)&local_28->granulepos + 4);
          iVar2 = vorbis_synthesis(&param_1->vb,local_28);
          if (iVar2 == 0) {
            iVar2 = vorbis_synthesis_pcmout(&param_1->vd,(float ***)0x0);
            if (iVar2 != 0) {
              return -0x81;
            }
            vorbis_synthesis_blockin(&param_1->vd,&param_1->vb);
            iVar2 = vorbis_synthesis_pcmout(&param_1->vd,(float ***)0x0);
            param_1->samptrack = (double)(iVar2 << ((byte)local_1c & 0x1f)) + param_1->samptrack;
            param_1->bittrack = (double)(local_28->bytes << 3) + param_1->bittrack;
            if (((local_24 & local_20) != 0xffffffff) && (local_28->e_o_s == 0)) {
              if (param_1->seekable == 0) {
                local_80 = 0;
              }
              else {
                local_80 = param_1->current_link;
              }
              if ((param_1->seekable != 0) && (0 < local_80)) {
                puVar1 = (uint *)(param_1->pcmlengths + local_80 * 2);
                bVar4 = local_24 < *puVar1;
                local_24 = local_24 - *puVar1;
                local_20 = (local_20 - *(int *)((int)param_1->pcmlengths + local_80 * 0x10 + 4)) -
                           (uint)bVar4;
              }
              if (((int)local_20 < 1) && ((int)local_20 < 0)) {
                local_24 = 0;
                local_20 = 0;
              }
              iVar2 = vorbis_synthesis_pcmout(&param_1->vd,(float ***)0x0);
              uVar3 = iVar2 << ((byte)local_1c & 0x1f);
              bVar4 = local_24 < uVar3;
              local_24 = local_24 - uVar3;
              local_20 = (local_20 - ((int)uVar3 >> 0x1f)) - (uint)bVar4;
              for (local_54 = 0; local_54 < local_80; local_54 = local_54 + 1) {
                puVar1 = (uint *)(param_1->pcmlengths + local_54 * 2 + 1);
                bVar4 = CARRY4(local_24,*puVar1);
                local_24 = local_24 + *puVar1;
                local_20 = local_20 + *(int *)((int)param_1->pcmlengths + local_54 * 0x10 + 0xc) +
                           (uint)bVar4;
              }
              *(uint *)&param_1->pcm_offset = local_24;
              *(uint *)((int)&param_1->pcm_offset + 4) = local_20;
            }
            return 1;
          }
        }
      }
      if (1 < param_1->ready_state) {
        do {
          if (param_3 == 0) {
            return 0;
          }
          lVar5 = _get_next_page(param_1,&local_14,-1);
          local_60 = (int)((ulonglong)lVar5 >> 0x20);
          if ((local_60 < 1) && (lVar5 < 0)) {
            return -2;
          }
          param_1->bittrack = (double)(local_14.header_len << 3) + param_1->bittrack;
          if ((param_1->ready_state != 4) ||
             (iVar2 = ogg_page_serialno(&local_14), param_1->current_serialno == iVar2))
          goto LAB_0059e092;
          iVar2 = ogg_page_bos(&local_14);
        } while (iVar2 == 0);
        if (param_4 == 0) {
          return -2;
        }
        _decode_clear(param_1);
        if (param_1->seekable == 0) {
          vorbis_info_clear(param_1->vi);
          vorbis_comment_clear(param_1->vc);
        }
      }
LAB_0059e092:
      if ((param_1->ready_state == 4) || (2 < param_1->ready_state)) goto LAB_0059e193;
      if (param_1->seekable == 0) {
        iVar2 = _fetch_headers(param_1,param_1->vi,param_1->vc,(long **)0x0,(int *)0x0,&local_14);
        if (iVar2 != 0) {
          return iVar2;
        }
        param_1->current_serialno = (param_1->os).serialno;
        param_1->current_link = param_1->current_link + 1;
        goto LAB_0059e193;
      }
      iVar2 = ogg_page_serialno(&local_14);
      for (local_68 = 0; (local_68 < param_1->links && (param_1->serialnos[local_68] != iVar2));
          local_68 = local_68 + 1) {
      }
    } while (local_68 == param_1->links);
    param_1->current_serialno = iVar2;
    param_1->current_link = local_68;
    ogg_stream_reset_serialno(&param_1->os,param_1->current_serialno);
    param_1->ready_state = 3;
LAB_0059e193:
    ogg_stream_pagein(&param_1->os,&local_14);
  } while( true );
}
