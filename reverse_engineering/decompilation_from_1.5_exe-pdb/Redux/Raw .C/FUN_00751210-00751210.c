
undefined4 FUN_00751210(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_1c [8];
  undefined1 local_14 [12];
  int *local_8;
  
  iVar1 = FUN_007508c0();
  if (iVar1 == 0) {
    FUN_0073a6b0();
  }
  else {
    local_8 = (int *)FUN_007508c0();
    puVar2 = (undefined4 *)FUN_0073a970(local_14);
    uVar3 = (**(code **)(*local_8 + 0x48))(local_1c,*puVar2,puVar2[1],param_3);
    FUN_0073a6e0(uVar3);
  }
  return param_1;
}

