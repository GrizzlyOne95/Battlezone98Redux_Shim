
void FUN_004d7000(int param_1,int param_2,undefined1 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_c = param_2 - param_1 >> 2;
  local_8 = local_c / 2;
  while (0 < local_8) {
    local_8 = local_8 + -1;
    puVar1 = (undefined4 *)FUN_00417780(param_1 + local_8 * 4);
    local_10 = *puVar1;
    uVar2 = FUN_00417780(&local_10,param_3);
    FUN_004d8190(param_1,local_8,local_c,uVar2);
  }
  return;
}

