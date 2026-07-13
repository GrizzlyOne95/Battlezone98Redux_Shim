/*
 * Entry: 005c03f7
 * Name: match
 * Namespace: Global
 * Signature: char * match(MatchState * param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl match(MatchState *param_1,char *param_2,char *param_3)

{
  char cVar1;
  byte bVar2;
  bool bVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  int unaff_EBX;
  MatchState *pMVar7;
  char *unaff_ESI;
  MatchState *unaff_EDI;
  
LAB_005c0401:
  while( true ) {
    cVar1 = *param_3;
    if (cVar1 == '\0') {
      return (char *)(MatchState *)param_2;
    }
    if (cVar1 == '$') break;
    if (cVar1 != '%') {
      if (cVar1 == '(') {
        pMVar7 = (MatchState *)(param_3 + 1);
        if (*(char *)&pMVar7->src_init == ')') {
          pcVar4 = (char *)0xfffffffe;
          pMVar7 = (MatchState *)(param_3 + 2);
        }
        else {
          pcVar4 = (char *)0xffffffff;
        }
        pcVar4 = start_capture(pMVar7,pcVar4,(char *)unaff_EDI,(int)unaff_ESI);
        return pcVar4;
      }
      if (cVar1 == ')') {
        pcVar4 = end_capture((MatchState *)param_2,param_3 + 1,(char *)unaff_EDI);
        return pcVar4;
      }
      goto LAB_005c055f;
    }
    bVar2 = param_3[1];
    if (bVar2 == 0x62) {
      if ((param_3[2] == '\0') || (param_3[3] == '\0')) {
        luaL_error(param_1->L,"unbalanced pattern");
      }
      if (*(char *)&((MatchState *)param_2)->src_init != param_3[2]) {
        return (char *)0x0;
      }
      iVar5 = 1;
      do {
        while( true ) {
          pMVar7 = (MatchState *)param_2;
          param_2 = (char *)((int)&pMVar7->src_init + 1);
          if ((MatchState *)param_1->src_end <= param_2) {
            param_2 = (char *)0x0;
            goto LAB_005c0542;
          }
          if (*(char *)&((MatchState *)param_2)->src_init == param_3[3]) break;
          if (*(char *)&((MatchState *)param_2)->src_init == param_3[2]) {
            iVar5 = iVar5 + 1;
          }
        }
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      param_2 = (char *)((int)&pMVar7->src_init + 2);
LAB_005c0542:
      if ((MatchState *)param_2 == (MatchState *)0x0) {
        return (char *)0x0;
      }
      param_3 = param_3 + 4;
    }
    else if (bVar2 == 0x66) {
      if (param_3[2] != '[') {
        luaL_error(param_1->L,"missing \'[\' after \'%%f\' in pattern");
      }
      param_3 = classend(unaff_EDI,unaff_ESI);
      iVar5 = matchbracketclass((int)(param_3 + -1),(char *)unaff_EDI,unaff_ESI);
      if (iVar5 != 0) {
        return (char *)0x0;
      }
      iVar5 = matchbracketclass((int)(param_3 + -1),(char *)unaff_EDI,unaff_ESI);
      if (iVar5 == 0) {
        return (char *)0x0;
      }
    }
    else {
      iVar5 = isdigit((uint)bVar2);
      if (iVar5 == 0) goto LAB_005c055f;
      param_2 = match_capture(unaff_EDI,unaff_ESI,unaff_EBX);
      if ((MatchState *)param_2 == (MatchState *)0x0) {
        return (char *)0x0;
      }
      param_3 = param_3 + 2;
    }
  }
  if (param_3[1] == '\0') {
    return (char *)(~-(uint)((MatchState *)param_2 != (MatchState *)param_1->src_end) &
                   (uint)param_2);
  }
LAB_005c055f:
  pcVar4 = classend(unaff_EDI,unaff_ESI);
  if ((param_2 < (MatchState *)param_1->src_end) &&
     (iVar5 = singlematch((int)pcVar4,(char *)unaff_EDI,unaff_ESI), iVar5 != 0)) {
    bVar3 = true;
  }
  else {
    bVar3 = false;
  }
  cVar1 = *pcVar4;
  if (cVar1 != '*') {
    if (cVar1 != '+') {
      if (cVar1 == '-') {
        while( true ) {
          pcVar6 = match(param_1,param_2,pcVar4 + 1);
          if (pcVar6 != (char *)0x0) {
            return pcVar6;
          }
          if (((MatchState *)param_1->src_end <= param_2) ||
             (iVar5 = singlematch((int)pcVar4,(char *)unaff_EDI,unaff_ESI), iVar5 == 0)) break;
          param_2 = (char *)((int)&((MatchState *)param_2)->src_init + 1);
        }
        return (char *)0x0;
      }
      if (cVar1 == '?') {
        if ((bVar3) &&
           (pcVar6 = match(param_1,(char *)((int)&((MatchState *)param_2)->src_init + 1),pcVar4 + 1)
           , pcVar6 != (char *)0x0)) {
          return pcVar6;
        }
        param_3 = pcVar4 + 1;
      }
      else {
        if (!bVar3) {
          return (char *)0x0;
        }
        param_2 = (char *)((int)&((MatchState *)param_2)->src_init + 1);
        param_3 = pcVar4;
      }
      goto LAB_005c0401;
    }
    if (!bVar3) {
      return (char *)0x0;
    }
  }
  pcVar4 = max_expand(param_1,param_3,pcVar4,(char *)unaff_EDI);
  return pcVar4;
}
