
void __fastcall FUN_005a4500(int param_1)

{
  undefined4 uVar1;
  undefined4 local_14;
  undefined4 *local_10;
  int local_c;
  int local_8;
  
  local_8 = param_1;
  if (*(int *)(param_1 + 0x18) != 0) {
    if (*(char *)(param_1 + 0x7c) == '\0') {
      local_14 = 0x461c4000;
      local_c = FUN_00462630(*(undefined4 *)(*(int *)(param_1 + 0x34) + 0x22c));
      local_c = FUN_004641c0(*(undefined4 *)(local_8 + 0x34),&local_14,local_c);
      if (local_c != 0) {
        *(undefined1 *)(local_8 + 0x7c) = 1;
        if ((*(int *)(local_8 + 0x38) != 0) &&
           (local_10 = *(undefined4 **)(local_8 + 0x38), local_10 != (undefined4 *)0x0)) {
          (**(code **)*local_10)(1);
        }
        uVar1 = (**(code **)(*(int *)(*(int *)(local_8 + 0x34) + 0x18) + 4))();
        FUN_005a3870(uVar1);
        uVar1 = FUN_005a3da0(*(undefined4 *)(local_8 + 0x34),local_c);
        *(undefined4 *)(local_8 + 0x38) = uVar1;
      }
    }
    uVar1 = FUN_005a3b40(*(undefined4 *)(local_8 + 0x34));
    *(undefined4 *)(local_8 + 0x80) = uVar1;
    if (*(int *)(local_8 + 0x80) != 0) {
      *(undefined4 *)(local_8 + 0x20) = 0x10;
    }
  }
  FUN_005fb450();
  return;
}

