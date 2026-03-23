
void __fastcall FUN_007cf870(int param_1)

{
  char cVar1;
  double in_XMM0_Qa;
  undefined8 uVar2;
  
  FUN_00417c60();
  FUN_0056f760(0);
  FUN_0084495f();
  if (0.75 <= in_XMM0_Qa) {
    uVar2 = FUN_0056f760(0);
    *(undefined8 *)(param_1 + 0x958) = uVar2;
    cVar1 = FUN_007d3360();
    if (cVar1 == '\x01') {
      cVar1 = FUN_007d3360();
      (**(code **)(**(int **)(param_1 + 0x954) + 0x24))(cVar1 == '\0');
    }
    else {
      (**(code **)(**(int **)(param_1 + 0x954) + 0x24))(0);
    }
  }
  return;
}

