
undefined1
FUN_007f04f0(undefined4 param_1,undefined4 param_2,undefined1 *param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 local_18 [4];
  undefined1 local_14;
  undefined1 local_10 [11];
  undefined1 local_5;
  
  uVar2 = FUN_00417780(param_4);
  puVar4 = local_10;
  get(puVar4,uVar2);
  FUN_007f0a00(puVar4,uVar2);
  puVar4 = local_18;
  get(puVar4);
  uVar2 = FID_conflict_begin(puVar4);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 == '\0') {
    uVar2 = FUN_00417780(&local_5,param_4);
    iVar3 = FUN_00423870(uVar2);
    cVar1 = FUN_007f11c0(param_1,iVar3 + 4);
    if ((cVar1 == '\0') || (cVar1 = operator==<>(param_1,*param_3), cVar1 == '\0')) {
      local_14 = 0;
    }
    else {
      local_14 = 1;
    }
    return local_14;
  }
  return 0;
}

