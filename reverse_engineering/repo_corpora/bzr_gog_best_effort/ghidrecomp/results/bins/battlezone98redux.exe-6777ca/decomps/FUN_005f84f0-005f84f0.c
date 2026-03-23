
void __fastcall FUN_005f84f0(int param_1)

{
  undefined4 *puVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_30 [4];
  undefined1 local_2c [8];
  int local_24;
  int local_20;
  uint local_1c;
  int *local_18;
  int local_14;
  undefined1 local_10 [4];
  uint local_c;
  int local_8;
  
  local_8 = param_1;
  local_24 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
  if (local_24 == 0) {
    *(undefined4 *)(local_8 + 0x110) = 0x40400000;
    *(undefined4 *)(local_8 + 0x114) = 0xc1f00000;
  }
  else {
    local_c = 0;
    local_1c = 0xffffffff;
    local_20 = *(int *)(local_8 + 0x104) + 8;
    FUN_0042d8c0(local_10);
    while( true ) {
      uVar3 = FID_conflict_begin(local_30);
      cVar2 = FUN_00420f10(uVar3);
      if (cVar2 == '\0') break;
      local_18 = (int *)FUN_0042de50();
      local_14 = *(int *)(local_18[1] + 8);
      if ((2 < local_14) &&
         (((local_14 < 5 || (local_14 == 0xc)) && (iVar4 = FUN_00473940(), iVar4 == local_24)))) {
        if (*local_18 == *(int *)(local_8 + 0x10)) {
          local_1c = local_c;
        }
        local_c = local_c + 1;
      }
      FUN_00438c10(local_2c,0);
    }
    if (local_c < 5) {
      puVar1 = (undefined4 *)(*(int *)(&DAT_008ea41c + local_c * 4) + local_1c * 8);
      *(undefined4 *)(local_8 + 0x110) = *puVar1;
      *(undefined4 *)(local_8 + 0x114) = puVar1[1];
    }
    else {
      *(undefined4 *)(local_8 + 0x110) = 0;
      *(float *)(local_8 + 0x114) = (float)(int)(local_1c + 1) * -20.0;
    }
  }
  return;
}

