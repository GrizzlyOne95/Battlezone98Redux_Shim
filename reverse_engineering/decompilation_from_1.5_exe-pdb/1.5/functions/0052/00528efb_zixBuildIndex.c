/*
 * Entry: 00528efb
 * Name: zixBuildIndex
 * Namespace: Global
 * Signature: int zixBuildIndex(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl zixBuildIndex(char *param_1)

{
  byte bVar1;
  char cVar2;
  FILE *_File;
  int iVar3;
  int iVar4;
  ZIX_FENTRY_TYPE *pZVar5;
  ZIX_FENTRY_TYPE *_Source;
  ZIX_CD_TYPE *_Str2;
  int unaff_EDI;
  int iVar6;
  ZIX_FENTRY_TYPE *pZVar7;
  bool bVar8;
  char *pcVar9;
  ZIX_FENTRY_TYPE *local_18;
  ZIX_FENTRY_TYPE *local_14;
  FILE *local_10;
  int local_c;
  size_t local_8;
  
  local_8 = 0;
  _File = fopen(param_1,"rt");
  if (_File == (FILE *)0x0) {
    pcVar9 = "Couldn\'t open file \"%s\"";
  }
  else {
    iVar3 = fscanf(_File,"%d\n",&local_8);
    if (iVar3 == 1) {
      zix_numpaths = 0;
      oridedir_build_zix_paths("addon");
      iVar3 = oridedir_countfiles();
      iVar6 = zix_numpaths + -1;
      local_8 = local_8 + iVar3;
      iVar4 = zixReadPath((_iobuf *)_File,iVar6);
      if (iVar4 == 0) {
        return 0;
      }
      local_14 = calloc(1,local_8 * 0x30);
      if (local_14 == (ZIX_FENTRY_TYPE *)0x0) {
                    /* WARNING: Subroutine does not return */
        I76FatalError((char *)0x0);
      }
      oridedir_getpaths(local_14,local_8);
      local_c = iVar3;
      if (iVar3 < (int)local_8) {
        pZVar5 = local_14 + iVar3;
        do {
          iVar3 = fscanf(_File,"%d %s\n",&local_18,pZVar5);
          if (iVar3 != 2) {
            sprintf(&zfserr,"Invalid file line in %s",param_1);
            return 0;
          }
          pZVar5->paths[0] = (ulong)(local_18->name + iVar6);
          to_zfsname(pZVar5->name,pZVar5->name);
          local_c = local_c + 1;
          pZVar5 = pZVar5 + 1;
        } while (local_c < (int)local_8);
      }
      qsort(local_14,local_8,0x30,fentry_compare1);
      fentry = calloc(1,local_8 * 0x30);
      if (fentry == (ZIX_FENTRY_TYPE *)0x0) {
                    /* WARNING: Subroutine does not return */
        I76FatalError((char *)0x0);
      }
      local_10 = fopen("zixindex.log","wt");
      fprintf(local_10,"%s\n",param_1);
      iVar3 = -1;
      local_18 = (ZIX_FENTRY_TYPE *)0x5d0e3a;
      num_fentries = -1;
      local_c = 0;
      pZVar5 = local_18;
      pZVar7 = local_14;
      _Source = local_14;
      if (0 < (int)local_8) {
LAB_0052908a:
        do {
          bVar1 = pZVar5->name[0];
          bVar8 = bVar1 < (byte)pZVar7->name[0];
          if (bVar1 == pZVar7->name[0]) {
            if (bVar1 != 0) {
              bVar1 = pZVar5->name[1];
              bVar8 = bVar1 < (byte)pZVar7->name[1];
              if (bVar1 != pZVar7->name[1]) goto LAB_005290c5;
              pZVar5 = (ZIX_FENTRY_TYPE *)(pZVar5->name + 2);
              pZVar7 = (ZIX_FENTRY_TYPE *)(pZVar7->name + 2);
              if (bVar1 != 0) goto LAB_0052908a;
            }
            iVar4 = 0;
          }
          else {
LAB_005290c5:
            iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          }
          if (iVar4 == 0) {
            pZVar5 = local_18;
            if (local_10 != (FILE *)0x0) {
              fprintf(local_10,"                 ! %s\n",zix_paths + _Source->paths[0]);
              iVar3 = num_fentries;
              pZVar5 = local_18;
            }
          }
          else {
            num_fentries = iVar3 + 1;
            pZVar5 = fentry + num_fentries;
            pZVar5->name[0] = '\0';
            pZVar5->name[1] = '\0';
            pZVar5->name[2] = '\0';
            pZVar5->name[3] = '\0';
            pZVar5->name[4] = '\0';
            pZVar5->name[5] = '\0';
            pZVar5->name[6] = '\0';
            pZVar5->name[7] = '\0';
            pZVar5->name[8] = '\0';
            pZVar5->name[9] = '\0';
            pZVar5->name[10] = '\0';
            pZVar5->name[0xb] = '\0';
            pZVar5->name[0xc] = '\0';
            pZVar5->name[0xd] = '\0';
            pZVar5->name[0xe] = '\0';
            pZVar5->name[0xf] = '\0';
            strncpy(pZVar5->name,_Source->name,0x10);
            iVar3 = num_fentries;
            pZVar5 = _Source;
            if (local_10 != (FILE *)0x0) {
              fprintf(local_10,"%16s @ %s\n",_Source,zix_paths + _Source->paths[0]);
              iVar3 = num_fentries;
            }
          }
          local_18 = pZVar5;
          paths_setbit(fentry[iVar3].paths,unaff_EDI);
          local_c = local_c + 1;
          pZVar5 = local_18;
          pZVar7 = _Source + 1;
          _Source = _Source + 1;
        } while (local_c < (int)local_8);
      }
      iVar4 = 0;
      if (local_10 != (FILE *)0x0) {
        fclose(local_10);
        iVar3 = num_fentries;
      }
      num_fentries = iVar3 + 1;
      fentry = realloc(fentry,num_fentries * 0x30);
      free(local_14);
      fclose(_File);
      cVar2 = CDDriveLetter();
      pcVar9 = (*zixGetVolumeName)(cVar2);
      if ((pcVar9 != (char *)0x0) && (0 < zix_numcds)) {
        _Str2 = zix_cds;
        do {
          iVar3 = _stricmp(pcVar9,_Str2->cd_name);
          if (iVar3 == 0) {
            current_cd = iVar4;
            return 1;
          }
          iVar4 = iVar4 + 1;
          _Str2 = _Str2 + 1;
        } while (iVar4 < zix_numcds);
      }
      return 1;
    }
    pcVar9 = "Could not read number of files from %s";
  }
  sprintf(&zfserr,pcVar9,param_1);
  return 0;
}
