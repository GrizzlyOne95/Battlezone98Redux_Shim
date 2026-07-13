
undefined4
FUN_0070f510(undefined4 param_1,undefined4 param_2,int param_3,int param_4,undefined4 param_5)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_10 [4];
  undefined1 local_c [8];
  
  puVar1 = (undefined4 *)FUN_00447eb0(param_5);
  uVar3 = *puVar1;
  param_4 = param_3 + param_4;
  puVar1 = (undefined4 *)FUN_004fee40(local_c);
  uVar2 = *puVar1;
  puVar1 = (undefined4 *)FID_conflict_begin(local_10);
  FUN_0071a580(param_1,*puVar1,uVar2,param_3,param_4,uVar3);
  return param_1;
}

