/*
 * Entry: 005c8c10
 * Name: ogg_stream_reset
 * Namespace: Global
 * Signature: undefined ogg_stream_reset()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_stream_reset */

undefined4 __cdecl ogg_stream_reset(int *param_1)

{
  if ((param_1 != (int *)0x0) && (*param_1 != 0)) {
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[9] = 0;
    param_1[0x51] = 0;
    param_1[0x52] = 0;
    param_1[0x53] = 0;
    param_1[0x55] = -1;
    param_1[0x56] = 0;
    param_1[0x57] = 0;
    param_1[0x58] = 0;
    param_1[0x59] = 0;
    return 0;
  }
  return 0xffffffff;
}
