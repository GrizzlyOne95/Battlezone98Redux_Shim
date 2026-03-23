
undefined4 FUN_00502360(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  undefined4 uVar6;
  float10 fVar7;
  float10 fVar8;
  uint local_8;
  
  fVar7 = (float10)FUN_0082d3e1(param_1,0xffffd8ed);
  uVar2 = FUN_004ff7c0(param_1,0xffffd8ec);
  local_8 = FUN_0082d338(param_1,0xffffd8eb);
  do {
    do {
      uVar3 = size();
      if (uVar3 <= local_8) {
        return 0;
      }
      piVar4 = (int *)FUN_0050b870(local_8);
      iVar1 = *piVar4;
      local_8 = local_8 + 1;
      iVar5 = (**(code **)(*(int *)(iVar1 + 0x18) + 0x30))();
    } while ((*(uint *)(iVar5 + 0x14) & 0x200) != 0);
    uVar6 = (**(code **)(*(int *)(iVar1 + 0x18) + 0xc))();
    fVar8 = (float10)FUN_00462010(uVar2,uVar6);
  } while ((float)fVar7 * (float)fVar7 < (float)fVar8);
  FUN_0082ccca(param_1,local_8);
  FUN_0082cfd8(param_1,0xffffd8eb);
  uVar2 = FUN_00477590(iVar1);
  FUN_004ff770(param_1,uVar2);
  return 1;
}

