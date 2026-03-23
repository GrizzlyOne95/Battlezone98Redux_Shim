
void FUN_00750d10(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_14 [12];
  int *local_8;
  
  local_8 = (int *)FUN_007508c0();
  if (local_8 != (int *)0x0) {
    uVar1 = FUN_0041f870();
    uVar1 = FUN_0041f870(uVar1);
    puVar2 = (undefined4 *)FUN_0073a970(local_14);
    (**(code **)(*local_8 + 100))(*puVar2,puVar2[1],uVar1);
  }
  return;
}

