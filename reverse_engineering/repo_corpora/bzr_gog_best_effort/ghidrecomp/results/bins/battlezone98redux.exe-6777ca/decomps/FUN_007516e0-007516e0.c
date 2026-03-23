
void FUN_007516e0(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_1c [8];
  undefined1 local_14 [12];
  int *local_8;
  
  local_8 = (int *)FUN_007508c0();
  puVar1 = (undefined4 *)FUN_0073a970(local_14);
  uVar3 = puVar1[1];
  uVar2 = *puVar1;
  puVar1 = (undefined4 *)FUN_0073a970(local_1c);
  (**(code **)(*local_8 + 0x90))(*puVar1,puVar1[1],uVar2,uVar3);
  return;
}

