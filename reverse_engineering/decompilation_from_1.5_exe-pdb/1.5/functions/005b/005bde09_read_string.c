/*
 * Entry: 005bde09
 * Name: read_string
 * Namespace: Global
 * Signature: void read_string(LexState * param_1, int param_2, SemInfo * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl read_string(LexState *param_1,int param_2,SemInfo *param_3)

{
  byte *pbVar1;
  LexState *in_EAX;
  LexState *pLVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  TString *pTVar6;
  int unaff_EBX;
  LexState *unaff_EDI;
  
  save((LexState *)in_EAX->current,unaff_EBX);
  uVar3 = in_EAX->z->n;
  in_EAX->z->n = uVar3 - 1;
  if (uVar3 == 0) {
    pLVar2 = (LexState *)luaZ_fill(in_EAX->z);
  }
  else {
    pbVar1 = (byte *)in_EAX->z->p;
    pLVar2 = (LexState *)(uint)*pbVar1;
    in_EAX->z->p = (char *)(pbVar1 + 1);
  }
  in_EAX->current = (int)pLVar2;
  do {
    if (pLVar2 == param_1) {
      save((LexState *)in_EAX->current,unaff_EBX);
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
      pTVar6 = luaX_newstring(in_EAX,in_EAX->buff->buffer + 1,in_EAX->buff->n - 2);
      *(TString **)param_2 = pTVar6;
      return;
    }
    pLVar2 = (LexState *)in_EAX->current;
    if (pLVar2 == (LexState *)0xffffffff) {
      iVar4 = 0x11f;
LAB_005bdfda:
      luaX_lexerror(in_EAX,"unfinished string",iVar4);
    }
    else {
      if ((pLVar2 == (LexState *)0xa) || (pLVar2 == (LexState *)0xd)) {
        iVar4 = 0x11e;
        goto LAB_005bdfda;
      }
      if (pLVar2 == (LexState *)0x5c) {
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
        if (0x66 < (int)uVar3) {
          pLVar2 = (LexState *)0xa;
          if (uVar3 != 0x6e) {
            if (uVar3 == 0x72) {
              pLVar2 = (LexState *)0xd;
            }
            else if (uVar3 == 0x74) {
              pLVar2 = (LexState *)0x9;
            }
            else if (uVar3 == 0x76) {
              pLVar2 = (LexState *)0xb;
            }
            else {
LAB_005bdf34:
              iVar4 = isdigit(uVar3);
              if (iVar4 != 0) {
                iVar4 = 0;
                pLVar2 = (LexState *)0x0;
                do {
                  pLVar2 = (LexState *)((int)pLVar2 * 10 + -0x30 + in_EAX->current);
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
                  iVar4 = iVar4 + 1;
                  in_EAX->current = uVar3;
                } while ((iVar4 < 3) && (iVar5 = isdigit(uVar3), iVar5 != 0));
                if (0xff < (int)pLVar2) {
                  luaX_lexerror(in_EAX,"escape sequence too large",0x11e);
                }
                save(pLVar2,(int)unaff_EDI);
                goto LAB_005bdfe4;
              }
              pLVar2 = (LexState *)in_EAX->current;
            }
          }
          goto LAB_005bde73;
        }
        if (uVar3 == 0x66) {
          pLVar2 = (LexState *)&DAT_0000000c;
          goto LAB_005bde73;
        }
        if (uVar3 != 0xffffffff) {
          if ((uVar3 != 10) && (uVar3 != 0xd)) {
            if (uVar3 == 0x61) {
              pLVar2 = (LexState *)0x7;
            }
            else {
              if (uVar3 != 0x62) goto LAB_005bdf34;
              pLVar2 = (LexState *)0x8;
            }
            goto LAB_005bde73;
          }
          save((LexState *)0xa,(int)unaff_EDI);
          inclinenumber(unaff_EDI);
        }
      }
      else {
LAB_005bde73:
        save(pLVar2,(int)unaff_EDI);
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
    }
LAB_005bdfe4:
    pLVar2 = (LexState *)in_EAX->current;
  } while( true );
}
