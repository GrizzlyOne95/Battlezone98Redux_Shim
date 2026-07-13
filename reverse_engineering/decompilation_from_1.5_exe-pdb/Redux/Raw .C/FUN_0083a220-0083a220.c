
void FUN_0083a220(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_10 [12];
  
  uVar1 = *(undefined4 *)(param_1 + 0x30);
  FUN_008397cc(param_1,3);
  FUN_00839bb2(param_1,0x103);
  if (param_5 == 0) {
    iVar2 = FUN_0083c9bd(uVar1);
  }
  else {
    iVar2 = FUN_0083c5ff(uVar1,0x20,param_2,0x1fffe);
  }
  FUN_0083a00d(uVar1,local_10,0);
  FUN_008397cc(param_1,param_4);
  FUN_0083cd31(uVar1,param_4);
  FUN_00839934(param_1);
  FUN_0083a945(uVar1);
  FUN_0083cadc(uVar1,iVar2);
  if (param_5 == 0) {
    uVar3 = FUN_0083c5d2(uVar1,0x21,param_2,0,param_4);
  }
  else {
    uVar3 = FUN_0083c5ff(uVar1,0x1f,param_2,0x1fffe);
  }
  FUN_0083c857(uVar1,param_3);
  if (param_5 == 0) {
    uVar3 = FUN_0083c9bd(uVar1);
  }
  FUN_0083caac(uVar1,uVar3,iVar2 + 1);
  return;
}

