
undefined1 __thiscall FUN_0049ca10(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined8 local_24;
  undefined1 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  uint local_10;
  int local_c;
  char local_5;
  
  local_5 = '\x01';
  *(undefined4 *)(param_1 + 0x370) = 0;
  local_c = param_1;
  if (DAT_00917b20 < 0x407) {
    puVar3 = (undefined4 *)FUN_0045c4d0();
    puVar5 = (undefined4 *)(local_c + 0x378);
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
  }
  else {
    local_24 = 0;
    cVar1 = FUN_004cef70(param_2,param_1 + 0x378,0x40);
    local_5 = cVar1 != '\0';
    local_10 = (uint)(byte)local_5;
    if ((local_10 == 0) || (cVar1 = FUN_004cf210(param_2,&local_24,8), cVar1 == '\0')) {
      local_14 = 0;
    }
    else {
      local_14 = 1;
    }
    local_5 = (char)local_14;
    if ((int)local_24 != 0 || local_24._4_4_ != 0) {
      uVar2 = FUN_004e0f70((int)local_24,local_24._4_4_);
      *(undefined4 *)(local_c + 0x370) = uVar2;
    }
    if (2000 < DAT_00917b20) {
      if ((local_5 == '\0') || (cVar1 = FUN_004ce910(param_2,local_c + 0x3b8,4), cVar1 == '\0')) {
        local_18 = 0;
      }
      else {
        local_18 = 1;
      }
      local_5 = (char)local_18;
    }
  }
  if ((local_5 == '\0') || (cVar1 = FUN_005afb30(param_2), cVar1 == '\0')) {
    local_1c = 0;
  }
  else {
    local_1c = 1;
  }
  return local_1c;
}

