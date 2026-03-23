
void FUN_00731050(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  int iVar2;
  iterator *this;
  iterator *piVar3;
  undefined1 local_64 [8];
  undefined1 local_5c [8];
  undefined1 local_54 [8];
  undefined1 local_4c [8];
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 *local_24;
  undefined4 *local_20;
  int local_1c;
  undefined4 *local_18;
  undefined4 *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = FUN_00732ef0(&param_1);
  local_8 = FUN_00732ef0(&param_1);
  local_10 = local_c;
  while (local_10 != 0) {
    local_1c = local_8 % local_10;
    local_8 = local_10;
    local_10 = local_1c;
  }
  iVar2 = FUN_00732ef0(&param_1);
  if (local_8 < iVar2) {
    for (; 0 < local_8; local_8 = local_8 + -1) {
      FUN_00732eb0(&local_3c,local_8);
      local_34 = local_3c;
      local_30 = local_38;
      piVar3 = (iterator *)&stack0x00000014;
      this = (iterator *)FUN_00732eb0(local_4c,local_c);
      bVar1 = __FrameHandler3::HandlerMap::iterator::operator==(this,piVar3);
      if (bVar1) {
        local_44 = param_1;
        local_40 = param_2;
        local_14 = &local_44;
      }
      else {
        local_14 = (undefined4 *)FUN_00732eb0(local_54,local_c);
      }
      local_20 = local_14;
      local_2c = *local_14;
      local_28 = local_14[1];
      do {
        FUN_00731030(local_34,local_30,local_2c,local_28);
        local_34 = local_2c;
        local_30 = local_28;
        iVar2 = FUN_00732ef0(&local_2c);
        if (local_c < iVar2) {
          local_18 = (undefined4 *)FUN_00732eb0(local_5c,local_c);
        }
        else {
          iVar2 = FUN_00732ef0(&local_2c);
          local_18 = (undefined4 *)FUN_00732eb0(local_64,local_c - iVar2);
        }
        local_24 = local_18;
        local_2c = *local_18;
        local_28 = local_18[1];
        bVar1 = __FrameHandler3::HandlerMap::iterator::operator==
                          ((iterator *)&local_2c,(iterator *)&local_3c);
      } while (!bVar1);
    }
  }
  return;
}

