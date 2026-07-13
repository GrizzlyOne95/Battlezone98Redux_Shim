
void __thiscall FUN_0052e260(int param_1,undefined4 param_2)

{
  char cVar1;
  
  if ((*(int *)(param_1 + 0x15c) == 0) && (cVar1 = FUN_005c8410(param_2,"avmu8"), cVar1 != '\0')) {
    *(undefined4 *)(param_1 + 0x15c) = param_2;
    return;
  }
  if ((*(int *)(param_1 + 0x198) == 0) && (cVar1 = FUN_005c8410(param_2,"svapc"), cVar1 != '\0')) {
    *(undefined4 *)(param_1 + 0x198) = param_2;
    return;
  }
  if ((*(int *)(param_1 + 0x19c) == 0) && (cVar1 = FUN_005c8410(param_2,"abtowe"), cVar1 != '\0')) {
    *(undefined4 *)(param_1 + 0x19c) = param_2;
    return;
  }
  if ((*(int *)(param_1 + 0x1a0) == 0) && (cVar1 = FUN_005c8410(param_2,"abtowe"), cVar1 != '\0')) {
    *(undefined4 *)(param_1 + 0x1a0) = param_2;
  }
  return;
}

