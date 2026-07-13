/*
 * Entry: 005bdafd
 * Name: read_numeral
 * Namespace: Global
 * Signature: void read_numeral(LexState * param_1, SemInfo * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl read_numeral(LexState *param_1,SemInfo *param_2)

{
  byte *pbVar1;
  uint *in_EAX;
  uint uVar2;
  int iVar3;
  char *unaff_EBX;
  SemInfo *unaff_ESI;
  char cVar4;
  
  do {
    save((LexState *)*in_EAX,(int)unaff_EBX);
    iVar3 = *(int *)in_EAX[0xe];
    *(int *)in_EAX[0xe] = iVar3 + -1;
    if (iVar3 == 0) {
      uVar2 = luaZ_fill((Zio *)in_EAX[0xe]);
    }
    else {
      pbVar1 = *(byte **)(in_EAX[0xe] + 4);
      uVar2 = (uint)*pbVar1;
      *(byte **)(in_EAX[0xe] + 4) = pbVar1 + 1;
    }
    *in_EAX = uVar2;
    iVar3 = isdigit(uVar2);
  } while ((iVar3 != 0) || (*in_EAX == 0x2e));
  iVar3 = check_next((LexState *)"Ee",unaff_EBX);
  if (iVar3 != 0) {
    check_next((LexState *)"+-",unaff_EBX);
  }
  while( true ) {
    iVar3 = isalnum(*in_EAX);
    if ((iVar3 == 0) && (*in_EAX != 0x5f)) break;
    save((LexState *)*in_EAX,(int)unaff_EBX);
    iVar3 = *(int *)in_EAX[0xe];
    *(int *)in_EAX[0xe] = iVar3 + -1;
    if (iVar3 == 0) {
      uVar2 = luaZ_fill((Zio *)in_EAX[0xe]);
    }
    else {
      pbVar1 = *(byte **)(in_EAX[0xe] + 4);
      uVar2 = (uint)*pbVar1;
      *(byte **)(in_EAX[0xe] + 4) = pbVar1 + 1;
    }
    *in_EAX = uVar2;
  }
  cVar4 = '\0';
  save((LexState *)0x0,(int)unaff_EBX);
  buffreplace((LexState *)0x2e,(char)in_EAX[0x11],cVar4);
  iVar3 = luaO_str2d(*(char **)in_EAX[0xf],(double *)param_1);
  if (iVar3 == 0) {
    trydecpoint(param_1,unaff_ESI);
  }
  return;
}
