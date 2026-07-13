
void __fastcall FUN_00472780(int param_1)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 local_30;
  int local_20;
  int *local_1c;
  int local_18;
  int local_14;
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
    local_1c = (int *)FUN_005e0f70(1);
    if ((local_1c != (int *)0x0) && (cVar2 = (**(code **)(*local_1c + 0x68))(), cVar2 == '\0')) {
      local_1c = (int *)0x0;
    }
    if ((*(char *)(param_1 + 0x188) == '\0') &&
       ((local_1c != (int *)0x0 || (iVar3 = FUN_005e0fd0(0x46,0x4a), -1 < iVar3)))) {
      local_5 = 1;
    }
    else {
      local_5 = 0;
    }
    FUN_0046fa60(10,8,local_5);
  }
  else {
    FUN_0046fa60(0,0,0);
    switch(*(undefined4 *)(param_1 + 0x378)) {
    case 0:
      local_18 = *(int *)(param_1 + 0xf8) + 0x608;
      local_20 = 5;
      FUN_0046fa60(6,0x12,*(int *)(param_1 + 0x228) == 2);
      FUN_0046fa60(7,0x13,*(int *)(param_1 + 0x228) == 2);
      FUN_0046fa60(8,0x14,*(int *)(param_1 + 0x228) == 2);
      FUN_0046fa60(9,0x15,*(int *)(param_1 + 0x228) == 2);
      break;
    case 1:
      local_18 = *(int *)(param_1 + 0xf8) + 0x660;
      local_20 = 9;
      break;
    case 2:
      local_18 = *(int *)(param_1 + 0xf8) + 0x684;
      local_20 = 9;
      break;
    case 3:
      local_18 = *(int *)(param_1 + 0xf8) + 0x6a8;
      local_20 = 9;
      break;
    case 4:
      local_18 = *(int *)(param_1 + 0xf8) + 0x6cc;
      local_20 = 9;
    }
    for (local_14 = 0; local_14 < local_20; local_14 = local_14 + 1) {
      if (*(int *)(local_18 + local_14 * 4) == 0) {
        FUN_0046fa60(local_14 + 1,0,0);
      }
      else {
        iVar4 = FUN_004e1b90(*(undefined4 *)(param_1 + 0x174),
                             *(undefined4 *)(local_18 + local_14 * 4));
        iVar5 = FUN_004e1c10(*(undefined4 *)(param_1 + 0x174),
                             *(undefined4 *)(local_18 + local_14 * 4));
        iVar3 = *(int *)(*(int *)(local_18 + local_14 * 4) + 0x13c);
        iVar1 = *(int *)(*(int *)(local_18 + local_14 * 4) + 0x140);
        if (((((*(int *)(param_1 + 0x228) == 2) && (cVar2 = FUN_004723d0(), cVar2 == '\0')) &&
             (iVar6 = FUN_005e10b0(), iVar4 <= iVar6)) && (iVar4 = FUN_005e1220(), iVar5 <= iVar4))
           && (((iVar3 == -1 || (iVar1 == -1)) || (iVar3 = FUN_005e0f90(iVar3,iVar1), iVar3 != -1)))
           ) {
          local_30 = 1;
        }
        else {
          local_30 = 0;
        }
        FUN_0046fa60(local_14 + 1,*(undefined4 *)(local_18 + local_14 * 4),local_30);
      }
    }
    cVar2 = FUN_004723d0();
    if (cVar2 == '\0') {
      FUN_0046fa60(10,3,*(int *)(param_1 + 0x228) == 2);
    }
    else {
      FUN_0046fa60(10,0x17,1);
    }
  }
  return;
}

