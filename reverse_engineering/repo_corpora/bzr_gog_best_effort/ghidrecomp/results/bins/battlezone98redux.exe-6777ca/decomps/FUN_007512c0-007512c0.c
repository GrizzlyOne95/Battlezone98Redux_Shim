
void FUN_007512c0(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined1 local_60 [12];
  undefined4 local_54;
  int *local_50;
  uint local_4c;
  char *local_48;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845348;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_4c = 0;
  basic_string<>(local_14);
  local_8 = 0;
  iVar1 = FUN_006aa1d0();
  if (iVar1 != 0) {
    local_50 = (int *)FUN_006aa1d0();
    puVar2 = (undefined4 *)FUN_0073a970(local_60);
    local_48 = (char *)(**(code **)(*local_50 + 0x1c))(*puVar2,puVar2[1]);
    if ((local_48 != (char *)0x0) && (*local_48 != '\0')) {
      local_54 = FUN_0073bf60(local_44,local_48);
      FUN_0045e0f0(local_54);
      ~basic_string<>();
    }
  }
  basic_string<>(local_2c);
  local_4c = local_4c | 1;
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

