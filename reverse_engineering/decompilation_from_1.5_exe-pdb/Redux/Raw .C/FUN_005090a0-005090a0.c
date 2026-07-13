
/* WARNING: Removing unreachable block (ram,0x005090ea) */

void FUN_005090a0(void)

{
  char cVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  undefined4 *local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  int local_24;
  undefined1 local_1c [4];
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18[0] = '\0';
  local_18[1] = '\0';
  local_18[2] = '\0';
  local_18[3] = '\0';
  local_18[4] = '\0';
  local_18[5] = '\0';
  local_18[6] = '\0';
  local_18[7] = '\0';
  local_18[8] = '\0';
  local_18[9] = '\0';
  local_18[10] = '\0';
  local_18[0xb] = '\0';
  local_18[0xc] = '\0';
  local_18[0xd] = '\0';
  local_18[0xe] = '\0';
  local_18[0xf] = '\0';
  strncpy(local_18,&DAT_00915540,8);
                    /* WARNING: Ignoring partial resolution of indirect */
  local_18[8] = 0;
  puVar2 = (undefined1 *)FUN_00434140(local_18);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 0;
  }
  puVar7 = (undefined4 *)(local_1c + 3);
  do {
    local_38 = puVar7;
    puVar7 = (undefined4 *)((int)local_38 + 1);
  } while (*(char *)((int)local_38 + 1) != '\0');
  *(undefined4 *)((int)local_38 + 1) = 0x61756c2e;
  *(undefined1 *)((int)local_38 + 5) = 0;
  iVar3 = FUN_00481f10();
  if (iVar3 == 0) {
    FUN_007d6a70("No Lua script \"%s\"\n",local_18);
  }
  else {
    uVar4 = FUN_0082c0b0();
    *(undefined4 *)((int)local_1c + 0x58) = uVar4;
    if (*(int *)((int)local_1c + 0x58) != 0) {
      memset(&DAT_00917b28,0,0x400);
      for (local_34 = 0; local_34 < 0x21; local_34 = local_34 + 1) {
        *(undefined **)(&DAT_00917b28 + (uint)(byte)(&DAT_008e891c)[local_34 * 8] * 4) =
             (&PTR_s_Escape_008e8918)[local_34 * 2];
      }
      FUN_0082d51d();
      FUN_0082c571(*(undefined4 *)((int)local_1c + 0x58),FUN_004ff5d0);
      FUN_0082cd77(*(undefined4 *)((int)local_1c + 0x58),"2.2.301");
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xffffd8ee,"GameVersion");
      iVar3 = FUN_0081dee0();
      FUN_0082ccca(*(undefined4 *)((int)local_1c + 0x58),iVar3);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xffffd8ee,"Language");
      FUN_0082cd77(*(undefined4 *)((int)local_1c + 0x58),(&PTR_DAT_008fe198)[iVar3]);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xffffd8ee,"LanguageName");
      FUN_0082cd77(*(undefined4 *)((int)local_1c + 0x58),(&PTR_DAT_008fe178)[iVar3]);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xffffd8ee,"LanguageSuffix");
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_004ff550,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xffffd8ee,"print");
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_004ff590,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xffffd8ee,"warning");
      FUN_0082cdd2(*(undefined4 *)((int)local_1c + 0x58),0xffffd8ee);
      FUN_004ff260(*(undefined4 *)((int)local_1c + 0x58),&PTR_s_RepeatAudioMessage_00871bc8,0);
      FUN_0082cced(*(undefined4 *)((int)local_1c + 0x58),0);
      FUN_0082c058(*(undefined4 *)((int)local_1c + 0x58),"BZHandle");
      FUN_0082cd77(*(undefined4 *)((int)local_1c + 0x58),"BZHandle");
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__type");
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_00507a40,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__tostring");
      FUN_0082d16f(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe);
      FUN_0082c058(*(undefined4 *)((int)local_1c + 0x58),"ParameterDB");
      FUN_0082cd77(*(undefined4 *)((int)local_1c + 0x58),"ParameterDB");
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__type");
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_00506470,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,&DAT_0087d000);
      FUN_0082d226(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe);
      FUN_0082c058(*(undefined4 *)((int)local_1c + 0x58),"VECTOR_3D");
      FUN_0082cd77(*(undefined4 *)((int)local_1c + 0x58),"VECTOR_3D");
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__type");
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_00507aa0,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__index");
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_00507b80,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__newindex");
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_00507c40,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__unm");
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_00507cd0,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__add");
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_00507d80,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__sub");
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_00507e30,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__mul");
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_00508040,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__div");
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_00508270,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,&DAT_0087d114);
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_00508300,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__tostring");
      FUN_0082d226(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe);
      FUN_0082c058(*(undefined4 *)((int)local_1c + 0x58),"MAT_3D");
      FUN_0082cd77(*(undefined4 *)((int)local_1c + 0x58),"MAT_3D");
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__type");
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_005083a0,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__index");
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_005087f0,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__newindex");
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_00508b80,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__mul");
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_00508c60,0);
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,"__tostring");
      FUN_0082d226(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe);
      puVar5 = (undefined4 *)FUN_004ff840();
      puVar7 = &DAT_008fe1e0;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar5 = puVar5 + 1;
      }
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xffffd8ee,"IdentityMatrix");
      FUN_0082c68b(*(undefined4 *)((int)local_1c + 0x58),0x1d,0x1d);
      for (local_24 = 0; local_24 < 0x1d; local_24 = local_24 + 1) {
        FUN_0082cd58(*(undefined4 *)((int)local_1c + 0x58),(double)local_24);
        FUN_0082cd77(*(undefined4 *)((int)local_1c + 0x58));
        FUN_0082cdd2(*(undefined4 *)((int)local_1c + 0x58));
        FUN_0082cdd2(*(undefined4 *)((int)local_1c + 0x58));
        FUN_0082ced4(*(undefined4 *)((int)local_1c + 0x58));
        FUN_0082ced4();
      }
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xffffd8ee,"AiCommand");
      FUN_0082c68b(*(undefined4 *)((int)local_1c + 0x58),0,0x50);
      for (local_30 = 0; local_30 < 0x28; local_30 = local_30 + 1) {
        FUN_0082cd58(*(undefined4 *)((int)local_1c + 0x58),
                     (double)*(int *)(&DAT_008e87d8 + local_30 * 8));
        FUN_0082cd77(*(undefined4 *)((int)local_1c + 0x58));
        FUN_0082cdd2(*(undefined4 *)((int)local_1c + 0x58));
        FUN_0082cdd2(*(undefined4 *)((int)local_1c + 0x58));
        FUN_0082ced4(*(undefined4 *)((int)local_1c + 0x58));
        FUN_0082ced4();
      }
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xffffd8ee,"ClassId");
      FUN_0082c68b(*(undefined4 *)((int)local_1c + 0x58),0,0x38);
      for (local_28 = 0; local_28 < 0x1c; local_28 = local_28 + 1) {
        FUN_0082cd58(*(undefined4 *)((int)local_1c + 0x58),
                     (double)*(int *)(&DAT_008e8a20 + local_28 * 8));
        FUN_0082cd77(*(undefined4 *)((int)local_1c + 0x58));
        FUN_0082cdd2(*(undefined4 *)((int)local_1c + 0x58));
        FUN_0082cdd2(*(undefined4 *)((int)local_1c + 0x58));
        FUN_0082ced4(*(undefined4 *)((int)local_1c + 0x58));
        FUN_0082ced4();
      }
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xffffd8ee,"TeamSlot");
      FUN_0082c68b(*(undefined4 *)((int)local_1c + 0x58),0,8);
      for (local_2c = 0; local_2c < 4; local_2c = local_2c + 1) {
        FUN_0082cd58(*(undefined4 *)((int)local_1c + 0x58),
                     (double)*(int *)(&DAT_008e8b00 + local_2c * 8));
        FUN_0082cd77(*(undefined4 *)((int)local_1c + 0x58));
        FUN_0082cdd2(*(undefined4 *)((int)local_1c + 0x58));
        FUN_0082cdd2(*(undefined4 *)((int)local_1c + 0x58));
        FUN_0082ced4(*(undefined4 *)((int)local_1c + 0x58));
        FUN_0082ced4();
      }
      FUN_0082d102(*(undefined4 *)((int)local_1c + 0x58),0xffffd8ee,"PathType");
      FUN_0082c82c(*(undefined4 *)((int)local_1c + 0x58),0xffffd8ee,"package");
      FUN_0082c82c(*(undefined4 *)((int)local_1c + 0x58),0xffffffff,"loaders");
      FUN_0082cf99(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe);
      iVar3 = FUN_0082cb3b(*(undefined4 *)((int)local_1c + 0x58),0xffffffff);
      FUN_0082cc15(*(undefined4 *)((int)local_1c + 0x58),FUN_004ff640,0);
      FUN_0082cf37(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe,iVar3 + 1);
      FUN_0082d226(*(undefined4 *)((int)local_1c + 0x58),0xfffffffe);
      uVar4 = FUN_00481af0();
      uVar6 = FUN_00481a60();
      uVar4 = FUN_0082be6f(*(undefined4 *)((int)local_1c + 0x58),uVar4,uVar6,local_18,
                           *(undefined4 *)((int)local_1c + 0x58),"Lua script load error:\n%s");
      cVar1 = FUN_004ff600(uVar4);
      if (cVar1 != '\0') {
        uVar4 = FUN_0082cb8c(*(undefined4 *)((int)local_1c + 0x58),0,0xffffffff,0,
                             *(undefined4 *)((int)local_1c + 0x58),"Lua script run error:\n%s");
        FUN_004ff600(uVar4);
      }
      FUN_00481990();
    }
  }
  FUN_0083e885();
  return;
}

