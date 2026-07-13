
undefined4 FUN_006b7860(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [8];
  undefined4 local_8;
  
  iVar1 = FUN_004170c0();
  if (iVar1 == 0) {
    uVar3 = 0;
  }
  else {
    FUN_00423890();
    puVar2 = (undefined4 *)FUN_004fee40(local_10);
    uVar3 = *puVar2;
    puVar2 = (undefined4 *)FID_conflict_begin(local_14);
    puVar2 = (undefined4 *)FUN_006d9bb0(local_18,*puVar2,uVar3,param_2);
    local_8 = *puVar2;
    uVar3 = FID_conflict_begin(local_1c);
    uVar3 = FID_conflict_operator__(uVar3);
  }
  return uVar3;
}

