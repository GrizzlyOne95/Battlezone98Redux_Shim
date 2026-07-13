
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_0046a230(void)

{
  char cVar1;
  short sVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  ushort *puStack_202b0;
  undefined1 auStack_202a4 [20];
  int iStack_20290;
  undefined1 *puStack_2028c;
  int iStack_20288;
  uint uStack_20284;
  undefined4 *puStack_20280;
  undefined4 *puStack_2027c;
  int *piStack_20278;
  undefined4 *puStack_20274;
  undefined4 *puStack_20270;
  uint uStack_2026c;
  int *piStack_20268;
  undefined4 *puStack_20264;
  short sStack_2025c;
  int iStack_20254;
  int iStack_20248;
  int iStack_20244;
  int iStack_20240;
  undefined1 *puStack_2023c;
  int *piStack_20238;
  int iStack_20234;
  uint uStack_20230;
  int iStack_2022c;
  int iStack_20228;
  uint uStack_20224;
  uint uStack_20220;
  int iStack_2021c;
  void *pvStack_20218;
  short sStack_20214;
  ushort uStack_20210;
  short sStack_2020c;
  ushort auStack_20208 [65536];
  short local_208 [256];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uStack_20210 = 1;
  iStack_20288 = DAT_02ce99a0 - DAT_02ce99c0;
  pvStack_20218 = malloc(DAT_0260d114 << 1);
  iStack_20234 = DAT_02ce99c0;
  iStack_20228 = DAT_02cd9984;
  for (iStack_2021c = 0; iStack_2021c < DAT_0260d114; iStack_2021c = iStack_2021c + 1) {
    iStack_20290 = FUN_00591670();
    if (iStack_20290 == 6) {
      *(undefined2 *)((int)pvStack_20218 + iStack_2021c * 2) = 0;
    }
    else {
      if (DAT_02ce99c0 < iStack_20234) {
        uStack_2026c = (uint)*(ushort *)((int)pvStack_20218 + iStack_2021c * 2 + -2);
      }
      else {
        uStack_2026c = 0;
      }
      sStack_20214 = (short)uStack_2026c;
      if (DAT_02cd9984 < iStack_20228) {
        uStack_20284 = (uint)*(ushort *)((int)pvStack_20218 + (iStack_2021c - iStack_20288) * 2);
      }
      else {
        uStack_20284 = 0;
      }
      sStack_2020c = (short)uStack_20284;
      if ((short)uStack_2026c == 0) {
        if ((short)uStack_20284 == 0) {
          *(ushort *)((int)pvStack_20218 + iStack_2021c * 2) = uStack_20210;
          auStack_20208[uStack_20210] = uStack_20210;
          uStack_20210 = uStack_20210 + 1;
        }
        else {
          *(short *)((int)pvStack_20218 + iStack_2021c * 2) = (short)uStack_20284;
        }
      }
      else if (((short)uStack_20284 == 0) || (uStack_2026c == uStack_20284)) {
        *(short *)((int)pvStack_20218 + iStack_2021c * 2) = (short)uStack_2026c;
      }
      else if (uStack_2026c < uStack_20284) {
        *(short *)((int)pvStack_20218 + iStack_2021c * 2) = (short)uStack_2026c;
        puStack_202b0 = auStack_20208;
        FUN_0046a020();
      }
      else {
        *(short *)((int)pvStack_20218 + iStack_2021c * 2) = (short)uStack_20284;
        puStack_202b0 = auStack_20208;
        FUN_0046a020();
      }
    }
    iStack_20234 = iStack_20234 + 1;
    if (DAT_02ce99a0 <= iStack_20234) {
      iStack_20234 = DAT_02ce99c0;
      iStack_20228 = iStack_20228 + 1;
      if (DAT_02ce99c4 <= iStack_20228) {
        iStack_20228 = DAT_02cd9984;
      }
    }
  }
  uStack_20220 = 0;
  FID_conflict_begin();
  while( true ) {
    FID_conflict_end();
    cVar1 = FID_conflict_operator__();
    if (cVar1 == '\0') break;
    piVar3 = (int *)FUN_00421ec0();
    piStack_20278 = (int *)(*piVar3 + 0x18);
    puStack_2027c = (undefined4 *)(**(code **)(*piStack_20278 + 0xc))();
    puStack_202b0 = auStack_20208;
    FUN_0046a140(*puStack_2027c,puStack_2027c[2],pvStack_20218);
    FUN_00421ee0();
  }
  for (iStack_20240 = 0; iStack_20240 < 0x10; iStack_20240 = iStack_20240 + 1) {
    for (iStack_20248 = 0x23; iStack_20248 < 0x2d; iStack_20248 = iStack_20248 + 1) {
      puStack_202b0 = (ushort *)0x46a62d;
      FUN_005e0bc0();
      iStack_20254 = FUN_005e0f70();
      if (iStack_20254 != 0) {
        puStack_20270 = (undefined4 *)(**(code **)(*(int *)(iStack_20254 + 0x18) + 0xc))();
        puStack_202b0 = auStack_20208;
        FUN_0046a140(*puStack_20270,puStack_20270[2],pvStack_20218);
      }
    }
  }
  if (DAT_00918338 == 0) {
    FID_conflict_begin();
    while( true ) {
      FID_conflict_end();
      cVar1 = FID_conflict_operator__();
      if (cVar1 == '\0') break;
      piVar3 = (int *)FUN_00421ec0();
      piStack_20268 = (int *)(*piVar3 + 0x18);
      puStack_20264 = (undefined4 *)(**(code **)(*piStack_20268 + 0xc))();
      puStack_202b0 = auStack_20208;
      FUN_0046a140(*puStack_20264,puStack_20264[2],pvStack_20218);
      FUN_00421ee0();
    }
  }
  else {
    FID_conflict_begin();
    while( true ) {
      FID_conflict_end();
      cVar1 = FID_conflict_operator__();
      if (cVar1 == '\0') break;
      puVar4 = (undefined4 *)FUN_00421ec0();
      puStack_20280 =
           (undefined4 *)std::allocator<char>::allocator<char>((allocator<char> *)*puVar4);
      puStack_202b0 = auStack_20208;
      FUN_0046a140(*puStack_20280,puStack_20280[2],pvStack_20218);
      FUN_00421ee0();
    }
  }
  FUN_0042d8c0();
  while( true ) {
    FID_conflict_begin();
    cVar1 = FUN_00420f10();
    if (cVar1 == '\0') break;
    puVar4 = (undefined4 *)FUN_0042de50();
    piStack_20238 = (int *)*puVar4;
    if (*piStack_20238 != 0) {
      puStack_202b0 = (ushort *)0x46a8aa;
      iVar5 = _stricmp((char *)*piStack_20238,"edge_path");
      if (iVar5 != 0) {
        for (iStack_20244 = 0; iStack_20244 < piStack_20238[1]; iStack_20244 = iStack_20244 + 1) {
          puStack_20274 = (undefined4 *)(piStack_20238[2] + iStack_20244 * 8);
          puStack_202b0 = auStack_20208;
          FUN_0046a140(*puStack_20274,puStack_20274[1],pvStack_20218);
        }
      }
    }
    puStack_202b0 = (ushort *)0x46a84c;
    FUN_00438c10();
  }
  puStack_202b0 = (ushort *)0x46a956;
  FUN_007d6a70();
  iVar5 = -(uint)uStack_20210;
  puStack_2028c = auStack_202a4 + iVar5;
  puStack_2023c = auStack_202a4 + iVar5;
  auStack_202a4[iVar5] = 0;
  uStack_20224 = 1;
  do {
    if (uStack_20210 <= uStack_20224) {
      for (iStack_2022c = 0; iStack_2022c < DAT_0260d114; iStack_2022c = iStack_2022c + 1) {
        *(undefined1 *)(DAT_0260d17c + iStack_2022c) =
             puStack_2023c[*(ushort *)((int)pvStack_20218 + iStack_2022c * 2)];
      }
      *(void **)(&stack0xfffdfd58 + iVar5) = pvStack_20218;
      *(undefined4 *)(&stack0xfffdfd54 + iVar5) = 0x46aaa5;
      free(*(void **)(&stack0xfffdfd58 + iVar5));
      FUN_0083e885();
      return;
    }
    *(uint *)(&stack0xfffdfd58 + iVar5) = uStack_20224 & 0xffff;
    *(ushort **)(&stack0xfffdfd54 + iVar5) = auStack_20208;
    *(undefined4 *)((int)&puStack_202b0 + iVar5) = 0x46a9cb;
    sVar2 = FUN_00469fd0();
    sStack_2025c = sVar2;
    puStack_2023c[uStack_20224] = 0;
    for (uStack_20230 = 0; uStack_20230 < uStack_20220; uStack_20230 = uStack_20230 + 1) {
      if (sVar2 == local_208[uStack_20230]) {
        puStack_2023c[uStack_20224] = (char)uStack_20230 + '\x01';
        break;
      }
    }
    uStack_20224 = uStack_20224 + 1;
  } while( true );
}

