
void FUN_00751280(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined1 local_14 [12];
  int *local_8;
  
  iVar1 = FUN_007508e0();
  if (iVar1 != 0) {
    local_8 = (int *)FUN_007508e0();
    puVar2 = (undefined4 *)FUN_0073a970(local_14);
    (**(code **)(*local_8 + 0x10))(*puVar2,puVar2[1]);
  }
  return;
}

