
void FUN_0056d010(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 extraout_var;
  undefined1 local_8;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  uVar2 = FID_conflict_get_allocator(&local_7);
  uVar4 = extraout_var;
  uVar3 = FID_conflict_get_allocator(&local_8);
  cVar1 = operator==<>(uVar3,uVar2,uVar4);
  if (cVar1 == '\0') {
    local_6 = 0;
    FUN_0056d160(param_1,0);
  }
  else {
    local_5 = 0;
    uVar2 = 0;
    uVar4 = FUN_00417780(param_1,0);
    FUN_004245e0(uVar4,uVar2);
  }
  return;
}

