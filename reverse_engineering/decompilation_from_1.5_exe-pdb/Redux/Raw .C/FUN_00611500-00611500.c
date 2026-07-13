
void __fastcall FUN_00611500(undefined4 *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined4 *local_c;
  undefined4 local_8;
  
  *param_1 = Weapon::vftable;
  local_c = param_1;
  FUN_00430590();
  puVar2 = (undefined4 *)FUN_0042d8c0(local_14);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_begin(local_1c);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') {
      return;
    }
    piVar4 = (int *)FUN_0042de50();
    if (local_c == (undefined4 *)*piVar4) break;
    FUN_00438c10(local_18,0);
  }
  local_10 = local_8;
  FUN_0042d920(local_20,local_8);
  return;
}

