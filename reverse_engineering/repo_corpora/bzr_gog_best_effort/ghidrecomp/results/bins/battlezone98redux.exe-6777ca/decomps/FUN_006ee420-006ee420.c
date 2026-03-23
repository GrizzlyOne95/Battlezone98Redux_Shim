
int FUN_006ee420(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 extraout_ECX;
  undefined4 uVar2;
  int local_10;
  int local_8;
  
  local_10 = FUN_00433f60(param_1);
  uVar2 = extraout_ECX;
  FUN_006f21a0(&stack0x0000000c);
  local_8 = FUN_006fbad0(param_1,param_2,uVar2);
  if ((local_8 != local_10) && (cVar1 = FUN_006fbb10(param_2,&local_8), cVar1 == '\0')) {
    local_10 = local_8;
  }
  return local_10;
}

