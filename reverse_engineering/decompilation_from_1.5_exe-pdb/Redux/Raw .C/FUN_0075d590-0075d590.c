
void __thiscall FUN_0075d590(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined1 local_78 [4];
  undefined1 local_74 [4];
  undefined1 local_70 [4];
  undefined1 local_6c [4];
  undefined1 local_68 [4];
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  undefined1 local_44 [4];
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853818;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = param_1;
  local_14 = uVar2;
  cVar1 = FUN_0073ba10(param_1 + 0x48);
  if (cVar1 == '\0') {
    local_5c = FUN_0073a9f0(local_2c);
    local_8 = 0;
    local_54 = local_5c;
    uVar3 = FUN_0041f870(uVar2);
    FUN_007d6a70("BZRNet P2P Removing Player %s From P2P Handler\n",uVar3);
    local_8 = 0xffffffff;
    ~basic_string<>();
    FUN_0042d8c0(&local_40);
    FID_conflict_begin(local_4c);
    while (cVar1 = FUN_00420f10(local_4c), cVar1 != '\0') {
      uVar3 = param_3;
      FUN_0042de50(param_3);
      cVar1 = FUN_0056f780(uVar3);
      if (cVar1 != '\0') {
        local_58 = local_40;
        FUN_0042d920(local_6c,local_40);
        break;
      }
      FUN_0042da80();
    }
    FUN_00420260(&local_34);
    FID_conflict_begin(local_44);
    while (cVar1 = FUN_00420f10(local_44), cVar1 != '\0') {
      uVar3 = param_3;
      FUN_00422150(param_3);
      cVar1 = FUN_0056f780(uVar3);
      if (cVar1 != '\0') {
        local_60 = local_34;
        FUN_00429560(local_78,local_34);
        break;
      }
      FUN_00428570();
    }
    FUN_00420260(&local_3c);
    FID_conflict_begin(local_68);
    while (cVar1 = FUN_00420f10(local_68), cVar1 != '\0') {
      uVar3 = param_3;
      FUN_00422150(param_3);
      cVar1 = FUN_0056f780(uVar3);
      if (cVar1 != '\0') {
        local_64 = local_3c;
        FUN_00429560(local_74,local_3c);
        break;
      }
      FUN_00428570();
    }
    FUN_0042d8c0(&local_38);
    FID_conflict_begin(local_48);
    while (cVar1 = FUN_00420f10(local_48), cVar1 != '\0') {
      uVar3 = param_3;
      FUN_0042da60(param_3);
      cVar1 = FUN_0056f780(uVar3);
      if (cVar1 != '\0') {
        local_50 = local_38;
        FUN_0075fb70(local_70,local_38);
        break;
      }
      FUN_0042da80();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

