
undefined1 __thiscall FUN_004db510(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  if (param_2 != 0) {
    uVar2 = (**(code **)(*(int *)(param_2 + 0x18) + 4))(param_1);
    cVar1 = FUN_004db560(uVar2);
    if (cVar1 != '\0') {
      return 1;
    }
  }
  return 0;
}

