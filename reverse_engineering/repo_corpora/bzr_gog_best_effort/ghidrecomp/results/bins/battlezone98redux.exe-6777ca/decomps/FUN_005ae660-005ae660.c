
void __fastcall FUN_005ae660(int param_1)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 local_2c;
  int local_20;
  int local_1c;
  int *local_18;
  int local_10;
  undefined1 local_5;
  
  if (*(int *)(param_1 + 0x228) == 0) {
    FUN_0046fa60(0,1,1);
    FUN_0046fa60(1,2,1);
    FUN_0046fa60(2,10,1);
    FUN_0046fa60(3,0xb,1);
    FUN_0046fa60(4,0,0);
    FUN_0046fa60(5,0,0);
    FUN_0046fa60(6,0,0);
    FUN_004aefa0(7);
    FUN_0046fa60(8,0,0);
    FUN_0046fa60(9,0,0);
    iVar3 = FUN_005e0f70(1);
    if (iVar3 == param_1) {
      FUN_0046fa60(10,0,0);
    }
    else {
      local_18 = (int *)FUN_005e0f70(1);
      if ((local_18 != (int *)0x0) && (cVar2 = (**(code **)(*local_18 + 0x68))(), cVar2 == '\0')) {
        local_18 = (int *)0x0;
      }
      if ((*(char *)(param_1 + 0x188) == '\0') &&
         ((local_18 != (int *)0x0 || (iVar3 = FUN_005e0fd0(0x46,0x4a), -1 < iVar3)))) {
        local_5 = 1;
      }
      else {
        local_5 = 0;
      }
      FUN_0046fa60(10,8,local_5);
    }
  }
  else if (*(int *)(param_1 + 0x228) == 1) {
    FUN_0046fa60(0,0,0);
    iVar3 = *(int *)(param_1 + 0xf8);
    for (local_1c = 0; local_1c < 9; local_1c = local_1c + 1) {
      FUN_0046fa60(local_1c + 1,*(undefined4 *)(iVar3 + 0x608 + local_1c * 4),0);
    }
    FUN_0046fa60(10,3,0);
  }
  else if (*(int *)(param_1 + 0x228) == 2) {
    FUN_0046fa60(0,0,0);
    iVar3 = *(int *)(param_1 + 0xf8) + 0x608;
    for (local_10 = 0; local_10 < 9; local_10 = local_10 + 1) {
      if (*(int *)(iVar3 + local_10 * 4) == 0) {
        FUN_0046fa60(local_10 + 1,0,0);
      }
      else {
        iVar4 = FUN_004e1b90(*(undefined4 *)(param_1 + 0x174),*(undefined4 *)(iVar3 + local_10 * 4))
        ;
        iVar5 = FUN_004e1c10(*(undefined4 *)(param_1 + 0x174),*(undefined4 *)(iVar3 + local_10 * 4))
        ;
        iVar7 = *(int *)(*(int *)(iVar3 + local_10 * 4) + 0x13c);
        iVar1 = *(int *)(*(int *)(iVar3 + local_10 * 4) + 0x140);
        cVar2 = FUN_004723d0();
        if ((((cVar2 == '\0') && (iVar6 = FUN_005e10b0(), iVar4 <= iVar6)) &&
            (iVar4 = FUN_005e1220(), iVar5 <= iVar4)) &&
           (((iVar7 == -1 || (iVar1 == -1)) || (iVar7 = FUN_005e0f90(iVar7,iVar1), iVar7 != -1)))) {
          local_2c = 1;
        }
        else {
          local_2c = 0;
        }
        FUN_0046fa60(local_10 + 1,*(undefined4 *)(iVar3 + local_10 * 4),local_2c);
      }
    }
    cVar2 = FUN_004723d0();
    if (cVar2 == '\0') {
      FUN_0046fa60(10,3,1);
    }
    else {
      FUN_0046fa60(10,0x17,1);
    }
  }
  else if (*(int *)(param_1 + 0x228) == 3) {
    FUN_0046fa60(0,0,0);
    iVar3 = *(int *)(param_1 + 0xf8);
    for (local_20 = 0; local_20 < 9; local_20 = local_20 + 1) {
      FUN_0046fa60(local_20 + 1,*(undefined4 *)(iVar3 + 0x608 + local_20 * 4),0);
    }
    FUN_0046fa60(10,3,0);
  }
  return;
}

