
/* WARNING: Removing unreachable block (ram,0x004fcd00) */

undefined4 FUN_004fc490(char *param_1,int param_2)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  char *pcVar4;
  undefined1 *puVar5;
  undefined4 uVar6;
  int iVar7;
  FILE *_File;
  int *piVar8;
  size_t _Count;
  void *pvVar9;
  char local_94;
  char local_7c;
  char local_6c;
  char local_64;
  char local_4c;
  char local_48;
  char *local_44;
  char *local_40;
  char *local_3c;
  char *local_38;
  char *local_34;
  char *local_30;
  char *local_28;
  char *local_20;
  char *local_14;
  char local_5;
  
  if (param_1 == (char *)0x0) {
    return 0;
  }
  FUN_005cd780();
  DAT_008e80b0 = 1;
  local_14 = (char *)FUN_004fbaf0();
  pcVar4 = (char *)FUN_004fbaf0();
  if (local_14 < pcVar4) {
    local_14 = pcVar4;
  }
  if (local_14 == (char *)0x0) {
    local_38 = param_1;
    local_28 = &DAT_02a13b28;
    do {
      cVar3 = *local_38;
      *local_28 = cVar3;
      local_38 = local_38 + 1;
      local_28 = local_28 + 1;
    } while (cVar3 != '\0');
    local_40 = param_1;
    local_20 = &DAT_00915540;
    do {
      cVar3 = *local_40;
      *local_20 = cVar3;
      local_40 = local_40 + 1;
      local_20 = local_20 + 1;
    } while (cVar3 != '\0');
    puVar5 = (undefined1 *)FUN_004fbaf0();
    if (puVar5 != (undefined1 *)0x0) {
      *puVar5 = 0;
    }
    if (DAT_0091836c != 0) {
      uVar6 = FUN_004fc020();
      return uVar6;
    }
    pcVar4 = (char *)FUN_004fbaf0();
    if ((pcVar4 == (char *)0x0) || (iVar7 = _stricmp(pcVar4,".trn"), iVar7 != 0)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      uVar6 = FUN_004fc020();
      return uVar6;
    }
    bVar1 = true;
    iVar7 = FUN_00829130();
    if (iVar7 == 0) {
      if (param_2 == 0) {
        FUN_007d6830();
      }
      uVar6 = FUN_004fc020();
      return uVar6;
    }
  }
  else {
    local_34 = &DAT_02a13b28;
    local_3c = local_14;
    do {
      local_3c = local_3c + 1;
      cVar3 = *local_3c;
      *local_34 = cVar3;
      local_34 = local_34 + 1;
    } while (cVar3 != '\0');
    local_30 = &DAT_00915540;
    do {
      local_44 = local_14 + 1;
      cVar3 = *local_44;
      *local_30 = cVar3;
      local_30 = local_30 + 1;
      local_14 = local_44;
    } while (cVar3 != '\0');
    puVar5 = (undefined1 *)FUN_004fbaf0();
    if (puVar5 != (undefined1 *)0x0) {
      *puVar5 = 0;
    }
    if (DAT_0091836c != 0) {
      uVar6 = FUN_004fc020();
      return uVar6;
    }
    pcVar4 = (char *)FUN_004fbaf0();
    if ((pcVar4 == (char *)0x0) || (iVar7 = _stricmp(pcVar4,".trn"), iVar7 != 0)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      uVar6 = FUN_004fc020();
      return uVar6;
    }
    bVar1 = false;
    _File = fopen(param_1,"rb");
    if (_File == (FILE *)0x0) {
      if (param_2 == 0) {
        piVar8 = _errno();
        strerror(*piVar8);
        FUN_007d6830();
      }
      uVar6 = FUN_004fc020();
      return uVar6;
    }
    fseek(_File,0,2);
    _Count = ftell(_File);
    fseek(_File,0,0);
    pvVar9 = (void *)FUN_0083d92c();
    fread(pvVar9,1,_Count,_File);
    fclose(_File);
  }
  FUN_004cdd10();
  FUN_007c9cd0();
  DAT_009173b6 = 0;
  local_5 = FUN_004ce910();
  if (local_5 == '\0') {
    uVar6 = 0;
  }
  else if (DAT_00917b20 < 0x7e1) {
    if (DAT_00917b20 == 0x7dc) {
      uVar6 = 0;
    }
    else if (DAT_00917b20 == 0x7dd) {
      uVar6 = 0;
    }
    else {
      if (0x3fe < DAT_00917b20) {
        cVar3 = FUN_004ce5e0();
        if ((cVar3 == '\0') || (local_5 == '\0')) {
          local_64 = '\0';
        }
        else {
          local_64 = '\x01';
        }
        local_5 = local_64;
      }
      if (0x3ff < DAT_00917b20) {
        cVar3 = FUN_004ce2f0();
        if ((cVar3 == '\0') || (local_5 == '\0')) {
          local_48 = '\0';
        }
        else {
          local_48 = '\x01';
        }
        local_5 = local_48;
      }
      FUN_004886e0();
      FUN_0078b9a0();
      cVar3 = FUN_004ce910();
      if ((cVar3 == '\0') || (local_5 == '\0')) {
        local_6c = '\0';
      }
      else {
        local_6c = '\x01';
      }
      local_5 = local_6c;
      if (DAT_00917b20 < 0x3f8) {
        DAT_009173b7 = '\0';
      }
      else {
        cVar3 = FUN_004ce5e0();
        if ((cVar3 == '\0') || (local_6c == '\0')) {
          local_94 = '\0';
        }
        else {
          local_94 = '\x01';
        }
        local_5 = local_94;
      }
      if ((0x406 < DAT_00917b20) && (DAT_009173b7 == '\0')) {
        cVar3 = FUN_004ce910();
        if ((cVar3 == '\0') || (local_5 == '\0')) {
          bVar2 = false;
        }
        else {
          bVar2 = true;
        }
        if (0x409 < DAT_00917b20) {
          cVar3 = FUN_004ce400();
          if ((cVar3 == '\0') || (!bVar2)) {
            bVar2 = false;
          }
          else {
            bVar2 = true;
          }
        }
        iVar7 = FUN_004fd900();
        if ((iVar7 == 0) || (!bVar2)) {
          local_7c = '\0';
        }
        else {
          local_7c = '\x01';
        }
        local_5 = local_7c;
      }
      if (local_5 == '\0') {
        uVar6 = 0;
      }
      else {
        FUN_00482850();
        DAT_0091831c = FUN_004888b0();
        cVar3 = FUN_00488d80();
        if (cVar3 != '\0') {
          FUN_00482850();
          FUN_00764790();
          uVar6 = FUN_0076ea20();
          FUN_004828f0(uVar6);
          FUN_00489dc0();
        }
        if (param_2 == 0) {
          if ((DAT_009173b7 == '\0') && (DAT_00917b20 < 0x40c)) {
            uVar6 = 0;
          }
          else {
            if (0x3ee < DAT_00917b20) {
              local_5 = FUN_004ce2f0();
              if (local_5 == '\0') {
                uVar6 = 0;
                goto LAB_004fd038;
              }
              puVar5 = (undefined1 *)FUN_004fbaf0();
              if (puVar5 != (undefined1 *)0x0) {
                *puVar5 = 0;
              }
            }
            FUN_00780c00();
            FUN_007800c0();
            FUN_00780160();
            iVar7 = FUN_007859d0();
            if ((iVar7 == 0) || (iVar7 = FUN_0077e990(), iVar7 == 0)) {
              uVar6 = 0;
            }
            else {
              FUN_0077ea10();
              FUN_0067e1d0();
              FUN_004b6ec0();
              FUN_007c9cd0();
              if (((DAT_00917b20 < 0x3eb) || (DAT_009173b7 != '\0')) ||
                 (local_5 = FUN_004ceb10(), local_5 != '\0')) {
                cVar3 = FUN_00571c40();
                if (cVar3 == '\0') {
                  FUN_00822de0();
                }
                else {
                  FUN_00822de0();
                }
                FUN_00591c00();
                if ((local_5 == '\0') || (cVar3 = FUN_004dc710(), cVar3 == '\0')) {
                  bVar2 = false;
                }
                else {
                  bVar2 = true;
                }
                FUN_007c9cd0();
                if ((bVar2) && (cVar3 = FUN_005e0bd0(), cVar3 != '\0')) {
                  bVar2 = true;
                }
                else {
                  bVar2 = false;
                }
                DAT_009180d7 = 0;
                if ((bVar2) && (cVar3 = FUN_0045d4b0(), cVar3 != '\0')) {
                  bVar2 = true;
                }
                else {
                  bVar2 = false;
                }
                if ((bVar2) && (cVar3 = FUN_0046f620(), cVar3 != '\0')) {
                  bVar2 = true;
                }
                else {
                  bVar2 = false;
                }
                if ((bVar2) && (cVar3 = FUN_00460670(), cVar3 != '\0')) {
                  local_4c = '\x01';
                }
                else {
                  local_4c = '\0';
                }
                local_5 = local_4c;
                FUN_004cc6f0();
                if (local_4c == '\0') {
                  FUN_004cc780();
                  uVar6 = 0;
                }
                else {
                  if (DAT_009173b7 == '\0') {
                    local_5 = FUN_00461d10();
                  }
                  cVar3 = FUN_005c7510();
                  if ((cVar3 == '\0') || (local_5 == '\0')) {
                    bVar2 = false;
                  }
                  else {
                    bVar2 = true;
                  }
                  cVar3 = FUN_004cc780();
                  if ((cVar3 == '\0') || (!bVar2)) {
                    bVar2 = false;
                  }
                  else {
                    bVar2 = true;
                  }
                  FUN_004d9c90();
                  cVar3 = FUN_00571c40();
                  if (cVar3 == '\0') {
                    FUN_00822de0();
                    FUN_00822a70();
                  }
                  cVar3 = FUN_0045d4f0();
                  if ((cVar3 == '\0') || (!bVar2)) {
                    bVar2 = false;
                  }
                  else {
                    bVar2 = true;
                  }
                  cVar3 = FUN_004dcc90();
                  if ((cVar3 == '\0') || (!bVar2)) {
                    bVar2 = false;
                  }
                  else {
                    bVar2 = true;
                  }
                  cVar3 = operator==<>();
                  if ((cVar3 == '\0') || (!bVar2)) {
                    bVar2 = false;
                  }
                  else {
                    bVar2 = true;
                  }
                  if (DAT_009173b7 == '\0') {
                    cVar3 = FUN_00461ed0();
                    if ((cVar3 == '\0') || (!bVar2)) {
                      bVar2 = false;
                    }
                    else {
                      bVar2 = true;
                    }
                  }
                  cVar3 = FUN_005c7a50();
                  if ((cVar3 == '\0') || (!bVar2)) {
                    bVar2 = false;
                  }
                  else {
                    bVar2 = true;
                  }
                  if (bVar2) {
                    uVar6 = 1;
                  }
                  else {
                    uVar6 = 0;
                  }
                }
              }
              else {
                uVar6 = 0;
              }
            }
          }
        }
        else {
          uVar6 = 1;
        }
      }
    }
  }
  else {
    uVar6 = 0;
  }
LAB_004fd038:
  pvVar9 = (void *)FUN_004cdd70();
  if (bVar1) {
    FUN_0062f240();
  }
  else {
    operator_delete__(pvVar9);
  }
  return uVar6;
}

