
undefined4 FUN_0068b0e0(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined4 local_1c;
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined1 local_10 [4];
  int local_c;
  undefined4 local_8;
  
  local_8 = 1;
  DAT_00920ef4 = DAT_008ed780;
  FUN_0068b050();
  FUN_0068bdd0();
  *(undefined2 *)(&DAT_025f8f40 + DAT_00920f00 * 0x24) = 0;
  *(undefined2 *)(&DAT_025f8f42 + DAT_00920f00 * 0x24) = 0;
  *(undefined2 *)(&DAT_025f8f44 + DAT_00920f00 * 0x24) = 0x10;
  *(undefined2 *)(&DAT_025f8f46 + DAT_00920f00 * 0x24) = 0x10;
  *(undefined4 *)(&DAT_025f8f48 + DAT_00920f00 * 0x24) = 0;
  *(undefined4 *)(&DAT_025f8f4c + DAT_00920f00 * 0x24) = 0;
  *(undefined4 *)(&DAT_025f8f50 + DAT_00920f00 * 0x24) = 0x3f800000;
  *(undefined4 *)(&DAT_025f8f54 + DAT_00920f00 * 0x24) = 0x3f800000;
  *(undefined4 *)(&DAT_025f8f58 + DAT_00920f00 * 0x24) = 0;
  DAT_00920f00 = DAT_00920f00 + 1;
  iVar2 = FUN_0081dee0();
  if (iVar2 == 7) {
    iVar2 = FUN_0068b340("bzfont_ru.st");
    if (iVar2 == 0) {
      FUN_007d6c70("Font sprite table \"bzfont_ru\" not found. Text will be missing.\n");
      local_8 = 0;
    }
  }
  else {
    iVar2 = FUN_0068b340("bzfont.st");
    if (iVar2 == 0) {
      FUN_007d6c70("Font sprite table \"bzfont\" not found. Text will be missing.\n");
      local_8 = 0;
    }
  }
  iVar2 = FUN_0068b340("spritea.st");
  if ((iVar2 == 0) && (iVar2 = FUN_0068ba00("spritea.stb"), iVar2 == 0)) {
    FUN_007d6830("Main sprite table \"spritea\" not found. Most sprites will be missing.\n");
    local_8 = 0;
  }
  local_c = 0;
  local_14 = 0;
  vector<>();
  while (local_c = FUN_008287d0("*.sta",&local_14), local_c != 0) {
    FUN_0041fe40(&local_c);
  }
  uVar3 = FUN_0068f170(local_20);
  FUN_0068f280(uVar3);
  uVar3 = FUN_0068f1a0(local_24);
  FUN_0068f280(uVar3);
  while (cVar1 = operator!=<>(local_10,local_18), cVar1 != '\0') {
    puVar4 = (undefined4 *)FUN_0068f1f0();
    FUN_0068b340(*puVar4);
    FUN_0068f1d0();
  }
  local_1c = local_8;
  FUN_0041fe20();
  return local_1c;
}

