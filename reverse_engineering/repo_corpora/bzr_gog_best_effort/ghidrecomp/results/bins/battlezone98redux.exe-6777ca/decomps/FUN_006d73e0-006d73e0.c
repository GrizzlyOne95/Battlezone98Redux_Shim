
undefined4 FUN_006d73e0(void)

{
  int iVar1;
  undefined8 uVar2;
  undefined1 local_34 [8];
  undefined1 local_2c [16];
  undefined8 local_1c;
  undefined1 local_14;
  int *local_c;
  int *local_8;
  
  FUN_006d1a50(local_2c);
  local_1c = FUN_006c94e0();
  local_8 = local_c;
  iVar1 = *local_c;
  if ((iVar1 != (int)local_1c) || (local_c[1] != (int)((ulonglong)local_1c >> 0x20))) {
    FUN_006d1a30(local_34);
    uVar2 = FUN_006c94e0();
    iVar1 = *local_c;
    if ((iVar1 != (int)uVar2) || (local_c[1] != (int)((ulonglong)uVar2 >> 0x20))) {
      local_14 = 0;
      goto LAB_006d7461;
    }
  }
  local_14 = 1;
LAB_006d7461:
  return CONCAT31((int3)((uint)iVar1 >> 8),local_14);
}

