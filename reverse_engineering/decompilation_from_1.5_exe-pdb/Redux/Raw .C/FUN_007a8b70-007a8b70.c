
void FUN_007a8b70(void)

{
  uint uVar1;
  undefined4 *puVar2;
  uint local_8;
  
  FUN_007cafa0(0xffffffff);
  local_8 = 0;
  while( true ) {
    uVar1 = FUN_007cb5a0();
    if (uVar1 <= local_8) break;
    FUN_007cabf0(&DAT_008a1ad8,local_8,0);
    puVar2 = (undefined4 *)FUN_004200d0(local_8);
    (**(code **)(*(int *)*puVar2 + 0x24))(0);
    puVar2 = (undefined4 *)FUN_004200d0(local_8);
    (**(code **)(*(int *)*puVar2 + 0x24))(0);
    puVar2 = (undefined4 *)FUN_004200d0(local_8);
    (**(code **)(*(int *)*puVar2 + 0x24))(0);
    puVar2 = (undefined4 *)FUN_004200d0(local_8);
    (**(code **)(*(int *)*puVar2 + 0x24))(0);
    local_8 = local_8 + 1;
  }
  return;
}

