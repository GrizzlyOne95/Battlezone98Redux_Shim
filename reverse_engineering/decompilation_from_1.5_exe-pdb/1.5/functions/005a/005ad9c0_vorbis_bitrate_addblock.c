/*
 * Entry: 005ad9c0
 * Name: vorbis_bitrate_addblock
 * Namespace: Global
 * Signature: int vorbis_bitrate_addblock(vorbis_block * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_bitrate_addblock(vorbis_block *param_1)

{
  int *piVar1;
  double dVar2;
  void *pvVar3;
  void *pvVar4;
  vorbis_info *pvVar5;
  void *pvVar6;
  int extraout_EAX;
  int iVar7;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  float10 fVar15;
  int local_30;
  int local_28;
  
  pvVar3 = param_1->internal;
  pvVar4 = param_1->vd->backend_state;
  pvVar5 = param_1->vd->vi;
  pvVar6 = pvVar5->codec_setup;
  floor(*(double *)((int)pvVar4 + 0x70) + 0.5);
  _ftol2_sse();
  iVar7 = oggpack_bytes(*(undefined4 *)((int)pvVar3 + extraout_EAX * 4 + 0xc));
  iVar7 = iVar7 * 8;
  if (param_1->W == 0) {
    local_28 = *(int *)((int)pvVar4 + 0x60);
    iVar8 = *(int *)((int)pvVar4 + 100);
  }
  else {
    local_28 = *(int *)((int)pvVar4 + 0x68) * *(int *)((int)pvVar4 + 0x60);
    iVar8 = *(int *)((int)pvVar4 + 0x68) * *(int *)((int)pvVar4 + 100);
  }
  iVar9 = *(int *)((int)pvVar6 + param_1->W * 4);
  piVar1 = (int *)((int)pvVar6 + 0xd2c);
  _ftol2_sse();
  if (*(int *)((int)pvVar4 + 0x50) == 0) {
    if (*(int *)((int)pvVar4 + 0x78) != 0) {
      return -1;
    }
    *(vorbis_block **)((int)pvVar4 + 0x78) = param_1;
    return 0;
  }
  iVar11 = *(int *)((int)pvVar4 + 0x5c);
  *(vorbis_block **)((int)pvVar4 + 0x78) = param_1;
  iVar10 = extraout_EAX;
  if (0 < iVar11) {
    if (param_1->W != 0) {
      iVar11 = *(int *)((int)pvVar4 + 0x68) * iVar11;
    }
    dVar2 = *(double *)((int)pvVar6 + 0xd38);
    iVar10 = (*(int *)((int)pvVar4 + 0x54) - iVar11) + iVar7;
    local_30 = extraout_EAX;
    if (extraout_EAX_00 < iVar10) {
      for (; ((0 < local_30 && (iVar11 < iVar7)) &&
             (extraout_EAX_00 < (*(int *)((int)pvVar4 + 0x54) - iVar11) + iVar7)); iVar7 = iVar7 * 8
          ) {
        local_30 = local_30 + -1;
        iVar7 = oggpack_bytes();
      }
    }
    else if ((iVar10 < extraout_EAX_00) && (extraout_EAX + 1 < 0xf)) {
      do {
        if ((iVar11 <= iVar7) ||
           (extraout_EAX_00 <= (*(int *)((int)pvVar4 + 0x54) - iVar11) + iVar7)) break;
        local_30 = local_30 + 1;
        iVar7 = oggpack_bytes();
        iVar7 = iVar7 * 8;
      } while (local_30 < 0xe);
    }
    iVar7 = pvVar5->rate;
    fVar12 = (float10)floor(((double)local_30 - *(double *)((int)pvVar4 + 0x70)) + 0.5);
    fVar13 = (float10)(iVar9 >> 1);
    fVar14 = (float10)iVar7;
    fVar12 = (fVar12 / fVar13) * fVar14;
    fVar15 = (float10)(15.0 / dVar2);
    if (fVar12 < -fVar15) {
      fVar12 = -fVar15;
    }
    if (fVar15 < fVar12) {
      fVar12 = fVar15;
    }
    fVar12 = fVar13 * (fVar12 / fVar14) + (float10)*(double *)((int)pvVar4 + 0x70);
    *(double *)((int)pvVar4 + 0x70) = (double)fVar12;
    floor((double)(fVar12 + (float10)0.5));
    _ftol2_sse();
    iVar7 = oggpack_bytes(*(undefined4 *)((int)pvVar3 + extraout_EAX_01 * 4 + 0xc));
    iVar7 = iVar7 * 8;
    iVar10 = extraout_EAX_01;
  }
  if ((0 < *(int *)((int)pvVar4 + 0x60)) && (iVar7 < local_28)) {
    iVar9 = (*(int *)((int)pvVar4 + 0x58) - local_28) + iVar7;
    while ((iVar9 < 0 && (iVar10 = iVar10 + 1, iVar10 < 0xf))) {
      iVar7 = oggpack_bytes();
      iVar7 = iVar7 * 8;
      iVar9 = (*(int *)((int)pvVar4 + 0x58) - local_28) + iVar7;
    }
  }
  if (((0 < *(int *)((int)pvVar4 + 100)) && (iVar8 < iVar7)) &&
     (*piVar1 < (*(int *)((int)pvVar4 + 0x58) - iVar8) + iVar7)) {
    do {
      iVar10 = iVar10 + -1;
      if (iVar10 < 0) goto LAB_005adcc1;
      iVar7 = oggpack_bytes();
      iVar7 = iVar7 * 8;
    } while (*piVar1 < (*(int *)((int)pvVar4 + 0x58) - iVar8) + iVar7);
  }
  if (iVar10 < 0) {
LAB_005adcc1:
    iVar9 = *piVar1;
    *(undefined4 *)((int)pvVar4 + 0x7c) = 0;
    iVar9 = (iVar9 - *(int *)((int)pvVar4 + 0x58)) + iVar8;
    iVar11 = (int)(iVar9 + (iVar9 >> 0x1f & 7U)) >> 3;
    iVar9 = oggpack_bytes();
    if (iVar11 < iVar9) {
      oggpack_writetrunc(*(undefined4 *)((int)pvVar3 + 0xc),iVar11 * 8);
      iVar7 = oggpack_bytes(*(undefined4 *)((int)pvVar3 + 0xc));
      goto LAB_005add7f;
    }
  }
  else {
    iVar7 = (local_28 - *(int *)((int)pvVar4 + 0x58)) + 7;
    if (0xe < iVar10) {
      iVar10 = 0xe;
    }
    *(int *)((int)pvVar4 + 0x7c) = iVar10;
    iVar9 = oggpack_bytes();
    for (iVar9 = ((int)(iVar7 + (iVar7 >> 0x1f & 7U)) >> 3) - iVar9; 0 < iVar9; iVar9 = iVar9 + -1)
    {
      oggpack_write(*(undefined4 *)((int)pvVar3 + iVar10 * 4 + 0xc),0,8);
    }
    iVar7 = oggpack_bytes();
LAB_005add7f:
    iVar7 = iVar7 * 8;
  }
  if ((0 < *(int *)((int)pvVar4 + 0x60)) || (0 < *(int *)((int)pvVar4 + 100))) {
    if ((iVar8 < 1) || (iVar7 <= iVar8)) {
      if ((local_28 < 1) || (local_28 <= iVar7)) {
        iVar9 = *(int *)((int)pvVar4 + 0x58);
        if (extraout_EAX_00 < iVar9) {
          if ((0 < iVar8) &&
             (iVar8 = (iVar9 - iVar8) + iVar7, *(int *)((int)pvVar4 + 0x58) = iVar8,
             extraout_EAX_00 <= iVar8)) goto LAB_005addeb;
        }
        else if ((0 < local_28) &&
                (iVar8 = (iVar9 - local_28) + iVar7, *(int *)((int)pvVar4 + 0x58) = iVar8,
                iVar8 <= extraout_EAX_00)) goto LAB_005addeb;
        *(int *)((int)pvVar4 + 0x58) = extraout_EAX_00;
      }
      else {
        *(int *)((int)pvVar4 + 0x58) = *(int *)((int)pvVar4 + 0x58) + (iVar7 - local_28);
      }
    }
    else {
      *(int *)((int)pvVar4 + 0x58) = *(int *)((int)pvVar4 + 0x58) + (iVar7 - iVar8);
    }
  }
LAB_005addeb:
  iVar8 = *(int *)((int)pvVar4 + 0x5c);
  if (0 < iVar8) {
    if (param_1->W != 0) {
      *(int *)((int)pvVar4 + 0x54) =
           *(int *)((int)pvVar4 + 0x54) + (iVar7 - *(int *)((int)pvVar4 + 0x68) * iVar8);
      return 0;
    }
    *(int *)((int)pvVar4 + 0x54) = *(int *)((int)pvVar4 + 0x54) + (iVar7 - iVar8);
  }
  return 0;
}
