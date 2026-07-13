
undefined4 FUN_00836cfc(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  code *pcVar5;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  uVar1 = FUN_008376b6(param_1,&local_8);
  iVar4 = local_8 + 1;
  iVar2 = FUN_0082d490(param_1,iVar4);
  if (iVar2 < 1) {
    FUN_0082d226(param_1,iVar4);
    pcVar5 = (code *)0x0;
    local_10 = 0;
    local_c = 0;
  }
  else {
    uVar3 = FUN_0082ba59(param_1,local_8 + 2,0);
    FUN_0082bbb2(param_1,local_8 + 1,6);
    local_c = FUN_0082c1fd(param_1,local_8 + 3,0);
    pcVar5 = FUN_008376eb;
    local_10 = FUN_00837783(uVar3,local_c);
  }
  FUN_00837655(param_1);
  FUN_0082cced(param_1,uVar1);
  FUN_0082cdd2(param_1,local_8 + 1);
  FUN_0082ced4(param_1,0xfffffffd);
  FUN_0082d226(param_1,0xfffffffe);
  FUN_0082e1d1(uVar1,pcVar5,local_10,local_c);
  return 0;
}

