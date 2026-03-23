
void FUN_00835411(undefined4 param_1)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  float10 fVar9;
  int local_434;
  uint local_430;
  char *local_42c;
  char *local_428 [131];
  char local_21c [512];
  char local_1c [20];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar3 = FUN_0082c8f6();
  iVar8 = 1;
  pcVar4 = (char *)FUN_0082ba59(param_1,1,&local_434);
  local_42c = pcVar4 + local_434;
  FUN_0082b98a(param_1,local_428);
LAB_008355ed:
  do {
    if (local_42c <= pcVar4) {
      FUN_0082c2cb();
LAB_00835609:
      FUN_0083e885();
      return;
    }
    if ((*pcVar4 == '%') && (pcVar4 = pcVar4 + 1, *pcVar4 != '%')) {
      iVar8 = iVar8 + 1;
      if (iVar3 < iVar8) {
        FUN_0082b8e4(param_1,iVar8);
      }
      pcVar5 = (char *)FUN_008360d9(param_1);
      iVar6 = (int)*pcVar5;
      pcVar4 = pcVar5 + 1;
      if (iVar6 < 0x6a) {
        if (iVar6 == 0x69) {
LAB_0083552b:
          pcVar5 = local_1c;
          pcVar1 = local_1c + 1;
          do {
            cVar2 = *pcVar5;
            pcVar5 = pcVar5 + 1;
          } while (cVar2 != '\0');
          cVar2 = pcVar5[(int)(local_21c + (0x1ff - (int)pcVar1))];
          (pcVar5 + (int)(local_21c + (0x1ff - (int)pcVar1)))[0] = 'l';
          (pcVar5 + (int)(local_21c + (0x1ff - (int)pcVar1)))[1] = '\0';
          pcVar5[(int)(local_1c + -(int)pcVar1)] = cVar2;
          pcVar5[(int)(local_1c + (1 - (int)pcVar1))] = '\0';
LAB_0083554f:
          FUN_0082ba89(param_1);
          uVar7 = FUN_0083f040();
          goto LAB_008355af;
        }
        if ((iVar6 != 0x45) && (iVar6 != 0x47)) {
          if (iVar6 == 0x58) goto LAB_0083557f;
          if (iVar6 == 99) goto LAB_0083554f;
          if (iVar6 == 100) goto LAB_0083552b;
          if (2 < iVar6 - 0x65U) goto LAB_00835691;
        }
        fVar9 = (float10)FUN_0082ba89(param_1,iVar8);
        sprintf(local_21c,local_1c,(double)fVar9);
      }
      else {
        if (iVar6 != 0x6f) {
          if (iVar6 == 0x71) {
            FUN_00835822(param_1,local_428);
            goto LAB_008355ed;
          }
          if (iVar6 == 0x73) {
            FUN_0082ba59(param_1,iVar8);
            pcVar5 = strchr(local_1c,0x2e);
            if ((pcVar5 != (char *)0x0) || (local_430 < 100)) {
              sprintf(local_21c,local_1c);
              goto LAB_008355c4;
            }
            FUN_0082cdd2(param_1);
            FUN_0082b87b(local_428);
            goto LAB_008355ed;
          }
          if ((iVar6 != 0x75) && (iVar6 != 0x78)) {
LAB_00835691:
            FUN_0082bc39(param_1,"invalid option \'%%%c\' to \'format\'",(int)*pcVar5);
            goto LAB_00835609;
          }
        }
LAB_0083557f:
        pcVar5 = local_1c;
        pcVar1 = local_1c + 1;
        do {
          cVar2 = *pcVar5;
          pcVar5 = pcVar5 + 1;
        } while (cVar2 != '\0');
        cVar2 = pcVar5[(int)(local_21c + (0x1ff - (int)pcVar1))];
        (pcVar5 + (int)(local_21c + (0x1ff - (int)pcVar1)))[0] = 'l';
        (pcVar5 + (int)(local_21c + (0x1ff - (int)pcVar1)))[1] = '\0';
        pcVar5[(int)(local_1c + -(int)pcVar1)] = cVar2;
        pcVar5[(int)(local_1c + (1 - (int)pcVar1))] = '\0';
        FUN_0082ba89(CONCAT44(iVar8,param_1));
        uVar7 = FUN_0083f076();
LAB_008355af:
        sprintf(local_21c,local_1c,uVar7);
      }
LAB_008355c4:
      pcVar5 = local_21c;
      do {
        cVar2 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar2 != '\0');
      FUN_0082b81b(local_428,local_21c);
      goto LAB_008355ed;
    }
    if (local_21c <= local_428[0]) {
      FUN_0082c2ac();
    }
    *local_428[0] = *pcVar4;
    local_428[0] = local_428[0] + 1;
    pcVar4 = pcVar4 + 1;
  } while( true );
}

