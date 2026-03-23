
void FUN_0045c6e0(void)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_40 [8];
  undefined1 local_38 [8];
  undefined1 local_30 [4];
  uint local_2c;
  undefined1 local_28 [4];
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847178;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_2c = 0;
  FUN_0045e380(local_14);
  local_8 = 0;
  FUN_00438c40(local_28);
  FID_conflict_begin(local_30);
  cVar1 = FUN_00420f10(local_30);
  if (cVar1 != '\0') {
    local_24[0] = '\0';
    local_24[1] = '\0';
    local_24[2] = '\0';
    local_24[3] = '\0';
    local_24[4] = '\0';
    local_24[5] = '\0';
    local_24[6] = '\0';
    local_24[7] = '\0';
    puVar2 = (undefined4 *)FUN_00422e80();
    sprintf(local_24,"%.8s",*puVar2);
    FUN_0045e3e0(local_40,local_24);
                    /* WARNING: Subroutine does not return */
    FUN_0042de70();
  }
  FUN_0045e3b0(local_38);
  local_2c = local_2c | 1;
  local_8 = 0xffffffff;
  FUN_0045c7d0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

