/*
 * Entry: 00512805
 * Name: IParse_Parse_File
 * Namespace: Global
 * Signature: int IParse_Parse_File(char * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl IParse_Parse_File(char *param_1,void *param_2)

{
  char cVar1;
  void *pvVar2;
  char *pcVar3;
  long lVar4;
  int iVar5;
  char *pcVar6;
  uint uVar7;
  uint uVar8;
  undefined4 *puVar9;
  bool bVar10;
  int local_504;
  int local_500;
  FILE *local_4fc;
  char *local_4f8;
  undefined1 local_4f4 [4];
  char local_4f0 [108];
  undefined1 local_484 [892];
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_484;
  local_4f8 = param_1;
  bVar10 = false;
  local_4fc = (FILE *)0x0;
  local_504 = 0;
  local_4f4 = (undefined1  [4])0x0;
  do {
    if (*(int *)((int)param_2 + 0x18) <= (int)local_4f4) break;
    pvVar2 = C_Linked_List_Return_Data_By_Number
                       ((tag_c_linked_list *)((int)param_2 + 0x10),(int)local_4f4);
    sprintf(local_108,"%s%s",pvVar2,local_4f8);
    local_4fc = fopen(local_108,"r");
    bVar10 = local_4fc != (FILE *)0x0;
    local_4f4 = (undefined1  [4])((int)local_4f4 + 1);
  } while (!bVar10);
  if ((bVar10) || (local_4fc = fopen(local_4f8,"r"), local_4fc != (FILE *)0x0)) {
    IParse_Read_File_Into_Buffer((_iobuf *)local_4fc,(char **)local_4f4,&local_500);
    fclose(local_4fc);
  }
  else {
    pcVar3 = UseItem(local_4f8);
    if (pcVar3 == (char *)0x0) {
      local_4f0[0] = 0;
      puVar9 = (undefined4 *)(local_4f4 + 3);
      do {
        pcVar3 = (char *)((int)puVar9 + 1);
        puVar9 = (undefined4 *)((int)puVar9 + 1);
      } while (*pcVar3 != '\0');
      pcVar3 = "Error Opening parse file: \'";
      for (iVar5 = 7; pcVar6 = local_4f8, iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar9 = *(undefined4 *)pcVar3;
        pcVar3 = pcVar3 + 4;
        puVar9 = puVar9 + 1;
      }
      do {
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      uVar7 = (int)pcVar6 - (int)local_4f8;
      pcVar3 = local_4f4 + 3;
      do {
        pcVar6 = pcVar3 + 1;
        pcVar3 = pcVar3 + 1;
      } while (*pcVar6 != '\0');
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar3 = *(undefined4 *)local_4f8;
        local_4f8 = local_4f8 + 4;
        pcVar3 = pcVar3 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar3 = *local_4f8;
        local_4f8 = local_4f8 + 1;
        pcVar3 = pcVar3 + 1;
      }
      pcVar3 = local_4f4 + 3;
      do {
        pcVar6 = pcVar3 + 1;
        pcVar3 = pcVar3 + 1;
      } while (*pcVar6 != '\0');
      *(char (*) [2])pcVar3 = (char  [2])0x27;
      return 10;
    }
    lVar4 = GetItemSize(local_4f8);
    IParse_Read_Data_Into_Buffer(pcVar3,lVar4,(char **)local_4f4,&local_500);
    UnlockItem(local_4f8);
  }
  iVar5 = do_parse((char *)local_4f4,&local_504,local_500,param_2);
  free((void *)local_4f4);
  return iVar5;
}
