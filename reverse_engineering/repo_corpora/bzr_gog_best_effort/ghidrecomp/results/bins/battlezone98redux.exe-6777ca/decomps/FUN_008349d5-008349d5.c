
void FUN_008349d5(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_8;
  
  iVar4 = param_3;
  if (param_2 < param_3) {
    do {
      FUN_0082ce9d(param_1,1,param_2);
      FUN_0082ce9d(param_1,1,iVar4);
      iVar1 = FUN_00834c5d(param_1,0xffffffff,0xfffffffe);
      if (iVar1 == 0) {
        FUN_0082d226(param_1,0xfffffffd);
      }
      else {
        FUN_00834c3b(param_1,param_2,iVar4);
      }
      if (iVar4 - param_2 == 1) {
        return;
      }
      iVar2 = (param_2 + iVar4) / 2;
      FUN_0082ce9d(param_1,1,iVar2);
      FUN_0082ce9d(param_1,1,param_2);
      iVar3 = FUN_00834c5d(param_1,0xfffffffe,0xffffffff);
      iVar1 = param_2;
      if (iVar3 == 0) {
        FUN_0082d226(param_1,0xfffffffe);
        FUN_0082ce9d(param_1,1,iVar4);
        iVar3 = FUN_00834c5d(param_1,0xffffffff,0xfffffffe);
        iVar1 = iVar4;
        if (iVar3 != 0) goto LAB_00834a8c;
        FUN_0082d226(param_1,0xfffffffd);
      }
      else {
LAB_00834a8c:
        FUN_00834c3b(param_1,iVar2,iVar1);
      }
      if (iVar4 - param_2 == 2) {
        return;
      }
      FUN_0082ce9d(param_1,1,iVar2);
      FUN_0082cdd2(param_1,0xffffffff);
      FUN_0082ce9d(param_1,1,iVar4 + -1);
      FUN_00834c3b(param_1,iVar2,iVar4 + -1);
      local_8 = iVar4 + -1;
      iVar1 = param_2;
      while( true ) {
        iVar1 = iVar1 + 1;
        FUN_0082ce9d(param_1,1,iVar1);
        iVar2 = FUN_00834c5d(param_1,0xffffffff,0xfffffffe);
        while (iVar2 != 0) {
          if (iVar4 < iVar1) {
            FUN_0082bc39(param_1,"invalid order function for sorting");
          }
          FUN_0082d226(param_1,0xfffffffe);
          iVar1 = iVar1 + 1;
          FUN_0082ce9d(param_1,1,iVar1);
          iVar2 = FUN_00834c5d(param_1,0xffffffff,0xfffffffe);
        }
        local_8 = local_8 + -1;
        FUN_0082ce9d(param_1,1,local_8);
        iVar2 = FUN_00834c5d(param_1,0xfffffffd,0xffffffff);
        while (iVar2 != 0) {
          if (local_8 < param_2) {
            FUN_0082bc39(param_1,"invalid order function for sorting");
          }
          FUN_0082d226(param_1,0xfffffffe);
          local_8 = local_8 + -1;
          FUN_0082ce9d(param_1,1,local_8);
          iVar2 = FUN_00834c5d(param_1,0xfffffffd,0xffffffff);
          iVar4 = param_3;
        }
        if (local_8 < iVar1) break;
        FUN_00834c3b(param_1,iVar1,local_8);
      }
      FUN_0082d226(param_1,0xfffffffc);
      FUN_0082ce9d(param_1,1,iVar4 + -1);
      FUN_0082ce9d(param_1,1,iVar1);
      FUN_00834c3b(param_1,iVar4 + -1,iVar1);
      if (iVar1 - param_2 < iVar4 - iVar1) {
        iVar2 = param_2;
        iVar3 = iVar4;
        iVar4 = iVar1 + -1;
        param_2 = iVar1 + 1;
      }
      else {
        iVar2 = iVar1 + 1;
        iVar3 = iVar1 + -1;
        param_3 = iVar3;
      }
      FUN_008349d5(param_1,iVar2,iVar4);
      iVar4 = iVar3;
    } while (param_2 < iVar3);
  }
  return;
}

