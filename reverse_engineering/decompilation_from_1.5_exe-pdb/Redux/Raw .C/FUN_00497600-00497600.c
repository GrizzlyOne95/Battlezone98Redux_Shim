
void FUN_00497600(undefined4 param_1,int param_2,undefined1 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined4 local_8;
  
  puVar1 = (undefined4 *)FUN_00417780(param_2 + -8);
  local_c = *puVar1;
  local_8 = puVar1[1];
  uVar2 = _Val_type<>(param_1);
  uVar2 = FUN_00417780(&local_c,param_3,uVar2);
  FUN_004976a0(param_1,param_2 + -8,param_2 + -8,uVar2);
  return;
}

