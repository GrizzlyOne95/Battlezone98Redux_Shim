/*
 * Entry: 00511367
 * Name: IParse_Save_Only_Alpha_Numeric
 * Namespace: Global
 * Signature: void IParse_Save_Only_Alpha_Numeric(char * * param_1, _func___cdecl_int_char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl IParse_Save_Only_Alpha_Numeric(char **param_1,_func___cdecl_int_char *param_2)

{
  char *_Memory;
  int iVar1;
  char *pcVar2;
  int iVar3;
  char cVar4;
  char *local_c;
  int local_8;
  
  iVar3 = 0;
  local_8 = 0;
  local_c = calloc(1,1);
  *local_c = '\0';
  cVar4 = **param_1;
  iVar1 = 0;
  do {
    if (cVar4 == '\0') {
      pcVar2 = realloc(local_c,iVar1 + 1);
      pcVar2[iVar1] = '\0';
      _Memory = *param_1;
      *param_1 = pcVar2;
      free(_Memory);
      return;
    }
    iVar1 = (*param_2)((*param_1)[iVar3]);
    if (iVar1 == 1) {
      cVar4 = (*param_1)[iVar3];
LAB_00511436:
      IParse_Append_Good_Char(&local_c,&local_8,cVar4);
    }
    else {
      if (iVar1 != 2) {
        cVar4 = ' ';
        goto LAB_00511436;
      }
      if ((*param_1)[iVar3] == '\"') {
        cVar4 = '\"';
        do {
          IParse_Append_Quote_Char(&local_c,&local_8,cVar4);
          iVar3 = iVar3 + 1;
          if ((*param_1)[iVar3] == '\0') break;
          cVar4 = (*param_1)[iVar3];
        } while (cVar4 != '\"');
        if ((*param_1)[iVar3] == '\"') {
          IParse_Append_Quote_Char(&local_c,&local_8,'\"');
        }
      }
      else {
        IParse_Append_Good_Char(&local_c,&local_8,' ');
        IParse_Append_Good_Char(&local_c,&local_8,(*param_1)[iVar3]);
        IParse_Append_Good_Char(&local_c,&local_8,' ');
      }
    }
    iVar3 = iVar3 + 1;
    cVar4 = (*param_1)[iVar3];
    iVar1 = local_8;
  } while( true );
}
