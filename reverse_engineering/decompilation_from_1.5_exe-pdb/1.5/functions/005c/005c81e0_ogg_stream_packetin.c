/*
 * Entry: 005c81e0
 * Name: ogg_stream_packetin
 * Namespace: Global
 * Signature: undefined ogg_stream_packetin()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_stream_packetin */

void __cdecl ogg_stream_packetin(undefined4 param_1,undefined4 *param_2)

{
  undefined4 local_8;
  undefined4 local_4;
  
  local_8 = *param_2;
  local_4 = param_2[1];
  ogg_stream_iovecin(param_1,&local_8,1,param_2[3],param_2[4],param_2[5]);
  return;
}
