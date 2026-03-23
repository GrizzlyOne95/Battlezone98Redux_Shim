
char FUN_00460910(undefined4 param_1)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  void *pvVar4;
  int local_48;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  int *local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084736c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_11 = FUN_004ce1c0(param_1,"[AiPath]",DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (DAT_00917b20 < 0x7dc) {
    if ((local_11 == '\0') || (cVar2 = FUN_004ce4e0(param_1,&local_40,4), cVar2 == '\0')) {
      local_24 = 0;
    }
    else {
      local_24 = 1;
    }
    local_11 = (char)local_24;
  }
  else {
    if ((local_11 == '\0') || (cVar2 = FUN_004cf7b0(param_1,&local_40,4), cVar2 == '\0')) {
      local_28 = 0;
    }
    else {
      local_28 = 1;
    }
    local_11 = (char)local_28;
  }
  piVar1 = local_18;
  if (local_11 != '\0') {
    if ((local_11 == '\0') || (cVar2 = FUN_004ce910(param_1,&local_1c,4), cVar2 == '\0')) {
      local_2c = 0;
    }
    else {
      local_2c = 1;
    }
    local_11 = (char)local_2c;
    if (local_2c != 0) {
      *local_18 = 0;
      if (0 < local_1c) {
        local_20 = FUN_0083d92c(local_1c + 1);
        if ((local_11 == '\0') || (cVar2 = FUN_004ce2f0(param_1,local_20,local_1c), cVar2 == '\0'))
        {
          local_30 = 0;
        }
        else {
          local_30 = 1;
        }
        local_11 = (char)local_30;
        *(undefined1 *)(local_20 + local_1c) = 0;
        *local_18 = local_20;
      }
      if (local_11 != '\0') {
        if ((local_11 == '\0') || (cVar2 = FUN_004ce910(param_1,local_18 + 1,4), cVar2 == '\0')) {
          local_34 = 0;
        }
        else {
          local_34 = 1;
        }
        local_11 = (char)local_34;
        if ((char)local_34 != '\0') {
          iVar3 = FUN_0083d92c(-(uint)((int)((ulonglong)(uint)local_18[1] * 8 >> 0x20) != 0) |
                               (uint)((ulonglong)(uint)local_18[1] * 8));
          local_18[2] = iVar3;
          if ((local_11 == '\0') ||
             (cVar2 = FUN_004cee40(param_1,local_18[2],local_18[1] << 3), cVar2 == '\0')) {
            local_38 = 0;
          }
          else {
            local_38 = 1;
          }
          local_11 = (char)local_38;
          if (DAT_00917b20 < 0x3f6) {
            local_18[4] = 0;
          }
          else if ((char)local_38 != '\0') {
            if (((char)local_38 == '\0') ||
               (cVar2 = FUN_0045c370(param_1,local_18 + 4,4), cVar2 == '\0')) {
              local_3c = 0;
            }
            else {
              local_3c = 1;
            }
            local_11 = (char)local_3c;
          }
        }
      }
    }
    if (local_11 != '\0') {
      pvVar4 = operator_new(8);
      local_8 = 0;
      if (pvVar4 == (void *)0x0) {
        local_48 = 0;
      }
      else {
        local_48 = FUN_004cc910(local_40,piVar1);
      }
      if (local_48 == 0) {
        local_11 = '\0';
      }
    }
  }
  ExceptionList = local_10;
  return local_11;
}

