
undefined4 FUN_00751120(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_14 [12];
  int *local_8;
  
  iVar1 = FUN_007508c0();
  if (iVar1 == 0) {
    uVar3 = 0;
  }
  else {
    local_8 = (int *)FUN_007508c0();
    puVar2 = (undefined4 *)FUN_0073a970(local_14);
    uVar3 = (**(code **)(*local_8 + 0x80))(*puVar2,puVar2[1]);
  }
  return uVar3;
}

