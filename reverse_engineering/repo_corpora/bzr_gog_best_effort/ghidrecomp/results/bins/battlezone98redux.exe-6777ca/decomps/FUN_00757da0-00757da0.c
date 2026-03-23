
void FUN_00757da0(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_14 [8];
  int local_c;
  int *local_8;
  
  iVar1 = FUN_006aa1b0();
  if (iVar1 != 0) {
    local_8 = (int *)FUN_006aa1b0();
    uVar2 = (**(code **)(*local_8 + 8))(local_14);
    FUN_0073a6e0(uVar2);
    *(undefined4 *)(local_c + 0x18) = local_24;
    *(undefined4 *)(local_c + 0x1c) = local_20;
    *(undefined4 *)(local_c + 0x20) = local_1c;
    *(undefined4 *)(local_c + 0x24) = local_18;
  }
  return;
}

