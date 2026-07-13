
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void FUN_004f4370(undefined4 param_1)

{
  undefined2 uVar1;
  char cVar2;
  undefined2 *puVar3;
  undefined4 local_1048;
  char local_1044;
  int local_1040;
  undefined4 local_103c;
  undefined4 local_1038;
  undefined4 local_1034;
  int local_1030;
  uint local_102c;
  int local_1028;
  int local_1024;
  undefined2 local_1020;
  byte local_101e;
  char local_1019;
  undefined1 local_1018 [4096];
  undefined1 local_18;
  undefined4 local_17;
  undefined4 local_13;
  undefined4 local_f;
  undefined2 local_b;
  undefined1 local_9;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1019 = '\x01';
  FUN_004f3920();
  local_1040 = 0;
  if (local_1019 == '\0') {
LAB_004f43dc:
    local_1034 = 0;
  }
  else {
    cVar2 = FUN_004ce910(param_1,&local_1040,4);
    if (cVar2 == '\0') goto LAB_004f43dc;
    local_1034 = 1;
  }
  local_1019 = (char)local_1034;
  for (local_1028 = 0; local_1028 < local_1040; local_1028 = local_1028 + 1) {
    local_18 = 0;
    local_17 = 0;
    local_13 = 0;
    local_f = 0;
    local_b = 0;
    local_9 = 0;
    if (local_1019 == '\0') {
LAB_004f44a9:
      local_103c = 0;
    }
    else {
      if ((DAT_00917b20 < 0x419) || ((1999 < DAT_00917b20 && (DAT_00917b20 < 0x7da)))) {
        local_1048 = 0xe;
      }
      else {
        local_1048 = 0x10;
      }
      cVar2 = FUN_004ce2f0(param_1,&local_18,local_1048);
      if (cVar2 == '\0') goto LAB_004f44a9;
      local_103c = 1;
    }
    local_1019 = (char)local_103c;
    if ((char)local_103c == '\0') {
LAB_004f44f2:
      local_1044 = '\0';
    }
    else {
      cVar2 = FUN_004ce910(param_1,&local_102c,4);
      if (cVar2 == '\0') goto LAB_004f44f2;
      local_1044 = '\x01';
    }
    local_1019 = local_1044;
    if (DAT_00917b20 < 0x7de) {
      FUN_00787a30("Color","Palette",&DAT_008a1ad8,local_1018,0x1000,&DAT_02cc40c0);
      local_1024 = FUN_00481af0(local_1018);
      if (local_1024 == 0) {
        local_1024 = FUN_00481af0("objects.act");
        if (local_1024 == 0) goto LAB_004f43fe;
      }
      puVar3 = (undefined2 *)(local_102c * 3 + local_1024);
      uVar1 = *puVar3;
      local_101e = *(byte *)(puVar3 + 1);
      local_1020._0_1_ = (byte)uVar1;
      local_1020._1_1_ = (byte)((ushort)uVar1 >> 8);
      local_102c = (uint)(byte)local_1020 << 0x10 | 0xff000000 | (uint)local_1020._1_1_ << 8 |
                   (uint)local_101e;
      local_1020 = uVar1;
      FUN_00481990(local_1018);
    }
LAB_004f43fe:
    FUN_004f39b0(&local_18,local_102c,0,0);
  }
  if (local_1019 != '\0') {
    cVar2 = FUN_004ceb10(param_1,local_1030 + 0xfc,4);
    if (cVar2 != '\0') {
      local_1038 = 1;
      goto LAB_004f4642;
    }
  }
  local_1038 = 0;
LAB_004f4642:
  local_1019 = (undefined1)local_1038;
  FUN_0083e885();
  return;
}

