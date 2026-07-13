
undefined4 FUN_006b7250(undefined4 param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined1 local_c [4];
  undefined4 local_8;
  
  local_8 = 0;
  puVar2 = (undefined4 *)FUN_004fee40(local_14);
  uVar3 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_18);
  FUN_006d9a90(&local_10,*puVar2,uVar3);
  uVar3 = FUN_004fee40(local_1c);
  cVar1 = FID_conflict_operator__(uVar3);
  if (cVar1 == '\0') {
    puVar2 = (undefined4 *)FUN_006c8940(local_20);
    uVar3 = *puVar2;
    puVar2 = (undefined4 *)FUN_006c8910(local_24);
    FUN_006d9b00(local_c,*puVar2,uVar3);
    uVar3 = FUN_006c8940(local_28);
    cVar1 = operator==<>(local_c,uVar3);
    if (cVar1 == '\0') {
      puVar2 = (undefined4 *)base(local_2c);
      FUN_006c8830(local_10,*puVar2);
    }
    else {
      basic_string<>();
    }
  }
  else {
    basic_string<>();
  }
  return param_1;
}

