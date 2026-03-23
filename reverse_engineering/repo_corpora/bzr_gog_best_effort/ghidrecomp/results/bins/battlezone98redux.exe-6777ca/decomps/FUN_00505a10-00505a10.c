
uint FUN_00505a10(int *param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int local_8;
  
  local_8 = 0;
  FUN_0082cd45(param_3);
  while (iVar2 = FUN_0082cb08(param_3,param_4), iVar2 != 0) {
    local_8 = local_8 + 1;
    FUN_0082d226(param_3,0xfffffffe);
  }
  iVar2 = *param_1;
  if (local_8 < 0x1f) {
    *(char *)(*param_1 + -1) = *(char *)(*param_1 + -1) + (char)local_8;
  }
  else {
    if (param_2 <= *param_1 + 1U) {
      return (uint)param_1 & 0xffffff00;
    }
    *(char *)(*param_1 + -1) = *(char *)(*param_1 + -1) + '\x1f';
    *(char *)*param_1 = (char)local_8;
    *param_1 = *param_1 + 1;
  }
  FUN_0082cd45(param_3);
  while( true ) {
    iVar3 = FUN_0082cb08(param_3,param_4);
    if (iVar3 == 0) {
      return 1;
    }
    cVar1 = FUN_00505ea0(param_1,param_2,param_3,0xfffffffe);
    if ((cVar1 == '\0') || (cVar1 = FUN_00505ea0(param_1,param_2,param_3,0xffffffff), cVar1 == '\0')
       ) break;
    FUN_0082d226(param_3,0xfffffffe);
  }
  uVar4 = FUN_0082d226(param_3,0xfffffffd);
  *param_1 = iVar2;
  return uVar4 & 0xffffff00;
}

