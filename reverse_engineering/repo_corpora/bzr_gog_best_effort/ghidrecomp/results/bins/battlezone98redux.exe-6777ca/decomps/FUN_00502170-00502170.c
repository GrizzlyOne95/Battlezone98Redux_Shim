
undefined4 FUN_00502170(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  undefined4 uVar5;
  uint local_8;
  
  local_8 = FUN_0082d338(param_1,0xffffd8ed);
  do {
    uVar2 = size();
    if (uVar2 <= local_8) {
      return 0;
    }
    piVar3 = (int *)FUN_0050b870(local_8);
    iVar1 = *piVar3;
    local_8 = local_8 + 1;
    iVar4 = (**(code **)(*(int *)(iVar1 + 0x18) + 0x30))();
  } while ((*(uint *)(iVar4 + 0x14) & 0x200) != 0);
  FUN_0082ccca(param_1,local_8);
  FUN_0082cfd8(param_1,0xffffd8ed);
  uVar5 = FUN_00477590(iVar1);
  FUN_004ff770(param_1,uVar5);
  return 1;
}

