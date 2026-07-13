/*
 * Entry: 0059ae20
 * Name: _get_next_page
 * Namespace: Global
 * Signature: long64 _get_next_page(OggVorbis_File * param_1, ogg_page * param_2, long64 param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Removing unreachable block (ram,0x0059ae2f) */
/* WARNING: Removing unreachable block (ram,0x0059ae5f) */

long64 __cdecl _get_next_page(OggVorbis_File *param_1,ogg_page *param_2,long64 param_3)

{
  int iVar1;
  uint uVar2;
  longlong lVar3;
  long64 lVar4;
  undefined4 uVar5;
  uint uVar6;
  long lVar7;
  undefined4 uVar8;
  
  lVar3 = param_3;
  if (0 < param_3) {
    lVar3 = CONCAT44(param_3._4_4_ + *(int *)((int)&param_1->offset + 4) +
                     (uint)CARRY4((uint)param_3,(uint)param_1->offset),
                     (uint)param_3 + (int)param_1->offset);
  }
  do {
    while( true ) {
      param_3._4_4_ = (int)((ulonglong)lVar3 >> 0x20);
      param_3._0_4_ = (uint)lVar3;
      if (((0 < lVar3) && (iVar1 = *(int *)((int)&param_1->offset + 4), param_3._4_4_ <= iVar1)) &&
         ((param_3._4_4_ < iVar1 || ((uint)param_3 <= (uint)param_1->offset)))) {
        uVar5 = 0xffffffff;
        uVar8 = 0xffffffff;
        goto LAB_0059af41;
      }
      uVar6 = ogg_sync_pageseek(&param_1->oy,param_2);
      if (-1 < (int)uVar6) break;
      uVar2 = (uint)param_1->offset;
      iVar1 = *(int *)((int)&param_1->offset + 4);
      *(uint *)&param_1->offset = uVar2 - uVar6;
      *(uint *)((int)&param_1->offset + 4) = (iVar1 - ((int)uVar6 >> 0x1f)) - (uint)(uVar2 < uVar6);
    }
    if (uVar6 != 0) {
      uVar5 = (undefined4)param_1->offset;
      uVar8 = *(undefined4 *)((int)&param_1->offset + 4);
      lVar4 = param_1->offset;
      iVar1 = *(int *)((int)&param_1->offset + 4);
      *(uint *)&param_1->offset = uVar6 + (int)param_1->offset;
      *(uint *)((int)&param_1->offset + 4) =
           iVar1 + ((int)uVar6 >> 0x1f) + (uint)CARRY4(uVar6,(uint)lVar4);
      goto LAB_0059af41;
    }
    if (lVar3 == 0) {
      uVar5 = 0xffffffff;
      uVar8 = 0xffffffff;
      goto LAB_0059af41;
    }
    lVar7 = _get_data(param_1);
    if (lVar7 == 0) {
      uVar5 = 0xfffffffe;
      uVar8 = 0xffffffff;
      goto LAB_0059af41;
    }
  } while (-1 < lVar7);
  uVar5 = 0xffffff80;
  uVar8 = 0xffffffff;
LAB_0059af41:
  return CONCAT44(uVar8,uVar5);
}
