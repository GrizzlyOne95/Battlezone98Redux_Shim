
bool FUN_008112c0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 local_c [2];
  
  local_c[0] = *param_1;
  cVar1 = FUN_00809970(local_c,param_2,param_3,param_4,&DAT_0260c0e5);
  return cVar1 == '\0';
}

