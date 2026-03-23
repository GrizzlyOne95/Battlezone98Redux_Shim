
void FUN_0043a5f0(void)

{
  int iVar1;
  undefined4 local_8;
  
  if (DAT_0260c217 != '\0') {
    DAT_0260c217 = '\0';
    iVar1 = FUN_0043bc50();
    while (local_8 = iVar1, local_8 != 0) {
      iVar1 = FUN_00439cc0(local_8);
      if ((*(uint *)(local_8 + 0x70) & 8) != 0) {
        *(uint *)(local_8 + 0x70) = *(uint *)(local_8 + 0x70) & 0xfffffff7;
      }
    }
  }
  return;
}

