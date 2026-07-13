
/* WARNING: Removing unreachable block (ram,0x0061d7cf) */

void FUN_0061d2d0(undefined2 param_1)

{
  int iVar1;
  uint local_10;
  uint local_c;
  uint local_8;
  
  iVar1 = FUN_0061d1e0(param_1);
  if (iVar1 != 0) {
    iVar1 = FUN_00572a70();
    if (iVar1 == 0) {
      iVar1 = FUN_0061d240("bzfree");
      if (iVar1 != 0) {
        *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) ^ 2;
        if ((*(uint *)(DAT_0094672c + 0x30) & 2) == 0) {
          FUN_0049b760(0x3f800000,0x40a00000,0x66,0x66,0x66);
        }
        else {
          DAT_00918430 = 1;
          FUN_0049b760(0x3f800000,0x40a00000,0xff,0xff,0xff);
          FUN_004376c0("suck.wav",0,0);
        }
      }
      iVar1 = FUN_0061d240("bztnt");
      if (iVar1 != 0) {
        *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) ^ 4;
        if ((*(uint *)(DAT_0094672c + 0x30) & 4) == 0) {
          FUN_0049b760(0x3f800000,0x40a00000,0,0x33,0x66);
        }
        else {
          DAT_00918430 = 1;
          FUN_0049b760(0x3f800000,0x40a00000,0,0x80,0xff);
          FUN_004376c0("weapon.wav",0,0);
        }
      }
      iVar1 = FUN_0061d240("bzbody");
      if (iVar1 != 0) {
        *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) ^ 8;
        if ((*(uint *)(DAT_0094672c + 0x30) & 8) == 0) {
          FUN_0049b760(0x3f800000,0x40a00000,0,0x66,0);
        }
        else {
          DAT_00918430 = 1;
          FUN_0049b760(0x3f800000,0x40a00000,0,0xff,0);
          FUN_004376c0("repair.wav",0,0);
        }
      }
      iVar1 = FUN_0061d240("bzview");
      if (iVar1 != 0) {
        *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) ^ 0x100;
        if ((*(uint *)(DAT_0094672c + 0x30) & 0x100) == 0) {
          FUN_0049b760(0x3f800000,0x40a00000,0x66,0x66,0);
        }
        else {
          DAT_00918430 = 1;
          FUN_0049b760(0x3f800000,0x40a00000,0xff,0xff,0);
          FUN_004376c0("mnu_next.wav",0,0);
        }
      }
      iVar1 = FUN_0061d240("bzradar");
      if (iVar1 != 0) {
        *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) ^ 0x200;
        if ((*(uint *)(DAT_0094672c + 0x30) & 0x200) == 0) {
          FUN_0049b760(0x3f800000,0x40a00000,0x66,0,0x66);
        }
        else {
          DAT_00918430 = 1;
          FUN_0049b760(0x3f800000,0x40a00000,0xff,0,0xff);
          FUN_004376c0("ping.wav",0,0);
        }
      }
      iVar1 = FUN_0061d240(&DAT_0088befc);
      if (iVar1 != 0) {
        if (((((*(uint *)(DAT_0094672c + 0x30) & 4) == 0) ||
             ((*(uint *)(DAT_0094672c + 0x30) & 8) == 0)) ||
            ((*(uint *)(DAT_0094672c + 0x30) & 0x200) == 0)) ||
           (((*(uint *)(DAT_0094672c + 0x30) & 0x100) == 0 ||
            ((*(uint *)(DAT_0094672c + 0x30) & 2) == 0)))) {
          *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) | 4;
          *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) | 8;
          *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) | 0x200;
          *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) | 0x100;
          *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) | 2;
        }
        else {
          *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) ^ 4;
          *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) ^ 8;
          *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) ^ 0x200;
          *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) ^ 0x100;
          *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) ^ 2;
        }
        FUN_0049b760(0x3f800000,0x3f000000,0xf4,0xf4,0xf4);
        FUN_004376c0("weapon.wav",0,0);
      }
      iVar1 = FUN_0061d240("bzwinner");
      if (iVar1 != 0) {
        FUN_0045bf70(0);
        DAT_00918430 = 1;
      }
      iVar1 = FUN_0061d240("bzloser");
      if (iVar1 != 0) {
        FUN_0045bf50(0);
      }
      iVar1 = FUN_0061d240("bzquitter");
      if (iVar1 != 0) {
        FUN_00434170(2);
      }
      if (DAT_009183c8 != 0) {
        iVar1 = FUN_0061d240("drawcoll");
        if (iVar1 != 0) {
          FUN_00499ff0();
          DAT_00918430 = 1;
        }
        iVar1 = FUN_0061d240("drawguns");
        if (iVar1 != 0) {
          FUN_00499500();
          DAT_00918430 = 1;
        }
      }
    }
    iVar1 = FUN_0061d240("loggit");
    if (iVar1 != 0) {
      local_8 = (uint)(DAT_009180d8 == 0);
      DAT_009180d8 = local_8;
    }
    iVar1 = FUN_0061d240("pktlog");
    if (iVar1 != 0) {
      local_c = (uint)(DAT_00917f6c == 0);
      DAT_00917f6c = local_c;
    }
    iVar1 = FUN_0061d240(&DAT_0088bf54);
    if (iVar1 != 0) {
      FUN_0049af00();
    }
    iVar1 = FUN_0061d240("waves");
    if (iVar1 != 0) {
      local_10 = (uint)(DAT_009454c8 == 0);
      DAT_009454c8 = local_10;
    }
    iVar1 = FUN_0061d240("level");
    if (iVar1 != 0) {
      *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) ^ 0x10;
      if ((*(uint *)(DAT_0094672c + 0x30) & 0x10) == 0) {
        FUN_0049b760(0x3f800000,0x40a00000,0,0,0);
      }
      else {
        FUN_0049b760(0x3f800000,0x40a00000,0xff,0xd7,0);
        FUN_004376c0("ping.wav",0,0);
      }
    }
    iVar1 = FUN_0061d240(&DAT_0088bf3c);
    if (iVar1 != 0) {
      *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) ^ 0x40;
      if ((*(uint *)(DAT_0094672c + 0x30) & 0x40) == 0) {
        FUN_0049b760(0x3f800000,0x40a00000,0,0,0);
      }
      else {
        FUN_0049b760(0x3f800000,0x40a00000,0xff,0xd7,0);
        FUN_004376c0("ping.wav",0,0);
      }
    }
    iVar1 = FUN_0061d240(&DAT_0088bf38);
    if (iVar1 != 0) {
      *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) ^ 0x20;
      if ((*(uint *)(DAT_0094672c + 0x30) & 0x20) == 0) {
        FUN_0049b760(0x3f800000,0x40a00000,0,0,0);
      }
      else {
        FUN_0049b760(0x3f800000,0x40a00000,0xff,0xd7,0);
        FUN_004376c0("ping.wav",0,0);
      }
    }
  }
  return;
}

