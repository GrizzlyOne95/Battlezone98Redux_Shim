
void __fastcall FUN_00741680(int *param_1)

{
  char cVar1;
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  int local_50;
  int local_4c;
  int *local_48;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b08e;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  param_1[0x15] = 0;
  local_48 = param_1;
  if ((char)param_1[8] != '\0') {
    if ((DAT_02cc37b0 & 1) == 0) {
      DAT_02cc37b0 = DAT_02cc37b0 | 1;
      local_8 = 0;
      basic_string<>("default");
      FUN_0083e979(FUN_00867b60);
    }
    local_8 = 0xffffffff;
    local_4c = 0;
    FUN_0042d8c0(local_54);
    FID_conflict_begin(local_58);
    while (cVar1 = FUN_00420f10(local_58), cVar1 != '\0') {
      local_50 = FUN_0042de50();
      if (((*(char *)(local_50 + 0xb0) != '\0') &&
          (cVar1 = FUN_00427310(local_50 + 0x80,&DAT_02cc3878), cVar1 != '\0')) &&
         ((local_4c == 0 || (cVar1 = FUN_0073b9a0(local_50 + 0x10), cVar1 == '\0')))) {
        local_4c = local_50;
      }
      FUN_0042da80();
    }
    if (local_4c == 0) {
      basic_string<>(&DAT_008a1ad8);
      local_8 = 2;
      (**(code **)(*local_48 + 0x14))(0,local_44,&DAT_02cc3878);
      local_8 = 0xffffffff;
      ~basic_string<>();
      *(undefined1 *)(local_48 + 8) = 0;
    }
    else {
      basic_string<>(&DAT_008a1ad8);
      local_8 = 1;
      FUN_00741990(local_4c,local_2c);
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

