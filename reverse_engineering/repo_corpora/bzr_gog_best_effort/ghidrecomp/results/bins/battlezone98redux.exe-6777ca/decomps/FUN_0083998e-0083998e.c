
void FUN_0083998e(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int local_244 [143];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_0083abfa(param_1,local_244);
  *(undefined4 *)(local_244[0] + 0x3c) = param_4;
  FUN_00839bb2(param_1,0x28);
  if (param_3 != 0) {
    uVar1 = FUN_00838fac(param_1,&DAT_008708a4,4,0);
    FUN_0083abae(param_1,uVar1);
    FUN_008397cc(param_1,1);
  }
  FUN_0083acb0(param_1);
  FUN_00839bb2(param_1,0x29);
  FUN_00839bcd(param_1);
  *(undefined4 *)(local_244[0] + 0x40) = *(undefined4 *)(param_1 + 4);
  FUN_00839b38(param_1,0x106,0x109,param_4);
  FUN_00839c1c(param_1);
  FUN_0083ae74(param_1,local_244,param_2);
  FUN_0083e885();
  return;
}

