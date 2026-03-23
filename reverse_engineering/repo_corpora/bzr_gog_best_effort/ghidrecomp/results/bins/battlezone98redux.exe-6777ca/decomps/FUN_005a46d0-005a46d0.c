
void __fastcall FUN_005a46d0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 local_14;
  undefined4 *local_10;
  int local_c;
  int local_8;
  
  local_8 = param_1;
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
      uVar2 = (**(code **)(*(int *)(*(int *)(local_8 + 0x34) + 0x18) + 4))();
      FUN_005a3870(uVar2);
      uVar2 = FUN_005a3da0(*(undefined4 *)(local_8 + 0x34),local_c);
      *(undefined4 *)(local_8 + 0x38) = uVar2;
    }
  }
  cVar1 = (**(code **)(**(int **)(local_8 + 0x38) + 0x18))();
  if (cVar1 == '\0') {
    (**(code **)(**(int **)(local_8 + 0x38) + 0x1c))();
  }
  else {
    *(undefined4 *)(local_8 + 0x20) = 3;
  }
  return;
}

