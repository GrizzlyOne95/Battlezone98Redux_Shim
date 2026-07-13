
void __thiscall FUN_0075ca90(int param_1,undefined4 *param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined1 *puVar7;
  undefined1 local_108 [4];
  undefined1 local_104 [4];
  undefined4 local_100;
  undefined1 local_fc [4];
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  int local_ec;
  int local_e8;
  undefined1 local_e4 [4];
  int local_e0;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085cbd3;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_e0 = param_1;
  local_14 = uVar2;
  cVar1 = FUN_0056f780(param_1 + 0x48);
  if (cVar1 == '\0') {
    FUN_0075cea0(local_e0 + 0x48);
    *(undefined4 *)(local_e0 + 0x48) = *param_2;
    *(undefined4 *)(local_e0 + 0x4c) = param_2[1];
    *(undefined4 *)(local_e0 + 0x50) = param_2[2];
    *(undefined4 *)(local_e0 + 0x54) = param_2[3];
    local_f8 = FUN_0075a1a0(uVar2);
    local_8 = 1;
    local_f4 = local_f8;
    FUN_0075fb10(local_f8);
    local_8 = 0xffffffff;
    FUN_0075ce60();
    local_ec = FUN_0045e220();
    *(undefined4 *)(local_ec + 8) = *(undefined4 *)(local_e0 + 0x38);
    *(undefined4 *)(local_ec + 0xc) = *(undefined4 *)(local_e0 + 0x3c);
    *(undefined4 *)(local_ec + 0x10) = *(undefined4 *)(local_e0 + 0x40);
    *(undefined4 *)(local_ec + 0x14) = *(undefined4 *)(local_e0 + 0x44);
    iVar3 = get();
    FUN_006cb4c0(iVar3 + 0xb44);
    iVar3 = get();
    FUN_006cc0c0(iVar3 + 0xb60);
    FUN_0075faa0(&local_ec);
  }
  else {
    FUN_0042d8c0(local_e4);
    FID_conflict_begin(local_fc);
    while (cVar1 = FUN_00420f10(local_fc), cVar1 != '\0') {
      iVar3 = local_e0 + 0x38;
      FUN_0042da60(iVar3);
      cVar1 = FUN_0056f780(iVar3);
      if (cVar1 != '\0') {
        local_e8 = FUN_0042de50();
        iVar3 = get();
        iVar3 = iVar3 + 0xb44;
        FUN_0042da60(iVar3);
        FUN_006cb4c0(iVar3);
        iVar3 = get();
        iVar3 = iVar3 + 0xb60;
        FUN_0042da60(iVar3);
        FUN_006cc0c0(iVar3);
        piVar4 = (int *)FUN_0042da60();
        if (*piVar4 == 0) break;
        piVar4 = (int *)FUN_0042da60();
        if (*piVar4 == 8) {
          cVar1 = operator!=<>(local_e8 + 0x28,local_e8 + 0x44);
          if ((cVar1 == '\0') ||
             (cVar1 = operator!=<>(local_e8 + 0x28,local_e8 + 0x60), cVar1 == '\0')) break;
          uVar5 = FID_conflict_begin(local_104);
          FUN_0075f8b0(local_108,local_e8 + 0x28);
          cVar1 = FUN_004221b0(uVar5);
          if (cVar1 == '\0') break;
        }
        if (DAT_008eda28 != 0) {
          puVar7 = local_2c;
          FUN_0042da60(puVar7);
          local_100 = FUN_0073a9f0(puVar7);
          local_8 = 0;
          local_f0 = local_100;
          uVar5 = FUN_0041f870();
          FUN_007d6a70("BZRNet P2P Resetting Connection Status For Client %s\n",uVar5);
          local_8 = 0xffffffff;
          ~basic_string<>();
        }
        puVar6 = (undefined4 *)FUN_0042da60();
        *puVar6 = 0;
        uVar5 = 0;
        iVar3 = FUN_0042da60(0);
        iVar3 = iVar3 + 8;
        get(iVar3);
        FUN_006c59c0(iVar3,uVar5);
        break;
      }
      FUN_0042da80();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

