
void FUN_007635d0(uint param_1,undefined1 param_2)

{
  uint uStack_954;
  undefined1 local_944 [16];
  undefined1 local_934 [12];
  undefined4 local_928 [2];
  int *local_920;
  char local_919;
  undefined1 local_918 [2304];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085cfb0;
  local_10 = ExceptionList;
  uStack_954 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_954;
  ExceptionList = &local_10;
  local_18 = uStack_954;
  local_920 = (int *)FUN_00763430();
  if (local_920 == (int *)0x0) {
    FUN_00763718();
    return;
  }
  local_8 = 0;
  if (0x900 < param_1) {
    param_1 = 0x900;
  }
  FUN_006a9140();
  local_928[0] = 0;
  local_919 = (**(code **)(*local_920 + 8))(local_918,param_1,local_928,local_934,param_2);
  if (local_919 != '\0') {
    FUN_0073a710(local_934);
    FUN_00758c90(local_918,param_1,local_944);
  }
  FUN_007636fd();
  return;
}

