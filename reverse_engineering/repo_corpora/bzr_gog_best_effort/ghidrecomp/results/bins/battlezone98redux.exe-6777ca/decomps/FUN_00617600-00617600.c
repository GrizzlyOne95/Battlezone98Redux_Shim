
void __thiscall FUN_00617600(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_00684ca0(0,param_1);
  if (iVar1 != 0) {
    FUN_00681610(param_3);
    uVar2 = FUN_00685560();
    uVar2 = uVar2 & 0xff;
    FUN_00685580(100,uVar2);
    if (DAT_008eaab0 != 0) {
      FUN_004b6f10();
    }
    FUN_00685580(0x32);
    FUN_004d46b0(0x32);
    FUN_00685580(100);
    FUN_004d46b0(0xff);
    FUN_00617e70();
    FUN_008216c0();
    FUN_00823d30();
    FUN_00627b80();
    FUN_00685580(uVar2 & 0xff);
  }
  return;
}

