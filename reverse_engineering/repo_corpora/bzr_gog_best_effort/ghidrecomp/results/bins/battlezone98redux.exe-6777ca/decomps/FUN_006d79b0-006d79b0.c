
undefined4 FUN_006d79b0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_54 [8];
  undefined1 local_4c [8];
  undefined1 local_44 [8];
  undefined1 local_3c [8];
  undefined1 local_34 [8];
  undefined1 local_2c [8];
  undefined1 local_24 [8];
  undefined1 local_1c [8];
  undefined1 local_14 [8];
  undefined1 local_c [8];
  
  FUN_006d7d50();
  cVar1 = operator!=<>(param_2,local_c);
  if (cVar1 == '\0') {
    cVar1 = FUN_006df220(param_3,local_c);
    if (cVar1 == '\0') {
      uVar2 = FUN_006d7d70(local_34);
      cVar1 = FUN_006df180(param_2,uVar2);
      if (cVar1 == '\0') {
        uVar2 = FUN_006df140(local_3c,local_c,param_2);
        uVar2 = FUN_006d7da0(local_44,param_3,uVar2);
        uVar2 = FUN_006df140(local_4c,uVar2);
        cVar1 = FUN_006df1b0(uVar2);
        if (cVar1 == '\0') {
          uVar2 = param_1;
          FUN_006df140(local_54,param_3,param_2,param_1);
          FUN_006d7dd0(uVar2);
        }
        else {
          FUN_006d7e10(param_1);
        }
      }
      else {
        FUN_006d7e10(param_1);
      }
    }
    else {
      FUN_006df140(param_1,param_2,param_3);
    }
  }
  else {
    cVar1 = operator!=<>(param_3,local_c);
    if (cVar1 == '\0') {
      uVar2 = FUN_006d7d70(local_14);
      cVar1 = FUN_006df180(param_3,uVar2);
      if (cVar1 == '\0') {
        uVar2 = FUN_006df140(local_1c,local_c,param_3);
        uVar2 = FUN_006d7da0(local_24,param_2,uVar2);
        uVar2 = FUN_006df140(local_2c,uVar2);
        cVar1 = FUN_006df1b0(uVar2);
        if (cVar1 == '\0') {
          FUN_006df140(param_1,param_2,param_3);
        }
        else {
          FUN_006d7e40(param_1);
        }
      }
      else {
        FUN_006d7e40(param_1);
      }
    }
    else {
      FUN_006df140(param_1,param_2,param_3);
    }
  }
  return param_1;
}

