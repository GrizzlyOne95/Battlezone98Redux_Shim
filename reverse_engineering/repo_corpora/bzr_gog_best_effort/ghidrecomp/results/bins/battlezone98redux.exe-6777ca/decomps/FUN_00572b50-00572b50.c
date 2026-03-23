
undefined4 FUN_00572b50(ushort param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 local_c;
  
  uVar1 = (uint)param_1;
  FUN_00764760(uVar1);
  iVar2 = FUN_00746720(uVar1);
  if ((iVar2 == 0) || (*(char *)(iVar2 + 0x44) == '\0')) {
    local_c = 0;
  }
  else {
    local_c = 1;
  }
  return local_c;
}

