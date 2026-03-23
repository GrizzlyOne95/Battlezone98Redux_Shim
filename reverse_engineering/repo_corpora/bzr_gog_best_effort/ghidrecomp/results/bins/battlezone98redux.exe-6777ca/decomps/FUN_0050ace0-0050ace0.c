
void __thiscall FUN_0050ace0(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_004178a0(param_2);
  if (*(int *)(param_1 + 0x58) != 0) {
    FUN_0082c82c(*(undefined4 *)(param_1 + 0x58),0xffffd8ee,"CreateObject");
    iVar1 = FUN_0082d490(*(undefined4 *)(param_1 + 0x58),0xffffffff);
    if (iVar1 == 6) {
      uVar2 = FUN_00462380();
      FUN_004ff770(*(undefined4 *)(param_1 + 0x58),uVar2);
      uVar2 = FUN_0082cb8c(*(undefined4 *)(param_1 + 0x58),1,0,0,*(undefined4 *)(param_1 + 0x58),
                           "Lua script CreateObject error:\n%s");
      FUN_004ff600(uVar2);
    }
    else {
      FUN_0082d226(*(undefined4 *)(param_1 + 0x58),0xfffffffe);
    }
  }
  return;
}

