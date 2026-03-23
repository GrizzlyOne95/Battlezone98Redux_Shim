
void FUN_00824050(int param_1)

{
  int iVar1;
  float10 fVar2;
  int local_50;
  int local_48;
  int local_1c;
  int local_10;
  uint local_c;
  
  DAT_009467a0 = DAT_009467a0 + 1;
  local_10 = FUN_008445c0();
  iVar1 = ((uint)(((DAT_02cecef4 - DAT_02ceceec) + 1) * *(int *)(param_1 + 4)) / 0x1e0 - 1) +
          *(int *)(param_1 + 0xc);
  for (local_c = *(uint *)(param_1 + 0x114); local_c < *(uint *)(param_1 + 0x110);
      local_c = local_c + 1) {
    FUN_00689a20(DAT_0091552c,(short)*(char *)(param_1 + local_c + 0x10));
    local_10 = FUN_008445c0();
  }
  if (*(char *)(param_1 + local_c + 0x10) == '\0') {
    fVar2 = (float10)FUN_00689a20(DAT_0091552c,0x77);
    local_50 = (int)(longlong)ROUND(fVar2);
    local_1c = local_50;
  }
  else {
    fVar2 = (float10)FUN_00689a20(DAT_0091552c,(short)*(char *)(param_1 + local_c + 0x10));
    local_48 = (int)(longlong)ROUND(fVar2);
    local_1c = local_48;
  }
  if ((DAT_009467a0 & 8) == 0) {
    FUN_0068af40(&DAT_02cecee0,local_10,iVar1,local_10 + local_1c,iVar1,
                 *(undefined4 *)(param_1 + 0x11c),0);
  }
  return;
}

