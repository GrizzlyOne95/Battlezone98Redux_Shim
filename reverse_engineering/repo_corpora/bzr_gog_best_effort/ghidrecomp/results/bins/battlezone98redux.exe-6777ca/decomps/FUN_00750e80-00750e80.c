
undefined4 FUN_00750e80(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined1 local_1c [8];
  undefined1 local_14 [12];
  int *local_8;
  
  local_8 = (int *)FUN_007508c0();
  if (local_8 == (int *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar2 = FUN_0041f870();
    puVar3 = (undefined4 *)FUN_0073a970(local_14);
    uVar1 = puVar3[1];
    uVar4 = *puVar3;
    puVar3 = (undefined4 *)FUN_0073a970(local_1c);
    uVar1 = (**(code **)(*local_8 + 0x60))(*puVar3,puVar3[1],uVar4,uVar1,uVar2);
  }
  return uVar1;
}

