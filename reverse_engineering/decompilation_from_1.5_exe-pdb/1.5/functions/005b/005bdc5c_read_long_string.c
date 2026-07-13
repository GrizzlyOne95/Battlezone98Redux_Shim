/*
 * Entry: 005bdc5c
 * Name: read_long_string
 * Namespace: Global
 * Signature: void read_long_string(LexState * param_1, SemInfo * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl read_long_string(LexState *param_1,SemInfo *param_2,int param_3)

{
  byte *pbVar1;
  LexState *pLVar2;
  LexState *in_EAX;
  uint uVar3;
  int iVar4;
  TString *pTVar5;
  LexState *unaff_ESI;
  int unaff_EDI;
  char *pcVar6;
  
  save((LexState *)in_EAX->current,(int)unaff_ESI);
  uVar3 = in_EAX->z->n;
  in_EAX->z->n = uVar3 - 1;
  if (uVar3 == 0) {
    uVar3 = luaZ_fill(in_EAX->z);
  }
  else {
    pbVar1 = (byte *)in_EAX->z->p;
    uVar3 = (uint)*pbVar1;
    in_EAX->z->p = (char *)(pbVar1 + 1);
  }
  in_EAX->current = uVar3;
  if ((uVar3 == 10) || (uVar3 == 0xd)) {
    inclinenumber(unaff_ESI);
  }
LAB_005bdca1:
  do {
    while (pLVar2 = (LexState *)in_EAX->current, pLVar2 == (LexState *)0xffffffff) {
      pcVar6 = "unfinished long string";
      if (param_1 == (LexState *)0x0) {
        pcVar6 = "unfinished long comment";
      }
      iVar4 = 0x11f;
LAB_005bddc4:
      luaX_lexerror(in_EAX,pcVar6,iVar4);
    }
    if ((pLVar2 != (LexState *)0xa) && (pLVar2 != (LexState *)0xd)) {
      if (pLVar2 == (LexState *)0x5b) {
        iVar4 = skip_sep(unaff_ESI);
        if (iVar4 == unaff_EDI) {
          save((LexState *)in_EAX->current,(int)unaff_ESI);
          uVar3 = in_EAX->z->n;
          in_EAX->z->n = uVar3 - 1;
          if (uVar3 == 0) {
            uVar3 = luaZ_fill(in_EAX->z);
          }
          else {
            pbVar1 = (byte *)in_EAX->z->p;
            uVar3 = (uint)*pbVar1;
            in_EAX->z->p = (char *)(pbVar1 + 1);
          }
          in_EAX->current = uVar3;
          if (unaff_EDI == 0) {
            iVar4 = 0x5b;
            pcVar6 = "nesting of [[...]] is deprecated";
            goto LAB_005bddc4;
          }
        }
      }
      else if (pLVar2 == (LexState *)0x5d) {
        iVar4 = skip_sep(unaff_ESI);
        if (iVar4 == unaff_EDI) {
          save((LexState *)in_EAX->current,(int)unaff_ESI);
          uVar3 = in_EAX->z->n;
          in_EAX->z->n = uVar3 - 1;
          if (uVar3 == 0) {
            uVar3 = luaZ_fill(in_EAX->z);
          }
          else {
            pbVar1 = (byte *)in_EAX->z->p;
            uVar3 = (uint)*pbVar1;
            in_EAX->z->p = (char *)(pbVar1 + 1);
          }
          in_EAX->current = uVar3;
          if (param_1 != (LexState *)0x0) {
            pTVar5 = luaX_newstring(in_EAX,in_EAX->buff->buffer + unaff_EDI + 2,
                                    (in_EAX->buff->n + unaff_EDI * -2) - 4);
            param_1->current = (int)pTVar5;
          }
          return;
        }
      }
      else {
        if (param_1 != (LexState *)0x0) {
          save(pLVar2,(int)unaff_ESI);
        }
        uVar3 = in_EAX->z->n;
        in_EAX->z->n = uVar3 - 1;
        if (uVar3 == 0) {
          uVar3 = luaZ_fill(in_EAX->z);
        }
        else {
          pbVar1 = (byte *)in_EAX->z->p;
          uVar3 = (uint)*pbVar1;
          in_EAX->z->p = (char *)(pbVar1 + 1);
        }
        in_EAX->current = uVar3;
      }
      goto LAB_005bdca1;
    }
    save((LexState *)0xa,(int)unaff_ESI);
    inclinenumber(unaff_ESI);
    if (param_1 == (LexState *)0x0) {
      in_EAX->buff->n = 0;
    }
  } while( true );
}
