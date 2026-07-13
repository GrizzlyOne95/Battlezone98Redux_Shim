/*
 * Entry: 0059d610
 * Name: _get_prev_page
 * Namespace: Global
 * Signature: long64 _get_prev_page(OggVorbis_File * param_1, ogg_page * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long64 __cdecl _get_prev_page(OggVorbis_File *param_1,ogg_page *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  long64 lVar7;
  OggVorbis_File *in_stack_ffffffd8;
  uint local_24;
  uint local_20;
  uint local_14;
  uint local_10;
  uint local_c;
  int local_8;
  
  uVar1 = (uint)param_1->offset;
  iVar2 = *(int *)((int)&param_1->offset + 4);
  local_14 = 0xffffffff;
  local_10 = 0xffffffff;
  local_c = uVar1;
  local_8 = iVar2;
  do {
    if ((local_14 & local_10) != 0xffffffff) {
      uVar4 = local_14;
      uVar5 = local_10;
      if (param_2->header_len == 0) {
        uVar4 = _seek_helper(param_1,CONCAT44(in_stack_ffffffd8,local_10));
        uVar5 = (int)uVar4 >> 0x1f;
        if (uVar4 == 0) {
          lVar7 = _get_next_page(param_1,param_2,0x10000);
          local_20 = (uint)((ulonglong)lVar7 >> 0x20);
          uVar4 = local_14;
          uVar5 = local_10;
          if (((int)local_20 < 1) && (lVar7 < 0)) {
            uVar4 = 0xffffff7f;
            uVar5 = 0xffffffff;
          }
        }
      }
LAB_0059d7b5:
      return CONCAT44(uVar5,uVar4);
    }
    bVar6 = local_c < 0x10000;
    local_c = local_c - 0x10000;
    local_8 = local_8 - (uint)bVar6;
    if ((local_8 < 1) && (local_8 < 0)) {
      local_c = 0;
      local_8 = 0;
    }
    uVar4 = _seek_helper(param_1,CONCAT44(in_stack_ffffffd8,local_8));
    uVar5 = (int)uVar4 >> 0x1f;
    if (uVar4 != 0) goto LAB_0059d7b5;
    while ((iVar3 = *(int *)((int)&param_1->offset + 4), in_stack_ffffffd8 = param_1, iVar3 <= iVar2
           && ((iVar3 < iVar2 || ((uint)param_1->offset < uVar1))))) {
      memset(param_2,0,0x10);
      lVar7 = _get_next_page(param_1,param_2,
                             CONCAT44((iVar2 - *(int *)((int)&param_1->offset + 4)) -
                                      (uint)(uVar1 < (uint)param_1->offset),
                                      uVar1 - (int)param_1->offset));
      local_24 = (uint)lVar7;
      local_20 = (uint)((ulonglong)lVar7 >> 0x20);
      if ((local_24 == 0xffffff80) && (local_20 == 0xffffffff)) {
        uVar4 = 0xffffff80;
        uVar5 = 0xffffffff;
        goto LAB_0059d7b5;
      }
      if (((int)local_20 < 1) && (lVar7 < 0)) break;
      local_14 = local_24;
      local_10 = local_20;
    }
  } while( true );
}
