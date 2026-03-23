
undefined1 __thiscall FUN_005c6430(undefined4 param_1,int param_2)

{
  char cVar1;
  int iVar2;
  
  if (((param_2 != 0) &&
      (iVar2 = (*(code *)**(undefined4 **)(param_2 + 0x18))(param_1),
      *(int *)(iVar2 + 0x14) == 0x53434156)) && (cVar1 = FUN_004db510(param_2), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}

