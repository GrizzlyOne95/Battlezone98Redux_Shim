
/* WARNING: Removing unreachable block (ram,0x0050ab0a) */

void __fastcall FUN_0050aa10(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  float10 fVar4;
  undefined *local_78;
  char *local_74;
  char *local_70;
  char *local_68;
  char *local_64;
  char local_58 [64];
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_0045d240();
  if (*(int *)(param_1 + 0x58) != 0) {
    if (DAT_0091989c != 0) {
      local_18[0] = '\0';
      local_18[1] = '\0';
      local_18[2] = '\0';
      local_18[3] = '\0';
      local_18[4] = '\0';
      local_18[5] = '\0';
      local_18[6] = '\0';
      local_18[7] = '\0';
      local_18[8] = 0;
      local_18[9] = '\0';
      local_18[10] = '\0';
      local_18[0xb] = '\0';
      local_18[0xc] = '\0';
      local_18[0xd] = '\0';
      local_18[0xe] = '\0';
      local_18[0xf] = 0;
      local_68 = *(char **)(&DAT_00917b28 + (uint)(byte)DAT_0091989c * 4);
      if (local_68 == (char *)0x0) {
        if ((DAT_0091989c & 0x800) == 0) {
          iVar2 = toupper((uint)(byte)DAT_0091989c);
          local_18[0] = (char)iVar2;
                    /* WARNING: Ignoring partial resolution of indirect */
          local_18[1] = 0;
        }
        else {
          builtin_strncpy(local_18,"CapsLock",9);
        }
      }
      else {
        local_64 = local_18;
        do {
          cVar1 = *local_68;
          *local_64 = cVar1;
          local_68 = local_68 + 1;
          local_64 = local_64 + 1;
        } while (cVar1 != '\0');
      }
      if ((DAT_0091989c & 0x400) == 0) {
        local_78 = &DAT_008a1ad8;
      }
      else {
        local_78 = &DAT_0087d248;
      }
      if ((DAT_0091989c & 0x200) == 0) {
        local_74 = "";
      }
      else {
        local_74 = "Shift+";
      }
      if ((DAT_0091989c & 0x100) == 0) {
        local_70 = "";
      }
      else {
        local_70 = "Ctrl+";
      }
      sprintf(local_58,"%s%s%s%s",local_70,local_74,local_78,local_18);
      FUN_0082c82c(*(undefined4 *)(param_1 + 0x58),0xffffd8ee,"GameKey");
      iVar2 = FUN_0082d490(*(undefined4 *)(param_1 + 0x58),0xffffffff);
      if (iVar2 == 6) {
        FUN_0082cd77(*(undefined4 *)(param_1 + 0x58),local_58);
        uVar3 = FUN_0082cb8c(*(undefined4 *)(param_1 + 0x58),1,0,0,*(undefined4 *)(param_1 + 0x58),
                             "Lua script GameKey error:\n%s");
        FUN_004ff600(uVar3);
      }
      else {
        FUN_0082d226(*(undefined4 *)(param_1 + 0x58),0xfffffffe);
      }
      FUN_0082cd77(*(undefined4 *)(param_1 + 0x58),local_58);
      FUN_0082d102(*(undefined4 *)(param_1 + 0x58),0xffffd8ee,"LastGameKey");
    }
    FUN_0082c82c(*(undefined4 *)(param_1 + 0x58),0xffffd8ee,"Update");
    iVar2 = FUN_0082d490(*(undefined4 *)(param_1 + 0x58),0xffffffff);
    if (iVar2 == 6) {
      fVar4 = (float10)FUN_00822d60();
      FUN_0082cd58(*(undefined4 *)(param_1 + 0x58),(double)fVar4);
      uVar3 = FUN_0082cb8c(*(undefined4 *)(param_1 + 0x58),1,0,0,*(undefined4 *)(param_1 + 0x58),
                           "Lua script Update error:\n%s");
      FUN_004ff600(uVar3);
    }
    else {
      FUN_0082d226(*(undefined4 *)(param_1 + 0x58),0xfffffffe);
    }
  }
  FUN_0083e885();
  return;
}

