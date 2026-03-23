
undefined4 FUN_006f5cc0(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  iVar1 = FUN_00477d50();
  local_8 = FUN_006f5b70();
  local_8 = iVar1 - local_8;
  iVar1 = FUN_0050cd60();
  local_c = FUN_006f5b70();
  local_c = iVar1 - local_c;
  local_10 = 0x200;
  uVar2 = _Min_value<>(&stack0x00000008,&local_8);
  uVar2 = _Max_value<>(&local_10,&local_c,uVar2);
  puVar3 = (undefined4 *)_Min_value<>(uVar2);
  return *puVar3;
}

