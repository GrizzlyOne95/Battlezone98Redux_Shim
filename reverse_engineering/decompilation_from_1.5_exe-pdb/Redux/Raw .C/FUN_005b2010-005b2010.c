
void __thiscall FUN_005b2010(int param_1,float param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  float *pfVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined1 local_130 [64];
  undefined4 local_f0;
  int local_ec;
  int *local_e8;
  undefined4 local_e4;
  int local_e0;
  undefined4 local_dc [16];
  undefined1 local_9c [16];
  undefined4 local_8c;
  undefined1 local_70 [28];
  undefined4 local_54 [6];
  float local_3c;
  float local_38;
  float local_34;
  double local_2c;
  double local_24;
  double local_1c;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(float *)(param_1 + 0xc0) = *(float *)(param_1 + 0xc0) + param_2;
  local_e0 = param_1;
  if (((*(int *)(param_1 + 0xe4) == 0) || (*(char *)(param_1 + 0xe0) != '\0')) ||
     (cVar1 = FUN_00611840(), cVar1 == '\0')) {
    if (0.0 < *(float *)(local_e0 + 0xc0)) {
      *(undefined4 *)(local_e0 + 0xc0) = 0;
    }
  }
  else if (0.0 < *(float *)(local_e0 + 0xc0)) {
    local_ec = *(int *)(local_e0 + 0xc);
    iVar2 = FUN_00417c80();
    if (*(int *)(*(int *)(local_e0 + 8) + 0x34) <= iVar2) {
      if (*(char *)(*(int *)(local_e0 + 8) + 0x58) != '\0') {
        FUN_0043a990(local_9c);
        local_8c = 0x1000;
        FUN_0043a9e0(local_70);
        FUN_0043aa30(*(int *)(local_e0 + 8) + 0x58,*(undefined4 *)(local_e0 + 0x10),local_9c,
                     local_70);
      }
      (**(code **)(**(int **)(local_e0 + 0xd8) + 0x18))(-*(int *)(local_ec + 0x5c));
      iVar2 = FUN_00572a70();
      if ((iVar2 == 0) || (cVar1 = FUN_004b9860(), cVar1 != '\0')) {
        puVar3 = (undefined4 *)
                 FUN_0081fe60(local_130,*(int *)(local_e0 + 0x10) + 0x20,local_e0 + 0x28);
        puVar6 = local_dc;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar6 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar6 = puVar6 + 1;
        }
        puVar3 = local_dc;
        puVar6 = local_54;
        for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar6 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar6 = puVar6 + 1;
        }
        local_2c = (double)local_3c + local_2c;
        local_24 = (double)local_3c + local_24;
        local_1c = (double)local_3c + local_1c;
        uVar9 = 0;
        uVar8 = 0xffffffff;
        uVar7 = 0;
        uVar4 = (**(code **)(*(int *)(*(int *)(local_e0 + 0xd8) + 0x18) + 4))(0,0xffffffff,0);
        local_e4 = FUN_004e1190(local_54,uVar4,uVar7,uVar8,uVar9);
        pfVar5 = (float *)FUN_004624b0();
        local_14 = local_3c * 20.0 + *pfVar5;
        local_10 = local_38 * 20.0 + pfVar5[1];
        local_c = local_34 * 20.0 + pfVar5[2];
        FUN_0046fb20(&local_14);
        local_e8 = (int *)FUN_0045ca50();
        (**(code **)(*local_e8 + 0x1c))(local_e4);
        local_f0 = FUN_004da060(*(undefined4 *)(local_e0 + 0xe4));
        FUN_0049f450(local_f0);
        FUN_0046fc40(*(undefined4 *)(local_e0 + 0xd8));
        FUN_0049f450(local_e4);
        iVar2 = FUN_00572a70();
        if (iVar2 != 0) {
          FUN_004b8460();
        }
      }
    }
    *(undefined4 *)(local_e0 + 0xe4) = 0;
    *(undefined4 *)(local_e0 + 0xc4) = 0;
    *(undefined4 *)(local_e0 + 0xd0) = 0;
    *(float *)(local_e0 + 0xc0) =
         *(float *)(local_e0 + 0xc0) - *(float *)(*(int *)(local_e0 + 8) + 0x84);
  }
  *(undefined1 *)(local_e0 + 0xe0) = 0;
  FUN_0083e885();
  return;
}

