
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00786340(void)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  short *psVar7;
  FILE *_File;
  size_t sVar8;
  char *local_20e8;
  char *local_20d8;
  char *local_20d4;
  char *local_20cc;
  undefined4 *local_20c8;
  undefined4 *local_20c4;
  char *local_20c0;
  undefined4 *local_20b8;
  undefined4 *local_20b4;
  undefined4 *local_20b0;
  char *local_20ac;
  char *local_2094;
  undefined1 local_208c [4];
  char local_2088 [4];
  undefined1 local_2084 [4091];
  undefined4 uStack_1089;
  undefined1 local_1084 [4091];
  undefined4 uStack_89;
  undefined1 auStack_84 [124];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  DAT_02c319e0 = 0;
  local_20d8 = (char *)&DAT_02cc40c0;
  local_20c0 = local_2088;
  do {
    cVar1 = *local_20d8;
    *local_20c0 = cVar1;
    local_20d8 = local_20d8 + 1;
    local_20c0 = local_20c0 + 1;
  } while (cVar1 != '\0');
  local_208c = (undefined1  [4])strrchr(local_2088,0x2e);
  if (local_208c != (undefined1  [4])0x0) {
    *(char *)local_208c = '\0';
  }
  if ((&stack0x00000000 != (undefined1 *)0x2088) && (local_2088[0] != '\0')) {
    puVar2 = (undefined4 *)(local_208c + 3);
    do {
      local_20c4 = puVar2;
      puVar2 = (undefined4 *)((int)local_20c4 + 1);
    } while (*(char *)((int)local_20c4 + 1) != '\0');
    *(undefined4 *)((int)local_20c4 + 1) = 0x3267682e;
    *(undefined1 *)((int)local_20c4 + 5) = 0;
    local_20e8 = local_2088;
    local_20cc = (char *)((int)&uStack_89 + 1);
    do {
      cVar1 = *local_20e8;
      *local_20cc = cVar1;
      local_20e8 = local_20e8 + 1;
      local_20cc = local_20cc + 1;
    } while (cVar1 != '\0');
    local_208c = (undefined1  [4])strrchr((char *)&DAT_02cc40c0,0x2e);
    if (local_208c != (undefined1  [4])0x0) {
      *(char *)local_208c = '\0';
    }
    local_20b0 = (undefined4 *)&DAT_02cc40bf;
    puVar2 = local_20b0;
    do {
      local_20b0 = puVar2;
      puVar2 = (undefined4 *)((int)local_20b0 + 1);
    } while (*(char *)((int)local_20b0 + 1) != '\0');
    *(undefined4 *)((int)local_20b0 + 1) = 0x6e72742e;
    *(undefined1 *)((int)local_20b0 + 5) = 0;
    iVar3 = FUN_00787ac0(&DAT_0089d064,"Width",0xffffffff,&DAT_02cc40c0);
    iVar4 = FUN_00787ac0(&DAT_0089d064,"Depth",0xffffffff,&DAT_02cc40c0);
    iVar5 = FUN_00787ac0(&DAT_0089d064,&DAT_0089d604,0xffffffff,&DAT_02cc40c0);
    iVar6 = FUN_00787ac0(&DAT_0089d064,&DAT_0089d6c0,0xffffffff,&DAT_02cc40c0);
    if ((((-1 < iVar3) && (-1 < iVar4)) && (-1 < iVar5)) && (-1 < iVar6)) {
      _DAT_02cc40a8 = (int)((float)iVar3 * 0.1) >> 7;
      _DAT_02cc40b4 = (int)((float)iVar4 * 0.1) >> 7;
      DAT_02cc40b0 = (int)((float)iVar5 * 0.1) >> 7;
      DAT_02cc40ac = (int)((float)iVar6 * 0.1) >> 7;
      if (((((0 < (int)_DAT_02cc40a8) && (0 < (int)_DAT_02cc40b4)) &&
           ((-1 < DAT_02cc40b0 && ((-1 < DAT_02cc40ac && (iVar4 == _DAT_02cc40b4 * 0x500)))))) &&
          (iVar3 == _DAT_02cc40a8 * 0x500)) &&
         ((iVar5 == DAT_02cc40b0 * 0x500 && (iVar6 == DAT_02cc40ac * 0x500)))) {
        FUN_0067dc90(_DAT_02cc40a8,_DAT_02cc40b4);
        FUN_0077c550(_DAT_02cc40a8,_DAT_02cc40b4,(float)iVar5,(float)iVar6);
        DAT_02c319e0 = _DAT_02cc40a8 * _DAT_02cc40b4;
        DAT_02c319d8 = (short *)FUN_00829130((int)&uStack_89 + 1,&DAT_02c319dc);
        if ((DAT_02c319d8 != (short *)0x0) &&
           ((((DAT_02c319dc < 0xd || (*DAT_02c319d8 != 1)) ||
             ((ushort)DAT_02c319d8[3] != _DAT_02cc40b4)) ||
            ((((ushort)DAT_02c319d8[2] != _DAT_02cc40a8 || (DAT_02c319d8[1] != 8)) ||
             (*(uint *)(DAT_02c319d8 + 4) < 10)))))) {
          FUN_0062f240(DAT_02c319d8);
          DAT_02c319d8 = (short *)0x0;
          DAT_02c319dc = 0;
        }
        if (DAT_02c319d8 == (short *)0x0) {
          local_208c = (undefined1  [4])strrchr((char *)((int)&uStack_89 + 1),0x2e);
          if (local_208c != (undefined1  [4])0x0) {
            *(char *)local_208c = '\0';
          }
          puVar2 = &uStack_89;
          do {
            local_20b8 = puVar2;
            puVar2 = (undefined4 *)((int)local_20b8 + 1);
          } while (*(char *)((int)local_20b8 + 1) != '\0');
          *(undefined4 *)((int)local_20b8 + 1) = 0x5447482e;
          *(undefined1 *)((int)local_20b8 + 5) = 0;
          DAT_02c319d8 = (short *)FUN_00829130((int)&uStack_89 + 1,&DAT_02c319dc);
          if (DAT_02c319d8 != (short *)0x0) {
            psVar7 = malloc(DAT_02c319dc * 4 + 0xc);
            FUN_00786200(psVar7 + 6,DAT_02c319d8,_DAT_02cc40a8,_DAT_02cc40b4);
            *psVar7 = 1;
            psVar7[3] = DAT_02cc40b4;
            psVar7[2] = DAT_02cc40a8;
            psVar7[1] = 8;
            psVar7[4] = 10;
            psVar7[5] = 0;
            FUN_0062f240(DAT_02c319d8);
            DAT_02c319dc = DAT_02c319dc * 4 + 0xc;
            DAT_02c319d8 = psVar7;
            sprintf((char *)((int)&uStack_1089 + 1),"%s%s%s",&DAT_02cf3000,&DAT_00871328,
                    (int)&uStack_89 + 1);
            local_208c = (undefined1  [4])strrchr((char *)((int)&uStack_1089 + 1),0x5c);
            if (local_208c == (undefined1  [4])0x0) {
              local_208c = (undefined1  [4])((int)&uStack_1089 + 1);
            }
            local_2094 = strrchr((char *)((int)&uStack_1089 + 1),0x2f);
            if (local_2094 == (char *)0x0) {
              local_2094 = (char *)((int)&uStack_1089 + 1);
            }
            if ((uint)local_208c < local_2094) {
              local_208c = (undefined1  [4])local_2094;
            }
            local_208c = (undefined1  [4])strrchr((char *)local_208c,0x2e);
            if (local_208c != (undefined1  [4])0x0) {
              *(char *)local_208c = '\0';
            }
            puVar2 = &uStack_1089;
            do {
              local_20c8 = puVar2;
              puVar2 = (undefined4 *)((int)local_20c8 + 1);
            } while (*(char *)((int)local_20c8 + 1) != '\0');
            *(undefined4 *)((int)local_20c8 + 1) = 0x3267682e;
            *(undefined1 *)((int)local_20c8 + 5) = 0;
            _File = fopen((char *)((int)&uStack_1089 + 1),"wb");
            if (_File == (FILE *)0x0) {
              iVar3 = FUN_007d6950("Can\'t open file %s",(int)&uStack_89 + 1);
              if (iVar3 == 0) goto LAB_00786c67;
            }
            else {
              sVar8 = fwrite(DAT_02c319d8,1,DAT_02c319dc,_File);
              if ((sVar8 != DAT_02c319dc) &&
                 (iVar3 = FUN_007d6950("Can\'t write file %s",(int)&uStack_1089 + 1), iVar3 == 0))
              goto LAB_00786c67;
              fclose(_File);
            }
          }
        }
        local_20d4 = (char *)((int)&uStack_89 + 1);
        local_20ac = (char *)((int)&uStack_1089 + 1);
        do {
          cVar1 = *local_20d4;
          *local_20ac = cVar1;
          local_20d4 = local_20d4 + 1;
          local_20ac = local_20ac + 1;
        } while (cVar1 != '\0');
        local_208c = (undefined1  [4])strrchr((char *)((int)&uStack_1089 + 1),0x5c);
        if (local_208c == (undefined1  [4])0x0) {
          local_208c = (undefined1  [4])((int)&uStack_1089 + 1);
        }
        local_2094 = strrchr((char *)((int)&uStack_1089 + 1),0x2f);
        if (local_2094 == (char *)0x0) {
          local_2094 = (char *)((int)&uStack_1089 + 1);
        }
        if ((uint)local_208c < local_2094) {
          local_208c = (undefined1  [4])local_2094;
        }
        local_208c = (undefined1  [4])strrchr((char *)local_208c,0x2e);
        if (local_208c != (undefined1  [4])0x0) {
          *(char *)local_208c = '\0';
        }
        puVar2 = &uStack_1089;
        do {
          local_20b4 = puVar2;
          puVar2 = (undefined4 *)((int)local_20b4 + 1);
        } while (*(char *)((int)local_20b4 + 1) != '\0');
        *(undefined4 *)((int)local_20b4 + 1) = 0x74616d2e;
        *(undefined1 *)((int)local_20b4 + 5) = 0;
        DAT_02c319d0 = FUN_00829130((int)&uStack_1089 + 1,&DAT_02c319d4);
      }
    }
  }
LAB_00786c67:
  FUN_0083e885();
  return;
}

