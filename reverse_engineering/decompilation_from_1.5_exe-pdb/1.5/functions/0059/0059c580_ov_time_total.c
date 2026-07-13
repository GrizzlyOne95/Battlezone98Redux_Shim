/*
 * Entry: 0059c580
 * Name: ov_time_total
 * Namespace: Global
 * Signature: double ov_time_total(OggVorbis_File * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl ov_time_total(OggVorbis_File *param_1,int param_2)

{
  double dVar1;
  double local_14;
  int local_8;
  
  if (param_1->ready_state < 2) {
    local_14 = -131.0;
  }
  else if ((param_1->seekable == 0) || (param_1->links <= param_2)) {
    local_14 = -131.0;
  }
  else if (param_2 < 0) {
    local_14 = 0.0;
    for (local_8 = 0; local_8 < param_1->links; local_8 = local_8 + 1) {
      dVar1 = ov_time_total(param_1,local_8);
      local_14 = dVar1 + local_14;
    }
  }
  else {
    local_14 = (double)param_1->pcmlengths[param_2 * 2 + 1] / (double)param_1->vi[param_2].rate;
  }
  return local_14;
}
