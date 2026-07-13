/*
 * Entry: 0059e450
 * Name: ov_time_tell
 * Namespace: Global
 * Signature: double ov_time_tell(OggVorbis_File * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl ov_time_tell(OggVorbis_File *param_1)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  int local_18;
  double local_14;
  undefined8 local_c;
  
  local_18 = 0;
  local_c = 0;
  local_14 = 0.0;
  if (param_1->ready_state < 2) {
    local_14 = -131.0;
  }
  else {
    if (param_1->seekable != 0) {
      local_c = ov_pcm_total(param_1,-1);
      local_14 = ov_time_total(param_1,-1);
      local_18 = param_1->links;
      while (local_18 = local_18 + -1, -1 < local_18) {
        puVar1 = (uint *)(param_1->pcmlengths + local_18 * 2 + 1);
        uVar3 = (uint)local_c - *puVar1;
        iVar4 = (local_c._4_4_ - *(int *)((int)param_1->pcmlengths + local_18 * 0x10 + 0xc)) -
                (uint)((uint)local_c < *puVar1);
        local_c = CONCAT44(iVar4,uVar3);
        dVar5 = ov_time_total(param_1,local_18);
        local_14 = local_14 - dVar5;
        iVar2 = *(int *)((int)&param_1->pcm_offset + 4);
        if ((iVar4 <= iVar2) && ((iVar4 < iVar2 || (uVar3 <= (uint)param_1->pcm_offset)))) break;
      }
    }
    uVar3 = (uint)param_1->pcm_offset;
    local_14 = (double)CONCAT44((*(int *)((int)&param_1->pcm_offset + 4) - local_c._4_4_) -
                                (uint)(uVar3 < (uint)local_c),uVar3 - (uint)local_c) /
               (double)param_1->vi[local_18].rate + local_14;
  }
  return local_14;
}
