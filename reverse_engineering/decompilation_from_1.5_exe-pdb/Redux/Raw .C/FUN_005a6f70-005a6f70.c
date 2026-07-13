
void __thiscall FUN_005a6f70(int param_1,float param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined1 local_258 [64];
  undefined1 local_218 [64];
  undefined1 local_1d8 [64];
  int local_198;
  int local_194;
  undefined4 local_190 [16];
  undefined4 local_150 [16];
  undefined4 local_110 [16];
  undefined4 local_d0 [16];
  undefined4 local_90 [16];
  undefined1 local_50 [16];
  undefined4 local_40;
  undefined1 local_24 [4];
  undefined4 local_20;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(float *)(param_1 + 0xc0) = *(float *)(param_1 + 0xc0) + param_2;
  local_194 = param_1;
  if (*(char *)(param_1 + 200) == '\0') {
    if (0.0 < *(float *)(param_1 + 0xc0)) {
      *(undefined4 *)(param_1 + 0xc0) = 0;
    }
  }
  else {
    if (0.0 < *(float *)(param_1 + 0xc0)) {
      iVar1 = FUN_00417c80();
      if (*(int *)(*(int *)(local_194 + 0xc) + 0x4c) <= iVar1) {
        if (*(char *)(*(int *)(local_194 + 8) + 0x58) != '\0') {
          FUN_0043a990(local_50);
          local_40 = 0x1000;
          FUN_0043a9e0(local_24);
          if ((*(uint *)(*(int *)(local_194 + 0x18) + 0x14) & 0x10) != 0) {
            local_20 = 0x41;
          }
          FUN_0043aa30(*(int *)(local_194 + 8) + 0x58,*(undefined4 *)(local_194 + 0x10),local_50,
                       local_24);
        }
        (**(code **)(**(int **)(local_194 + 0xc4) + 0x18))
                  (-*(int *)(*(int *)(local_194 + 0xc) + 0x4c));
        puVar2 = (undefined4 *)
                 FUN_0081fe60(local_1d8,*(int *)(local_194 + 0x10) + 0x20,local_194 + 0x28);
        puVar3 = local_d0;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar2 = local_d0;
        puVar3 = local_90;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar2 = (undefined4 *)
                 FUN_0081ec40(local_218,*(uint *)(*(int *)(local_194 + 8) + 0x84) ^ 0x80000000);
        puVar3 = local_190;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar2 = local_190;
        puVar3 = local_110;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar2 = (undefined4 *)FUN_0081fe60(local_258,local_110,local_90);
        puVar3 = local_150;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        puVar2 = local_150;
        puVar3 = local_90;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar3 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        }
        local_198 = FUN_00586ff0(local_90,*(undefined4 *)(local_194 + 0x18));
        *(float *)(local_198 + 0x10) = *(float *)(local_194 + 0xc0) - param_2;
      }
      *(float *)(local_194 + 0xc0) =
           *(float *)(local_194 + 0xc0) - *(float *)(*(int *)(local_194 + 8) + 0x80);
    }
    *(undefined1 *)(local_194 + 200) = 0;
  }
  FUN_0083e885();
  return;
}

