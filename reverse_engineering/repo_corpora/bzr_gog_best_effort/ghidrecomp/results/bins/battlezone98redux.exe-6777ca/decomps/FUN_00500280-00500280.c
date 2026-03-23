
bool FUN_00500280(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = FUN_004ff750(param_1,1);
  iVar2 = FUN_00462630(uVar1);
  if (iVar2 != 0) {
    iVar3 = (*(code *)**(undefined4 **)(iVar2 + 0x18))();
    FUN_0082cd77(param_1,*(undefined4 *)(iVar3 + 0x18));
  }
  return iVar2 != 0;
}

