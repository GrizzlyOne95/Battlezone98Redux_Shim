
undefined4 __thiscall
FUN_0057b140(int *param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_14 [4];
  int local_10;
  int *local_c;
  undefined1 local_6;
  undefined1 local_5;
  
  local_10 = param_3 - *param_1;
  local_c = param_1;
  puVar1 = (undefined1 *)_Iter_cat<>(&local_6,&param_4);
  local_5 = *puVar1;
  FUN_0057bca0(param_3,param_4,param_5,local_5);
  uVar2 = param_2;
  iVar3 = local_10;
  FID_conflict_begin(local_14);
  FID_conflict_operator_(uVar2,iVar3);
  return param_2;
}

