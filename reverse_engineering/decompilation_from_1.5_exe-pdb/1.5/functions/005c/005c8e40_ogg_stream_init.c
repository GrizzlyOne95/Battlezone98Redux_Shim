/*
 * Entry: 005c8e40
 * Name: ogg_stream_init
 * Namespace: Global
 * Signature: undefined ogg_stream_init()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_stream_init */

undefined4 __cdecl ogg_stream_init(int *param_1,int param_2)

{
  void *pvVar1;
  
  if (param_1 != (int *)0x0) {
    memset(param_1,0,0x168);
    param_1[1] = 0x4000;
    param_1[6] = 0x400;
    pvVar1 = malloc(0x4000);
    *param_1 = (int)pvVar1;
    pvVar1 = malloc(param_1[6] * 4);
    param_1[4] = (int)pvVar1;
    pvVar1 = malloc(param_1[6] * 8);
    param_1[5] = (int)pvVar1;
    if (((*param_1 != 0) && (param_1[4] != 0)) && (pvVar1 != (void *)0x0)) {
      param_1[0x54] = param_2;
      return 0;
    }
    ogg_stream_clear(param_1);
  }
  return 0xffffffff;
}
