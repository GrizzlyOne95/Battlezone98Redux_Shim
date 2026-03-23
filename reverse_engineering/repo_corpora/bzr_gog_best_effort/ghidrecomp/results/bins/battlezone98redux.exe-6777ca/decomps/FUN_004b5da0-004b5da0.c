
void __thiscall FUN_004b5da0(int param_1,float param_2)

{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined1 local_90 [16];
  undefined4 local_80;
  undefined1 local_64 [4];
  undefined4 local_60;
  undefined4 local_48 [6];
  float local_30;
  double local_20;
  double local_18;
  double local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(float *)(param_1 + 0xc0) = *(float *)(param_1 + 0xc0) + param_2;
  if (*(char *)(param_1 + 200) == '\0') {
    if (0.0 < *(float *)(param_1 + 0xc0)) {
      *(undefined4 *)(param_1 + 0xc0) = 0;
    }
    goto LAB_004b6149;
  }
  if (0.0 < *(float *)(param_1 + 0xc0)) {
    cVar2 = FUN_00611840();
    if (cVar2 != '\0') {
      iVar6 = *(int *)(param_1 + 0xc);
      iVar3 = *(int *)(iVar6 + 0x13c);
      iVar1 = *(int *)(iVar6 + 0x140);
      FUN_00462590();
      if ((iVar3 == -1) || (iVar1 == -1)) {
LAB_004b5e9f:
        iVar3 = FUN_00417c80();
        if (*(int *)(iVar6 + 0x5c) <= iVar3) {
          if (*(char *)(*(int *)(param_1 + 8) + 0x58) != '\0') {
            FUN_0043a990(local_90);
            local_80 = 0x1000;
            FUN_0043a9e0(local_64);
            if ((*(uint *)(*(int *)(param_1 + 0x18) + 0x14) & 0x10) != 0) {
              local_60 = 0x41;
            }
            FUN_0043aa30(*(int *)(param_1 + 8) + 0x58,*(undefined4 *)(param_1 + 0x10),local_90,
                         local_64);
          }
          (**(code **)(**(int **)(param_1 + 0xc4) + 0x18))(-*(int *)(iVar6 + 0x5c));
          puVar7 = (undefined4 *)(param_1 + 0x28);
          puVar8 = local_48;
          for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar8 = *puVar7;
            puVar7 = puVar7 + 1;
            puVar8 = puVar8 + 1;
          }
          if (((*(int *)(iVar6 + 0x1c) != 2) && (*(int *)(iVar6 + 0x1c) != 7)) &&
             (*(int *)(iVar6 + 0x1c) != 5)) {
            local_20 = (double)local_30 + local_20;
            local_18 = (double)local_30 + local_18;
            local_10 = (double)local_30 + local_10;
          }
          iVar3 = FUN_00572a70();
          if (iVar3 != 0) {
            cVar2 = FUN_004b9860();
            if (cVar2 == '\0') goto LAB_004b60e0;
          }
          uVar11 = 0;
          uVar10 = 0xffffffff;
          uVar9 = 0;
          uVar4 = FUN_0047e9a0(*(undefined4 *)(param_1 + 0x18),0,0xffffffff,0);
          uVar4 = FUN_004e1190(local_48,uVar4,uVar9,uVar10,uVar11);
          if (((*(int *)(iVar6 + 0x1c) != 2) && (*(int *)(iVar6 + 0x1c) != 7)) &&
             (*(int *)(iVar6 + 0x1c) != 5)) {
            uVar9 = FUN_004624b0();
            FUN_0046fb20(uVar9);
          }
          piVar5 = (int *)FUN_0045ca50();
          (**(code **)(*piVar5 + 0x1c))(uVar4);
          uVar4 = FUN_00462610();
          FUN_0049f450(uVar4);
          FUN_0046fc40(*(undefined4 *)(param_1 + 0xc4));
          iVar6 = FUN_00572a70();
          if (iVar6 != 0) {
            FUN_004b8460();
          }
        }
      }
      else {
        iVar3 = FUN_005e0f90(iVar3,iVar1);
        if (-1 < iVar3) goto LAB_004b5e9f;
      }
LAB_004b60e0:
      *(float *)(param_1 + 0xc0) =
           *(float *)(param_1 + 0xc0) - *(float *)(*(int *)(param_1 + 8) + 0x80);
    }
  }
  *(undefined1 *)(param_1 + 200) = 0;
LAB_004b6149:
  FUN_0083e885();
  return;
}

