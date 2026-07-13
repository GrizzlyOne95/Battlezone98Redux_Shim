
char FUN_00759750(undefined4 param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 extraout_var;
  undefined4 uVar6;
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined1 local_c [7];
  char local_5;
  
  if (param_3 < 0x481) {
    FUN_00424640(local_c);
    uVar6 = extraout_var;
    FID_conflict_begin(local_14);
    local_5 = '\x01';
    while (cVar1 = FUN_00420f10(local_14), cVar1 != '\0') {
      uVar3 = param_2;
      uVar4 = param_3;
      uVar5 = param_4;
      uVar2 = FUN_004237d0(param_2,param_3,param_4,uVar6);
      cVar1 = FUN_007592d0(uVar2,uVar3,uVar4,uVar5);
      if ((cVar1 == '\0') || (local_5 == '\0')) {
        local_10 = 0;
      }
      else {
        local_10 = 1;
      }
      local_5 = (char)local_10;
      FUN_00422190();
    }
  }
  else {
    local_5 = '\0';
  }
  return local_5;
}

