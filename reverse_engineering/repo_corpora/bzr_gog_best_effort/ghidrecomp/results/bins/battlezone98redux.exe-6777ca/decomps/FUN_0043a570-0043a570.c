
void FUN_0043a570(void)

{
  int iVar1;
  undefined4 local_8;
  
  if (DAT_0260c217 == '\0') {
    DAT_0260c217 = '\x01';
    local_8 = FUN_0043bc50();
    while (local_8 != 0) {
      iVar1 = FUN_00439cc0(local_8);
      FUN_0043aec0(local_8);
      if ((*(uint *)(local_8 + 0x14) & 1) == 0) {
        FUN_0043b010(local_8);
        local_8 = iVar1;
      }
      else {
        *(uint *)(local_8 + 0x70) = *(uint *)(local_8 + 0x70) | 8;
        local_8 = iVar1;
      }
    }
  }
  return;
}

