
undefined4 FUN_005064d0(undefined4 param_1)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  uint local_10;
  int local_c;
  undefined1 local_6;
  undefined1 local_5;
  
  iVar2 = FUN_005062f0(param_1,1);
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_0082c225(param_1,2,0,0);
    uVar4 = FUN_0082ba59(param_1,3,0,uVar3);
    iVar2 = FUN_0082d490(param_1,4,uVar3,uVar4);
    if (iVar2 < 1) {
      local_c = 0;
    }
    else {
      local_c = FUN_0082d2e8(param_1,4);
    }
    local_5 = local_c != 0;
    local_10 = (uint)(byte)local_5;
    puVar5 = &local_6;
    uVar4 = FUN_00446460(uVar4,0x811c9dc5,puVar5,local_10);
    uVar3 = FUN_00446460(uVar3,0x811c9dc5,uVar4);
    uVar1 = FUN_00589920(uVar3,uVar4,puVar5,local_10);
    FUN_0082cbf5(param_1,local_6);
    FUN_0082cbf5(param_1,uVar1);
    uVar3 = 2;
  }
  return uVar3;
}

