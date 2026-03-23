
void FUN_004f18f0(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  undefined4 *puVar7;
  undefined4 extraout_var;
  undefined4 uVar8;
  
  cVar2 = FUN_0041fc90();
  uVar8 = extraout_var;
  if (cVar2 == '\0') {
    uVar4 = rand();
    uVar5 = size();
    piVar6 = (int *)FUN_004200d0(uVar4 % uVar5);
    if (*piVar6 != 0) {
      puVar7 = (undefined4 *)(**(code **)(*(int *)(*piVar6 + 0x18) + 0xc))();
      uVar1 = puVar7[2];
      *param_1 = *puVar7;
      *param_2 = uVar1;
    }
  }
  else {
    iVar3 = size();
    if (iVar3 != 0) {
      uVar4 = rand();
      uVar5 = size();
      piVar6 = (int *)FUN_004200d0(uVar4 % uVar5);
      if (*piVar6 != 0) {
        puVar7 = (undefined4 *)(**(code **)(*(int *)(*piVar6 + 0x18) + 0xc))();
        uVar1 = puVar7[2];
        *param_1 = *puVar7;
        *param_2 = uVar1;
      }
    }
  }
  FUN_0083e885(uVar8);
  return;
}

