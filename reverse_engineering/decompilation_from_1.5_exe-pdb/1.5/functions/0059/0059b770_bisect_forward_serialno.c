/*
 * Entry: 0059b770
 * Name: _bisect_forward_serialno
 * Namespace: Global
 * Signature: int _bisect_forward_serialno(OggVorbis_File * param_1, long64 param_2, long64 param_3, long64 param_4, long64 param_5, int param_6, long * param_7, int param_8, long param_9)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
_bisect_forward_serialno
          (OggVorbis_File *param_1,long64 param_2,long64 param_3,long64 param_4,long64 param_5,
          int param_6,long *param_7,int param_8,long param_9)

{
  uint uVar1;
  int iVar2;
  long64 *plVar3;
  vorbis_info *pvVar4;
  vorbis_comment *pvVar5;
  long *plVar6;
  uint extraout_EAX;
  int extraout_EDX;
  long unaff_EDI;
  vorbis_info *pvVar7;
  long64 lVar8;
  long64 lVar9;
  undefined4 in_stack_00000008;
  undefined4 local_a0;
  int local_9c;
  int local_98;
  uint local_94;
  int local_90;
  long *local_8c;
  vorbis_comment local_88;
  long *local_78;
  vorbis_info local_74;
  undefined4 local_54;
  undefined4 local_50;
  undefined8 local_4c;
  ogg_page local_44;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  int local_28;
  uint local_24;
  int local_20;
  undefined8 local_1c;
  uint local_14;
  int local_10;
  long local_8;
  
  local_34 = param_2._4_4_;
  local_30 = (int)param_3;
  local_14 = param_3._4_4_;
  local_10 = (int)param_4;
  local_24 = param_3._4_4_;
  local_20 = (int)param_4;
  local_54 = 0xffffffff;
  local_50 = 0xffffffff;
  local_8 = (param_1->os).serialno;
  iVar2 = _lookup_serialno(param_5._4_4_,(long *)param_6,(int)param_7);
  lVar9 = param_5;
  if (iVar2 == 0) {
    local_78 = (long *)0x0;
    local_8c = (long *)0x0;
    lVar9 = param_3;
    while( true ) {
      param_2._4_4_ = (uint)((ulonglong)param_2 >> 0x20);
      param_3._4_4_ = (uint)((ulonglong)lVar9 >> 0x20);
      param_3._0_4_ = (int)lVar9;
      if ((local_10 < (int)param_3) || ((local_10 <= (int)param_3 && (local_14 <= param_2._4_4_))))
      break;
      iVar2 = (local_10 - (int)param_3) - (uint)(local_14 < param_2._4_4_);
      if ((iVar2 < 1) && ((iVar2 < 0 || (local_14 - param_2._4_4_ < 0x10000)))) {
        local_94 = param_2._4_4_;
        local_90 = (int)param_3;
      }
      else {
        _alldiv();
        local_94 = extraout_EAX;
        local_90 = extraout_EDX;
      }
      if ((local_94 != (uint)param_1->offset) || (local_90 != *(int *)((int)&param_1->offset + 4)))
      {
        local_2c = _seek_helper(param_1,CONCAT44(unaff_EDI,local_90));
        local_28 = local_2c >> 0x1f;
        if (local_2c != 0) {
          return local_2c;
        }
      }
      lVar9 = _get_next_page(param_1,&local_44,-1);
      local_1c._0_4_ = (uint)lVar9;
      local_1c._4_4_ = (int)((ulonglong)lVar9 >> 0x20);
      if (((uint)local_1c == -0x80) && (local_1c._4_4_ == -1)) {
        return -0x80;
      }
      local_1c = lVar9;
      if (lVar9 < 0) {
LAB_0059bad5:
        local_14 = local_94;
        local_10 = local_90;
        if (-1 < local_1c) {
          local_24 = (uint)local_1c;
          local_20 = local_1c._4_4_;
        }
      }
      else {
        iVar2 = _lookup_page_serialno(&local_44,(long *)param_6,(int)param_7);
        if (iVar2 == 0) goto LAB_0059bad5;
        param_2._4_4_ = (uint)param_1->offset;
        param_3._0_4_ = *(int *)((int)&param_1->offset + 4);
      }
      param_2 = (ulonglong)param_2._4_4_ << 0x20;
      lVar9 = CONCAT44(param_3._4_4_,(int)param_3);
    }
    local_98 = local_8 + 1;
    *(uint *)&param_1->offset = local_24;
    *(int *)((int)&param_1->offset + 4) = local_20;
    while (local_98 != local_8) {
      local_98 = local_8;
      lVar9 = _get_prev_page_serial
                        (param_1,(long *)param_6,(int)param_7,&local_98,(long64 *)&local_54);
      param_1->offset = lVar9;
    }
    if (((uint)param_1->offset != local_24) || (*(int *)((int)&param_1->offset + 4) != local_20)) {
      local_2c = _seek_helper(param_1,CONCAT44(unaff_EDI,local_20));
      local_28 = local_2c >> 0x1f;
      if (local_2c != 0) {
        return local_2c;
      }
    }
    local_2c = _fetch_headers(param_1,&local_74,&local_88,&local_78,(int *)&local_8c,(ogg_page *)0x0
                             );
    local_28 = local_2c >> 0x1f;
    if (local_2c != 0) {
      return local_2c;
    }
    local_8 = (param_1->os).serialno;
    local_34 = (undefined4)param_1->offset;
    local_30 = *(undefined4 *)((int)&param_1->offset + 4);
    local_4c = _initial_pcmoffset(param_1,&local_74);
    local_2c = _bisect_forward_serialno
                         (param_1,CONCAT44((int)param_1->offset,local_20),
                          CONCAT44(param_3._4_4_,*(undefined4 *)((int)&param_1->offset + 4)),param_4
                          ,param_5,(int)local_78,local_8c,param_8 + 1,unaff_EDI);
    local_28 = local_2c >> 0x1f;
    if (local_2c != 0) {
      return local_2c;
    }
    if (local_78 != (long *)0x0) {
      free(local_78);
    }
    plVar3 = param_1->offsets;
    *(uint *)(plVar3 + param_8 + 1) = local_24;
    *(int *)((int)plVar3 + param_8 * 8 + 0xc) = local_20;
    param_1->serialnos[param_8 + 1] = local_8;
    plVar3 = param_1->dataoffsets;
    *(undefined4 *)(plVar3 + param_8 + 1) = local_34;
    *(undefined4 *)((int)plVar3 + param_8 * 8 + 0xc) = local_30;
    pvVar4 = &local_74;
    pvVar7 = param_1->vi + param_8 + 1;
    for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
      pvVar7->version = pvVar4->version;
      pvVar4 = (vorbis_info *)&pvVar4->channels;
      pvVar7 = (vorbis_info *)&pvVar7->channels;
    }
    pvVar5 = param_1->vc + param_8 + 1;
    pvVar5->user_comments = local_88.user_comments;
    pvVar5->comment_lengths = local_88.comment_lengths;
    pvVar5->comments = local_88.comments;
    pvVar5->vendor = local_88.vendor;
    plVar3 = param_1->pcmlengths;
    *(undefined4 *)(plVar3 + param_8 * 2 + 1) = local_54;
    *(undefined4 *)((int)plVar3 + param_8 * 0x10 + 0xc) = local_50;
    plVar3 = param_1->pcmlengths;
    *(uint *)(plVar3 + param_8 * 2 + 2) = (uint)local_4c;
    *(int *)((int)plVar3 + param_8 * 0x10 + 0x14) = local_4c._4_4_;
    uVar1 = *(uint *)(param_1->pcmlengths + param_8 * 2 + 3);
    iVar2 = *(int *)((int)param_1->pcmlengths + param_8 * 0x10 + 0x1c);
    plVar3 = param_1->pcmlengths;
    *(uint *)(plVar3 + param_8 * 2 + 3) = uVar1 - (uint)local_4c;
    *(uint *)((int)plVar3 + param_8 * 0x10 + 0x1c) =
         (iVar2 - local_4c._4_4_) - (uint)(uVar1 < (uint)local_4c);
    iVar2 = *(int *)((int)param_1->pcmlengths + param_8 * 0x10 + 0x1c);
    if ((iVar2 < 1) && (iVar2 < 0)) {
      plVar3 = param_1->pcmlengths;
      *(undefined4 *)(plVar3 + param_8 * 2 + 3) = 0;
      *(undefined4 *)((int)plVar3 + param_8 * 0x10 + 0x1c) = 0;
    }
  }
  else {
    while( true ) {
      param_5._4_4_ = (long)((ulonglong)lVar9 >> 0x20);
      param_5._0_4_ = (int)lVar9;
      if (param_5._4_4_ == local_8) break;
      param_5._4_4_ = local_8;
      lVar8 = _get_prev_page_serial
                        (param_1,(long *)param_6,(int)param_7,(int *)((int)&param_5 + 4),
                         (long64 *)((int)&param_4 + 4));
      lVar9 = CONCAT44(param_5._4_4_,(int)param_5);
      param_1->offset = lVar8;
    }
    param_1->links = param_8 + 1;
    param_5 = lVar9;
    if (param_1->offsets != (long64 *)0x0) {
      free(param_1->offsets);
    }
    if (param_1->serialnos != (long *)0x0) {
      free(param_1->serialnos);
    }
    if (param_1->dataoffsets != (long64 *)0x0) {
      free(param_1->dataoffsets);
    }
    plVar3 = malloc(param_1->links * 8 + 8);
    param_1->offsets = plVar3;
    pvVar4 = realloc(param_1->vi,param_1->links << 5);
    param_1->vi = pvVar4;
    pvVar5 = realloc(param_1->vc,param_1->links << 4);
    param_1->vc = pvVar5;
    plVar6 = malloc(param_1->links << 2);
    param_1->serialnos = plVar6;
    plVar3 = malloc(param_1->links << 3);
    param_1->dataoffsets = plVar3;
    plVar3 = malloc(param_1->links << 4);
    param_1->pcmlengths = plVar3;
    plVar3 = param_1->offsets;
    *(uint *)(plVar3 + param_8 + 1) = param_3._4_4_;
    *(int *)((int)plVar3 + param_8 * 8 + 0xc) = (int)param_4;
    plVar3 = param_1->offsets;
    *(undefined4 *)(plVar3 + param_8) = in_stack_00000008;
    *(undefined4 *)((int)plVar3 + param_8 * 8 + 4) = (undefined4)param_2;
    if (((int)param_5 < 1) && ((int)param_5 < 0)) {
      local_a0 = 0;
      local_9c = 0;
    }
    else {
      local_a0 = param_4._4_4_;
      local_9c = (int)param_5;
    }
    plVar3 = param_1->pcmlengths;
    *(undefined4 *)(plVar3 + param_8 * 2 + 1) = local_a0;
    *(int *)((int)plVar3 + param_8 * 0x10 + 0xc) = local_9c;
  }
  return 0;
}
