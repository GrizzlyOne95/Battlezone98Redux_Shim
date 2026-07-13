/*
 * Entry: 005c8db0
 * Name: ogg_stream_packetout
 * Namespace: Global
 * Signature: undefined ogg_stream_packetout()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_stream_packetout */

undefined4 __cdecl ogg_stream_packetout(int *param_1)

{
  undefined4 uVar1;
  
  if ((param_1 != (int *)0x0) && (*param_1 != 0)) {
    uVar1 = FUN_005c8ca0(1);
    return uVar1;
  }
  return 0;
}
