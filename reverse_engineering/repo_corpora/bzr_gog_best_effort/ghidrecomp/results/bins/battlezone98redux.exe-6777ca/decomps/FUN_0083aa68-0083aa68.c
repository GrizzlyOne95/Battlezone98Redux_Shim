
void FUN_0083aa68(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 local_20 [6];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar3 = 0;
  iVar4 = 0;
  do {
    uVar1 = FUN_0083b57b(param_1,iVar4);
    FUN_0083abae(param_1,uVar1);
    iVar4 = iVar4 + 1;
    iVar2 = FUN_0083b6c3(param_1,0x2c);
  } while (iVar2 != 0);
  iVar2 = FUN_0083b6c3(param_1,0x3d);
  if (iVar2 == 0) {
    local_20[0] = 0;
  }
  else {
    uVar3 = FUN_0083a118(param_1,local_20);
  }
  FUN_0083975c(param_1,iVar4,uVar3,local_20);
  FUN_008397cc(param_1,iVar4);
  FUN_0083e885();
  return;
}

