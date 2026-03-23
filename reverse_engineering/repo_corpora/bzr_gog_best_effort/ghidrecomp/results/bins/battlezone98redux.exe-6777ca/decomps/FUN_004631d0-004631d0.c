
undefined4 FUN_004631d0(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = (*(code *)**(undefined4 **)(param_1 + 0x18))();
  uVar1 = *(uint *)(iVar2 + 0x14);
  if (uVar1 < 0x4d494e46) {
    if (((uVar1 == 0x4d494e45) || (uVar1 == 0x464c4152)) || (uVar1 == 0x4d474e54)) {
      return 1;
    }
  }
  else {
    if (uVar1 == 0x50524f58) {
      return 1;
    }
    if (uVar1 == 0x57504e4d) {
      return 1;
    }
  }
  return 0;
}

