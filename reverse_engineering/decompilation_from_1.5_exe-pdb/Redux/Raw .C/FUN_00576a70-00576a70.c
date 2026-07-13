
void FUN_00576a70(void)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined2 local_1c;
  undefined2 local_1a;
  int local_18;
  int local_14;
  int local_10;
  undefined2 *local_c;
  int local_8;
  
  local_c = &local_1c;
  local_10 = FUN_00764760();
  if (local_10 != 0) {
    uVar1 = FUN_0056f920();
    local_14 = FUN_00746720(uVar1);
    if (local_14 != 0) {
      *(undefined1 *)(local_14 + 0x61) = 1;
    }
  }
  *local_c = 0x4b41;
  local_18 = FUN_007659f0();
  if (local_18 != 0) {
    FUN_00759710(local_8 + 0x30,&local_1c,2,1);
  }
  *local_c = 0x5341;
  local_1a = FUN_0056f920();
  uVar2 = FUN_005765e0();
  uVar2 = FUN_0081cb40("multi_message","autokick",uVar2);
  FUN_0056fcb0("%s %s",uVar2);
  FUN_00575890(&local_1c,4,1,1);
  if (local_8 != 0) {
    FUN_005715a0(1);
  }
  return;
}

