
/* WARNING: Removing unreachable block (ram,0x0058dee5) */

void FUN_0058deb0(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  float10 fVar3;
  float fVar4;
  int local_10;
  int local_c;
  
  FUN_0058d3b0();
  if (*(char *)(param_1 + 0x1f) == '\0') {
    local_c = DAT_02a13c94;
  }
  else {
    local_c = DAT_02a13ca0;
  }
  if (param_1 == local_c) {
    FUN_0058d3c0(param_1,local_c);
  }
  else {
    puVar1 = *(undefined4 **)(param_1 + 0x30);
    for (local_10 = FUN_0058c850(param_1); -1 < local_10; local_10 = FUN_0058bf10(local_10)) {
      puVar2 = (undefined4 *)FUN_0058bf30(local_10);
      if (puVar2 != puVar1) {
        fVar3 = (float10)FUN_00447ed0(*(undefined4 *)(param_1 + 0x24),*puVar2,
                                      (float)puVar2[2] - 0.01);
        fVar4 = (float)fVar3;
        fVar3 = (float10)FUN_00447ed0(*(undefined4 *)(param_1 + 0x28),puVar2[1],
                                      (float)puVar2[3] - 0.01,fVar4);
        FUN_0058dc20(fVar4,(float)fVar3,param_1,puVar2);
      }
    }
  }
  return;
}

