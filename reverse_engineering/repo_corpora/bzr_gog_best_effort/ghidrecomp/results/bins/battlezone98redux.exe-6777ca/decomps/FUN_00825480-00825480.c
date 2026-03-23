
bool FUN_00825480(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 *local_10;
  undefined4 *local_8;
  
  local_10 = param_2;
  local_8 = (undefined4 *)(param_1 + 8);
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  FUN_00824c50(param_1 + 0xc,&local_28,6,*local_8);
  iVar1 = FUN_00825080(&local_28,*local_10,3,2,*local_8,0);
  return iVar1 != 0;
}

