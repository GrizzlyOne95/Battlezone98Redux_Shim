/*
 * Entry: 005279f4
 * Name: read_record_info
 * Namespace: Global
 * Signature: int read_record_info(ZFS_COOKIE * param_1, ZFS_FHEADER * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl read_record_info(ZFS_COOKIE *param_1,ZFS_FHEADER *param_2)

{
  void *pvVar1;
  size_t sVar2;
  int iVar3;
  undefined4 *in_ECX;
  int iVar4;
  int in_EDX;
  char *pcVar5;
  long _Offset;
  char *pcVar6;
  int iVar7;
  undefined4 *puVar8;
  int local_e24;
  int local_e20;
  int local_e1c;
  char local_e18 [112];
  undefined1 local_da8 [3488];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_da8;
  pvVar1 = malloc(in_ECX[5] << 2);
  in_ECX[9] = pvVar1;
  if (pvVar1 != (void *)0x0) {
    pvVar1 = malloc(*(int *)(in_EDX + 0x10) * 0x24);
    in_ECX[10] = pvVar1;
    if (pvVar1 != (void *)0x0) {
      iVar7 = 0;
      local_e20 = 0;
      _Offset = *(long *)(in_EDX + 0x18);
      do {
        fseek((FILE *)*in_ECX,_Offset,0);
        sVar2 = fread(&local_e1c,0xe14,1,(FILE *)*in_ECX);
        if (sVar2 == 0) {
          sprintf(&zfserr,"Could not read dtable %d of file \"%s\"",iVar7,in_ECX + 1);
          goto LAB_00527afe;
        }
        local_e24 = 0;
        *(long *)(in_ECX[9] + iVar7 * 4) = _Offset;
        iVar7 = iVar7 + 1;
        iVar3 = local_e20 * 0x24;
        pcVar5 = local_e18;
        do {
          if (*pcVar5 == '\0') break;
          if ((pcVar5[0x20] & 1U) == 0) {
            local_e20 = local_e20 + 1;
            pcVar6 = pcVar5;
            puVar8 = (undefined4 *)(in_ECX[10] + iVar3);
            for (iVar4 = 9; iVar4 != 0; iVar4 = iVar4 + -1) {
              *puVar8 = *(undefined4 *)pcVar6;
              pcVar6 = pcVar6 + 4;
              puVar8 = puVar8 + 1;
            }
            iVar3 = iVar3 + 0x24;
          }
          local_e24 = local_e24 + 1;
          pcVar5 = pcVar5 + 0x24;
        } while (local_e24 < 100);
        _Offset = local_e1c;
      } while (local_e1c != 0);
      in_ECX[6] = local_e20;
      if (iVar7 == in_ECX[5]) {
        iVar7 = 1;
      }
      else {
        sprintf(&zfserr,"Header has %d dtables; actually %d dtables in file \"%s\"",in_ECX[5],iVar7,
                in_ECX + 1);
LAB_00527afe:
        iVar7 = 0;
      }
      return iVar7;
    }
  }
                    /* WARNING: Subroutine does not return */
  I76FatalError((char *)0x0);
}
