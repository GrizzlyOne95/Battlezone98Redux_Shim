
undefined4 FUN_005cd440(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 in_stack_00000014;
  
  if (DAT_02a13c7b == '\0') {
    DAT_009182a4 = DAT_009182a4 + 1;
    iVar1 = FUN_00462630(in_stack_00000014);
    iVar2 = FUN_00462630(param_1);
    if ((iVar1 == 0) || (iVar2 == 0)) {
      uVar3 = 1;
    }
    else {
      uVar3 = (**(code **)(*(int *)(iVar1 + 0x18) + 0x30))();
      uVar3 = (**(code **)(*(int *)(iVar2 + 0x18) + 0x30))
                        (&stack0x00000008,&stack0x0000000c,&stack0x00000010,uVar3);
      FUN_00821f00(uVar3);
      uVar3 = 0;
    }
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

