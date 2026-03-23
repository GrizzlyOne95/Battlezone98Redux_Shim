
/* WARNING: Removing unreachable block (ram,0x006208b5) */

void FUN_00620010(void)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  FILE *pFVar4;
  char *pcVar5;
  uint uVar6;
  char *pcVar7;
  bool bVar8;
  uint local_2a0;
  uint local_294;
  char *local_290;
  char *local_28c;
  char *local_288;
  char *local_284;
  char *local_280;
  char *local_27c;
  byte *local_278;
  char *local_274;
  char *local_270;
  char *local_26c;
  char *local_268;
  char *local_264;
  char *local_260;
  byte *local_25c;
  char *local_258;
  char *local_254;
  byte *local_250;
  char *local_24c;
  byte *local_248;
  char *local_244;
  char *local_240;
  char *local_23c;
  char *local_238;
  char *local_234;
  char *local_230;
  int local_22c;
  FILE *local_210;
  char local_20c [259];
  char cStack_109;
  char local_108 [256];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_274 = "input.map";
  if (DAT_0091a448 == 0) {
    DAT_0091a360 = FUN_00434530();
    DAT_0091a448 = 1;
  }
  iVar3 = FUN_004344a0();
  if (iVar3 == 2) {
    local_274 = "inputmbl.map";
  }
  sprintf(local_20c,"%s%s%s",&DAT_02cf2000,&DAT_00871328,local_274);
  local_210 = fopen(local_20c,"r");
  if (local_210 == (FILE *)0x0) {
    sprintf(local_20c,"%s%s%s",&DAT_02cf0000,&DAT_00871328,local_274);
    local_210 = fopen(local_20c,"r");
  }
  if (local_210 == (FILE *)0x0) {
    FUN_007d6830("%s: can\'t open file.",local_274);
  }
  else {
    DAT_0091fef8 = 0;
    DAT_0091a454 = local_20c;
    FUN_0061fb20(local_210);
    fclose(local_210);
    for (local_22c = 0; local_22c < DAT_0091a364; local_22c = local_22c + 1) {
      if ((&DAT_0091a434)[local_22c] != 0) {
        local_28c = &DAT_02cf0000;
        local_27c = local_108;
        do {
          cVar1 = *local_28c;
          *local_27c = cVar1;
          local_28c = local_28c + 1;
          local_27c = local_27c + 1;
        } while (cVar1 != '\0');
        local_24c = &cStack_109;
        do {
          pcVar5 = local_24c + 1;
          local_24c = local_24c + 1;
        } while (*pcVar5 != '\0');
        local_24c[0] = '\\';
        local_24c[1] = '\0';
        pcVar5 = &cStack_109;
        do {
          local_288 = pcVar5;
          pcVar5 = local_288 + 1;
        } while (local_288[1] != '\0');
        builtin_strncpy(local_288 + 1,"giddi",6);
        local_284 = &cStack_109;
        do {
          pcVar5 = local_284 + 1;
          local_284 = local_284 + 1;
        } while (*pcVar5 != '\0');
        local_284[0] = '\\';
        local_284[1] = '\0';
        pcVar5 = &DAT_0091a368 + local_22c * 0x28;
        local_238 = pcVar5;
        do {
          cVar1 = *local_238;
          local_238 = local_238 + 1;
        } while (cVar1 != '\0');
        local_254 = &cStack_109;
        do {
          pcVar7 = local_254 + 1;
          local_254 = local_254 + 1;
        } while (*pcVar7 != '\0');
        pcVar7 = pcVar5;
        for (uVar6 = (uint)((int)local_238 - (int)pcVar5) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined4 *)local_254 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          local_254 = local_254 + 4;
        }
        for (uVar6 = (int)local_238 - (int)pcVar5 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *local_254 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          local_254 = local_254 + 1;
        }
        while( true ) {
          pcVar5 = local_108;
          do {
            local_240 = pcVar5;
            pcVar5 = local_240 + 1;
          } while (*local_240 != '\0');
          iVar3 = isdigit((int)local_240[-1]);
          if (iVar3 == 0) break;
          local_234 = local_108;
          do {
            cVar1 = *local_234;
            local_234 = local_234 + 1;
          } while (cVar1 != '\0');
          if ((char *)0xfe < local_234 + (-1 - (int)(local_108 + 1))) {
            ___report_rangecheckfailure();
          }
          (&cStack_109)[(int)(local_234 + (-1 - (int)(local_108 + 1)) + 1)] = '\0';
        }
        pcVar5 = &cStack_109;
        do {
          local_244 = pcVar5;
          pcVar5 = local_244 + 1;
        } while (local_244[1] != '\0');
        builtin_strncpy(local_244 + 1,".std",5);
        pFVar4 = fopen(local_108,"r");
        if (pFVar4 != (FILE *)0x0) {
          DAT_0091fef8 = 0;
          DAT_0091a454 = local_108;
          FUN_0061fb20(pFVar4);
          fclose(pFVar4);
        }
      }
    }
    local_278 = &DAT_00874be8;
    local_25c = &DAT_008ead70;
    do {
      bVar2 = *local_25c;
      bVar8 = bVar2 < *local_278;
      if (bVar2 != *local_278) {
LAB_00620560:
        local_294 = -(uint)bVar8 | 1;
        goto LAB_0062056b;
      }
      if (bVar2 == 0) break;
      bVar2 = local_25c[1];
      bVar8 = bVar2 < local_278[1];
      if (bVar2 != local_278[1]) goto LAB_00620560;
      local_25c = local_25c + 2;
      local_278 = local_278 + 2;
    } while (bVar2 != 0);
    local_294 = 0;
