
void FUN_007bba90(undefined4 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  char local_78;
  undefined4 local_74;
  undefined4 local_70;
  uint local_6c;
  int local_68;
  char local_61;
  undefined1 local_60 [52];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00861824;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_6c = 0;
  FUN_004fbb60(local_14);
  cVar1 = FUN_007bb840(&local_74);
  if (cVar1 == '\0') {
    do {
      cVar1 = FUN_007bd030();
      if (cVar1 == '\0') {
        uVar2 = FUN_00667590();
        local_8 = 0;
        local_6c = local_6c | 1;
        FUN_007bd050(uVar2);
        uVar2 = FUN_0066ae00();
        cVar1 = FUN_007bd6f0(uVar2);
        if (cVar1 == '\0') goto LAB_007bbb4f;
        local_78 = '\x01';
      }
      else {
LAB_007bbb4f:
        local_78 = '\0';
      }
      local_61 = local_78;
      local_8 = 0xffffffff;
      if ((local_6c & 1) != 0) {
        local_6c = local_6c & 0xfffffffe;
        FUN_00667660();
      }
      if (local_61 == '\0') goto LAB_007bbb9e;
      FUN_007bd090();
      *(int *)(local_68 + 0xc) = *(int *)(local_68 + 0xc) + -1;
    } while( true );
  }
  if (param_1 != (undefined4 *)0x0) {
    FUN_007bb040();
  }
LAB_007bbc15:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
LAB_007bbb9e:
  iVar3 = FUN_00667170();
  if (iVar3 == 0) {
    if (param_1 != (undefined4 *)0x0) {
      FUN_007bb040();
    }
  }
  else {
    if (param_1 == (undefined4 *)0x0) {
      basic_string<>("filesystem::recursive_directory_iterator directory error");
      local_8 = 1;
      FUN_007bb0e0(local_2c,local_74,local_70);
                    /* WARNING: Subroutine does not return */
      _CxxThrowException(local_60,(ThrowInfo *)&DAT_008d8618);
    }
    *param_1 = local_74;
    param_1[1] = local_70;
  }
  goto LAB_007bbc15;
}

