
char __thiscall FUN_00473210(int param_1,undefined4 param_2,undefined4 *param_3)

{
  char cVar1;
  int iVar2;
  
  if (((param_3 == (undefined4 *)0x0) || (*(int *)(param_1 + 0x1a0) == 0)) ||
     (iVar2 = FUN_00417fb0(), iVar2 == 0)) {
    cVar1 = '\0';
  }
  else {
    FUN_0062a270(*(undefined4 *)(param_1 + 0xf4),4,param_1 + 0x314);
    *(undefined4 *)(param_1 + 0x37c) = *param_3;
    *(undefined4 *)(param_1 + 0x380) = param_3[1];
    *(undefined4 *)(param_1 + 900) = param_3[2];
    cVar1 = FUN_005aecb0(param_2);
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0x304) = 0x3eb33333;
    }
  }
  return cVar1;
}

