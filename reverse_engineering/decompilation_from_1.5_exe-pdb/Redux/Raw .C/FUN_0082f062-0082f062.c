
void FUN_0082f062(int param_1,undefined4 param_2,undefined4 param_3)

{
  code *pcVar1;
  int iVar2;
  
  *(short *)(param_1 + 0x34) = *(short *)(param_1 + 0x34) + 1;
  if (199 < *(ushort *)(param_1 + 0x34)) {
    if (*(ushort *)(param_1 + 0x34) == 200) {
      FUN_0082df5b(param_1,"C stack overflow");
    }
    else if (0xe0 < *(ushort *)(param_1 + 0x34)) {
      FUN_0082f657(param_1,5);
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  iVar2 = FUN_0082f2d3(param_1,param_2,param_3);
  if (iVar2 == 0) {
    FUN_00832183(param_1,1);
  }
  *(short *)(param_1 + 0x34) = *(short *)(param_1 + 0x34) + -1;
  if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
    FUN_00830222(param_1);
  }
  return;
}

