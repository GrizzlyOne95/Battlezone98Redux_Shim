
undefined4 FUN_006a4380(int *param_1,undefined2 *param_2)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  
  param_1[7] = 3;
  cVar2 = (**(code **)(*(int *)param_1[2] + 0x68))();
  if (cVar2 == '\0') {
    FUN_00690020(*param_1,param_1,0);
    FUN_006905d0(*param_1,*param_2);
    param_1[7] = 1;
    uVar3 = 0;
  }
  else {
    puVar4 = (undefined4 *)FUN_004200d0(*(uint *)(param_2 + 0x12) >> 10 & 0xff);
    iVar1 = *(int *)*puVar4;
    FUN_00462590();
    iVar5 = FUN_005e10b0();
    if (iVar5 < *(int *)(iVar1 + 0x48)) {
      FUN_00690020(*param_1,param_1,0);
      FUN_006905d0(*param_1,*param_2);
      param_1[7] = 1;
      uVar3 = 0;
    }
    else {
      FUN_006a6090("\nBuild_ConstructBuild %s",param_2 + 0x20);
      FUN_005aecb0(iVar1);
      FUN_006a90a0(*param_1,-*(int *)(param_2 + 0x10));
      FUN_0068ffb0(*param_1,param_1,*(undefined4 *)(param_2 + 0x10));
      FUN_006a6090("\nteam credits: %d",*(undefined4 *)(&DAT_02ce9aa4 + *param_1 * 0x1e0));
      uVar3 = 1;
    }
  }
  return uVar3;
}

