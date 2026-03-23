
void * FUN_006a8d40(int param_1,int param_2,undefined4 param_3)

{
  void *pvVar1;
  void *pvVar2;
  undefined1 *puVar3;
  undefined4 local_1c;
  int local_14;
  int local_10;
  int local_8;
  
  pvVar1 = malloc(0x94);
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    *(undefined4 *)((int)pvVar1 + local_8 * 4) = 0;
  }
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    pvVar2 = operator_new(0x10);
    if (pvVar2 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_006a8f40(param_1,param_2);
    }
    *(undefined4 *)((int)pvVar1 + local_8 * 4 + 0x40) = local_1c;
    for (local_14 = 0; local_14 < param_1; local_14 = local_14 + 1) {
      for (local_10 = 0; local_10 < param_2; local_10 = local_10 + 1) {
        puVar3 = (undefined1 *)FUN_006a65e0(local_14,local_10);
        *puVar3 = 0;
      }
    }
  }
  *(int *)((int)pvVar1 + 0x84) = param_1;
  *(int *)((int)pvVar1 + 0x80) = param_2;
  *(undefined4 *)((int)pvVar1 + 0x88) = param_3;
  *(undefined4 *)((int)pvVar1 + 0x8c) = 0;
  *(undefined4 *)((int)pvVar1 + 0x90) = 0;
  return pvVar1;
}

