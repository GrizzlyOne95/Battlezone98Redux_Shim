/*
 * Entry: 0059b380
 * Name: _get_prev_page_serial
 * Namespace: Global
 * Signature: long64 _get_prev_page_serial(OggVorbis_File * param_1, long * param_2, int param_3, int * param_4, long64 * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long64 __cdecl
_get_prev_page_serial
          (OggVorbis_File *param_1,long *param_2,int param_3,int *param_4,long64 *param_5)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  long64 lVar5;
  int in_stack_ffffffa8;
  int local_4c;
  ogg_page local_44;
  uint local_34;
  uint local_30;
  undefined8 local_2c;
  uint local_24;
  int local_20;
  uint local_1c;
  uint local_18;
  long64 local_14;
  uint local_c;
  int local_8;
  
  local_24 = (uint)param_1->offset;
  local_20 = *(int *)((int)&param_1->offset + 4);
  local_34 = 0xffffffff;
  local_30 = 0xffffffff;
  local_1c = 0xffffffff;
  local_18 = 0xffffffff;
  local_4c = -1;
  local_14 = -1;
  local_c = local_24;
  local_8 = local_20;
  do {
    if ((local_1c & local_18) != 0xffffffff) {
      uVar1 = local_34;
      uVar3 = local_30;
      if ((int)local_30 < 0) {
        *param_4 = local_4c;
        *param_5 = local_14;
        uVar1 = local_1c;
        uVar3 = local_18;
      }
LAB_0059b58d:
      return CONCAT44(uVar3,uVar1);
    }
    bVar4 = local_c < 0x10000;
    local_c = local_c - 0x10000;
    local_8 = local_8 - (uint)bVar4;
    if ((local_8 < 1) && (local_8 < 0)) {
      local_c = 0;
      local_8 = 0;
    }
    uVar1 = _seek_helper(param_1,CONCAT44(in_stack_ffffffa8,local_8));
    uVar3 = (int)uVar1 >> 0x1f;
    local_2c = (long64)(int)uVar1;
    if (uVar1 != 0) goto LAB_0059b58d;
    while ((iVar2 = *(int *)((int)&param_1->offset + 4), iVar2 <= local_20 &&
           ((iVar2 < local_20 || ((uint)param_1->offset < local_24))))) {
      lVar5 = _get_next_page(param_1,&local_44,
                             CONCAT44((local_20 - *(int *)((int)&param_1->offset + 4)) -
                                      (uint)(local_24 < (uint)param_1->offset),
                                      local_24 - (int)param_1->offset));
      local_2c._0_4_ = (uint)lVar5;
      local_2c._4_4_ = (uint)((ulonglong)lVar5 >> 0x20);
      if (((uint)local_2c == -0x80) && (local_2c._4_4_ == -1)) {
        uVar1 = 0xffffff80;
        uVar3 = 0xffffffff;
        goto LAB_0059b58d;
      }
      local_2c = lVar5;
      if (((int)local_2c._4_4_ < 1) && (lVar5 < 0)) break;
      local_4c = ogg_page_serialno(&local_44);
      lVar5 = ogg_page_granulepos(&local_44);
      local_1c = (uint)local_2c;
      local_18 = local_2c._4_4_;
      in_stack_ffffffa8 = *param_4;
      if ((local_4c == in_stack_ffffffa8) && (local_4c >> 0x1f == in_stack_ffffffa8 >> 0x1f)) {
        local_34 = (uint)local_2c;
        local_30 = local_2c._4_4_;
        *param_5 = lVar5;
      }
      local_14 = lVar5;
      iVar2 = _lookup_serialno(local_4c,param_2,param_3);
      if (iVar2 == 0) {
        local_34 = 0xffffffff;
        local_30 = 0xffffffff;
      }
    }
  } while( true );
}
