
void FUN_005ec660(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined1 local_1d0 [64];
  undefined1 local_190 [24];
  undefined1 local_178 [12];
  undefined1 local_16c [12];
  undefined1 local_160 [12];
  undefined1 local_154 [12];
  undefined1 local_148 [12];
  float local_13c;
  int local_138;
  undefined4 local_134 [16];
  undefined4 local_f4 [10];
  undefined8 local_cc;
  undefined8 local_bc;
  undefined4 local_b4 [10];
  undefined8 local_8c;
  double local_84;
  undefined8 local_7c;
  undefined1 local_74 [12];
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
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (*(int *)(param_1 + 0x300) != 0) {
    uVar1 = (**(code **)(*(int *)(*(int *)(param_1 + 0x300) + 0x18) + 0x30))();
    iVar2 = FUN_0062e000(uVar1);
    if (iVar2 == 0) {
      puVar3 = (undefined4 *)FUN_0045c4d0();
      puVar4 = local_f4;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar3 = (undefined4 *)FUN_004560b0(local_148,local_f4);
      local_68 = *puVar3;
      local_64 = puVar3[1];
      local_60 = puVar3[2];
      local_38 = local_68;
      local_34 = local_64;
      local_30 = local_60;
      puVar3 = (undefined4 *)FUN_00447f60(local_190,local_f4);
      local_5c = *puVar3;
      local_58 = puVar3[1];
      local_54 = puVar3[2];
      local_50 = puVar3[3];
      local_4c = puVar3[4];
      local_48 = puVar3[5];
      uVar1 = (**(code **)(*(int *)(param_1 + 0x18) + 0x2c))
                        (local_5c,local_58,local_54,local_50,local_4c,local_48,&local_13c,local_74,0
                        );
      FUN_00444f70(uVar1);
      puVar3 = (undefined4 *)FUN_0081f920(local_1d0,local_74,&local_68);
      puVar4 = local_134;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar3 = local_134;
      puVar4 = local_b4;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      local_8c = local_cc;
      local_84 = (double)local_13c;
      local_7c = local_bc;
      FUN_0056d6a0(local_b4);
      local_138 = FUN_0045c490();
      puVar3 = (undefined4 *)FUN_00440000(local_178,0,0,0);
      local_44 = *puVar3;
      local_40 = puVar3[1];
      local_3c = puVar3[2];
      *(undefined4 *)(local_138 + 0x18) = local_44;
      *(undefined4 *)(local_138 + 0x1c) = local_40;
      *(undefined4 *)(local_138 + 0x20) = local_3c;
      *(undefined4 *)(local_138 + 8) = 0;
      *(undefined4 *)(local_138 + 0xc) = 0x7149f2ca;
      puVar3 = (undefined4 *)FUN_00440000(local_154,0,0,0);
      local_2c = *puVar3;
      local_28 = puVar3[1];
      local_24 = puVar3[2];
      *(undefined4 *)(local_138 + 0x24) = local_2c;
      *(undefined4 *)(local_138 + 0x28) = local_28;
      *(undefined4 *)(local_138 + 0x2c) = local_24;
      puVar3 = (undefined4 *)FUN_00440000(local_160,0,0,0);
      local_20 = *puVar3;
      local_1c = puVar3[1];
      local_18 = puVar3[2];
      *(undefined4 *)(local_138 + 0x30) = local_20;
      *(undefined4 *)(local_138 + 0x34) = local_1c;
      *(undefined4 *)(local_138 + 0x38) = local_18;
      puVar3 = (undefined4 *)FUN_00440000(local_16c,0,0,0);
      local_14 = *puVar3;
      local_10 = puVar3[1];
      local_c = puVar3[2];
      *(undefined4 *)(local_138 + 0x3c) = local_14;
      *(undefined4 *)(local_138 + 0x40) = local_10;
      *(undefined4 *)(local_138 + 0x44) = local_c;
    }
  }
  FUN_005ed4b0(0);
  FUN_0083e885();
  return;
}

