
void FUN_0083a7a5(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  iVar2 = param_1;
  param_1 = 0xffffffff;
  uVar1 = *(undefined4 *)(iVar2 + 0x30);
  uVar3 = FUN_0083b690(iVar2);
  while (*(int *)(iVar2 + 0x10) == 0x105) {
    uVar4 = FUN_0083c9bd(uVar1);
    FUN_0083c626(uVar1,&param_1,uVar4);
    FUN_0083cadc(uVar1,uVar3);
    uVar3 = FUN_0083b690(iVar2);
  }
  if (*(int *)(iVar2 + 0x10) == 0x104) {
    uVar4 = FUN_0083c9bd(uVar1);
    FUN_0083c626(uVar1,&param_1,uVar4);
    FUN_0083cadc(uVar1,uVar3);
    FUN_00838ffd(iVar2);
    FUN_00839934(iVar2);
  }
  else {
    FUN_0083c626(uVar1,&param_1,uVar3);
  }
  FUN_0083cadc(uVar1,param_1);
  FUN_00839b38(iVar2,0x106,0x10a,param_2);
  return;
}

