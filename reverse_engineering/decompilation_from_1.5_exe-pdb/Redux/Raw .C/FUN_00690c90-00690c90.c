
void FUN_00690c90(undefined4 param_1)

{
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  FUN_006a5fd0("Dumping resource %d\n",param_1);
  local_8 = 0;
  local_14 = FUN_00690c40(param_1,0,&local_10,&local_c);
  while (local_14 != 0) {
    FUN_006a5fd0("   #%d (%d, %d)\n",local_8,local_10,local_c);
    local_8 = local_8 + 1;
    local_14 = FUN_00690c40(param_1,local_8,&local_10,&local_c);
  }
  return;
}

