
void FUN_00837492(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int local_70;
  undefined1 local_6c [100];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = FUN_008376b6(param_1,&local_70);
  iVar4 = local_70 + 1;
  uVar2 = FUN_0082ba1c(param_1,iVar4,local_6c);
  iVar3 = FUN_0082e171(uVar1,uVar2);
  if (iVar3 == 0) {
    FUN_0082b8e4(param_1,iVar4,"level out of range");
  }
  else {
    uVar2 = FUN_0082ba1c(param_1,local_70 + 2);
    iVar3 = FUN_0082e12e(uVar1,local_6c,uVar2);
    if (iVar3 == 0) {
      FUN_0082cd45(param_1);
    }
    else {
      FUN_0082d4cc(uVar1,param_1,1);
      FUN_0082cd77(param_1,iVar3);
      FUN_0082cdd2(param_1,0xfffffffe);
    }
  }
  FUN_0083e885();
  return;
}

