
undefined4 FUN_006a3b60(uint *param_1)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  int *piVar4;
  undefined4 uVar5;
  
  uVar5 = DAT_00917a74;
  do {
    uVar3 = size();
    if (uVar3 <= *param_1) {
      return 0;
    }
    uVar3 = *param_1;
    *param_1 = *param_1 + 1;
    piVar4 = (int *)FUN_004200d0(uVar3);
    iVar1 = *piVar4;
    cVar2 = FUN_006a3ad0(iVar1,uVar3,uVar5);
  } while ((cVar2 == '\0') ||
          ((param_1[2] != 0xffffffff &&
           (uVar3 = (**(code **)(*(int *)(iVar1 + 0x18) + 4))(), param_1[2] != uVar3))));
  uVar5 = FUN_006a0e20(iVar1);
  return uVar5;
}

