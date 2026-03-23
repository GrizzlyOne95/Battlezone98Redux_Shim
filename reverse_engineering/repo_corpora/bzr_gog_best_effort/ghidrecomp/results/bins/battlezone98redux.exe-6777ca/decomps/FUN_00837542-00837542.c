
void FUN_00837542(undefined4 param_1)

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
    iVar3 = local_70 + 3;
    FUN_0082b9f2(param_1,iVar3);
    FUN_0082d226(param_1,iVar3);
    FUN_0082d4cc(param_1,uVar1,1);
    uVar2 = FUN_0082ba1c(param_1,local_70 + 2);
    uVar1 = FUN_0082e1fd(uVar1,local_6c,uVar2);
    FUN_0082cd77(param_1,uVar1);
  }
  FUN_0083e885();
  return;
}

