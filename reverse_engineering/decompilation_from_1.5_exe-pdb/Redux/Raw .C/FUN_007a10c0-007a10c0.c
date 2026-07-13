
void FUN_007a10c0(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 local_c;
  
  FUN_007cafa0(0xffffffff);
  FUN_007cb5c0();
  FUN_0041ff50();
  FUN_007cafa0(0xffffffff);
  FUN_007cb5c0();
  FUN_0041ff50();
  FUN_007cafa0(0xffffffff);
  FUN_007cb5c0();
  FUN_007cafa0(0xffffffff);
  FUN_007cb5c0();
  local_c = 0;
  while( true ) {
    uVar1 = size();
    if (uVar1 <= local_c) break;
    puVar2 = (undefined4 *)FUN_004200d0(local_c);
    (**(code **)(*(int *)*puVar2 + 0x24))(0);
    puVar2 = (undefined4 *)FUN_004200d0(local_c);
    (**(code **)(*(int *)*puVar2 + 0x24))(0);
    local_c = local_c + 1;
  }
  return;
}

