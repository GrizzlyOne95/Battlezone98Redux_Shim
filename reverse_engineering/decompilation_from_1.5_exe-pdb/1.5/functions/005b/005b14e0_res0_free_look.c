/*
 * Entry: 005b14e0
 * Name: res0_free_look
 * Namespace: Global
 * Signature: void res0_free_look(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl res0_free_look(void *param_1)

{
  int iVar1;
  
  if (param_1 != (void *)0x0) {
    iVar1 = 0;
    if (0 < *(int *)((int)param_1 + 4)) {
      do {
        if (*(int *)(*(int *)((int)param_1 + 0x14) + iVar1 * 4) != 0) {
          free(*(void **)(*(int *)((int)param_1 + 0x14) + iVar1 * 4));
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < *(int *)((int)param_1 + 4));
    }
    free(*(void **)((int)param_1 + 0x14));
    iVar1 = 0;
    if (0 < *(int *)((int)param_1 + 0x18)) {
      do {
        free(*(void **)(*(int *)((int)param_1 + 0x1c) + iVar1 * 4));
        iVar1 = iVar1 + 1;
      } while (iVar1 < *(int *)((int)param_1 + 0x18));
    }
    free(*(void **)((int)param_1 + 0x1c));
    memset(param_1,0,0x2c);
    free(param_1);
  }
  return;
}
