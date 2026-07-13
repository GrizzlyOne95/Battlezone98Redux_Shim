/*
 * Entry: 005a0ab0
 * Name: vorbis_granule_time
 * Namespace: Global
 * Signature: double vorbis_granule_time(vorbis_dsp_state * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl vorbis_granule_time(vorbis_dsp_state *param_1,long64 param_2)

{
  uint in_stack_00000008;
  
  if ((in_stack_00000008 & (uint)param_2) == 0xffffffff) {
    return -1.0;
  }
  if ((int)(uint)param_2 < 0) {
    return ((double)CONCAT44((uint)param_2,in_stack_00000008) + 2.0 + 9.223372036854776e+18 +
           9.223372036854776e+18) / (double)param_1->vi->rate;
  }
  return (double)CONCAT44((uint)param_2,in_stack_00000008) / (double)param_1->vi->rate;
}
