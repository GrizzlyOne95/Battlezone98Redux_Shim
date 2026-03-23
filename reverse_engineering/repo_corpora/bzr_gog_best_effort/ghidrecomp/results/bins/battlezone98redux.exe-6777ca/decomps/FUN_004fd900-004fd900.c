
void FUN_004fd900(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  uint local_80;
  char local_79;
  undefined1 local_78 [24];
  undefined1 local_60 [24];
  undefined1 local_48 [52];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084aa10;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  if (DAT_00917b20 < 0x7df) {
    local_79 = FUN_004ce910(param_1,&local_8c,4,uVar2);
    if (local_79 != '\0') {
      uVar3 = FUN_004fbc80(local_78,local_8c);
      local_8 = 1;
      FUN_00482860(uVar3);
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
  else {
    local_79 = FUN_004ce2f0(param_1,local_48,0x32);
    if (local_79 != '\0') {
      basic_string<>(local_48);
      local_8 = 0;
      FUN_00482860(local_60);
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
  if ((local_79 == '\0') || (cVar1 = FUN_004ce910(param_1,&DAT_0091830c,4,uVar2), cVar1 == '\0')) {
    local_84 = 0;
  }
  else {
    local_84 = 1;
  }
  local_79 = (char)local_84;
  if (0x40a < DAT_00917b20) {
    if (((char)local_84 == '\0') ||
       (cVar1 = FUN_004ce910(param_1,&DAT_00918314,4,uVar2), cVar1 == '\0')) {
      local_88 = 0;
    }
    else {
      local_88 = 1;
    }
    local_79 = (char)local_88;
  }
  local_80 = (uint)(local_79 != '\0');
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

