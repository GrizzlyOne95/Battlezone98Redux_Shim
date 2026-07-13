
bool FUN_0043d1d0(char *param_1,undefined4 param_2,uint param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  bool bVar4;
  undefined4 *local_c;
  char *local_8;
  
  if (DAT_00915644 == 0) {
    iVar2 = _stricmp(param_1,"STOPCBXX");
    if (iVar2 == 0) {
      FUN_0043d1a0(0);
      bVar4 = false;
    }
    else {
      iVar2 = FUN_0043d170(param_2);
      if (iVar2 == 0) {
        cVar1 = FUN_0043d160();
        if ((cVar1 == '\0') || (cVar1 = FUN_00439e50(), cVar1 == '\0')) {
          bVar4 = true;
        }
        else {
          if (DAT_00915640 != (undefined4 *)0x0) {
            if (param_3 == 5) {
              return false;
            }
            if ((param_3 == 6) && ((uint)DAT_00915640[6] < 5)) {
              return false;
            }
            if ((param_3 == 1) || ((param_3 < 5 && (4 < (uint)DAT_00915640[6])))) {
              FUN_0043d4f0(0);
            }
          }
          local_8 = malloc(0x24);
          if (local_8 == (char *)0x0) {
            bVar4 = false;
          }
          else {
            local_8[0] = '\0';
            local_8[1] = '\0';
            local_8[2] = '\0';
            local_8[3] = '\0';
            local_8[4] = '\0';
            local_8[5] = '\0';
            local_8[6] = '\0';
            local_8[7] = '\0';
            local_8[8] = '\0';
            local_8[9] = '\0';
            local_8[10] = '\0';
            local_8[0xb] = '\0';
            local_8[0xc] = '\0';
            local_8[0xd] = '\0';
            local_8[0xe] = '\0';
            local_8[0xf] = '\0';
            local_8[0x10] = '\0';
            local_8[0x11] = '\0';
            local_8[0x12] = '\0';
            local_8[0x13] = '\0';
            local_8[0x14] = '\0';
            local_8[0x15] = '\0';
            local_8[0x16] = '\0';
            local_8[0x17] = '\0';
            local_8[0x18] = '\0';
            local_8[0x19] = '\0';
            local_8[0x1a] = '\0';
            local_8[0x1b] = '\0';
            local_8[0x1c] = '\0';
            local_8[0x1d] = '\0';
            local_8[0x1e] = '\0';
            local_8[0x1f] = '\0';
            local_8[0x20] = '\0';
            local_8[0x21] = '\0';
            local_8[0x22] = '\0';
            local_8[0x23] = '\0';
            strncpy(local_8,param_1,0x10);
            *(uint *)(local_8 + 0x18) = param_3;
            *(undefined4 *)(local_8 + 0x10) = param_2;
            uVar3 = FUN_00822e60();
            *(undefined4 *)(local_8 + 0x1c) = uVar3;
            if (DAT_00915640 != (undefined4 *)0x0) {
              if (*(int *)(local_8 + 0x18) == 2) {
                uVar3 = FUN_0043d540(DAT_00915640);
                *(undefined4 *)(local_8 + 0x20) = uVar3;
                DAT_00915640 = (undefined4 *)0x0;
              }
              else {
                for (local_c = DAT_00915640; local_c[8] != 0; local_c = (undefined4 *)local_c[8]) {
                }
                local_c[8] = local_8;
                local_8 = (char *)0x0;
              }
            }
            if ((DAT_00915640 == (undefined4 *)0x0) && (local_8 != (char *)0x0)) {
              for (; local_8 != (char *)0x0; local_8 = (char *)FUN_0043d540(local_8)) {
                iVar2 = FUN_0043d460(local_8);
                *(int *)(local_8 + 0x14) = iVar2;
                if (iVar2 != 0) break;
              }
              DAT_00915640 = (undefined4 *)local_8;
            }
            bVar4 = local_8 != (char *)0x0;
          }
        }
      }
      else {
        bVar4 = false;
      }
    }
  }
  else {
    bVar4 = false;
  }
  return bVar4;
}

