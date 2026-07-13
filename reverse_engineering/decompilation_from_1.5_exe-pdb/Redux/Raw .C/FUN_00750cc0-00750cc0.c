
undefined4 FUN_00750cc0(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 local_1c [8];
  undefined1 local_14 [12];
  int *local_8;
  
  local_8 = (int *)FUN_007508c0();
  puVar1 = (undefined4 *)FUN_0073a970(local_14);
  uVar2 = (**(code **)(*local_8 + 0x8c))(local_1c,*puVar1,puVar1[1]);
  FUN_0073a6e0(uVar2);
  return param_1;
}

