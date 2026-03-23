
void __thiscall FUN_0050afd0(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_004178a0(param_2);
  if (*(int *)(param_1 + 0x58) != 0) {
    FUN_0082c82c(*(undefined4 *)(param_1 + 0x58),0xffffd8ee,"AddPlayer");
    iVar1 = FUN_0082d490(*(undefined4 *)(param_1 + 0x58),0xffffffff);
    if (iVar1 == 6) {
      FUN_0082ccca(*(undefined4 *)(param_1 + 0x58),*(undefined2 *)(param_2 + 0x28));
      uVar2 = FUN_0041f870();
      FUN_0082cd77(*(undefined4 *)(param_1 + 0x58),uVar2);
      FUN_0082ccca(*(undefined4 *)(param_1 + 0x58),*(undefined1 *)(param_2 + 0x68));
      uVar2 = FUN_0082cb8c(*(undefined4 *)(param_1 + 0x58),3,0,0,*(undefined4 *)(param_1 + 0x58),
                           "Lua script AddPlayer error:\n%s");
      FUN_004ff600(uVar2);
    }
    else {
      FUN_0082d226(*(undefined4 *)(param_1 + 0x58),0xfffffffe);
    }
  }
  return;
}

