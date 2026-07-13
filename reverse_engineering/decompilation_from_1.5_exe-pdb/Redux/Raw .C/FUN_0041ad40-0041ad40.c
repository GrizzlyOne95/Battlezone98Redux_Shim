
void FUN_0041ad40(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  bool bVar5;
  undefined1 local_68 [4];
  undefined4 local_64;
  undefined4 *local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined1 local_50 [4];
  uint local_4c;
  undefined4 *local_48;
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844c46;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_0041ab20(param_3);
  local_8 = 0;
  *local_48 = TouchInputMasterButton::vftable;
  vector<>(uVar2);
  local_8 = CONCAT31(local_8._1_3_,1);
  local_60 = local_48;
  FUN_0041fe40(&local_60);
  *(undefined1 *)(local_48 + 0x26) = 0;
  FID_conflict_operator_(param_2);
  local_48[0x27] = param_4;
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    uVar3 = FUN_0041f870();
    uVar3 = FUN_0081cb40("buttonSystem",uVar3);
    local_48[0x18] = uVar3;
  }
  else {
    local_48[0x18] = 0;
  }
  local_48[0x28] = local_48[0x18];
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    uVar3 = FUN_0041f870();
    uVar3 = FUN_0081cb40("buttonSystem",uVar3);
    local_48[0x29] = uVar3;
  }
  else {
    local_48[0x29] = local_48[0x18];
  }
  local_64 = basic_string<>("MASTER:");
  local_8._0_1_ = 2;
  local_54 = local_64;
  local_5c = FUN_00426a20(local_44,local_64,param_2);
  local_8._0_1_ = 3;
  local_58 = local_5c;
  FUN_00421e00(local_50,local_5c);
  local_8._0_1_ = 2;
  ~basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,1);
  ~basic_string<>();
  uVar3 = FID_conflict_begin(local_68);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 != '\0') {
    iVar4 = FUN_00421ea0();
    bVar5 = *(int *)(iVar4 + 0x18) != 0;
    local_4c = (uint)bVar5;
    *(bool *)(local_48 + 0x26) = bVar5;
    if (*(char *)(local_48 + 0x26) != '\0') {
      local_48[0x18] = local_48[0x29];
    }
  }
  *(undefined1 *)(local_48 + 0xf) = 0;
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

