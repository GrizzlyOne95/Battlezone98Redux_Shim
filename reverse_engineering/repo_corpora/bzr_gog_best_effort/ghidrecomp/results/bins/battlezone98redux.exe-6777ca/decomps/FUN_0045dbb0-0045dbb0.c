
void FUN_0045dbb0(char param_1)

{
  int iVar1;
  undefined8 local_24;
  undefined1 local_1b;
  undefined1 local_1a;
  char local_19;
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = 0;
  local_19 = param_1;
  if (((param_1 == 'a') || (param_1 == 's')) || (DAT_008e8c0d != '\0')) {
    local_24 = CONCAT71(0x706d657276,param_1);
    sprintf(local_18,"%.8s.odf",&local_24);
    iVar1 = FUN_00481f10(local_18);
    if (iVar1 == 0) {
      local_24 = CONCAT71(0x7963657276,local_19);
      sprintf(local_18,"%.8s.odf",&local_24);
      iVar1 = FUN_00481f10(local_18);
      if (iVar1 == 0) {
        local_24 = 0;
      }
    }
  }
  if ((int)local_24 == 0 && local_24._4_4_ == 0) {
    if ((local_19 == 'c') || (local_19 == 's')) {
      local_1b = 0x73;
    }
    else {
      local_1b = 0x61;
    }
    local_1a = local_1b;
    local_24 = CONCAT71(0x706d657276,local_1b);
    sprintf(local_18,"%.8s.odf",&local_24);
    iVar1 = FUN_00481f10(local_18);
    if (iVar1 == 0) {
      local_24 = CONCAT71(0x7963657276,local_1a);
      sprintf(local_18,"%.8s.odf",&local_24);
      iVar1 = FUN_00481f10(local_18);
      if (iVar1 == 0) {
        local_24 = 0;
      }
    }
  }
  FUN_0083e885();
  return;
}

