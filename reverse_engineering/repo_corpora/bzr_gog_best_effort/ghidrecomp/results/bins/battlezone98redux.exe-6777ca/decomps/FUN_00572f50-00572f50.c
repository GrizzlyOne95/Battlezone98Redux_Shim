
void FUN_00572f50(undefined2 param_1)

{
  undefined4 uVar1;
  undefined2 local_1c;
  undefined2 local_1a;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined2 *local_8;
  
  local_8 = &local_1c;
  local_10 = FUN_00764760();
  if ((local_10 != 0) && (local_14 = FUN_00746720(param_1), local_14 != 0)) {
    *(undefined1 *)(local_14 + 0x61) = 1;
  }
  local_18 = FUN_007659f0();
  *local_8 = 0x4b4b;
  if (local_18 != 0) {
    FUN_007596b0(param_1,&local_1c,2,1);
  }
  *local_8 = 0x534b;
  local_1a = param_1;
  FUN_00575890(&local_1c,4,1,1);
  local_c = FUN_005771b0(param_1);
  if (local_c != 0) {
    if (*(char *)(local_c + 0x8e) == '\0') {
      if (local_c != 0) {
        FUN_005715a0(1);
      }
    }
    else {
      uVar1 = 0;
      FUN_00764760(0);
      FUN_00740a90(uVar1);
      DAT_00917f4d = 1;
      FUN_00434170(2);
    }
  }
  return;
}

