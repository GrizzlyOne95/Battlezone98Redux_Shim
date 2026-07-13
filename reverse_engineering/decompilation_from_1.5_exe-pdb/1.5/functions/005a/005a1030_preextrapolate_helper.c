/*
 * Entry: 005a1030
 * Name: _preextrapolate_helper
 * Namespace: Global
 * Signature: void _preextrapolate_helper(vorbis_dsp_state * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: Type propagation algorithm not settling */

void __cdecl _preextrapolate_helper(vorbis_dsp_state *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int unaff_ESI;
  undefined1 auStack_94 [24];
  int aiStack_7c [6];
  int aiStack_64 [19];
  undefined4 uStack_18;
  int local_c;
  
  uStack_18 = 0x5a1042;
  iVar1 = *(int *)(unaff_ESI + 0x14);
  aiStack_64[3] = 0x5a1054;
  *(undefined4 *)(unaff_ESI + 0x1c) = 1;
  if (0x20 < iVar1 - *(int *)(unaff_ESI + 0x30)) {
    iVar5 = 0;
    local_c = 0;
    if (0 < *(int *)(*(int *)(unaff_ESI + 4) + 4)) {
      do {
        iVar3 = 0;
        if (0 < *(int *)(unaff_ESI + 0x14)) {
          do {
            iVar2 = iVar3 + 1;
            aiStack_64[(iVar3 - iVar1) + 4] =
                 *(int *)(*(int *)(*(int *)(unaff_ESI + 8) + iVar5) + -4 +
                         (*(int *)(unaff_ESI + 0x14) - iVar3) * 4);
            iVar3 = iVar2;
          } while (iVar2 < *(int *)(unaff_ESI + 0x14));
        }
        iVar3 = *(int *)(unaff_ESI + 0x14);
        iVar2 = *(int *)(unaff_ESI + 0x30);
        aiStack_64[3 - iVar1] = 0x10;
        *(int *)((int)aiStack_64 + (1 - iVar1) * 4 + 4U) = iVar3 - iVar2;
        *(int **)((int)aiStack_64 + iVar1 * 0xfffffffcU + 4U) = aiStack_64 + 4;
        aiStack_64[-iVar1] = (int)(aiStack_64 + (4 - iVar1));
        *(undefined4 *)((int)aiStack_7c + (4 - iVar1) * 4 + 4U) = 0x5a10ad;
        vorbis_lpc_from_data
                  ((float *)aiStack_64[-iVar1],
                   *(float **)((int)aiStack_64 + iVar1 * 0xfffffffcU + 4U),
                   *(int *)((int)aiStack_64 + (1 - iVar1) * 4 + 4U),aiStack_64[3 - iVar1]);
        iVar3 = *(int *)(unaff_ESI + 0x14) - *(int *)(unaff_ESI + 0x30);
        *(int *)((int)aiStack_7c + (4 - iVar1) * 4 + 4U) = *(int *)(unaff_ESI + 0x30);
        *(int **)((int)aiStack_7c + (3 - iVar1) * 4 + 4U) = aiStack_64 + (iVar3 - iVar1) + 4;
        *(undefined4 *)((int)aiStack_7c + (2 - iVar1) * 4 + 4U) = 0x10;
        *(undefined1 **)((int)aiStack_7c + (1 - iVar1) * 4 + 4U) =
             auStack_94 + iVar3 * 4 + iVar1 * -4;
        *(int **)((int)aiStack_7c + iVar1 * 0xfffffffcU + 4U) = aiStack_64 + 4;
        aiStack_7c[-iVar1] = 0x5a10cc;
        vorbis_lpc_predict(*(float **)((int)aiStack_7c + iVar1 * 0xfffffffcU + 4U),
                           *(float **)((int)aiStack_7c + (1 - iVar1) * 4 + 4U),
                           *(int *)((int)aiStack_7c + (2 - iVar1) * 4 + 4U),
                           *(float **)((int)aiStack_7c + (3 - iVar1) * 4 + 4U),
                           *(long *)((int)aiStack_7c + (4 - iVar1) * 4 + 4U));
        iVar3 = 0;
        if (0 < *(int *)(unaff_ESI + 0x14)) {
          do {
            iVar2 = iVar3 - iVar1;
            iVar4 = *(int *)(unaff_ESI + 0x14) - iVar3;
            iVar3 = iVar3 + 1;
            *(int *)(*(int *)(*(int *)(unaff_ESI + 8) + iVar5) + -4 + iVar4 * 4) =
                 aiStack_64[iVar2 + 4];
          } while (iVar3 < *(int *)(unaff_ESI + 0x14));
        }
        local_c = local_c + 1;
        iVar5 = iVar5 + 4;
      } while (local_c < *(int *)(*(int *)(unaff_ESI + 4) + 4));
    }
  }
  return;
}
