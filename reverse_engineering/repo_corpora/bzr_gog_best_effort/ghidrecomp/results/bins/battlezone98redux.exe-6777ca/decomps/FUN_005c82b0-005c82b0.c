
undefined4 FUN_005c82b0(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  
  iVar2 = FUN_004ff060(param_1);
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    iVar4 = FUN_004e1190(param_3,param_2,0,0xffffffff,0);
    if (iVar4 == 0) {
      uVar3 = 0;
    }
    else {
      if (*(int *)(iVar2 + 0x1c) == 3) {
        *(uint *)(*(int *)(iVar4 + 0x228) + 0x114) =
             *(uint *)(*(int *)(iVar4 + 0x228) + 0x114) | 0xc;
      }
      if (param_4 != 0) {
        FUN_004d9630(param_4);
      }
      cVar1 = FUN_00571c30();
      if (cVar1 != '\0') {
        FUN_004b8460();
      }
      piVar5 = (int *)FUN_0045ca50();
      (**(code **)(*piVar5 + 0x1c))(iVar4);
      uVar3 = FUN_00477590(iVar4);
    }
  }
  return uVar3;
}

