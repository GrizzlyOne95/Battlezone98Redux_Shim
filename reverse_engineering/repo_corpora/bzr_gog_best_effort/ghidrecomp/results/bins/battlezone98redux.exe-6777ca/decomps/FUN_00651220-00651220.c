
void __fastcall FUN_00651220(int param_1)

{
  char cVar1;
  int local_8;
  
  if (*(int *)(param_1 + 0x6c) != *(int *)(param_1 + 0x70)) {
    for (local_8 = 0; local_8 < 0x19; local_8 = local_8 + 1) {
      cVar1 = FUN_005c84d0(param_1 + 0x9c + local_8 * 4);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x9c + local_8 * 4),*(undefined4 *)(param_1 + 0x6c),1
                    );
      }
    }
    for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
      cVar1 = FUN_005c84d0(param_1 + 0x100 + local_8 * 4);
      if (cVar1 != '\0') {
        FUN_005cb820(*(undefined4 *)(param_1 + 0x100 + local_8 * 4),*(undefined4 *)(param_1 + 0x6c),
                     1);
      }
    }
    if (0xc < *(int *)(param_1 + 0x1d4)) {
      for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
        cVar1 = FUN_005c84d0(param_1 + 0x120 + local_8 * 4);
        if (cVar1 != '\0') {
          FUN_005cb820(*(undefined4 *)(param_1 + 0x120 + local_8 * 4),
                       *(undefined4 *)(param_1 + 0x6c),1);
        }
      }
      for (local_8 = 0; local_8 < 6; local_8 = local_8 + 1) {
        cVar1 = FUN_005c84d0(param_1 + 0x140 + local_8 * 4);
        if (cVar1 != '\0') {
          FUN_005cb820(*(undefined4 *)(param_1 + 0x140 + local_8 * 4),
                       *(undefined4 *)(param_1 + 0x6c),1);
        }
      }
    }
  }
  return;
}

