
void FUN_007467b0(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined4 local_24 [2];
  int local_1c;
  uint local_18;
  int local_14;
  undefined4 local_10;
  int local_c;
  char local_5;
  
  local_1c = FUN_0056f900();
  if (local_1c != 0) {
    local_c = *(int *)(param_1 + 0x80);
    local_5 = *(int *)(param_1 + 0x80) < 1;
    local_18 = (uint)(byte)local_5;
    local_14 = local_1c;
    if (local_c < 0) {
      local_c = 0;
    }
    while (local_5 != '\0') {
      local_c = local_c + 1;
      local_5 = '\0';
      puVar2 = (undefined4 *)FUN_0042d8c0(local_28);
      local_10 = *puVar2;
      puVar2 = (undefined4 *)FID_conflict_begin(local_2c);
      local_24[0] = *puVar2;
      cVar1 = FUN_00420f10(local_24);
      if (cVar1 != '\0') {
        iVar3 = FUN_004305e0();
        if (*(int *)(iVar3 + 0x80) != local_c) {
                    /* WARNING: Subroutine does not return */
          FUN_0042de70();
        }
        local_5 = '\x01';
      }
    }
    FUN_007468b0(param_1,local_c);
  }
  return;
}

