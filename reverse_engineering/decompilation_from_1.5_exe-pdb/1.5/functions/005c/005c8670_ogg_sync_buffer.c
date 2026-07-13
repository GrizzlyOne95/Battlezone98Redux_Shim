/*
 * Entry: 005c8670
 * Name: ogg_sync_buffer
 * Namespace: Global
 * Signature: undefined ogg_sync_buffer()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_sync_buffer */

int __cdecl ogg_sync_buffer(int *param_1,int param_2)

{
  size_t _Size;
  int iVar1;
  void *pvVar2;
  
  if (param_1[1] < 0) {
    return 0;
  }
  iVar1 = param_1[3];
  if (iVar1 != 0) {
    param_1[2] = param_1[2] - iVar1;
    if (0 < param_1[2]) {
      memmove((void *)*param_1,(void *)(iVar1 + *param_1),param_1[2]);
    }
    param_1[3] = 0;
  }
  if (param_1[1] - param_1[2] < param_2) {
    _Size = param_1[2] + 0x1000 + param_2;
    if ((void *)*param_1 == (void *)0x0) {
      pvVar2 = malloc(_Size);
    }
    else {
      pvVar2 = realloc((void *)*param_1,_Size);
    }
    if (pvVar2 == (void *)0x0) {
      ogg_sync_clear(param_1);
      return 0;
    }
    *param_1 = (int)pvVar2;
    param_1[1] = _Size;
  }
  return param_1[2] + *param_1;
}
