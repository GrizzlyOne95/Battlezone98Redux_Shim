
undefined4 * FUN_0041b7b0(undefined4 param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int local_20;
  int local_1c;
  undefined4 local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844cf8;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0041ab20(param_3);
  local_8 = 0;
  *local_14 = TouchInputActionButton::vftable;
  if (*(int *)(param_2 + 0x18) == 8) {
    local_14[0x1b] = 0;
  }
  else if (*(int *)(param_2 + 0x18) == 6) {
    uVar3 = FUN_0068bed0("button_toggle_weapon",uVar2);
    local_14[0x1b] = uVar3;
  }
  else if (*(int *)(param_2 + 0x18) == 7) {
    uVar3 = FUN_0068bed0("button_toggle_weapon",uVar2);
    local_14[0x1b] = uVar3;
    *(undefined1 *)(local_14 + 0x17) = 1;
  }
  local_1c = 1;
  local_14[0x27] = 0;
  local_14[0x28] = 0;
  local_18 = 0;
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    local_20 = param_2 + 0x2c;
  }
  else {
    local_20 = param_2 + 0x48;
  }
  cVar1 = FUN_0041f890(uVar2,local_20);
  if (cVar1 == '\0') {
    FID_conflict_operator_(param_2 + 0x2c);
    uVar3 = FUN_0041f870();
    uVar3 = FUN_0061ffb0(uVar3);
    local_14[0x26] = uVar3;
    if (local_14[0x26] == 0) {
      uVar3 = FUN_0041f870(&local_1c);
      uVar3 = FUN_00621950(uVar3);
      local_14[0x27] = uVar3;
    }
    if ((*(uint *)(param_2 + 0x44) & 0x80) == 0) {
      if ((*(uint *)(param_2 + 0x44) & 0x100) == 0) {
        uVar3 = FUN_0041f870();
        local_18 = FUN_004184d0(uVar3);
      }
      else {
        uVar3 = FUN_0041f870();
        local_18 = FUN_004184d0(uVar3);
      }
    }
    if ((local_14[0x26] == 0) && (local_14[0x27] == 0)) {
      uVar3 = FUN_0041f870();
      local_14[0x28] = uVar3;
    }
  }
  else {
    FID_conflict_operator_(param_2 + 0x48);
    uVar3 = FUN_0041f870();
    uVar3 = FUN_0061ffb0(uVar3);
    local_14[0x26] = uVar3;
    if (local_14[0x26] == 0) {
      uVar3 = FUN_0041f870(&local_1c);
      uVar3 = FUN_00621950(uVar3);
      local_14[0x27] = uVar3;
    }
    if ((*(uint *)(param_2 + 0x60) & 0x80) == 0) {
      uVar3 = FUN_0041f870();
      local_18 = FUN_004184d0(uVar3);
    }
    if ((local_14[0x26] == 0) && (local_14[0x27] == 0)) {
      uVar3 = FUN_0041f870();
      local_14[0x28] = uVar3;
    }
  }
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    uVar3 = FUN_0041f870();
    uVar3 = FUN_0081cb40("buttonsystem",uVar3);
    local_14[0x18] = uVar3;
  }
  else {
    local_14[0x18] = 0;
  }
  local_14[0x29] = local_18;
  *(bool *)(local_14 + 0xf) = local_1c == 0;
  ExceptionList = local_10;
  return local_14;
}

