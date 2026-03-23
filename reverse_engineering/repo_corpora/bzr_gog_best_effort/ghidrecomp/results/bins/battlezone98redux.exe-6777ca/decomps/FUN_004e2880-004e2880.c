
void FUN_004e2880(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_15c [64];
  undefined1 local_11c [24];
  undefined1 local_104 [12];
  undefined1 local_f8 [12];
  undefined1 local_ec [12];
  undefined4 *local_e0;
  float local_dc;
  float local_d8;
  undefined4 *local_d4;
  undefined4 *local_d0;
  undefined4 local_cc [16];
  undefined1 local_8c [12];
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  double local_30;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a2bc;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_0047e9c0(param_1,param_2);
  local_8 = 0;
  *local_d0 = Geizer::vftable;
  local_d0[6] = Geizer::vftable;
  FUN_00423890(uVar1);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00442d30(local_d0[0x3c]);
  *(undefined4 *)(local_d0[0x3c] + 0x14) = 0x41200000;
  *(undefined1 *)(local_d0 + 0x8e) = 0;
  FUN_004e2ce0();
  FUN_004e2e40();
  local_e0 = local_d0;
  FUN_0041fe40(&local_e0);
  local_d4 = (undefined4 *)(local_d0[0x3d] + 0x20);
  puVar2 = (undefined4 *)FUN_00447f60(local_11c,local_d4);
  local_74 = *puVar2;
  local_70 = puVar2[1];
  local_6c = puVar2[2];
  local_68 = puVar2[3];
  local_30 = *(double *)(puVar2 + 2);
  local_64 = puVar2[4];
  local_60 = puVar2[5];
  local_38 = local_74;
  local_34 = local_70;
  local_28 = local_64;
  local_24 = local_60;
  FUN_00444f70(local_d0[0x3c],local_74,local_70,local_6c,local_68,local_64,local_60,&local_d8,
               local_8c,0);
  local_30 = (double)local_d8;
  if ((float)local_d4[4] <= 0.9 && (float)local_d4[4] != 0.9) {
    puVar2 = (undefined4 *)FUN_004795e0(local_f8,local_d4);
    local_44 = *puVar2;
    local_40 = puVar2[1];
    local_3c = puVar2[2];
    local_20 = local_44;
    local_1c = local_40;
    local_18 = local_3c;
    fVar5 = (float10)FUN_004428b0(&local_20,local_8c);
    local_dc = (float)fVar5;
    if (local_dc < 0.9) {
      puVar2 = (undefined4 *)FUN_00440000(local_ec,0,0x3f800000,0);
      local_5c = *puVar2;
      local_58 = puVar2[1];
      local_54 = puVar2[2];
      local_20 = local_5c;
      local_1c = local_58;
      local_18 = local_54;
      puVar2 = (undefined4 *)FUN_004560b0(local_104,local_d4);
      local_80 = *puVar2;
      local_7c = puVar2[1];
      local_78 = puVar2[2];
      local_50 = local_80;
      local_4c = local_7c;
      local_48 = local_78;
      puVar2 = (undefined4 *)FUN_0081f920(local_15c,&local_20,&local_80);
      puVar4 = local_cc;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar2 = local_cc;
      puVar4 = local_d4;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
    }
  }
  FUN_0044b7d0(local_d4,&local_38);
  FUN_004db100();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

