
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0049f9e0(void)

{
  undefined *puVar1;
  undefined4 uVar2;
  float fVar3;
  float fVar4;
  float10 fVar5;
  float10 fVar6;
  undefined8 uVar7;
  float local_c;
  int local_8;
  
  if (DAT_00915567 == '\0') {
    if (*(char *)(DAT_0094672c + 0x26) == '\0') {
      fVar5 = (float10)FUN_00461fd0((float)DAT_02cecee0 * 0.00052083336 * 2.0 + 0.5);
      fVar6 = (float10)FUN_00461fd0((float)DAT_02cecee4 * 0.0009259259 * 2.0 + 0.5);
      fVar5 = (float10)FUN_00456080((float)fVar5,(float)fVar6);
      FUN_00689ec0((float)fVar5,(float)fVar5);
    }
    else {
      FUN_00689ec0((float)*(byte *)(DAT_0094672c + 0x26),(float)*(byte *)(DAT_0094672c + 0x26));
    }
  }
  else {
    fVar5 = (float10)FUN_00461fd0((float)DAT_02cecee0 * 0.00048828125 * 3.0 + 0.5);
    fVar6 = (float10)FUN_00461fd0((float)DAT_02cecee4 * 0.0006510417 * 3.0 + 0.5);
    fVar5 = (float10)FUN_00456080((float)fVar5,(float)fVar6);
    local_c = (float)fVar5;
    if (local_c < 1.0) {
      local_c = 1.0;
    }
    FUN_00689ec0(local_c,local_c);
  }
  uVar7 = FUN_00689eb0();
  fVar4 = (float)((ulonglong)uVar7 >> 0x20);
  fVar3 = (float)uVar7;
  if (DAT_00915567 == '\0') {
    DAT_008e7a00 = (int)(fVar3 * 23.0);
    _DAT_009173e0 = 0;
    _DAT_009174b8 = 0;
  }
  else {
    DAT_008e7a00 = 0;
    _DAT_009173e0 = (int)(fVar3 * 32.0);
    _DAT_009174b8 = (int)(fVar3 * 20.0);
  }
  _DAT_008e7bd0 = (int)(fVar3 * 4.0);
  _DAT_008e7a10 = (int)(fVar3 * 120.0);
  DAT_00978e00 = DAT_008e7a00 + _DAT_008e7bd0 + _DAT_008e7a10 + _DAT_009173e0;
  DAT_008e7984 = (int)((float)_DAT_008e7be8 * fVar4);
  _DAT_008e7988 = (int)((float)_DAT_008e7a0c * fVar4);
  _DAT_008e7980 = (int)((float)_DAT_008e7a14 * fVar4);
  for (local_8 = 0; local_8 < 0xd; local_8 = local_8 + 1) {
    FUN_00689ee0(&DAT_009173e8 + local_8 * 0x10,(int)((float)_DAT_008e79fc * fVar3),
                 (int)((float)_DAT_008e7bfc * fVar4) +
                 (local_8 + 1) * (DAT_008e7984 + _DAT_008e7988),
                 (int)((float)_DAT_008e79fc * fVar3) + -1 + DAT_00978e00,
                 (local_8 + 1) * (DAT_008e7984 + _DAT_008e7988) + -1 +
                 (int)((float)_DAT_008e7bfc * fVar4) + DAT_008e7984);
    *(int *)(&DAT_009174e8 + local_8 * 8) =
         *(int *)(&DAT_009173e8 + local_8 * 0x10) + _DAT_009174b8 + DAT_008e7a00 + _DAT_008e7bd0;
    *(int *)(&DAT_009174ec + local_8 * 8) =
         (*(int *)(&DAT_009173ec + local_8 * 0x10) + 1 + *(int *)(&DAT_009173f4 + local_8 * 0x10)) /
         2;
  }
  FUN_00689ee0(&DAT_008fe62c,(int)(fVar3 * 10.0),(int)(fVar4 * 5.0),
               (int)(fVar3 * 10.0) + -1 + DAT_00978e00,(int)(fVar4 * 5.0) + -1 + DAT_008e7984);
  puVar1 = PTR_DAT_008e7c90;
  DAT_0260d758 = DAT_008fe62c;
  DAT_0260d75c = (DAT_008fe630 + 1 + DAT_008fe638) / 2;
  *(undefined4 *)PTR_DAT_008e7c90 = DAT_00917488;
  *(undefined4 *)(puVar1 + 4) = DAT_0091748c;
  *(undefined4 *)(puVar1 + 8) = DAT_00917490;
  *(undefined4 *)(puVar1 + 0xc) = DAT_00917494;
  uVar2 = DAT_0091753c;
  puVar1 = PTR_DAT_008e7bf8;
  *(undefined4 *)PTR_DAT_008e7bf8 = DAT_00917538;
  *(undefined4 *)(puVar1 + 4) = uVar2;
  puVar1 = PTR_DAT_008e7c84;
  *(undefined4 *)PTR_DAT_008e7c84 = DAT_00917498;
  *(undefined4 *)(puVar1 + 4) = DAT_0091749c;
  *(undefined4 *)(puVar1 + 8) = DAT_009174a0;
  *(undefined4 *)(puVar1 + 0xc) = DAT_009174a4;
  uVar2 = DAT_00917544;
  puVar1 = PTR_DAT_008e798c;
  *(undefined4 *)PTR_DAT_008e798c = DAT_00917540;
  *(undefined4 *)(puVar1 + 4) = uVar2;
  puVar1 = PTR_DAT_008e7c88;
  *(undefined4 *)PTR_DAT_008e7c88 = DAT_009174a8;
  *(undefined4 *)(puVar1 + 4) = DAT_009174ac;
  *(undefined4 *)(puVar1 + 8) = DAT_009174b0;
  *(undefined4 *)(puVar1 + 0xc) = DAT_009174b4;
  uVar2 = DAT_0091754c;
  puVar1 = PTR_DAT_008e7c8c;
  *(undefined4 *)PTR_DAT_008e7c8c = DAT_00917548;
  *(undefined4 *)(puVar1 + 4) = uVar2;
  FUN_00689ee0(&DAT_0260d748,DAT_008fe62c,DAT_008fe630,*(undefined4 *)(PTR_DAT_008e7c88 + 8),
               *(undefined4 *)(PTR_DAT_008e7c88 + 0xc));
  DAT_0260d738 = DAT_02cecee0;
  DAT_0260d73c = DAT_02cecee4;
  DAT_0260d740 = (uint)*(byte *)(DAT_0094672c + 0x26);
  return;
}

