
void FUN_006d2300(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  
  puVar5 = (undefined4 *)FUN_005111d0(param_1);
  uVar1 = *puVar5;
  uVar2 = puVar5[1];
  uVar3 = puVar5[2];
  uVar4 = puVar5[3];
  puVar5 = (undefined4 *)FUN_005111d0(param_2);
  puVar6 = (undefined4 *)FUN_005111d0(param_1);
  *puVar6 = *puVar5;
  puVar6[1] = puVar5[1];
  puVar6[2] = puVar5[2];
  puVar6[3] = puVar5[3];
  puVar5 = (undefined4 *)FUN_005111d0(param_2);
  *puVar5 = uVar1;
  puVar5[1] = uVar2;
  puVar5[2] = uVar3;
  puVar5[3] = uVar4;
  iVar7 = FUN_005111d0(param_1);
  *(undefined4 *)(*(int *)(iVar7 + 8) + 8) = param_1;
  iVar7 = FUN_005111d0(param_2);
  *(undefined4 *)(*(int *)(iVar7 + 8) + 8) = param_2;
  return;
}

