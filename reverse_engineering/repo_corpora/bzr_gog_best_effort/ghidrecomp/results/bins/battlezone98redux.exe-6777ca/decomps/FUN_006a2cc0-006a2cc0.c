
undefined1 __thiscall FUN_006a2cc0(int param_1,undefined4 param_2)

{
  char cVar1;
  void *pvVar2;
  undefined1 local_30;
  char local_2c;
  char local_28;
  char local_24;
  char local_20;
  int local_10;
  uint local_c;
  char local_5;
  
  local_5 = 1;
  cVar1 = FUN_004ce910(param_2,param_1 + 0x18,4);
  local_5 = cVar1 != '\0';
  if (((bool)local_5) && (cVar1 = FUN_004ce910(param_2,param_1 + 0x1c,4), cVar1 != '\0')) {
    local_20 = '\x01';
  }
  else {
    local_20 = '\0';
  }
  local_5 = local_20;
  if ((local_20 == '\0') || (cVar1 = FUN_004ce910(param_2,param_1 + 0x20,4), cVar1 == '\0')) {
    local_24 = '\0';
  }
  else {
    local_24 = '\x01';
  }
  local_5 = local_24;
  if ((local_24 == '\0') || (cVar1 = FUN_004ce910(param_2,&local_c,4), cVar1 == '\0')) {
    local_28 = '\0';
  }
  else {
    local_28 = '\x01';
  }
  local_5 = local_28;
  if (DAT_009310a8 != 0) {
    operator_delete((void *)DAT_009310a8);
  }
  DAT_009310a8 = FUN_0083d92c(local_c);
  if (((DAT_00917b20 < 0x418) || (1999 < DAT_00917b20)) && (DAT_00917b20 < 0x7da)) {
    pvVar2 = (void *)FUN_0083d92c(-(uint)((int)((ulonglong)local_c * 4 >> 0x20) != 0) |
                                  (uint)((ulonglong)local_c * 4));
    cVar1 = FUN_004ce910(param_2,pvVar2,local_c << 2);
    if (cVar1 == '\0') {
      local_5 = '\0';
    }
    else {
      for (local_10 = 0; local_10 < (int)local_c; local_10 = local_10 + 1) {
        *(undefined1 *)(DAT_009310a8 + local_10) = *(undefined1 *)((int)pvVar2 + local_10 * 4);
      }
    }
    operator_delete__(pvVar2);
  }
  else {
    if ((local_5 == '\0') || (cVar1 = FUN_004ce730(param_2,DAT_009310a8,local_c), cVar1 == '\0')) {
      local_2c = '\0';
    }
    else {
      local_2c = '\x01';
    }
    local_5 = local_2c;
  }
  if ((local_5 == '\0') || (cVar1 = FUN_004616d0(param_2), cVar1 == '\0')) {
    local_30 = 0;
  }
  else {
    local_30 = 1;
  }
  return local_30;
}

