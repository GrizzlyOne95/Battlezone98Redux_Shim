
int FUN_0041d170(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  int local_c;
  int local_8;
  
  local_c = 0;
  cVar1 = FUN_004202c0();
  if (cVar1 != '\0') {
    FUN_0041c580();
  }
  FUN_00420350(local_10,param_1);
  uVar2 = FID_conflict_begin(local_14);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 != '\0') {
    iVar3 = FUN_00422150(param_2);
    local_c = FUN_0041d100(iVar3 + 0x18);
  }
  if (local_c == 0) {
    local_c = FUN_0041d100(local_8 + 0xac,param_2);
  }
  return local_c;
}

