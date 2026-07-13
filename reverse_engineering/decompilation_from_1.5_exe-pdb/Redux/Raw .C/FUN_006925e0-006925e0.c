
void FUN_006925e0(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  uint local_c;
  int local_8;
  
  do {
    local_1c = 0;
    local_8 = FUN_00690710(param_1);
    if (local_8 != 0) {
      local_c = FUN_00690fc0(param_1,*(undefined2 *)(*(int *)(local_8 + 8) + 0x5a),0,&local_20,
                             &local_18,&local_14);
      if (local_c != 0) {
        uVar1 = FUN_006a0480(local_c,local_18,local_14);
        FUN_006a44d0(local_8,uVar1);
        local_10 = FUN_006a0670(local_c & 0xffff);
        uVar1 = FUN_00690870(*param_1,local_18 + -1,local_14 + -1,
                             (*(uint *)(local_10 + 0x24) >> 0x12 & 0xf) + 2,
                             (*(uint *)(local_10 + 0x24) >> 0x16 & 0xf) + 2);
        *(undefined4 *)(local_8 + 0x3c) = uVar1;
        FUN_006907b0(param_1,local_8);
        uVar1 = FUN_00690d20(local_c);
        *(undefined4 *)(local_8 + 0x34) = uVar1;
        *(uint *)(local_8 + 0x30) = local_c;
        *(undefined4 *)(local_8 + 0x40) = local_20;
        local_1c = 1;
        FUN_00690da0(param_1);
      }
    }
  } while (local_1c != 0);
  return;
}

