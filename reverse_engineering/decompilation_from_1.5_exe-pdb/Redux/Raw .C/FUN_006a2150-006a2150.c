
uint FUN_006a2150(int param_1,int param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined *local_14;
  undefined *local_10;
  int *local_c;
  undefined4 local_8;
  
  cVar1 = FUN_006a0810(param_1);
  if (cVar1 == '\0') {
    local_10 = &DAT_0260af90;
  }
  else {
    local_10 = &DAT_0260afd0;
  }
  local_14 = local_10;
  FUN_00422170();
  puVar2 = (undefined4 *)FID_conflict_begin(local_18);
  local_8 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_20);
    uVar4 = FID_conflict_operator__(uVar3);
    if ((uVar4 & 0xff) == 0) {
      return uVar4 & 0xffffff00;
    }
    local_c = (int *)FUN_00421ec0();
    local_c = (int *)*local_c;
    if (*local_c == param_1) break;
    FUN_0046b260(local_1c,0);
  }
  if (local_c[1] == 0) {
    local_c[1] = param_2;
  }
  return CONCAT31((int3)((uint)local_c >> 8),1);
}

