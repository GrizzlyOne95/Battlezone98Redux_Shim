
void __fastcall FUN_007a41c0(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_007cb0a0();
  FUN_00764760();
  iVar2 = FUN_0056f900();
  if (iVar2 == 0) {
    FUN_007cafa0(0xffffffff);
  }
  else {
    *(undefined4 *)(param_1 + 0x38) = uVar1;
    FUN_007a3f80();
    FUN_007a4070();
    (**(code **)(param_1 + 0x3c))();
  }
  return;
}

