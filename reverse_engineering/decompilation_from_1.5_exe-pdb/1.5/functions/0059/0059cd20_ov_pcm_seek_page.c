/*
 * Entry: 0059cd20
 * Name: ov_pcm_seek_page
 * Namespace: Global
 * Signature: int ov_pcm_seek_page(OggVorbis_File * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Removing unreachable block (ram,0x0059d140) */

int __cdecl ov_pcm_seek_page(OggVorbis_File *param_1,long64 param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint extraout_EAX;
  int iVar4;
  int extraout_EDX;
  uint extraout_EDX_00;
  undefined4 unaff_ESI;
  int iVar5;
  bool bVar6;
  long64 lVar7;
  longlong lVar8;
  longlong lVar9;
  uint in_stack_00000008;
  uint local_fc;
  int local_f8;
  undefined1 local_9c [16];
  uint local_8c;
  uint local_88;
  ogg_page local_7c;
  undefined8 local_6c;
  uint local_64;
  int local_60;
  longlong local_5c;
  ogg_page local_54;
  uint local_44;
  int local_40;
  uint local_3c;
  int local_38;
  longlong local_34;
  uint local_2c;
  int local_28;
  uint local_24;
  int local_20;
  undefined8 local_1c;
  int local_10;
  undefined8 local_c;
  
  local_10 = 0xffffffff;
  local_1c = 0;
  lVar7 = ov_pcm_total(param_1,-1);
  lVar9 = CONCAT44(local_6c._4_4_,(undefined4)local_6c);
  if (param_1->ready_state < 2) {
    local_1c._0_4_ = -0x83;
  }
  else if (param_1->seekable == 0) {
    local_1c._0_4_ = -0x8a;
  }
  else if (((int)param_2 < 0) ||
          ((local_c._4_4_ = (int)((ulonglong)lVar7 >> 0x20), local_c._4_4_ <= (int)param_2 &&
           ((local_c._4_4_ < (int)param_2 ||
            (local_c._0_4_ = (uint)lVar7, (uint)local_c < in_stack_00000008)))))) {
    local_1c._0_4_ = -0x83;
  }
  else {
    local_c = lVar7;
    local_10 = param_1->links;
    while (iVar4 = local_10, local_10 = iVar4 + -1, -1 < local_10) {
      puVar1 = (uint *)(param_1->pcmlengths + local_10 * 2 + 1);
      uVar3 = (uint)local_c - *puVar1;
      iVar5 = (local_c._4_4_ - *(int *)((int)param_1->pcmlengths + local_10 * 0x10 + 0xc)) -
              (uint)((uint)local_c < *puVar1);
      local_c = CONCAT44(iVar5,uVar3);
      if ((iVar5 <= (int)param_2) && ((iVar5 < (int)param_2 || (uVar3 <= in_stack_00000008))))
      break;
    }
    local_3c = *(uint *)(param_1->offsets + iVar4);
    local_38 = *(int *)((int)param_1->offsets + local_10 * 8 + 0xc);
    local_2c = *(uint *)(param_1->offsets + local_10);
    local_28 = *(int *)((int)param_1->offsets + local_10 * 8 + 4);
    uVar3 = *(uint *)(param_1->pcmlengths + local_10 * 2);
    iVar4 = *(int *)((int)param_1->pcmlengths + local_10 * 0x10 + 4);
    uVar2 = *(uint *)(param_1->pcmlengths + local_10 * 2 + 1);
    local_44 = (in_stack_00000008 - (uint)local_c) + uVar3;
    local_40 = (((int)param_2 - local_c._4_4_) - (uint)(in_stack_00000008 < (uint)local_c)) + iVar4
               + (uint)CARRY4(in_stack_00000008 - (uint)local_c,uVar3);
    local_24 = local_2c;
    local_20 = local_28;
    local_34 = CONCAT44(iVar4,uVar3);
    local_5c = CONCAT44(*(int *)((int)param_1->pcmlengths + local_10 * 0x10 + 0xc) + iVar4 +
                        (uint)CARRY4(uVar2,uVar3),uVar2 + uVar3);
LAB_0059ce7d:
    local_6c = lVar9;
    if ((local_20 <= local_38) && ((local_20 < local_38 || (local_24 < local_3c)))) {
      iVar4 = (local_38 - local_20) - (uint)(local_3c < local_24);
      if ((iVar4 < 1) && ((iVar4 < 0 || (local_3c - local_24 < 0x10000)))) {
        local_64 = local_24;
        local_60 = local_20;
      }
      else {
        _ftol2();
        local_64 = (extraout_EAX + local_24) - 0x10000;
        local_60 = (local_20 + extraout_EDX + (uint)CARRY4(extraout_EAX,local_24)) -
                   (uint)(extraout_EAX + local_24 < 0x10000);
        iVar4 = local_20 + (uint)(0xfffeffff < local_24);
        if ((local_60 <= iVar4) && ((local_60 < iVar4 || (local_64 < local_24 + 0x10000)))) {
          local_64 = local_24;
          local_60 = local_20;
        }
      }
      if ((local_64 != (uint)param_1->offset) ||
         (uVar3 = local_64, iVar4 = local_60, lVar9 = local_6c,
         local_60 != *(int *)((int)&param_1->offset + 4))) {
        iVar5 = _seek_helper(param_1,CONCAT44(unaff_ESI,local_60));
        goto joined_r0x0059d27f;
      }
LAB_0059cfdc:
      do {
        do {
          do {
            while( true ) {
              local_60 = iVar4;
              local_64 = uVar3;
              if ((local_38 < local_20) || ((local_38 <= local_20 && (local_3c <= local_24))))
              goto LAB_0059ce7d;
              local_6c = lVar9;
              lVar8 = _get_next_page(param_1,&local_54,
                                     CONCAT44((local_38 - *(int *)((int)&param_1->offset + 4)) -
                                              (uint)(local_3c < (uint)param_1->offset),
                                              local_3c - (int)param_1->offset));
              local_1c._0_4_ = (uint)lVar8;
              local_1c._4_4_ = (int)((ulonglong)lVar8 >> 0x20);
              if (((uint)local_1c == -0x80) && (local_1c._4_4_ == -1)) goto LAB_0059d5e8;
              local_1c = lVar8;
              if ((0 < local_1c._4_4_) || (-1 < lVar8)) break;
              iVar4 = local_20 + (uint)(0xfffffffe < local_24);
              if ((iVar4 < local_60) || ((iVar4 <= local_60 && (local_24 + 1 < local_64)))) {
                if (local_64 == 0 && local_60 == 0) goto LAB_0059d5e8;
                bVar6 = local_64 < 0x10000;
                local_64 = local_64 - 0x10000;
                local_60 = local_60 - (uint)bVar6;
                if ((local_60 <= local_20) && ((local_60 < local_20 || (local_64 <= local_24)))) {
                  local_64 = local_24 + 1;
                  local_60 = local_20 + (uint)(0xfffffffe < local_24);
                }
                iVar5 = _seek_helper(param_1,CONCAT44(unaff_ESI,local_60));
joined_r0x0059d27f:
                uVar3 = local_64;
                iVar4 = local_60;
                lVar8 = (longlong)iVar5;
                local_1c = (longlong)iVar5;
                lVar9 = local_6c;
                if (iVar5 != 0) goto LAB_0059d5e8;
              }
              else {
                local_3c = local_24;
                local_38 = local_20;
                uVar3 = local_64;
                iVar4 = local_60;
                lVar9 = local_6c;
              }
            }
            iVar5 = ogg_page_serialno(&local_54);
            uVar3 = local_64;
            iVar4 = local_60;
            lVar9 = local_6c;
          } while (iVar5 != param_1->serialnos[local_10]);
          lVar9 = ogg_page_granulepos(&local_54);
          uVar3 = local_64;
          iVar4 = local_60;
        } while (lVar9 == -1);
        if (lVar9 < CONCAT44(local_40,local_44)) {
          local_2c = (uint)local_1c;
          local_28 = local_1c._4_4_;
          local_24 = (uint)param_1->offset;
          local_20 = *(int *)((int)&param_1->offset + 4);
          iVar5 = (local_40 - (int)((ulonglong)lVar9 >> 0x20)) - (uint)(local_44 < (uint)lVar9);
          uVar3 = local_24;
          iVar4 = local_20;
          local_34 = lVar9;
          if ((-1 < iVar5) && ((0 < iVar5 || (0xac44 < local_44 - (uint)lVar9)))) goto LAB_0059ce7d;
          goto LAB_0059cfdc;
        }
        iVar5 = local_20 + (uint)(0xfffffffe < local_24);
        if ((iVar5 < local_60) || ((iVar5 <= local_60 && (local_24 + 1 < local_64)))) {
          if ((local_3c == (uint)param_1->offset) &&
             (local_38 == *(int *)((int)&param_1->offset + 4))) {
            local_3c = (uint)local_1c;
            local_38 = local_1c._4_4_;
            bVar6 = local_64 < 0x10000;
            local_64 = local_64 - 0x10000;
            local_60 = local_60 - (uint)bVar6;
            if ((local_60 <= local_20) && ((local_60 < local_20 || (local_64 <= local_24)))) {
              local_64 = local_24 + 1;
              local_60 = local_20 + (uint)(0xfffffffe < local_24);
            }
            local_6c = lVar9;
            iVar5 = _seek_helper(param_1,CONCAT44(unaff_ESI,local_60));
            goto joined_r0x0059d27f;
          }
          local_3c = local_64;
          local_38 = local_60;
          local_5c = lVar9;
          goto LAB_0059ce7d;
        }
        local_3c = local_24;
        local_38 = local_20;
      } while( true );
    }
    iVar4 = _seek_helper(param_1,CONCAT44(unaff_ESI,local_28));
    local_1c = (long64)iVar4;
    *(undefined4 *)&param_1->pcm_offset = 0xffffffff;
    *(undefined4 *)((int)&param_1->pcm_offset + 4) = 0xffffffff;
    lVar8 = local_1c;
    if (iVar4 == 0) {
      lVar8 = _get_next_page(param_1,&local_7c,-1);
      local_1c._4_4_ = (int)((ulonglong)lVar8 >> 0x20);
      if ((0 < local_1c._4_4_) || (-1 < lVar8)) {
        local_1c = lVar8;
        if (local_10 == param_1->current_link) {
          vorbis_synthesis_restart(&param_1->vd);
        }
        else {
          _decode_clear(param_1);
          param_1->current_link = local_10;
          param_1->current_serialno = param_1->serialnos[local_10];
          param_1->ready_state = 3;
        }
        ogg_stream_reset_serialno(&param_1->os,param_1->current_serialno);
        ogg_stream_pagein(&param_1->os,&local_7c);
        while( true ) {
          iVar4 = ogg_stream_packetpeek(&param_1->os,local_9c);
          local_1c = (long64)iVar4;
          if (iVar4 == 0) break;
          if ((iVar4 >> 0x1f < 1) && (iVar4 >> 0x1f < 0)) {
            local_1c = -0x88;
            lVar8 = local_1c;
            goto LAB_0059d5e8;
          }
          if ((local_8c & local_88) != 0xffffffff) {
            puVar1 = (uint *)(param_1->pcmlengths + param_1->current_link * 2);
            uVar3 = *puVar1;
            iVar4 = *(int *)((int)param_1->pcmlengths + param_1->current_link * 0x10 + 4);
            *(uint *)&param_1->pcm_offset = local_8c - *puVar1;
            *(uint *)((int)&param_1->pcm_offset + 4) = (local_88 - iVar4) - (uint)(local_8c < uVar3)
            ;
            iVar4 = *(int *)((int)&param_1->pcm_offset + 4);
            if ((iVar4 < 1) && (iVar4 < 0)) {
              *(undefined4 *)&param_1->pcm_offset = 0;
              *(undefined4 *)((int)&param_1->pcm_offset + 4) = 0;
            }
            uVar3 = (uint)param_1->pcm_offset;
            iVar4 = *(int *)((int)&param_1->pcm_offset + 4);
            *(uint *)&param_1->pcm_offset = uVar3 + (uint)local_c;
            *(uint *)((int)&param_1->pcm_offset + 4) =
                 iVar4 + local_c._4_4_ + (uint)CARRY4(uVar3,(uint)local_c);
            iVar4 = *(int *)((int)&param_1->pcm_offset + 4);
            if ((iVar4 <= (int)param_2) &&
               ((iVar4 < (int)param_2 || ((uint)param_1->pcm_offset <= in_stack_00000008)))) {
              lVar7 = ov_pcm_total(param_1,-1);
              local_f8 = (int)((ulonglong)lVar7 >> 0x20);
              if (((int)param_2 < local_f8) ||
                 (((int)param_2 <= local_f8 &&
                  (local_fc = (uint)lVar7, in_stack_00000008 <= local_fc)))) {
                param_1->bittrack = 0.0;
                param_1->samptrack = 0.0;
                return 0;
              }
            }
            local_1c = -0x81;
            lVar8 = local_1c;
            goto LAB_0059d5e8;
          }
          iVar4 = ogg_stream_packetout(&param_1->os,0);
          local_1c = (long64)iVar4;
        }
        iVar4 = _seek_helper(param_1,CONCAT44(unaff_ESI,local_28));
        local_1c = (long64)iVar4;
        if ((0 < iVar4 >> 0x1f) || (lVar8 = local_1c, -1 < iVar4 >> 0x1f)) {
          do {
            lVar8 = _get_prev_page(param_1,&local_7c);
            local_1c._4_4_ = (int)((ulonglong)lVar8 >> 0x20);
            if ((local_1c._4_4_ < 1) && (lVar8 < 0)) break;
            local_1c = lVar8;
            iVar4 = ogg_page_serialno(&local_7c);
            if (iVar4 == param_1->current_serialno) {
              ogg_page_granulepos(&local_7c);
              if (extraout_EDX_00 < 0x80000000) {
LAB_0059d475:
                iVar4 = ov_raw_seek(param_1,CONCAT44(unaff_ESI,local_1c._4_4_));
                return iVar4;
              }
              iVar4 = ogg_page_continued(&local_7c);
              if (iVar4 == 0) goto LAB_0059d475;
            }
            *(uint *)&param_1->offset = (uint)local_1c;
            *(int *)((int)&param_1->offset + 4) = local_1c._4_4_;
          } while( true );
        }
      }
    }
LAB_0059d5e8:
    local_1c = lVar8;
    *(undefined4 *)&param_1->pcm_offset = 0xffffffff;
    *(undefined4 *)((int)&param_1->pcm_offset + 4) = 0xffffffff;
    _decode_clear(param_1);
  }
  return (uint)local_1c;
}
