
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0077ea10(void)

{
  char cVar1;
  char cVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  float *pfVar8;
  int local_5b0;
  char local_5a8;
  char *local_5a4;
  char *local_5a0;
  char *local_598;
  int local_590;
  int local_58c;
  int local_588;
  int local_580;
  int local_57c;
  int local_578;
  int local_574;
  uint local_570;
  char local_568 [1280];
  char local_68 [64];
  char local_28 [32];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_598 = s_TextureTiles_008f05cc;
  pcVar3 = local_598;
  do {
    local_598 = pcVar3;
    pcVar3 = local_598 + 1;
  } while (*local_598 != '\0');
  FUN_00780800(0);
  FUN_00774d40();
  builtin_strncpy(s_TextureTiles_008f05cc,"TextureType0",0xd);
  memset(&DAT_02c069d0,0,0x1000);
  memset(local_568,0,0x500);
  memset(&DAT_02c06778,0,0x200);
  _DAT_009454b4 = 0;
  for (local_570 = 0; (int)local_570 < 0x100; local_570 = local_570 + 1) {
    (&DAT_02cd9580)[local_570] =
         (local_570 & 0xff) << 0x10 | 0xff000000 |
         ((int)(local_570 * 0xe0) / 0xff + 0x1fU & 0xff) << 8 |
         (int)(local_570 * 0xc0) / 0xff + 0x3fU & 0xff;
  }
  for (local_570 = 0; (int)local_570 < 0x20; local_570 = local_570 + 1) {
    uVar4 = FUN_008445c0();
    uVar5 = FUN_008445c0();
    uVar6 = FUN_008445c0();
    *(uint *)(&DAT_02cd9500 + local_570 * 4) =
         (uVar4 & 0xff) << 0x10 | 0xff000000 | (uVar5 & 0xff) << 8 | uVar6 & 0xff;
    uVar4 = FUN_008445c0();
    *(uint *)(&DAT_02cd9460 + local_570 * 4) = (uVar4 & 0xff) << 0x10 | 0xff000000;
  }
  _DAT_02cd9138 = FUN_0077d400();
  _DAT_02cd9138 = _DAT_02cd9138 & 0xff;
  for (local_570 = 0; (int)local_570 < 0x100; local_570 = local_570 + 1) {
    (&DAT_02cd9140)[local_570 * 3] = 0xff;
    (&DAT_02cd9141)[local_570 * 3] = 0;
    (&DAT_02cd9142)[local_570 * 3] = 0xff;
  }
  _DAT_009454b4 = _DAT_009454b4 + 1;
  for (local_570 = 0; (int)local_570 < 8; local_570 = local_570 + 1) {
    cVar2 = (char)local_570;
    local_598[-1] = cVar2 + '0';
    for (local_57c = 0; local_57c < 3; local_57c = local_57c + 1) {
      for (local_588 = 0; local_588 < 4; local_588 = local_588 + 1) {
        if (local_57c == 0) {
          local_5b0 = 1;
        }
        else {
          local_5b0 = 8;
        }
        for (local_590 = 0; local_590 < local_5b0; local_590 = local_590 + 1) {
          if (local_57c == 0) {
            sprintf(local_28,"%s%c0",PTR_s_Solid_008f05e0,local_588 + 0x41);
          }
          else {
            sprintf(local_28,"%s%d_%c0",(&PTR_s_Solid_008f05e0)[local_57c],local_590,
                    local_588 + 0x41);
          }
          FUN_00787a30(s_TextureTiles_008f05cc,local_28,&DAT_008a1ad8,
                       &DAT_02c069d0 + _DAT_009454b4 * 0x10,0x10,&DAT_02cc40c0);
          if ((&DAT_02c069d0)[_DAT_009454b4 * 0x10] != '\0') {
            if (local_57c == 0) {
              for (local_58c = local_588; local_58c < 4; local_58c = local_58c + 1) {
                (&DAT_02c06778)[local_58c * 2 + local_570 * 0x48] = DAT_009454b4;
                *(undefined1 *)(local_570 * 0x48 + local_58c * 2 + 0x2c06779) = DAT_009454b4;
              }
            }
            else {
              for (local_58c = local_588; local_58c < 4; local_58c = local_58c + 1) {
                (&DAT_02c06778)[(local_57c >> 1) + local_58c * 2 + local_590 * 8 + local_570 * 0x40]
                     = DAT_009454b4;
              }
            }
            for (local_580 = 0; local_580 < 1; local_580 = local_580 + 1) {
              local_568[_DAT_009454b4 * 5] = cVar2;
              local_5a8 = cVar2;
              if (local_57c != 0) {
                local_5a8 = (char)local_590;
              }
              local_568[_DAT_009454b4 * 5 + 1] = local_5a8;
              local_568[_DAT_009454b4 * 5 + 3] = (char)local_588;
              local_568[_DAT_009454b4 * 5 + 4] = (char)local_57c;
              local_568[_DAT_009454b4 * 5 + 2] = (char)local_580;
              if (local_57c == 0) {
                sprintf(local_28,"%s%c%d",PTR_s_Solid_008f05e0,local_588 + 0x41,local_580);
              }
              else {
                sprintf(local_28,"%s%d_%c%d",(&PTR_s_Solid_008f05e0)[local_57c],local_590,
                        local_588 + 0x41,local_580);
              }
              FUN_00787a30(s_TextureTiles_008f05cc,local_28,&DAT_008a1ad8,
                           &DAT_02c069d0 + _DAT_009454b4 * 0x10,0x10,&DAT_02cc40c0);
              if ((&DAT_02c069d0)[_DAT_009454b4 * 0x10] == '\0') {
                local_5a4 = &DAT_02c069d0 + (_DAT_009454b4 + -1) * 0x10;
                local_5a0 = &DAT_02c069d0 + _DAT_009454b4 * 0x10;
                do {
                  cVar1 = *local_5a4;
                  *local_5a0 = cVar1;
                  local_5a4 = local_5a4 + 1;
                  local_5a0 = local_5a0 + 1;
                } while (cVar1 != '\0');
              }
              if (_DAT_009454b4 < 0xff) {
                _DAT_009454b4 = _DAT_009454b4 + 1;
              }
            }
          }
        }
      }
    }
  }
  uVar7 = FUN_00780db0(1);
  _snprintf(local_68,0x40,"%.2s_DETAIL_ATLAS",uVar7);
  _strupr(local_68);
  FUN_00787a30("Atlases","MaterialName",local_68,local_68,0x40,&DAT_02cc40c0);
  FUN_0077c580(local_68);
  FUN_0077c5d0();
  FUN_0077c650(&DAT_02cd9140,0x100);
  for (local_580 = 0; local_580 < 0x10; local_580 = local_580 + 1) {
    for (local_574 = 0; local_574 < 8; local_574 = local_574 + 1) {
      for (local_578 = 0; local_578 < 8; local_578 = local_578 + 1) {
        pfVar8 = (float *)(&DAT_02c079d0 + local_574 * 0x20 + local_578 * 0x100 + local_580 * 0x800)
        ;
        switch(local_580) {
        case 0:
          *pfVar8 = (float)local_574 * 0.25;
          pfVar8[1] = (float)local_578 * 0.25;
          pfVar8[2] = *pfVar8 + 0.25;
          pfVar8[3] = pfVar8[1];
          pfVar8[4] = *pfVar8 + 0.25;
          pfVar8[5] = pfVar8[1] + 0.25;
          pfVar8[6] = *pfVar8;
          pfVar8[7] = pfVar8[1] + 0.25;
          break;
        case 1:
          *pfVar8 = (float)local_578 * 0.25;
          pfVar8[1] = (float)(4 - local_574) * 0.25;
          pfVar8[2] = *pfVar8;
          pfVar8[3] = pfVar8[1] - 0.25;
          pfVar8[4] = *pfVar8 + 0.25;
          pfVar8[5] = pfVar8[1] - 0.25;
          pfVar8[6] = *pfVar8 + 0.25;
          pfVar8[7] = pfVar8[1];
          break;
        case 2:
          *pfVar8 = (float)(4 - local_574) * 0.25;
          pfVar8[1] = (float)(4 - local_578) * 0.25;
          pfVar8[2] = *pfVar8 - 0.25;
          pfVar8[3] = pfVar8[1];
          pfVar8[4] = *pfVar8 - 0.25;
          pfVar8[5] = pfVar8[1] - 0.25;
          pfVar8[6] = *pfVar8;
          pfVar8[7] = pfVar8[1] - 0.25;
          break;
        case 3:
          *pfVar8 = (float)(4 - local_578) * 0.25;
          pfVar8[1] = (float)local_574 * 0.25;
          pfVar8[2] = *pfVar8;
          pfVar8[3] = pfVar8[1] + 0.25;
          pfVar8[4] = *pfVar8 - 0.25;
          pfVar8[5] = pfVar8[1] + 0.25;
          pfVar8[6] = *pfVar8 - 0.25;
          pfVar8[7] = pfVar8[1];
          break;
        case 4:
          *pfVar8 = (float)(4 - local_574) * 0.25;
          pfVar8[1] = (float)local_578 * 0.25;
          pfVar8[2] = *pfVar8 - 0.25;
          pfVar8[3] = pfVar8[1];
          pfVar8[4] = *pfVar8 - 0.25;
          pfVar8[5] = pfVar8[1] + 0.25;
          pfVar8[6] = *pfVar8;
          pfVar8[7] = pfVar8[1] + 0.25;
          break;
        case 5:
          *pfVar8 = (float)(4 - local_578) * 0.25;
          pfVar8[1] = (float)(4 - local_574) * 0.25;
          pfVar8[2] = *pfVar8;
          pfVar8[3] = pfVar8[1] - 0.25;
          pfVar8[4] = *pfVar8 - 0.25;
          pfVar8[5] = pfVar8[1] - 0.25;
          pfVar8[6] = *pfVar8 - 0.25;
          pfVar8[7] = pfVar8[1];
          break;
        case 6:
          *pfVar8 = (float)local_574 * 0.25;
          pfVar8[1] = (float)(4 - local_578) * 0.25;
          pfVar8[2] = *pfVar8 + 0.25;
          pfVar8[3] = pfVar8[1];
          pfVar8[4] = *pfVar8 + 0.25;
          pfVar8[5] = pfVar8[1] - 0.25;
          pfVar8[6] = *pfVar8;
          pfVar8[7] = pfVar8[1] - 0.25;
          break;
        case 7:
          *pfVar8 = (float)local_578 * 0.25;
          pfVar8[1] = (float)local_574 * 0.25;
          pfVar8[2] = *pfVar8;
          pfVar8[3] = pfVar8[1] + 0.25;
          pfVar8[4] = *pfVar8 + 0.25;
          pfVar8[5] = pfVar8[1] + 0.25;
          pfVar8[6] = *pfVar8 + 0.25;
          pfVar8[7] = pfVar8[1];
          break;
        case 8:
          *pfVar8 = (float)local_574 * 0.25;
          pfVar8[1] = (float)local_578 * 0.25;
          pfVar8[2] = *pfVar8 + 0.25;
          pfVar8[3] = pfVar8[1];
          pfVar8[4] = *pfVar8 + 0.25;
          pfVar8[5] = pfVar8[1] + 0.25;
          pfVar8[6] = *pfVar8;
          pfVar8[7] = pfVar8[1] + 0.25;
          break;
        case 9:
          *pfVar8 = (float)local_578 * 0.25;
          pfVar8[1] = (float)(4 - local_574) * 0.25;
          pfVar8[2] = *pfVar8;
          pfVar8[3] = pfVar8[1] - 0.25;
          pfVar8[4] = *pfVar8 + 0.25;
          pfVar8[5] = pfVar8[1] - 0.25;
          pfVar8[6] = *pfVar8 + 0.25;
          pfVar8[7] = pfVar8[1];
          break;
        case 10:
          *pfVar8 = (float)(4 - local_574) * 0.25;
          pfVar8[1] = (float)(4 - local_578) * 0.25;
          pfVar8[2] = *pfVar8 - 0.25;
          pfVar8[3] = pfVar8[1];
          pfVar8[4] = *pfVar8 - 0.25;
          pfVar8[5] = pfVar8[1] - 0.25;
          pfVar8[6] = *pfVar8;
          pfVar8[7] = pfVar8[1] - 0.25;
          break;
        case 0xb:
          *pfVar8 = (float)(4 - local_578) * 0.25;
          pfVar8[1] = (float)local_574 * 0.25;
          pfVar8[2] = *pfVar8;
          pfVar8[3] = pfVar8[1] + 0.25;
          pfVar8[4] = *pfVar8 - 0.25;
          pfVar8[5] = pfVar8[1] + 0.25;
          pfVar8[6] = *pfVar8 - 0.25;
          pfVar8[7] = pfVar8[1];
          break;
        case 0xc:
          *pfVar8 = (float)(4 - local_578) * 0.25;
          pfVar8[1] = (float)(4 - local_574) * 0.25;
          pfVar8[2] = *pfVar8;
          pfVar8[3] = pfVar8[1] - 0.25;
          pfVar8[4] = *pfVar8 - 0.25;
          pfVar8[5] = pfVar8[1] - 0.25;
          pfVar8[6] = *pfVar8 - 0.25;
          pfVar8[7] = pfVar8[1];
          break;
        case 0xd:
          *pfVar8 = (float)local_574 * 0.25;
          pfVar8[1] = (float)(4 - local_578) * 0.25;
          pfVar8[2] = *pfVar8 + 0.25;
          pfVar8[3] = pfVar8[1];
          pfVar8[4] = *pfVar8 + 0.25;
          pfVar8[5] = pfVar8[1] - 0.25;
          pfVar8[6] = *pfVar8;
          pfVar8[7] = pfVar8[1] - 0.25;
          break;
        case 0xe:
          *pfVar8 = (float)local_578 * 0.25;
          pfVar8[1] = (float)local_574 * 0.25;
          pfVar8[2] = *pfVar8;
          pfVar8[3] = pfVar8[1] + 0.25;
          pfVar8[4] = *pfVar8 + 0.25;
          pfVar8[5] = pfVar8[1] + 0.25;
          pfVar8[6] = *pfVar8 + 0.25;
          pfVar8[7] = pfVar8[1];
          break;
        case 0xf:
          *pfVar8 = (float)(4 - local_574) * 0.25;
          pfVar8[1] = (float)local_578 * 0.25;
          pfVar8[2] = *pfVar8 - 0.25;
          pfVar8[3] = pfVar8[1];
          pfVar8[4] = *pfVar8 - 0.25;
          pfVar8[5] = pfVar8[1] + 0.25;
          pfVar8[6] = *pfVar8;
          pfVar8[7] = pfVar8[1] + 0.25;
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

