
void __thiscall FUN_005e7f50(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = FUN_005c8800(param_2);
  if (iVar2 == 1) {
    cVar1 = FUN_005c8410(param_2,"avscav");
    if (cVar1 != '\0') {
      *(undefined1 *)(param_1 + 0x54) = 1;
      *(undefined4 *)(param_1 + 0x78) = param_2;
    }
  }
  return;
}

