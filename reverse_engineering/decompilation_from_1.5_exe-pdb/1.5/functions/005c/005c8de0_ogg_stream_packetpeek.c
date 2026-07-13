/*
 * Entry: 005c8de0
 * Name: ogg_stream_packetpeek
 * Namespace: Global
 * Signature: undefined ogg_stream_packetpeek()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_stream_packetpeek */

undefined4 __cdecl ogg_stream_packetpeek(int *param_1)

{
  undefined4 uVar1;
  
  if ((param_1 != (int *)0x0) && (*param_1 != 0)) {
    uVar1 = FUN_005c8ca0(0);
    return uVar1;
  }
  return 0;
}
