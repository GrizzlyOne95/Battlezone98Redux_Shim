
void FUN_0083b0da(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_1c [12];
  undefined1 local_10 [9];
  char local_7;
  
  uVar1 = *(undefined4 *)(param_1 + 0x30);
  uVar2 = FUN_0083c86e(uVar1);
  FUN_0083a00d(uVar1,local_1c,1);
  FUN_0083a00d(uVar1,local_10,0);
  FUN_00838ffd(param_1);
  FUN_00839bcd(param_1);
  FUN_00839b38(param_1,0x114,0x110,param_2);
  uVar3 = FUN_00839df0(param_1);
  if (local_7 == '\0') {
    FUN_0083a945(uVar1);
    FUN_0083caac(*(undefined4 *)(param_1 + 0x30),uVar3,uVar2);
  }
  else {
    FUN_00839a51(param_1);
    FUN_0083cadc(*(undefined4 *)(param_1 + 0x30),uVar3);
    FUN_0083a945(uVar1);
    uVar2 = FUN_0083c9bd(uVar1,uVar2);
    FUN_0083caac(*(undefined4 *)(param_1 + 0x30),uVar2);
  }
  FUN_0083a945(uVar1);
  return;
}

