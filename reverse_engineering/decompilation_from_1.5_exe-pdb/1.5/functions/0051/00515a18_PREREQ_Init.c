/*
 * Entry: 00515a18
 * Name: PREREQ_Init
 * Namespace: Global
 * Signature: void PREREQ_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PREREQ_Init(void)

{
  uint *puVar1;
  ushort *puVar2;
  ushort *puVar3;
  ushort uVar4;
  int iVar5;
  tagUNITTYPE *ptVar6;
  PREREQ_equiv *pPVar7;
  ushort *puVar8;
  void *pvVar9;
  tagUNIT *ptVar10;
  tagBUILDING *ptVar11;
  int *piVar12;
  uchar uVar13;
  int extraout_EDX;
  uint uVar14;
  int iVar15;
  size_t sVar16;
  int local_5c;
  int local_58;
  int local_54;
  tagITERATOR local_50;
  
  if (PREREQ_online == '\0') {
    sVar16 = 0x9c;
    iVar5 = Units_UnitTypeCount();
    PREREQ_table = calloc(iVar5 + 1 + maxbuildingtypes,sVar16);
    PREREQ_assignment = calloc(0x10000,4);
    PREREQ_equiv_assignment = calloc(0x10000,4);
    PREREQ_maxassigned = 1;
    PREREQ_maxequiv = 1;
    iVar5 = 0;
    do {
      *(undefined4 *)(iVar5 + (int)PREREQ_assignment) = 0;
      iVar5 = iVar5 + 4;
    } while (iVar5 < 0x40000);
    iVar5 = 0;
    do {
      *(undefined4 *)(iVar5 + (int)PREREQ_equiv_assignment) = 0;
      iVar5 = iVar5 + 4;
    } while (iVar5 < 0x40000);
    iVar15 = 0;
    iVar5 = Units_UnitTypeCount();
    if (0 < iVar5) {
      do {
        ptVar6 = Units_GetTypePtr(iVar15);
        if (PREREQ_assignment[(ptVar6->prereq).prereqtype] == 0) {
          uVar4 = (ptVar6->prereq).equivalence;
          if (uVar4 != 0) {
            puVar8 = (ushort *)(PREREQ_equiv_assignment + uVar4);
            if (*(int *)puVar8 == 0) {
              *(int *)puVar8 = PREREQ_maxequiv;
              (ptVar6->prereq).equivalence = (ushort)PREREQ_maxequiv;
              PREREQ_maxequiv = PREREQ_maxequiv + 1;
            }
            else {
              (ptVar6->prereq).equivalence = *puVar8;
            }
          }
          PREREQ_assignment[(ptVar6->prereq).prereqtype] = PREREQ_maxassigned;
          (ptVar6->prereq).prereqtype = (ushort)PREREQ_maxassigned;
          PREREQ_maxassigned = PREREQ_maxassigned + 1;
        }
        else {
          tlog(2,"Duplicate Unit Prereqtype Found : %d");
          (ptVar6->prereq).prereqtype = *(ushort *)(PREREQ_assignment + (ptVar6->prereq).prereqtype)
          ;
        }
        iVar15 = iVar15 + 1;
        iVar5 = Units_UnitTypeCount();
      } while (iVar15 < iVar5);
    }
    PREREQ_cutoff = PREREQ_maxassigned;
    local_5c = 0;
    if (0 < maxbuildingtypes) {
      iVar5 = 0;
      do {
        puVar8 = (ushort *)((int)buildingtypes->prereqs + iVar5 + -0xe);
        if (PREREQ_assignment[*puVar8] == 0) {
          if (puVar8[6] != 0) {
            puVar2 = (ushort *)(PREREQ_equiv_assignment + puVar8[6]);
            if (*(int *)puVar2 == 0) {
              *(int *)puVar2 = PREREQ_maxequiv;
              puVar8[6] = (ushort)PREREQ_maxequiv;
              PREREQ_maxequiv = PREREQ_maxequiv + 1;
            }
            else {
              puVar8[6] = *puVar2;
            }
          }
          PREREQ_assignment[*puVar8] = PREREQ_maxassigned;
          *puVar8 = (ushort)PREREQ_maxassigned;
          PREREQ_maxassigned = PREREQ_maxassigned + 1;
        }
        else {
          tlog(2,"Duplicate Building Prereqtype Found : %d");
          *puVar8 = *(ushort *)(PREREQ_assignment + *puVar8);
        }
        local_5c = local_5c + 1;
        iVar5 = iVar5 + 0x80;
      } while (local_5c < maxbuildingtypes);
    }
    free(PREREQ_equiv_assignment);
    PREREQ_equiv_table = calloc(PREREQ_maxequiv,4);
    iVar5 = 0;
    if (0 < PREREQ_maxequiv) {
      do {
        PREREQ_equiv_table[iVar5] = (PREREQ_equiv *)0x0;
        iVar5 = iVar5 + 1;
      } while (iVar5 < PREREQ_maxequiv);
    }
    iVar15 = 0;
    iVar5 = Units_UnitTypeCount();
    if (0 < iVar5) {
      do {
        ptVar6 = Units_GetTypePtr(iVar15);
        uVar4 = (ptVar6->prereq).equivalence;
        if (uVar4 != 0) {
          pPVar7 = calloc(1,8);
          pPVar7->side = (ushort)ptVar6->side;
          pPVar7->type = (ptVar6->prereq).prereqtype;
          pPVar7->next = PREREQ_equiv_table[uVar4];
          PREREQ_equiv_table[uVar4] = pPVar7;
        }
        iVar15 = iVar15 + 1;
        iVar5 = Units_UnitTypeCount();
      } while (iVar15 < iVar5);
    }
    local_5c = 0;
    if (0 < maxbuildingtypes) {
      iVar5 = 0;
      do {
        puVar8 = (ushort *)((int)buildingtypes->prereqs + iVar5 + -0xe);
        uVar4 = puVar8[6];
        if (uVar4 != 0) {
          pPVar7 = calloc(1,8);
          pPVar7->side = (ushort)(*(uint *)(puVar8 + 0x12) >> 2) & 0xff;
          pPVar7->type = *puVar8;
          pPVar7->next = PREREQ_equiv_table[uVar4];
          PREREQ_equiv_table[uVar4] = pPVar7;
        }
        local_5c = local_5c + 1;
        iVar5 = iVar5 + 0x80;
      } while (local_5c < maxbuildingtypes);
    }
    local_5c = 0;
    iVar5 = Units_UnitTypeCount();
    if (0 < iVar5) {
      do {
        ptVar6 = Units_GetTypePtr(local_5c);
        uVar14 = (uint)(ptVar6->prereq).prereqtype;
        PREREQ_table[uVar14].type = '\0';
        PREREQ_table[uVar14].data = ptVar6;
        PREREQ_table[uVar14].side = ptVar6->side;
        PREREQ_table[uVar14].equiv = PREREQ_equiv_table[(ptVar6->prereq).equivalence];
        puVar8 = calloc(5,2);
        PREREQ_table[uVar14].prereqs = puVar8;
        puVar8 = (ptVar6->prereq).prereqs;
        iVar5 = 0;
        do {
          PREREQ_table[uVar14].prereqs[iVar5] = *(ushort *)(PREREQ_assignment + *puVar8);
          *puVar8 = PREREQ_table[uVar14].prereqs[iVar5];
          iVar5 = iVar5 + 1;
          puVar8 = puVar8 + 1;
        } while (iVar5 < 4);
        PREREQ_table[uVar14].prereqs[iVar5] = 0;
        puVar8 = calloc(5,2);
        local_58 = 0;
        PREREQ_table[uVar14].makers = puVar8;
        puVar8 = (ptVar6->prereq).makers;
        do {
          PREREQ_table[uVar14].makers[local_58] = *(ushort *)(PREREQ_assignment + *puVar8);
          puVar2 = PREREQ_table[uVar14].makers + local_58;
          local_58 = local_58 + 1;
          *puVar8 = *puVar2;
          puVar8 = puVar8 + 1;
        } while (local_58 < 4);
        PREREQ_table[uVar14].makers[local_58] = 0;
        local_54 = uVar14 * 0x9c + 0x1c;
        iVar5 = 0;
        piVar12 = &teamdata[0].side;
        do {
          *(undefined4 *)((int)PREREQ_table->howmany + local_54 + -0x1c) = 0;
          PREREQ_table[uVar14].canmake[iVar5] = '\0';
          if (((*piVar12 == (uint)ptVar6->side) || (ptVar6->side == 0xffffffff)) &&
             (*PREREQ_table[uVar14].makers != 0)) {
            uVar13 = '\x01';
          }
          else {
            uVar13 = '\0';
          }
          local_54 = local_54 + 4;
          PREREQ_table[uVar14].haveplans[iVar5] = uVar13;
          PREREQ_table[uVar14].havestolen[iVar5] = '\0';
          piVar12 = piVar12 + 0x7a;
          iVar5 = iVar5 + 1;
        } while ((int)piVar12 < 0xcd5930);
        local_5c = local_5c + 1;
        iVar5 = Units_UnitTypeCount();
      } while (local_5c < iVar5);
    }
    local_5c = 0;
    if (0 < maxbuildingtypes) {
      local_54 = 0;
      do {
        puVar2 = (ushort *)((int)buildingtypes->prereqs + local_54 + -0xe);
        uVar14 = (uint)*puVar2;
        PREREQ_table[uVar14].type = '\x01';
        PREREQ_table[uVar14].data = puVar2;
        PREREQ_table[uVar14].side = (char)(*(uint *)(puVar2 + 0x12) >> 2);
        PREREQ_table[uVar14].equiv = PREREQ_equiv_table[puVar2[6]];
        puVar8 = calloc(5,2);
        PREREQ_table[uVar14].prereqs = puVar8;
        puVar8 = puVar2 + 7;
        iVar5 = 0;
        do {
          PREREQ_table[uVar14].prereqs[iVar5] = *(ushort *)(PREREQ_assignment + *puVar8);
          *puVar8 = PREREQ_table[uVar14].prereqs[iVar5];
          iVar5 = iVar5 + 1;
          puVar8 = puVar8 + 1;
        } while (iVar5 < 4);
        PREREQ_table[uVar14].prereqs[iVar5] = 0;
        puVar8 = calloc(5,2);
        local_58 = 0;
        PREREQ_table[uVar14].makers = puVar8;
        puVar8 = puVar2 + 0xb;
        do {
          PREREQ_table[uVar14].makers[local_58] = *(ushort *)(PREREQ_assignment + *puVar8);
          puVar3 = PREREQ_table[uVar14].makers + local_58;
          local_58 = local_58 + 1;
          *puVar8 = *puVar3;
          puVar8 = puVar8 + 1;
        } while (local_58 < 4);
        PREREQ_table[uVar14].makers[local_58] = 0;
        local_58 = uVar14 * 0x9c + 0x1c;
        iVar5 = 0;
        piVar12 = &teamdata[0].side;
        do {
          *(undefined4 *)((int)PREREQ_table->howmany + local_58 + -0x1c) = 0;
          PREREQ_table[uVar14].canmake[iVar5] = '\0';
          if (((*piVar12 == (*(uint *)(puVar2 + 0x12) >> 2 & 0xff)) ||
              ((*(uint *)((int)(buildingtypes->resource + -2) + local_54) >> 2 & 0xff) == 0xffffffff
              )) && (*PREREQ_table[uVar14].makers != 0)) {
            uVar13 = '\x01';
          }
          else {
            uVar13 = '\0';
          }
          local_58 = local_58 + 4;
          PREREQ_table[uVar14].haveplans[iVar5] = uVar13;
          PREREQ_table[uVar14].havestolen[iVar5] = '\0';
          piVar12 = piVar12 + 0x7a;
          iVar5 = iVar5 + 1;
        } while ((int)piVar12 < 0xcd5930);
        local_5c = local_5c + 1;
        local_54 = local_54 + 0x80;
      } while (local_5c < maxbuildingtypes);
    }
    free(PREREQ_assignment);
    iVar5 = 1;
    if (1 < PREREQ_maxassigned) {
      iVar15 = 0x9c;
      do {
        for (puVar8 = *(ushort **)((int)PREREQ_table->howmany + iVar15 + -8); *puVar8 != 0;
            puVar8 = puVar8 + 1) {
          if (PREREQ_table[*puVar8].type == '\0') {
            puVar1 = (uint *)((int)PREREQ_table[*puVar8].data + 0x70);
            *puVar1 = *puVar1 | 2;
          }
        }
        iVar5 = iVar5 + 1;
        iVar15 = iVar15 + 0x9c;
      } while (iVar5 < PREREQ_maxassigned);
    }
    sVar16 = 2;
    iVar5 = Units_UnitTypeCount();
    PREREQ_temp = calloc(iVar5 + 1 + maxbuildingtypes,sVar16);
    iVar5 = 1;
    if (1 < PREREQ_maxassigned) {
      iVar15 = 0x9c;
      do {
        PREREQ_ptr = PREREQ_temp;
        puVar8 = *(ushort **)((int)PREREQ_table->howmany + iVar15 + -0x10);
        while (*puVar8 != 0) {
          PREREQ_Search(*puVar8,&PREREQ_ptr);
          puVar8 = (ushort *)(extraout_EDX + 2);
        }
        *PREREQ_ptr = 0;
        PREREQ_ptr = PREREQ_ptr + 1;
        PREREQ_PruneDuplicates(PREREQ_temp);
        sVar16 = 1;
        for (PREREQ_ptr = PREREQ_temp; *PREREQ_ptr != 0; PREREQ_ptr = PREREQ_ptr + 1) {
          sVar16 = sVar16 + 1;
        }
        pvVar9 = calloc(sVar16,2);
        *(void **)((int)PREREQ_table->howmany + iVar15 + -0xc) = pvVar9;
        memcpy(*(undefined4 *)((int)PREREQ_table->howmany + iVar15 + -0xc),PREREQ_temp,sVar16 * 2);
        iVar5 = iVar5 + 1;
        iVar15 = iVar15 + 0x9c;
      } while (iVar5 < PREREQ_maxassigned);
    }
    free(PREREQ_temp);
    PREREQ_online = '\x01';
    Iterate_UnitInitAll(&local_50);
    ptVar10 = Iterate_UnitNext(&local_50);
    while (ptVar10 != (tagUNIT *)0x0) {
      PREREQ_Add((ptVar10->type->prereq).prereqtype,ptVar10->team);
      ptVar10 = Iterate_UnitNext(&local_50);
    }
    ITERATE_BUILDINIT_ALL(&local_50);
    ptVar11 = Iterate_BuildNext(&local_50);
    while (ptVar11 != (tagBUILDING *)0x0) {
      PREREQ_Add(ptVar11->buildingtype->prereqtype,(char)ptVar11->team);
      ptVar11 = Iterate_BuildNext(&local_50);
    }
  }
  return;
}
