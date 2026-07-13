/*
 * Entry: 0059c400
 * Name: ov_raw_total
 * Namespace: Global
 * Signature: long64 ov_raw_total(OggVorbis_File * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long64 __cdecl ov_raw_total(OggVorbis_File *param_1,int param_2)

{
  uint *puVar1;
  uint uVar2;
  longlong lVar3;
  long64 lVar4;
  int local_8;
  
  if (param_1->ready_state < 2) {
    lVar3 = -0x83;
  }
  else if ((param_1->seekable == 0) || (param_1->links <= param_2)) {
    lVar3 = -0x83;
  }
  else if (param_2 < 0) {
    lVar3 = 0;
    for (local_8 = 0; local_8 < param_1->links; local_8 = local_8 + 1) {
      lVar4 = ov_raw_total(param_1,local_8);
      lVar3 = lVar4 + lVar3;
    }
  }
  else {
    uVar2 = *(uint *)(param_1->offsets + param_2 + 1);
    puVar1 = (uint *)(param_1->offsets + param_2);
    lVar3 = CONCAT44((*(int *)((int)param_1->offsets + param_2 * 8 + 0xc) -
                     *(int *)((int)param_1->offsets + param_2 * 8 + 4)) - (uint)(uVar2 < *puVar1),
                     uVar2 - *puVar1);
  }
  return lVar3;
}
