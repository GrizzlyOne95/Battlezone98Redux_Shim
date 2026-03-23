
undefined4 FUN_005065d0(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  undefined1 local_5;
  
  local_c = FUN_005062f0(param_1,1);
  if (local_c == 0) {
    uVar1 = 0;
  }
  else {
    local_18 = FUN_0082c225(param_1,2,0,0);
    local_14 = FUN_0082ba59(param_1,3,0);
    uVar1 = FUN_0082c1fd(param_1,4,0);
    puVar4 = &local_1c;
    local_10 = uVar1;
    uVar2 = FUN_00446460(local_14,0x811c9dc5,puVar4,uVar1);
    uVar3 = FUN_00446460(local_18,0x811c9dc5,uVar2);
    local_5 = FUN_005896c0(uVar3,uVar2,puVar4,uVar1);
    FUN_0082ccca(param_1,local_1c);
    FUN_0082cbf5(param_1,local_5);
    uVar1 = 2;
  }
  return uVar1;
}

