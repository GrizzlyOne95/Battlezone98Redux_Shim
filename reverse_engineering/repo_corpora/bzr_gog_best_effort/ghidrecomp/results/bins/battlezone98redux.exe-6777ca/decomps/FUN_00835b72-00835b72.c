
char * FUN_00835b72(int *param_1,char *param_2,char *param_3)

{
  byte bVar1;
  bool bVar2;
  char cVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  undefined4 uVar7;
  
  do {
    while( true ) {
      cVar3 = *param_3;
      if (cVar3 == '\0') {
        return param_2;
      }
      if (cVar3 != '$') break;
      if (param_3[1] == '\0') {
        if (param_2 == (char *)param_1[1]) {
          return param_2;
        }
        return (char *)0x0;
      }
LAB_00835cde:
      pcVar4 = (char *)FUN_008358d9(param_1,param_3);
      if ((param_2 < (char *)param_1[1]) &&
         (iVar5 = FUN_0083619b(*param_2,param_3,pcVar4), iVar5 != 0)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      cVar3 = *pcVar4;
      if (cVar3 == '*') {
        pcVar4 = (char *)FUN_00835f9b(param_1,param_2,param_3,pcVar4);
        return pcVar4;
      }
      if (cVar3 == '+') {
        if (bVar2) {
          pcVar4 = (char *)FUN_00835f9b(param_1,param_2 + 1,param_3,pcVar4);
          return pcVar4;
        }
        return (char *)0x0;
      }
      if (cVar3 == '-') {
        while( true ) {
          pcVar6 = (char *)FUN_00835b72(param_1,param_2,pcVar4 + 1);
          if (pcVar6 != (char *)0x0) {
            return pcVar6;
          }
          if (((char *)param_1[1] <= param_2) ||
             (iVar5 = FUN_0083619b(*param_2,param_3,pcVar4), iVar5 == 0)) break;
          param_2 = param_2 + 1;
        }
        return (char *)0x0;
      }
      if (cVar3 == '?') {
        if ((bVar2) &&
           (pcVar6 = (char *)FUN_00835b72(param_1,param_2 + 1,pcVar4 + 1), pcVar6 != (char *)0x0)) {
          return pcVar6;
        }
        param_3 = pcVar4 + 1;
      }
      else {
        if (!bVar2) {
          return (char *)0x0;
        }
        param_2 = param_2 + 1;
        param_3 = pcVar4;
      }
    }
    if (cVar3 != '%') {
      if (cVar3 == '(') {
        pcVar4 = param_3 + 1;
        if (*pcVar4 == ')') {
          uVar7 = 0xfffffffe;
          pcVar4 = param_3 + 2;
        }
        else {
          uVar7 = 0xffffffff;
        }
        pcVar4 = (char *)FUN_008361e7(param_1,param_2,pcVar4,uVar7);
        return pcVar4;
      }
      if (cVar3 == ')') {
        pcVar4 = (char *)FUN_00835942(param_1,param_2,param_3 + 1);
        return pcVar4;
      }
      goto LAB_00835cde;
    }
    bVar1 = param_3[1];
    if (bVar1 == 0x62) {
      if ((param_3[2] == '\0') || (param_3[3] == '\0')) {
        FUN_0082bc39(param_1[2],"unbalanced pattern");
      }
      pcVar4 = (char *)0x0;
      if (*param_2 != param_3[2]) {
        return (char *)0x0;
      }
      iVar5 = 1;
      do {
        while( true ) {
          pcVar6 = param_2;
          param_2 = pcVar6 + 1;
          if ((char *)param_1[1] <= param_2) goto LAB_00835cc4;
          if (*param_2 == param_3[3]) break;
          if (*param_2 == param_3[2]) {
            iVar5 = iVar5 + 1;
          }
        }
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      pcVar4 = pcVar6 + 2;
LAB_00835cc4:
      if (pcVar4 == (char *)0x0) {
        return (char *)0x0;
      }
      param_3 = param_3 + 4;
      param_2 = pcVar4;
    }
    else if (bVar1 == 0x66) {
      pcVar4 = param_3 + 2;
      if (*pcVar4 != '[') {
        FUN_0082bc39(param_1[2],"missing \'[\' after \'%%f\' in pattern");
      }
      param_3 = (char *)FUN_008358d9(param_1,pcVar4);
      if (param_2 == (char *)*param_1) {
        cVar3 = '\0';
      }
      else {
        cVar3 = param_2[-1];
      }
      iVar5 = FUN_00835f1e(cVar3,pcVar4,param_3 + -1);
      if (iVar5 != 0) {
        return (char *)0x0;
      }
      iVar5 = FUN_00835f1e(*param_2,pcVar4,param_3 + -1);
      if (iVar5 == 0) {
        return (char *)0x0;
      }
    }
    else {
      iVar5 = isdigit((uint)bVar1);
      if (iVar5 == 0) goto LAB_00835cde;
      param_2 = (char *)FUN_00835df5(param_1,param_2,param_3[1]);
      if (param_2 == (char *)0x0) {
        return (char *)0x0;
      }
      param_3 = param_3 + 2;
    }
  } while( true );
}

