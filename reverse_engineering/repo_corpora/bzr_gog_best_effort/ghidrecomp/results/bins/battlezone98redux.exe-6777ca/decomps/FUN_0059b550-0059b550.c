
void __fastcall FUN_0059b550(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  float10 fVar8;
  char *local_90;
  int local_8c;
  uint local_88;
  int local_84;
  uint local_80;
  int local_6c;
  int local_68;
  undefined4 local_60 [10];
  double local_38;
  double local_30;
  double local_28;
  float local_20;
  float local_1c;
  float local_18;
  uint local_14 [4];
  
  local_14[3] = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = param_1[7];
  local_6c = param_1[2];
  if (param_1[0x1b] == 5) {
    local_88 = DAT_0091755c;
  }
  else {
    if (param_1[0x1b] == 0) {
      local_80 = DAT_009175b0;
    }
    else {
      local_80 = DAT_00917588;
    }
    local_88 = local_80;
  }
  if (*(int *)param_1[0x1f] == 0) {
    local_90 = "Build";
  }
  else {
    local_90 = (char *)(param_1[0x1f] + 4);
  }
  if (param_1[0x1b] == 0) {
    local_8c = param_1[0x56] + 5;
  }
  else {
    local_8c = 0;
  }
  FUN_00595080(iVar1,local_6c,local_8c,local_90,local_88,DAT_00917584);
  local_6c = local_6c + param_1[9];
  if (param_1[0x1b] == 5) {
    local_14[0] = DAT_0091755c;
    local_14[1] = DAT_009175b0;
    local_14[2] = DAT_0091757c;
    if (*(int *)(param_1[0x1f] + 0x18) != 0) {
      for (local_68 = 0; local_68 < 10; local_68 = local_68 + 1) {
        if (*(char *)(*(int *)(param_1[0x1f] + 0x18) + local_68 * 0x20 + 4) != '\0') {
          iVar5 = (local_68 + 1) % 10;
          iVar4 = *(int *)(param_1[0x1f] + 0x18);
          iVar2 = FUN_00453d10();
          FUN_00595080(iVar1,local_6c,param_1[0x56] + iVar5,iVar4 + 4 + local_68 * 0x20,
                       local_14[iVar2],DAT_00917584);
          if ((&DAT_00919878)[iVar5] != '\0') {
            if (*(int *)(*(int *)(param_1[0x1f] + 0x18) + 0x18 + local_68 * 0x20) == 0) {
              if (*(int *)(*(int *)(param_1[0x1f] + 0x18) + 0x1c + local_68 * 0x20) != 0) {
                (**(code **)(*param_1 + 0x28))(DAT_009175a0,DAT_009175a4,&local_20,&local_18);
                fVar8 = (float10)FUN_007855e0((double)local_20,(double)local_18);
                local_1c = (float)fVar8;
                puVar6 = &DAT_008fe1e0;
                puVar7 = local_60;
                for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
                  *puVar7 = *puVar6;
                  puVar6 = puVar6 + 1;
                  puVar7 = puVar7 + 1;
                }
                local_38 = (double)local_20;
                local_30 = (double)local_1c;
                local_28 = (double)local_18;
                if (param_1[0x21] < 0) {
                  local_84 = *(int *)(*(int *)(param_1[0x1f] + 0x18) + 0x14 + local_68 * 0x20);
                }
                else {
                  local_84 = param_1[0x21];
                }
                iVar4 = FUN_004e1190(local_60,local_84,0,0xffffffff,0);
                if (iVar4 != 0) {
                  piVar3 = (int *)FUN_0045ca50();
                  (**(code **)(*piVar3 + 0x1c))();
                  iVar4 = FUN_00572a70();
                  if (iVar4 != 0) {
                    FUN_004b8460();
                  }
                  iVar4 = FUN_00462380();
                  param_1[0x31] = iVar4;
                }
              }
            }
            else {
              param_1[0x1f] = local_68 * 0x20 + *(int *)(param_1[0x1f] + 0x18);
            }
          }
          local_6c = local_6c + param_1[10];
        }
      }
      if (*(int *)param_1[0x1f] == 0) {
        FUN_00595080(iVar1,local_6c + param_1[0xb],param_1[0x57],"Cancel",DAT_0091755c,DAT_00917584)
        ;
        if (DAT_0091988b != '\0') {
          param_1[0x1b] = 0;
        }
      }
      else {
        FUN_00595080(iVar1,local_6c + param_1[0xb],param_1[0x57],&DAT_00877f98,DAT_0091755c,
                     DAT_00917584);
        if (DAT_0091988b != '\0') {
          param_1[0x1f] = *(int *)param_1[0x1f];
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

