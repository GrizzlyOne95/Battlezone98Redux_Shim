
void __thiscall FUN_00575810(int param_1,void *param_2,size_t param_3)

{
  void *pvVar1;
  
  if (*(int *)(param_1 + 0x1c) != 0) {
    free(*(void **)(param_1 + 0x1c));
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  if (param_2 != (void *)0x0) {
    pvVar1 = malloc(param_3);
    *(void **)(param_1 + 0x1c) = pvVar1;
    memcpy(*(void **)(param_1 + 0x1c),param_2,param_3);
  }
  return;
}

