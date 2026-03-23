
void __thiscall FUN_00547d30(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = FUN_005c8800(param_2);
  if (iVar2 == 1) {
    cVar1 = FUN_005c8410(param_2,"avscav");
    if (cVar1 == '\0') {
      cVar1 = FUN_005c8410(param_2,"absilo");
      if (cVar1 != '\0') {
        *(int *)(param_1 + 0x2a0) = *(int *)(param_1 + 0x2a0) + 1;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x59) = 1;
      *(undefined4 *)(param_1 + 0x104) = param_2;
    }
  }
  return;
}

