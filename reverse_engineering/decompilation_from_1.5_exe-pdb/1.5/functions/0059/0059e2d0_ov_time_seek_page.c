/*
 * Entry: 0059e2d0
 * Name: ov_time_seek_page
 * Namespace: Global
 * Signature: int ov_time_seek_page(OggVorbis_File * param_1, double param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ov_time_seek_page(OggVorbis_File *param_1,double param_2)

{
  int iVar1;
  undefined4 extraout_EDX;
  undefined4 unaff_ESI;
  double dVar2;
  undefined4 in_stack_00000008;
  int local_18;
  double local_14;
  
  local_14 = 0.0;
  if (param_1->ready_state < 2) {
    iVar1 = -0x83;
  }
  else if (param_1->seekable == 0) {
    iVar1 = -0x8a;
  }
  else if (0.0 <= (double)CONCAT44(param_2._0_4_,in_stack_00000008)) {
    local_18 = 0;
    for (; (local_18 < param_1->links &&
           (dVar2 = ov_time_total(param_1,local_18),
           local_14 + dVar2 <= (double)CONCAT44(param_2._0_4_,in_stack_00000008)));
        local_14 = local_14 + dVar2) {
      local_18 = local_18 + 1;
    }
    if (local_18 == param_1->links) {
      iVar1 = -0x83;
    }
    else {
      _ftol2();
      iVar1 = ov_pcm_seek_page(param_1,CONCAT44(unaff_ESI,extraout_EDX));
    }
  }
  else {
    iVar1 = -0x83;
  }
  return iVar1;
}
