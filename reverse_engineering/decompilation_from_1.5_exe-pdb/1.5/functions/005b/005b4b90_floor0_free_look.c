/*
 * Entry: 005b4b90
 * Name: floor0_free_look
 * Namespace: Global
 * Signature: void floor0_free_look(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl floor0_free_look(void *param_1)

{
  int *piVar1;
  
  if (param_1 != (void *)0x0) {
    piVar1 = *(int **)((int)param_1 + 8);
    if (piVar1 != (int *)0x0) {
      if (*piVar1 != 0) {
        free((void *)*piVar1);
      }
      if (*(int *)(*(int *)((int)param_1 + 8) + 4) != 0) {
        free(*(void **)(*(int *)((int)param_1 + 8) + 4));
      }
      free(*(void **)((int)param_1 + 8));
    }
    *(undefined4 *)param_1 = 0;
    *(undefined4 *)((int)param_1 + 4) = 0;
    *(undefined4 *)((int)param_1 + 8) = 0;
    *(undefined4 *)((int)param_1 + 0xc) = 0;
    *(undefined4 *)((int)param_1 + 0x10) = 0;
    *(undefined4 *)((int)param_1 + 0x14) = 0;
    *(undefined4 *)((int)param_1 + 0x18) = 0;
    *(undefined4 *)((int)param_1 + 0x1c) = 0;
    free(param_1);
  }
  return;
}
