
uint FUN_0082f6a3(int param_1,int param_2)

{
  short sVar1;
  uint uVar2;
  char *pcVar3;
  
  if ((*(char *)(param_1 + 6) == '\x01') ||
     ((*(char *)(param_1 + 6) == '\0' && (*(int *)(param_1 + 0x14) == *(int *)(param_1 + 0x28))))) {
    if (*(ushort *)(param_1 + 0x34) < 200) {
      sVar1 = *(ushort *)(param_1 + 0x34) + 1;
      *(short *)(param_1 + 0x34) = sVar1;
      *(short *)(param_1 + 0x36) = sVar1;
      uVar2 = FUN_0082f4cb(param_1,FUN_0082f7e4,*(int *)(param_1 + 8) + param_2 * -0x10);
      if (uVar2 == 0) {
        uVar2 = (uint)*(byte *)(param_1 + 6);
      }
      else {
        *(char *)(param_1 + 6) = (char)uVar2;
        FUN_0082f5f3(param_1,uVar2,*(undefined4 *)(param_1 + 8));
        *(undefined4 *)(*(int *)(param_1 + 0x14) + 8) = *(undefined4 *)(param_1 + 8);
      }
      *(short *)(param_1 + 0x34) = *(short *)(param_1 + 0x34) + -1;
      return uVar2;
    }
    pcVar3 = "C stack overflow";
  }
  else {
    pcVar3 = "cannot resume non-suspended coroutine";
  }
  uVar2 = FUN_0082f852(param_1,pcVar3);
  return uVar2;
}

