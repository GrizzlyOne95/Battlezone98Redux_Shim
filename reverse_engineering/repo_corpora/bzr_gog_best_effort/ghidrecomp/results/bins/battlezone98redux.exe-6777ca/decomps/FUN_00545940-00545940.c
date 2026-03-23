
void __thiscall FUN_00545940(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  
  cVar1 = FUN_005c8410(param_2,"avapc");
  if (cVar1 != '\0') {
    iVar2 = FUN_005c8800(param_2);
    if (iVar2 == 1) {
      *(undefined1 *)(param_1 + 0x5f) = 1;
      *(undefined4 *)(param_1 + 0xcc) = param_2;
    }
  }
  return;
}

