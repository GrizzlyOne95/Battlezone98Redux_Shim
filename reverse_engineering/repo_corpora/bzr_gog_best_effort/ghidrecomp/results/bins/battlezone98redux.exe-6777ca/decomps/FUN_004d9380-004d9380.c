
void FUN_004d9380(undefined4 param_1,int param_2,undefined1 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 local_8;
  
  puVar1 = (undefined4 *)FUN_00417780(param_2 + -4);
  local_8 = *puVar1;
  uVar2 = _Val_type<>(param_1);
  uVar2 = FUN_00417780(&local_8,param_3,uVar2);
  FUN_004d95c0(param_1,param_2 + -4,param_2 + -4,uVar2);
  return;
}

