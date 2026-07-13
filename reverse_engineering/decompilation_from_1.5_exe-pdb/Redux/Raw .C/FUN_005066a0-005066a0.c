
undefined4 FUN_005066a0(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  float10 fVar3;
  undefined8 uVar4;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  float local_10;
  int local_c;
  undefined1 local_5;
  
  local_c = FUN_005062f0(param_1,1);
  if (local_c == 0) {
    uVar1 = 0;
  }
  else {
    local_18 = FUN_0082c225(param_1,2,0,0);
    local_14 = FUN_0082ba59(param_1,3,0);
    fVar3 = (float10)FUN_0082c276(param_1,4,0);
    local_10 = (float)fVar3;
    uVar4 = CONCAT44(local_10,&local_1c);
    uVar1 = FUN_00446460(local_14,0x811c9dc5,&local_1c,local_10);
    uVar2 = FUN_00446460(local_18,0x811c9dc5,uVar1);
    local_5 = FUN_00589800(uVar2,uVar1,uVar4);
    FUN_0082cd58(param_1,(double)local_1c);
    FUN_0082cbf5(param_1,local_5);
    uVar1 = 2;
  }
  return uVar1;
}

