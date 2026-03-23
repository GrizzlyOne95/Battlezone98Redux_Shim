
void __thiscall FUN_005a0c90(int *param_1,int param_2)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  float10 fVar9;
  int local_6c;
  int local_68;
  float local_5c;
  int local_54;
  int local_50;
  undefined4 local_48 [10];
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (((*(uint *)(param_1[0x37] + 0x14) & 0x1000200) == 0) &&
     ((*(uint *)(DAT_0094672c + 0x30) & 1) == 0)) {
    FUN_004dc130(param_2);
    fVar9 = (float10)FUN_0047e990(param_2);
    local_5c = (float)fVar9;
    if ((*(ushort *)(param_2 + 8) & 0xf) == 8) {
      local_5c = local_5c * 10.0;
    }
    if (param_1 + -6 == DAT_00917afc) {
      FUN_0049b430(local_5c * 0.03,0x40a00000,0xff,0,0);
    }
    iVar1 = param_1[0x38];
    cVar2 = FUN_004b9830();
    if (cVar2 == '\0') {
      FUN_004dc030(-local_5c);
      fVar9 = (float10)FUN_0046fbd0();
      if ((float)fVar9 < 0.0) {
        *(uint *)(param_1[0x37] + 0x14) = *(uint *)(param_1[0x37] + 0x14) | 0x1000000;
        puVar7 = (undefined4 *)(param_1[0x37] + 0x20);
        puVar8 = local_48;
        for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
          *puVar8 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar8 = puVar8 + 1;
        }
        local_20 = (double)(float)param_1[0x3c];
        local_18 = (double)(float)param_1[0x3d];
        local_10 = (double)(float)param_1[0x3e];
        local_54 = 0;
        if (*(int *)(param_1[0x38] + 0x144) == 0) {
          if (DAT_00917a4c != 0) {
            local_54 = FUN_004cb7b0(local_48,0);
          }
        }
        else {
          local_54 = FUN_004cb7b0(local_48,0);
        }
        if ((*(ushort *)(param_2 + 8) & 8) == 0) {
          if (param_1[0x39] != 0) {
            if (local_54 == 0) {
              local_68 = param_1[0x37];
            }
            else {
              local_68 = *(int *)(local_54 + 0xc);
            }
            uVar4 = 0;
            uVar3 = rand();
            FUN_00437720(iVar1 + 0x444 + (uVar3 % 5) * 0x10,local_68,uVar4);
          }
        }
        else {
          if (local_54 == 0) {
            local_6c = param_1[0x37];
          }
          else {
            local_6c = *(int *)(local_54 + 0xc);
          }
          FUN_00437720(iVar1 + 0x494,local_6c,0);
        }
        iVar6 = FUN_00572a70();
        if ((((iVar6 != 0) && (iVar6 = (**(code **)(*param_1 + 4))(), iVar6 != 0)) &&
            (0 < *(int *)(iVar1 + 0x50))) && ((*(uint *)(param_1[0x37] + 0x14) & 4) == 0)) {
          *(uint *)(param_1[0x37] + 0x14) = *(uint *)(param_1[0x37] + 0x14) | 4;
          FUN_004b9ba0(*(ushort *)(param_2 + 8) >> 6 & 0xf);
          uVar4 = (**(code **)(*param_1 + 4))
                            (*(ushort *)(param_2 + 8) >> 6 & 0xf,0x50,param_1 + -6 == DAT_00917afc);
          FUN_00626470(uVar4);
        }
        goto LAB_005a115f;
      }
    }
    fVar9 = (float10)FUN_0046fbd0();
    if (((0.0 < (float)fVar9) && (param_1[0x39] != 0)) &&
       (fVar9 = (float10)FUN_00822da0(),
       (float)param_1[0xa7] <= (float)fVar9 && (float)fVar9 != (float)param_1[0xa7])) {
      if ((*(ushort *)(param_2 + 8) & 4) == 0) {
        if (local_5c <= 0.0) {
          FUN_004376c0(iVar1 + 0x4b4,param_1[0x37],0);
        }
        else {
          fVar9 = (float10)FUN_0046fbd0();
          local_50 = (int)((local_5c * 6.0) / (float)fVar9);
          iVar6 = rand();
          uVar3 = iVar6 >> 8 & 3;
          if (uVar3 == 1) {
            local_50 = local_50 + 1;
          }
          else if (uVar3 == 2) {
            local_50 = local_50 + -1;
          }
          iVar6 = FUN_00453d10(local_50,0,5);
          FUN_004376c0(iVar1 + 0x3c4 + iVar6 * 0x10,param_1[0x37],0);
        }
      }
      else {
        uVar4 = 0;
        iVar6 = param_1[0x37];
        iVar5 = rand();
        FUN_004376c0(iVar1 + 0x424 + (iVar5 >> 8 & 1U) * 0x10,iVar6,uVar4);
      }
      fVar9 = (float10)FUN_00822da0();
      param_1[0xa7] = (int)((float)fVar9 + 0.5);
    }
  }
LAB_005a115f:
  FUN_0083e885();
  return;
}

