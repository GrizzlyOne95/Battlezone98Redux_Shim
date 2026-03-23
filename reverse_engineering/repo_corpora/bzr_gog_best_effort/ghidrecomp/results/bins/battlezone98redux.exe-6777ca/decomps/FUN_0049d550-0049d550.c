
void __fastcall FUN_0049d550(int param_1)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 local_28;
  int local_1c;
  int *local_18;
  int local_10;
  undefined1 local_5;
  
  if (*(int *)(param_1 + 0x228) == 0) {
    FUN_0046fa60(0,1,1);
    FUN_0046fa60(1,2,1);
    FUN_0046fa60(2,10,1);
    iVar7 = *(int *)(param_1 + 0xf8) + 0x608;
    for (local_10 = 0; local_10 < 7; local_10 = local_10 + 1) {
      if (*(int *)(iVar7 + local_10 * 4) == 0) {
        FUN_0046fa60(local_10 + 3,0,0);
      }
      else {
        iVar3 = FUN_004e1b90(*(undefined4 *)(param_1 + 0x174),*(undefined4 *)(iVar7 + local_10 * 4))
        ;
        iVar4 = FUN_004e1c10(*(undefined4 *)(param_1 + 0x174),*(undefined4 *)(iVar7 + local_10 * 4))
        ;
        iVar6 = *(int *)(*(int *)(iVar7 + local_10 * 4) + 0x13c);
        iVar1 = *(int *)(*(int *)(iVar7 + local_10 * 4) + 0x140);
        cVar2 = FUN_004723d0();
        if ((((cVar2 == '\0') && (iVar5 = FUN_005e10b0(), iVar3 <= iVar5)) &&
            (iVar3 = FUN_005e1220(), iVar4 <= iVar3)) &&
           (((iVar6 == -1 || (iVar1 == -1)) || (iVar6 = FUN_005e0f90(iVar6,iVar1), iVar6 != -1)))) {
          local_28 = 1;
        }
        else {
          local_28 = 0;
        }
        FUN_0046fa60(local_10 + 3,*(undefined4 *)(iVar7 + local_10 * 4),local_28);
      }
    }
    local_18 = (int *)FUN_005e0f70(1);
    if ((local_18 != (int *)0x0) && (cVar2 = (**(code **)(*local_18 + 0x68))(), cVar2 == '\0')) {
      local_18 = (int *)0x0;
    }
    if ((local_18 == (int *)0x0) && (iVar7 = FUN_005e0fd0(0x46,0x4a), iVar7 < 0)) {
      local_5 = 0;
    }
    else {
      local_5 = 1;
    }
    FUN_0046fa60(10,8,local_5);
  }
  else {
    FUN_0046fa60(0,0,0);
    FUN_0046fa60(1,0,0);
    FUN_0046fa60(2,0,0);
    iVar7 = *(int *)(param_1 + 0xf8);
    for (local_1c = 3; local_1c < 10; local_1c = local_1c + 1) {
      FUN_0046fa60(local_1c,*(undefined4 *)(iVar7 + 0x5fc + local_1c * 4),0);
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