LAB_0062056b:
    if (local_294 != 0) {
      local_290 = &DAT_02cf0000;
      local_264 = local_108;
      do {
        cVar1 = *local_290;
        *local_264 = cVar1;
        local_290 = local_290 + 1;
        local_264 = local_264 + 1;
      } while (cVar1 != '\0');
      local_280 = &cStack_109;
      do {
        pcVar5 = local_280 + 1;
        local_280 = local_280 + 1;
      } while (*pcVar5 != '\0');
      local_280[0] = '\\';
      local_280[1] = '\0';
      builtin_strncpy(local_108,"giddi",6);
      local_26c = &cStack_109;
      do {
        pcVar5 = local_26c + 1;
        local_26c = local_26c + 1;
      } while (*pcVar5 != '\0');
      local_26c[0] = '\\';
      local_26c[1] = '\0';
      local_250 = &DAT_0088cb1c;
      local_248 = &DAT_008ead70;
      do {
        bVar2 = *local_248;
        bVar8 = bVar2 < *local_250;
        if (bVar2 != *local_250) {
LAB_006206f6:
          local_2a0 = -(uint)bVar8 | 1;
          goto LAB_00620701;
        }
        if (bVar2 == 0) break;
        bVar2 = local_248[1];
        bVar8 = bVar2 < local_250[1];
        if (bVar2 != local_250[1]) goto LAB_006206f6;
        local_248 = local_248 + 2;
        local_250 = local_250 + 2;
      } while (bVar2 != 0);
      local_2a0 = 0;
LAB_00620701:
      if (local_2a0 == 0) {
        if (DAT_0091a360 == 0) {
          pcVar5 = &cStack_109;
          do {
            local_260 = pcVar5;
            pcVar5 = local_260 + 1;
          } while (local_260[1] != '\0');
          builtin_strncpy(local_260 + 1,"xbox",5);
        }
        else {
          local_23c = &DAT_008ead70;
          pcVar5 = local_23c;
          do {
            local_23c = pcVar5;
            pcVar5 = local_23c + 1;
          } while (*local_23c != '\0');
          local_258 = &cStack_109;
          do {
            pcVar5 = local_258 + 1;
            local_258 = local_258 + 1;
          } while (*pcVar5 != '\0');
          pcVar5 = &DAT_008ead70;
          for (uVar6 = (uint)(local_23c + -0x8ead6f) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
            *(undefined4 *)local_258 = *(undefined4 *)pcVar5;
            pcVar5 = pcVar5 + 4;
            local_258 = local_258 + 4;
          }
          for (uVar6 = (uint)(local_23c + -0x8ead6f) & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *local_258 = *pcVar5;
            pcVar5 = pcVar5 + 1;
            local_258 = local_258 + 1;
          }
        }
      }
      else {
        local_230 = &DAT_008ead70;
        pcVar5 = local_230;
        do {
          local_230 = pcVar5;
          pcVar5 = local_230 + 1;
        } while (*local_230 != '\0');
        local_268 = &cStack_109;
        do {
          pcVar5 = local_268 + 1;
          local_268 = local_268 + 1;
        } while (*pcVar5 != '\0');
        pcVar5 = &DAT_008ead70;
        for (uVar6 = (uint)(local_230 + -0x8ead6f) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined4 *)local_268 = *(undefined4 *)pcVar5;
          pcVar5 = pcVar5 + 4;
          local_268 = local_268 + 4;
        }
        for (uVar6 = (uint)(local_230 + -0x8ead6f) & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *local_268 = *pcVar5;
          pcVar5 = pcVar5 + 1;
          local_268 = local_268 + 1;
        }
      }
      pcVar5 = &cStack_109;
      do {
        local_270 = pcVar5;
        pcVar5 = local_270 + 1;
      } while (local_270[1] != '\0');
      builtin_strncpy(local_270 + 1,".std",5);
      pFVar4 = fopen(local_108,"r");
      if (pFVar4 != (FILE *)0x0) {
        DAT_0091fef8 = 0;
        DAT_0091a454 = local_108;
        FUN_0061fb20(pFVar4);
        fclose(pFVar4);
      }
      DAT_0091a454 = (char *)0x0;
    }
  }
  FUN_0083e885();
  return;
}

