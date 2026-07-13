/*
 * Entry: 005a2c30
 * Name: _vp_global_free
 * Namespace: Global
 * Signature: void _vp_global_free(vorbis_look_psy_global * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _vp_global_free(vorbis_look_psy_global *param_1)

{
  if (param_1 != (vorbis_look_psy_global *)0x0) {
    param_1->ampmax = 0.0;
    param_1->channels = 0;
    param_1->gi = (vorbis_info_psy_global *)0x0;
    param_1->coupling_pointlimit[0][0] = 0;
    param_1->coupling_pointlimit[0][1] = 0;
    param_1->coupling_pointlimit[0][2] = 0;
    param_1->coupling_pointlimit[1][0] = 0;
    param_1->coupling_pointlimit[1][1] = 0;
    param_1->coupling_pointlimit[1][2] = 0;
                    /* WARNING: Could not recover jumptable at 0x005a2c58. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    free(param_1);
    return;
  }
  return;
}
