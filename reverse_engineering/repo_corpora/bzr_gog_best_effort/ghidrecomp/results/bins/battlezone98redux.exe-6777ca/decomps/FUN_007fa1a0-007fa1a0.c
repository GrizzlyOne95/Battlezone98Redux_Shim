
uint FUN_007fa1a0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined1 *param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_c;
  
  uVar2 = FUN_007d70b0(*param_4);
  uVar3 = FUN_007d70b0(*param_4);
  uVar4 = FUN_004324a0(param_1,param_2,param_3);
  FUN_007fa510(uVar4,uVar2,uVar3);
  local_c = FUN_0044dba0();
  while ((cVar1 = FUN_007fa550(), cVar1 == '\0' && (cVar1 = FUN_007fa3f0(local_c), cVar1 == '\0')))
  {
    uVar5 = FUN_007fa5d0(local_38,local_34,local_30,local_2c,local_28,*param_4,0);
    if ((uVar5 & 0xff) == 0) {
      return uVar5 & 0xffffff00;
    }
    local_c = local_c + 1;
  }
  cVar1 = FUN_007fa550();
  if ((cVar1 == '\0') || (uVar5 = FUN_007fa3f0(local_c), (uVar5 & 0xff) != 0)) {
    while ((cVar1 = FUN_007fa550(), cVar1 == '\0' &&
           ((cVar1 = FUN_007fa3f0(local_c), cVar1 == '\0' &&
            (cVar1 = FUN_007fa5d0(local_38,local_34,local_30,local_2c,local_28,*param_4,0),
            cVar1 != '\0'))))) {
      local_c = local_c + 1;
    }
    uVar5 = FUN_007eba50(param_1);
  }
  else {
    uVar5 = uVar5 & 0xffffff00;
  }
  return uVar5;
}

