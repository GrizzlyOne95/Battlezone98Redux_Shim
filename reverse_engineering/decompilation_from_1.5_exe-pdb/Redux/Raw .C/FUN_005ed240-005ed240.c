
void __fastcall FUN_005ed240(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  int *local_18;
  int local_14;
  undefined1 local_9;
  undefined1 local_8;
  undefined1 local_7;
  undefined1 local_6;
  
  FUN_0046fa60(0,1,1);
  FUN_0046fa60(1,2,1);
  FUN_0046fa60(2,10,1);
  FUN_0046fa60(3,4,*(int *)(param_1 + 0x300) != 0);
  iVar2 = FUN_005e0f70(0);
  if ((((*(char *)(param_1 + 0x188) == '\0') && (*(int *)(param_1 + 0xec) != 0)) && (iVar2 != 0)) &&
     (iVar2 = (*(code *)**(undefined4 **)(iVar2 + 0x18))(), *(int *)(iVar2 + 0x1c) == 4)) {
    local_6 = 1;
  }
  else {
    local_6 = 0;
  }
  FUN_0046fa60(4,7,local_6);
  local_14 = FUN_005e0f70(3);
  if ((local_14 != 0) && (cVar1 = FUN_00472700(), cVar1 == '\0')) {
    local_14 = 0;
  }
  fVar4 = (float10)FUN_0046fbd0();
  if ((*(float *)(param_1 + 0x208) <= (float)fVar4) ||
     ((local_14 == 0 && (iVar2 = FUN_005e0fd0(0x3c,0x40), iVar2 < 0)))) {
    local_7 = 0;
  }
  else {
    local_7 = 1;
  }
  FUN_0046fa60(5,5,local_7);
  iVar2 = FUN_00417c80();
  iVar3 = FUN_0046d060();
  if ((iVar2 < iVar3) && ((local_14 != 0 || (iVar2 = FUN_005e0fd0(0x41,0x45), -1 < iVar2)))) {
    local_8 = 1;
  }
  else {
    local_8 = 0;
  }
  FUN_0046fa60(6,6,local_8);
  FUN_004aefa0(7);
  FUN_0046fa60(8,0,0);
  FUN_0046fa60(9,0,0);
  local_18 = (int *)FUN_005e0f70(1);
  if ((local_18 != (int *)0x0) && (cVar1 = (**(code **)(*local_18 + 0x68))(), cVar1 == '\0')) {
    local_18 = (int *)0x0;
  }
  if ((*(char *)(param_1 + 0x188) == '\0') &&
     ((local_18 != (int *)0x0 || (iVar2 = FUN_005e0fd0(0x46,0x4a), -1 < iVar2)))) {
    local_9 = 1;
  }
  else {
    local_9 = 0;
  }
  FUN_0046fa60(10,8,local_9);
  return;
}

