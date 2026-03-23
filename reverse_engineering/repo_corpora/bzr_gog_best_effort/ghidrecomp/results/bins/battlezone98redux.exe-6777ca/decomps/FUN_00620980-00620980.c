
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void FUN_00620980(void)

{
  char cVar1;
  short sVar2;
  FILE *_File;
  int iVar3;
  char *local_116c;
  char *local_1168;
  uint local_1160;
  short local_115c;
  char local_1158 [4096];
  char local_158 [256];
  char local_58 [40];
  char local_30 [40];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  DAT_0091886b = 0xb;
  sprintf(local_1158,"%s%s%s",&DAT_02cf0000,&DAT_00871328,"gamekey.map");
  DAT_0091fef8 = 0;
  DAT_0091a454 = local_1158;
  _File = fopen(local_1158,"r");
  if (_File == (FILE *)0x0) {
    FUN_007d6830("gamekey.map error: can\'t open file.");
  }
  else {
    while (iVar3 = FUN_0061e470(local_158,0xff,_File), iVar3 != 0) {
      iVar3 = sscanf(local_158,"%s %s",local_30,local_58);
      if (iVar3 == 2) {
        local_1168 = strtok(local_58,"+");
        if (local_1168 == (char *)0x0) {
          FUN_007d6830("gamekey.map error: line %d, bad sequence.",DAT_0091fef8);
        }
        else {
          local_115c = 0;
          while (local_1168 != (char *)0x0) {
            sVar2 = 0;
            for (local_1160 = 0; local_1160 < 0x59; local_1160 = local_1160 + 1) {
              iVar3 = _stricmp((&PTR_DAT_008eadc0)[local_1160 * 2],local_1168);
              if (iVar3 == 0) {
                sVar2 = *(short *)(&DAT_008eadc4 + local_1160 * 8);
                break;
              }
            }
            if (sVar2 == 0) {
              local_116c = local_1168;
              do {
                cVar1 = *local_116c;
                local_116c = local_116c + 1;
              } while (cVar1 != '\0');
              if ((uint)((int)local_116c - (int)(local_1168 + 1)) < 2) {
                iVar3 = tolower((int)*local_1168);
                local_115c = local_115c + (short)iVar3;
              }
              else {
                FUN_007d6830("gamekey.map error: line %d, not a valid key name.",DAT_0091fef8);
              }
            }
            else {
              local_115c = local_115c + sVar2;
            }
            local_1168 = strtok((char *)0x0,"+");
          }
          local_1160 = 0;
          while ((local_1160 < 0x2c &&
                 (iVar3 = _stricmp((&PTR_s_COCKPIT_VIEW_008eb088)[local_1160 * 2],local_30),
                 iVar3 != 0))) {
            local_1160 = local_1160 + 1;
          }
          if (local_1160 < 0x2c) {
            if (((&DAT_00918850)[local_115c] == '\0') ||
               ((&DAT_00918850)[local_115c] == (&DAT_008eb08c)[local_1160 * 8])) {
              if (local_115c < 0x1001) {
                (&DAT_00918850)[local_115c] = (&DAT_008eb08c)[local_1160 * 8];
              }
            }
            else {
              FUN_007d6830("gamekey.map error: line %d, multiple defines \"%s\".",DAT_0091fef8,
                           local_158);
            }
          }
          else {
            FUN_007d6830("gamekey.map error: line %d, no gamekey %s.",DAT_0091fef8,local_30);
          }
        }
      }
      else {
        FUN_007d6830("gamekey.map error: line %d, read error.",DAT_0091fef8);
      }
    }
    fclose(_File);
  }
  FUN_0083e885();
  return;
}

