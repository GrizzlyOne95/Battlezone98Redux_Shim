
void __fastcall FUN_007d0ed0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_007cb1a0();
  if (iVar1 != 0) {
    uVar2 = FUN_007cf960();
    FUN_00764760(iVar1,uVar2);
    FUN_00746090(iVar1,uVar2);
    FUN_007cf9f0();
    (**(code **)(param_1 + 0x14))();
  }
  return;
}

