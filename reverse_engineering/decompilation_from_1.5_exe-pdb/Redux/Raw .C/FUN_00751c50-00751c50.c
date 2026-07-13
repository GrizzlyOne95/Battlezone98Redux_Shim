
void FUN_00751c50(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_14 [12];
  int *local_8;
  
  local_8 = (int *)FUN_007508c0();
  iVar1 = FUN_004170c0();
  uVar2 = FUN_0041f870(iVar1 + 1);
  puVar3 = (undefined4 *)FUN_0073a970(local_14);
  (**(code **)(*local_8 + 0x68))(*puVar3,puVar3[1],uVar2);
  return;
}

