
undefined4 FUN_004cf880(uint param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  uint local_1c;
  uint local_18;
  undefined4 local_14;
  undefined4 local_10;
  uint local_c;
  undefined1 local_8 [4];
  
  if (param_1 != 0) {
    if ((DAT_00917b20 < 0x417) || ((1999 < DAT_00917b20 && (DAT_00917b20 < 0x7da)))) {
      local_18 = param_1;
      local_c = param_1 & 0x7fffff;
    }
    else {
      local_1c = param_1;
      local_c = param_1 & 0xfffff;
    }
    local_10 = DAT_00917a74;
    FID_conflict_begin(local_8);
    while( true ) {
      uVar2 = FID_conflict_end(local_24);
      cVar1 = FID_conflict_operator__(uVar2);
      if (cVar1 == '\0') break;
      puVar3 = (undefined4 *)FUN_00421ec0();
      local_14 = *puVar3;
      uVar4 = FUN_00462450();
      if (uVar4 == local_c) {
        uVar2 = FUN_00462380();
        return uVar2;
      }
      FUN_0046b260(local_20,0);
    }
  }
  return 0;
}

