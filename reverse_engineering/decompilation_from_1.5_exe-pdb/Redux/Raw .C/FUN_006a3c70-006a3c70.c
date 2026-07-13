
undefined4 FUN_006a3c70(uint *param_1)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  uVar7 = DAT_00917a74;
  do {
    do {
      uVar3 = size();
      if (uVar3 <= *param_1) {
        return 0;
      }
      uVar3 = *param_1;
      *param_1 = *param_1 + 1;
      piVar4 = (int *)FUN_004200d0(uVar3);
      iVar1 = *piVar4;
      iVar5 = (**(code **)(*(int *)(iVar1 + 0x18) + 0x2c))(uVar3,uVar7);
    } while (iVar5 == 0);
    uVar6 = (*(code *)**(undefined4 **)(iVar1 + 0x18))();
    cVar2 = FUN_006a0810(uVar6);
  } while ((cVar2 == '\0') ||
          ((param_1[2] != 0xffffffff &&
           (uVar3 = (**(code **)(*(int *)(iVar1 + 0x18) + 4))(), param_1[2] != uVar3))));
  uVar7 = FUN_006a1590(iVar1);
  return uVar7;
}

