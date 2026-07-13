/*
 * Entry: 005c8c70
 * Name: ogg_stream_reset_serialno
 * Namespace: Global
 * Signature: undefined ogg_stream_reset_serialno()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_stream_reset_serialno */

undefined4 __cdecl ogg_stream_reset_serialno(int *param_1,undefined4 param_2)

{
  int extraout_EDX;
  
  if ((param_1 != (int *)0x0) && (*param_1 != 0)) {
    ogg_stream_reset(param_1);
    *(undefined4 *)(extraout_EDX + 0x150) = param_2;
    return 0;
  }
  return 0xffffffff;
}
