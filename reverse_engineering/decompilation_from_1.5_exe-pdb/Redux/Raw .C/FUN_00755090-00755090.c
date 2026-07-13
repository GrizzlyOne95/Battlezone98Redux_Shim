
void FUN_00755090(void)

{
  undefined4 uVar1;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_14 [8];
  int local_c;
  int *local_8;
  
  local_8 = (int *)FUN_0073add0();
  uVar1 = (**(code **)(*local_8 + 8))(local_14);
  FUN_0073a710(uVar1);
  *(undefined4 *)(local_c + 0x18) = local_24;
  *(undefined4 *)(local_c + 0x1c) = local_20;
  *(undefined4 *)(local_c + 0x20) = local_1c;
  *(undefined4 *)(local_c + 0x24) = local_18;
  return;
}

