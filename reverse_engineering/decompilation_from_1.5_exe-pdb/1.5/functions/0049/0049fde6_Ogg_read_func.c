/*
 * Entry: 0049fde6
 * Name: Ogg_read_func
 * Namespace: Global
 * Signature: uint Ogg_read_func(void * param_1, uint param_2, uint param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl Ogg_read_func(void *param_1,uint param_2,uint param_3,void *param_4)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = param_2 * param_3;
  uVar1 = *(int *)((int)param_4 + 0x14) - *(int *)((int)param_4 + 0x2f0);
  if (uVar1 <= uVar2 && uVar2 - uVar1 != 0) {
    uVar2 = uVar1;
  }
  memcpy(param_1,*(int *)((int)param_4 + 0x10) + *(int *)((int)param_4 + 0x2f0),uVar2);
  *(int *)((int)param_4 + 0x2f0) = *(int *)((int)param_4 + 0x2f0) + uVar2;
  return uVar2;
}
