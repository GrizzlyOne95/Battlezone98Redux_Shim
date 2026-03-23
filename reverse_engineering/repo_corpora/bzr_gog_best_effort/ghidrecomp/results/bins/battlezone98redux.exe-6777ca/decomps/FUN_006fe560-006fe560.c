
void FUN_006fe560(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 local_14 [8];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  puVar1 = (undefined4 *)FUN_006fc690(local_8,param_1);
  uVar2 = *puVar1;
  puVar1 = (undefined4 *)FUN_006fc670(local_c,param_1,uVar2);
  puVar1 = (undefined4 *)FUN_006fc6b0(local_14,*puVar1,uVar2);
  FUN_0070da80(param_1,param_2,param_3,param_4,param_5,param_6,*puVar1,puVar1[1]);
  return;
}

