/*
 * Entry: 005be041
 * Name: llex
 * Namespace: Global
 * Signature: int llex(LexState * param_1, SemInfo * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl llex(LexState *param_1,SemInfo *param_2)

{
  byte *pbVar1;
  LexState *in_EAX;
  uint uVar2;
  int iVar3;
  TString *pTVar4;
  int unaff_ESI;
  SemInfo *unaff_EDI;
  
LAB_005be049:
  in_EAX->buff->n = 0;
LAB_005be050:
  do {
    while( true ) {
      iVar3 = in_EAX->current;
      if (iVar3 < 0x2f) break;
      if (iVar3 == 0x3c) {
        uVar2 = in_EAX->z->n;
        in_EAX->z->n = uVar2 - 1;
        if (uVar2 == 0) {
          uVar2 = luaZ_fill(in_EAX->z);
        }
        else {
          pbVar1 = (byte *)in_EAX->z->p;
          uVar2 = (uint)*pbVar1;
          in_EAX->z->p = (char *)(pbVar1 + 1);
        }
        in_EAX->current = uVar2;
        if (uVar2 == 0x3d) {
          uVar2 = in_EAX->z->n;
          in_EAX->z->n = uVar2 - 1;
          if (uVar2 == 0) {
            uVar2 = luaZ_fill(in_EAX->z);
          }
          else {
            pbVar1 = (byte *)in_EAX->z->p;
            uVar2 = (uint)*pbVar1;
            in_EAX->z->p = (char *)(pbVar1 + 1);
          }
          in_EAX->current = uVar2;
          return 0x11a;
        }
        return 0x3c;
      }
      if (iVar3 == 0x3d) {
LAB_005be3ef:
        uVar2 = in_EAX->z->n;
        in_EAX->z->n = uVar2 - 1;
        if (uVar2 == 0) {
          uVar2 = luaZ_fill(in_EAX->z);
        }
        else {
          pbVar1 = (byte *)in_EAX->z->p;
          uVar2 = (uint)*pbVar1;
          in_EAX->z->p = (char *)(pbVar1 + 1);
        }
        in_EAX->current = uVar2;
        if (uVar2 == 0x3d) {
          uVar2 = in_EAX->z->n;
          in_EAX->z->n = uVar2 - 1;
          if (uVar2 == 0) {
            uVar2 = luaZ_fill(in_EAX->z);
          }
          else {
            pbVar1 = (byte *)in_EAX->z->p;
            uVar2 = (uint)*pbVar1;
            in_EAX->z->p = (char *)(pbVar1 + 1);
          }
          in_EAX->current = uVar2;
          return 0x118;
        }
        return 0x3d;
      }
      if (iVar3 == 0x3e) {
        uVar2 = in_EAX->z->n;
        in_EAX->z->n = uVar2 - 1;
        if (uVar2 == 0) {
          uVar2 = luaZ_fill(in_EAX->z);
        }
        else {
          pbVar1 = (byte *)in_EAX->z->p;
          uVar2 = (uint)*pbVar1;
          in_EAX->z->p = (char *)(pbVar1 + 1);
        }
        in_EAX->current = uVar2;
        if (uVar2 == 0x3d) {
          uVar2 = in_EAX->z->n;
          in_EAX->z->n = uVar2 - 1;
          if (uVar2 == 0) {
            uVar2 = luaZ_fill(in_EAX->z);
          }
          else {
            pbVar1 = (byte *)in_EAX->z->p;
            uVar2 = (uint)*pbVar1;
            in_EAX->z->p = (char *)(pbVar1 + 1);
          }
          in_EAX->current = uVar2;
          return 0x119;
        }
        return 0x3e;
      }
      if (iVar3 == 0x5b) {
        iVar3 = skip_sep((LexState *)unaff_EDI);
        if (-1 < iVar3) {
          read_long_string(param_1,unaff_EDI,unaff_ESI);
          return 0x11e;
        }
        if (iVar3 == -1) {
          return 0x5b;
        }
        luaX_lexerror(in_EAX,"invalid long string delimiter",0x11e);
        goto LAB_005be3ef;
      }
      if (iVar3 == 0x7e) {
        uVar2 = in_EAX->z->n;
        in_EAX->z->n = uVar2 - 1;
        if (uVar2 == 0) {
          uVar2 = luaZ_fill(in_EAX->z);
        }
        else {
          pbVar1 = (byte *)in_EAX->z->p;
          uVar2 = (uint)*pbVar1;
          in_EAX->z->p = (char *)(pbVar1 + 1);
        }
        in_EAX->current = uVar2;
        if (uVar2 == 0x3d) {
          uVar2 = in_EAX->z->n;
          in_EAX->z->n = uVar2 - 1;
          if (uVar2 == 0) {
            uVar2 = luaZ_fill(in_EAX->z);
          }
          else {
            pbVar1 = (byte *)in_EAX->z->p;
            uVar2 = (uint)*pbVar1;
            in_EAX->z->p = (char *)(pbVar1 + 1);
          }
          in_EAX->current = uVar2;
          return 0x11b;
        }
        return 0x7e;
      }
LAB_005be19e:
      iVar3 = isspace(iVar3);
      if (iVar3 == 0) {
        iVar3 = isdigit(in_EAX->current);
        if (iVar3 == 0) {
          iVar3 = isalpha(in_EAX->current);
          if ((iVar3 == 0) && (iVar3 = in_EAX->current, iVar3 != 0x5f)) {
            uVar2 = in_EAX->z->n;
            in_EAX->z->n = uVar2 - 1;
            if (uVar2 == 0) {
              uVar2 = luaZ_fill(in_EAX->z);
            }
            else {
              pbVar1 = (byte *)in_EAX->z->p;
              uVar2 = (uint)*pbVar1;
              in_EAX->z->p = (char *)(pbVar1 + 1);
            }
            in_EAX->current = uVar2;
          }
          else {
            do {
              save((LexState *)in_EAX->current,(int)unaff_EDI);
              uVar2 = in_EAX->z->n;
              in_EAX->z->n = uVar2 - 1;
              if (uVar2 == 0) {
                uVar2 = luaZ_fill(in_EAX->z);
              }
              else {
                pbVar1 = (byte *)in_EAX->z->p;
                uVar2 = (uint)*pbVar1;
                in_EAX->z->p = (char *)(pbVar1 + 1);
              }
              in_EAX->current = uVar2;
              iVar3 = isalnum(uVar2);
            } while ((iVar3 != 0) || (in_EAX->current == 0x5f));
            pTVar4 = luaX_newstring(in_EAX,in_EAX->buff->buffer,in_EAX->buff->n);
            if ((pTVar4->tsv).reserved == 0) {
              param_1->current = (int)pTVar4;
              iVar3 = 0x11d;
            }
            else {
              iVar3 = (pTVar4->tsv).reserved + 0x100;
            }
          }
          return iVar3;
        }
LAB_005be26e:
        read_numeral(param_1,unaff_EDI);
        return 0x11c;
      }
      uVar2 = in_EAX->z->n;
      in_EAX->z->n = uVar2 - 1;
      if (uVar2 == 0) {
        uVar2 = luaZ_fill(in_EAX->z);
      }
      else {
        pbVar1 = (byte *)in_EAX->z->p;
        uVar2 = (uint)*pbVar1;
        in_EAX->z->p = (char *)(pbVar1 + 1);
      }
      in_EAX->current = uVar2;
    }
    if (iVar3 == 0x2e) {
      save((LexState *)in_EAX->current,(int)unaff_EDI);
      uVar2 = in_EAX->z->n;
      in_EAX->z->n = uVar2 - 1;
      if (uVar2 == 0) {
        uVar2 = luaZ_fill(in_EAX->z);
      }
      else {
        pbVar1 = (byte *)in_EAX->z->p;
        uVar2 = (uint)*pbVar1;
        in_EAX->z->p = (char *)(pbVar1 + 1);
      }
      in_EAX->current = uVar2;
      iVar3 = check_next((LexState *)".",(char *)unaff_EDI);
      if (iVar3 != 0) {
        iVar3 = check_next((LexState *)".",(char *)unaff_EDI);
        return (iVar3 != 0) + 0x116;
      }
      iVar3 = isdigit(in_EAX->current);
      if (iVar3 == 0) {
        return 0x2e;
      }
      goto LAB_005be26e;
    }
    if (iVar3 == -1) {
      return 0x11f;
    }
    if ((iVar3 != 10) && (iVar3 != 0xd)) {
      if ((iVar3 == 0x22) || (iVar3 == 0x27)) {
        read_string((LexState *)in_EAX->current,(int)param_1,unaff_EDI);
        return 0x11e;
      }
      if (iVar3 != 0x2d) goto LAB_005be19e;
      uVar2 = in_EAX->z->n;
      in_EAX->z->n = uVar2 - 1;
      if (uVar2 == 0) {
        uVar2 = luaZ_fill(in_EAX->z);
      }
      else {
        pbVar1 = (byte *)in_EAX->z->p;
        uVar2 = (uint)*pbVar1;
        in_EAX->z->p = (char *)(pbVar1 + 1);
      }
      in_EAX->current = uVar2;
      if (uVar2 != 0x2d) {
        return 0x2d;
      }
      uVar2 = in_EAX->z->n;
      in_EAX->z->n = uVar2 - 1;
      if (uVar2 == 0) {
        uVar2 = luaZ_fill(in_EAX->z);
      }
      else {
        pbVar1 = (byte *)in_EAX->z->p;
        uVar2 = (uint)*pbVar1;
        in_EAX->z->p = (char *)(pbVar1 + 1);
      }
      in_EAX->current = uVar2;
      if (uVar2 == 0x5b) {
        iVar3 = skip_sep((LexState *)unaff_EDI);
        in_EAX->buff->n = 0;
        if (-1 < iVar3) break;
      }
      uVar2 = in_EAX->current;
      while (((uVar2 != 10 && (in_EAX->current != 0xd)) && (in_EAX->current != -1))) {
        uVar2 = in_EAX->z->n;
        in_EAX->z->n = uVar2 - 1;
        if (uVar2 == 0) {
          uVar2 = luaZ_fill(in_EAX->z);
        }
        else {
          pbVar1 = (byte *)in_EAX->z->p;
          uVar2 = (uint)*pbVar1;
          in_EAX->z->p = (char *)(pbVar1 + 1);
        }
        in_EAX->current = uVar2;
      }
      goto LAB_005be050;
    }
    inclinenumber((LexState *)unaff_EDI);
  } while( true );
  read_long_string((LexState *)0x0,unaff_EDI,unaff_ESI);
  goto LAB_005be049;
}
