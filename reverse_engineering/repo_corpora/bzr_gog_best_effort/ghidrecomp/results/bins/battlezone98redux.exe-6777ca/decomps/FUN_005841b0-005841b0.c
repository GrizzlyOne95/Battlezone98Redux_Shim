
void FUN_005841b0(void)

{
  char cVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined4 auStack_2a8 [13];
  undefined4 uStack_274;
  byte *pbStack_270;
  byte *pbStack_26c;
  undefined1 local_260 [12];
  undefined4 local_254;
  undefined1 local_250 [4];
  undefined1 local_24c [4];
  undefined4 local_248;
  byte *local_244;
  byte *local_240;
  int local_23c;
  int local_238;
  undefined4 local_234;
  uint local_230;
  float local_22c;
  int *local_228;
  byte *local_224;
  byte local_21d;
  undefined1 local_21c [4];
  byte *local_218;
  undefined4 local_214;
  undefined4 local_210;
  undefined2 local_20c;
  byte local_208 [512];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  DAT_00917f8d = 0;
  pbStack_26c = (byte *)0x5841d1;
  fVar6 = (float10)FUN_00822d80();
  local_22c = (float)fVar6;
  if (local_22c < DAT_0091812c) {
    DAT_0091812c = local_22c;
  }
  local_240 = local_208;
  local_218 = local_208 + 2;
  local_208[0] = 0x52;
  local_208[1] = 0x4f;
  pbStack_26c = local_21c;
  pbStack_270 = (byte *)0x58423b;
  FUN_0042d8c0();
  do {
    pbStack_26c = local_250;
    pbStack_270 = (byte *)0x58424c;
    pbStack_26c = (byte *)FID_conflict_begin();
    pbStack_270 = (byte *)0x584258;
    cVar1 = FUN_00420f10();
    if (cVar1 == '\0') {
LAB_005844e2:
      local_230 = (int)local_218 - (int)local_208;
      if (2 < local_230) {
        pbStack_270 = local_208;
        uStack_274 = 0x584512;
        pbStack_26c = (byte *)local_230;
        local_254 = FUN_00573170();
      }
      FUN_0083e885();
      return;
    }
    pbStack_26c = (byte *)0x58426e;
    piVar2 = (int *)FUN_0042de50();
    if (*(int *)(*piVar2 + 0x80) != 0) {
      pbStack_26c = (byte *)0x584288;
      piVar2 = (int *)FUN_0042de50();
      local_248 = *(undefined4 *)(*piVar2 + 0x80);
      local_244 = local_218;
      pbStack_26c = (byte *)0x5842ad;
      piVar2 = (int *)FUN_0042de50();
      local_23c = *(int *)(*piVar2 + 0xc);
      pbStack_26c = *(byte **)(local_23c + 0x1c);
      pbStack_270 = *(byte **)(local_23c + 0x18);
      uStack_274 = 0x5842cb;
      local_21d = FUN_00583e70();
      if ((local_21d & 0x80) == 0) {
        *(undefined4 *)local_218 = *(undefined4 *)(local_23c + 0x18);
        *(undefined4 *)(local_218 + 4) = *(undefined4 *)(local_23c + 0x1c);
        local_218 = local_218 + 8;
      }
      else {
        *local_218 = local_21d;
        local_218 = local_218 + 1;
      }
      local_224 = local_218;
      pbStack_26c = (byte *)0x58433e;
      piVar2 = (int *)FUN_0042de50();
      puVar3 = (undefined4 *)(*piVar2 + 0x88);
      puVar5 = auStack_2a8;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar5 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar5 = puVar5 + 1;
      }
      puVar3 = (undefined4 *)FUN_00625c50(local_260);
      local_214 = *puVar3;
      local_210 = puVar3[1];
      local_20c = *(undefined2 *)(puVar3 + 2);
      *(undefined4 *)local_224 = local_214;
      *(undefined4 *)(local_224 + 4) = local_210;
      *(undefined2 *)(local_224 + 8) = local_20c;
      pbStack_26c = (byte *)0x5843aa;
      piVar2 = (int *)FUN_0042de50();
      *(undefined2 *)(local_224 + 10) = *(undefined2 *)(*piVar2 + 0x7e);
      pbStack_26c = (byte *)0x5843c5;
      FUN_0042de50();
      pbStack_26c = (byte *)0x5843cc;
      pbStack_26c = (byte *)FUN_0046d000();
      pbStack_270 = (byte *)0x5843d2;
      local_238 = FUN_00479f30();
      if (local_238 == 0) {
        local_234 = 0;
      }
      else {
        pbStack_26c = (byte *)0x5843f2;
        local_234 = FUN_004b9a90();
      }
      *(undefined4 *)(local_224 + 0xc) = local_234;
      pbStack_26c = (byte *)0x58441e;
      piVar2 = (int *)FUN_0042de50();
      *(undefined4 *)(local_224 + 0x10) = *(undefined4 *)(*piVar2 + 200);
      local_218 = local_218 + 0x14;
      pbStack_26c = (byte *)0x584449;
      puVar3 = (undefined4 *)FUN_0042de50();
      local_228 = (int *)*puVar3;
      pbStack_26c = local_218;
      pbStack_270 = (byte *)0x58446b;
      iVar4 = (**(code **)(*local_228 + 0x1c))();
      local_218 = local_218 + iVar4;
      if (local_208 + DAT_00917fa0 < local_218) {
        pbStack_26c = (byte *)0x584496;
        piVar2 = (int *)FUN_0042de50();
        *(undefined4 *)(*piVar2 + 0x80) = local_248;
        local_218 = local_244;
        goto LAB_005844e2;
      }
      pbStack_26c = (byte *)0x5844bd;
      piVar2 = (int *)FUN_0042de50();
      *(undefined4 *)(*piVar2 + 0x80) = 2;
    }
    pbStack_26c = (byte *)0x0;
    pbStack_270 = local_24c;
    uStack_274 = 0x5844dd;
    FUN_00438c10();
  } while( true );
}

