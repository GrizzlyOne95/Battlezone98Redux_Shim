/*
 * Entry: 00513e9f
 * Name: Mapgrid_Show
 * Namespace: Global
 * Signature: void Mapgrid_Show(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mapgrid_Show(void)

{
  int iVar1;
  tagMAPGRID *ptVar2;
  int iVar3;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  tlog_cbc("Mapgrid_Show:\n");
  if ((mapgrid != (tagMAPGRID **)0x0) && (local_8 = 0, 0 < mapgridysize)) {
    do {
      local_18 = 0;
      if (0 < mapgridxsize) {
        local_1c = 0;
        do {
          ptVar2 = mapgrid[local_8];
          local_14 = 0;
          do {
            local_10 = 0;
            local_c = 0x101;
            tlog_cbc(" grid[%d][%d], team=%d, nrunits=%d, units=\n");
            iVar3 = *(int *)((int)ptVar2->firstunit + local_14 * 4 + local_1c);
            if (iVar3 != 0) {
              do {
                iVar1 = local_c + -1;
                if (local_c == 0) break;
                local_10 = local_10 + 1;
                tlog_cbc("  id=%d, u=%08x\n");
                iVar3 = *(int *)(iVar3 + 100);
                local_c = iVar1;
              } while (iVar3 != 0);
              if (iVar1 < 1) {
                tlog_cbc("  ERROR!! too many units!!!\n");
              }
            }
            if (local_10 != *(int *)((int)ptVar2->nrunits + local_14 * 4 + local_1c)) {
              tlog_cbc("  ERROR!! found %d units but expecting %d!!!\n");
            }
            local_14 = local_14 + 1;
          } while (local_14 < 0x10);
          local_18 = local_18 + 1;
          local_1c = local_1c + 0x10c;
        } while (local_18 < mapgridxsize);
      }
      local_8 = local_8 + 1;
    } while (local_8 < mapgridysize);
  }
  return;
}
