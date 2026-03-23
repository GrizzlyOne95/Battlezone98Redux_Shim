
bool FUN_00825d10(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined1 local_80 [112];
  undefined4 *local_10;
  undefined4 *local_8;
  
  local_10 = param_2;
  local_8 = (undefined4 *)(param_1 + 8);
  memset(local_80,0,0x70);
  FUN_00824c10(local_8 + 1,local_80,0x1c,*local_8);
  iVar1 = FUN_00824c90(local_80,*local_10,7,4,*local_8,0);
  return iVar1 != 0;
}

