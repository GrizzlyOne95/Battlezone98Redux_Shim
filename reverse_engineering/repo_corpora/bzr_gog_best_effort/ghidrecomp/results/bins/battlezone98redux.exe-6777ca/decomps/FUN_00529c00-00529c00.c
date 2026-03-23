
void FUN_00529c00(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_434 [64];
  undefined1 local_3f4 [64];
  undefined1 local_3b4 [64];
  undefined1 local_374 [64];
  float local_334;
  float local_330;
  float local_32c;
  float local_328;
  float local_324;
  float local_320;
  float local_31c;
  float local_318;
  float local_314;
  float local_310;
  float local_30c;
  float local_308;
  float local_304;
  float local_300;
  float local_2fc;
  float local_2f8;
  float local_2f4;
  float local_2f0;
  float local_2ec;
  float local_2e8;
  float local_2e4;
  float local_2e0;
  float local_2dc;
  float local_2d8;
  float local_2d4;
  float local_2d0;
  float local_2cc;
  float local_2c8;
  float local_2c4;
  float local_2c0;
  float local_2bc;
  float local_2b8;
  float local_2b4;
  float local_2b0;
  float local_2ac;
  float local_2a8;
  float local_2a4;
  float local_2a0;
  float local_29c;
  float local_298;
  float local_294;
  float local_290;
  float local_28c;
  float local_288;
  float local_284;
  float local_280;
  float local_27c;
  float local_278;
  float local_274;
  float local_270;
  float local_26c;
  float local_268;
  float local_264;
  float local_260;
  float local_25c;
  float local_258;
  float local_254;
  float local_250;
  float local_24c;
  float local_248;
  float local_244;
  float local_240;
  float local_23c;
  float local_238;
  float local_234;
  float local_230;
  float local_22c;
  float local_228;
  float local_224;
  float local_220;
  float local_21c;
  int local_218;
  undefined4 local_214 [16];
  undefined4 local_1d4 [16];
  undefined4 local_194 [16];
  undefined4 local_154 [16];
  undefined4 local_114 [16];
  undefined4 local_d4 [16];
  undefined4 local_94 [16];
  undefined4 local_54 [16];
  char local_14 [12];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar2 = FUN_005c7fb0();
  *(undefined4 *)(local_218 + 0x1f8) = uVar2;
  *(int *)(local_218 + 0x6e4) = *(int *)(local_218 + 0x6e4) + 10;
  if (0x6e < *(int *)(local_218 + 0x6e4)) {
    *(undefined4 *)(local_218 + 0x6e4) = 1;
  }
  if (*(char *)(local_218 + 0x56) == '\0') {
    FUN_005c9640(*(undefined4 *)(local_218 + 0x260),"Rendezvous Point");
    FUN_005cadd0(1,10);
    FUN_005c9610(*(undefined4 *)(local_218 + 0x234));
    FUN_005cc0c0(*(undefined4 *)(local_218 + 0x490),"patrol_path3",1);
    FUN_005cc0c0(*(undefined4 *)(local_218 + 0x494),"patrol_path3",1);
    FUN_005cc0c0(*(undefined4 *)(local_218 + 0x4b4),"patrol_path1",1);
    FUN_005cc0c0(*(undefined4 *)(local_218 + 0x4b8),"patrol_path1",1);
    FUN_005cc0c0(*(undefined4 *)(local_218 + 0x4c0),"patrol_path2",1);
    FUN_005cc0c0(*(undefined4 *)(local_218 + 0x4c4),"patrol_path2",1);
    FUN_005cb620(*(undefined4 *)(local_218 + 0x290),0);
    FUN_005cbd40(*(undefined4 *)(local_218 + 0x290),1);
    FUN_005c88b0(*(undefined4 *)(local_218 + 0x290),1);
    FUN_005cb620(*(undefined4 *)(local_218 + 0x294),0);
    FUN_005cbd40(*(undefined4 *)(local_218 + 0x294),1);
    FUN_005c88b0(*(undefined4 *)(local_218 + 0x294),1);
    FUN_005cbd40(*(undefined4 *)(local_218 + 0x4a8),1);
    FUN_005cbd40(*(undefined4 *)(local_218 + 0x4ac),1);
    fVar6 = (float10)FUN_00822d80();
    local_2a0 = (float)fVar6;
    *(float *)(local_218 + 0x1a4) = local_2a0 + 9.0;
    fVar6 = (float10)FUN_00822d80();
    local_2e4 = (float)fVar6;
    *(float *)(local_218 + 0x194) = local_2e4 + 121.0;
    fVar6 = (float10)FUN_00822d80();
    local_2ec = (float)fVar6;
    *(float *)(local_218 + 0x1a8) = local_2ec + 27.0;
    uVar2 = FUN_00460fc0("turret1_spot");
    *(undefined4 *)(local_218 + 0x51c) = uVar2;
    *(undefined4 *)(local_218 + 0x6e0) = 0;
    while (*(int *)(local_218 + 0x6e0) < 0x6f) {
      sprintf(local_14,"m%0.3d",*(undefined4 *)(local_218 + 0x6e0));
      uVar2 = FUN_00460fc0(local_14);
      *(undefined4 *)(local_218 + 0x520 + *(int *)(local_218 + 0x6e0) * 4) = uVar2;
      *(int *)(local_218 + 0x6e0) = *(int *)(local_218 + 0x6e0) + 1;
    }
    *(undefined1 *)(local_218 + 0x56) = 1;
  }
  if ((*(char *)(local_218 + 0x17b) == '\0') && (*(char *)(local_218 + 0x56) != '\0')) {
    fVar6 = (float10)FUN_00822d80();
    local_2f4 = (float)fVar6;
    if (*(float *)(local_218 + 0x1a4) <= local_2f4 && local_2f4 != *(float *)(local_218 + 0x1a4)) {
      fVar6 = (float10)FUN_00822d80();
      local_2fc = (float)fVar6;
      *(float *)(local_218 + 0x1a4) = local_2fc + 15.0;
      FUN_00437d30("misn0700.wav");
      FUN_004f6aa0();
      FUN_004f6ab0("misn0700.otf",DAT_0091755c,0x41000000,0);
      *(undefined1 *)(local_218 + 0x17b) = 1;
    }
  }
  if (*(char *)(local_218 + 0x56) != '\0') {
    fVar6 = (float10)FUN_00822d80();
    local_304 = (float)fVar6;
    if ((*(float *)(local_218 + 0x194) <= local_304 && local_304 != *(float *)(local_218 + 0x194))
       && (*(char *)(local_218 + 0x61) == '\0')) {
      cVar1 = FUN_005c84d0(local_218 + 0x4a8);
      if (cVar1 != '\0') {
        cVar1 = FUN_005c84d0(local_218 + 0x4ac);
        if ((cVar1 != '\0') && (*(char *)(local_218 + 0x7f) == '\0')) {
          FUN_005cc0c0(*(undefined4 *)(local_218 + 0x4a8),"patrol_path1",1);
          FUN_005cc0c0(*(undefined4 *)(local_218 + 0x4ac),"patrol_path1",1);
          *(undefined1 *)(local_218 + 0x7f) = 1;
        }
      }
    }
  }
  if (*(char *)(local_218 + 0x6f) == '\0') {
    fVar6 = (float10)FUN_00822d80();
    local_30c = (float)fVar6;
    if (((*(float *)(local_218 + 0x1a4) <= local_30c && local_30c != *(float *)(local_218 + 0x1a4))
        && (*(char *)(local_218 + 0x61) == '\0')) && (*(char *)(local_218 + 0x58) == '\0')) {
      fVar6 = (float10)FUN_00822d80();
      local_314 = (float)fVar6;
      *(float *)(local_218 + 0x1a4) = local_314 + 3.0;
      cVar1 = FUN_005c84d0(local_218 + 0x290);
      if (cVar1 == '\0') {
LAB_0052a1a0:
        cVar1 = FUN_005c84d0(local_218 + 0x294);
        if (cVar1 != '\0') {
          fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x1f8),
                                        *(undefined4 *)(local_218 + 0x294));
          local_324 = (float)fVar6;
          if ((local_324 < 150.0) && (*(char *)(local_218 + 0x61) == '\0')) goto LAB_0052a20f;
        }
      }
      else {
        fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x1f8),
                                      *(undefined4 *)(local_218 + 0x290));
        local_31c = (float)fVar6;
        if ((150.0 <= local_31c) || (*(char *)(local_218 + 0x61) != '\0')) goto LAB_0052a1a0;
LAB_0052a20f:
        uVar2 = FUN_00437d30("misn0701.wav");
        *(undefined4 *)(local_218 + 0x6f0) = uVar2;
        cVar1 = FUN_005c84d0(local_218 + 0x290);
        if (cVar1 != '\0') {
          puVar3 = (undefined4 *)FUN_005c8a90(local_374,*(undefined4 *)(local_218 + 0x290));
          puVar5 = local_114;
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar3 = local_114;
          puVar5 = local_54;
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          FUN_005c83e0(*(undefined4 *)(local_218 + 0x290));
          uVar2 = FUN_005c82b0("avtank",1,local_54,0);
          *(undefined4 *)(local_218 + 0x510) = uVar2;
        }
        cVar1 = FUN_005c84d0(local_218 + 0x294);
        if (cVar1 != '\0') {
          puVar3 = (undefined4 *)FUN_005c8a90(local_3f4,*(undefined4 *)(local_218 + 0x294));
          puVar5 = local_94;
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar3 = local_94;
          puVar5 = local_d4;
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          FUN_005c83e0(*(undefined4 *)(local_218 + 0x294));
          uVar2 = FUN_005c82b0("avtank",1,local_d4,0);
          *(undefined4 *)(local_218 + 0x514) = uVar2;
        }
        FUN_004f6aa0();
        FUN_004f6ab0("misn0700.otf",DAT_009175b0,0x41000000,0);
        FUN_004f6ab0("misn0701.otf",DAT_0091755c,0x41000000,0);
        fVar6 = (float10)FUN_00822d80();
        local_320 = (float)fVar6;
        *(float *)(local_218 + 0x184) = local_320 + 240.0;
        fVar6 = (float10)FUN_00822d80();
        local_228 = (float)fVar6;
        *(float *)(local_218 + 0x1b0) = local_228 + 6.0;
        fVar6 = (float10)FUN_00822d80();
        local_2b8 = (float)fVar6;
        *(float *)(local_218 + 0x194) = local_2b8 + 60.0;
        uVar2 = FUN_005c8250(&DAT_00878c18,1,"cam1_spawn",0,0);
        *(undefined4 *)(local_218 + 600) = uVar2;
        FUN_005c9640(*(undefined4 *)(local_218 + 600),"CCA Outpost");
        fVar6 = (float10)FUN_00822d80();
        local_230 = (float)fVar6;
        *(float *)(local_218 + 0x1f0) = local_230 + 10.0;
        *(undefined1 *)(local_218 + 0x61) = 1;
      }
    }
    if (*(char *)(local_218 + 0x61) != '\0') {
      fVar6 = (float10)FUN_00822d80();
      local_300 = (float)fVar6;
      if ((*(float *)(local_218 + 0x194) <= local_300 && local_300 != *(float *)(local_218 + 0x194))
         && (*(char *)(local_218 + 0x7f) == '\0')) {
        if (*(int *)(local_218 + 0x4a8) != 0) {
          FUN_005cb820(*(undefined4 *)(local_218 + 0x4a8),*(undefined4 *)(local_218 + 0x1f8),1);
        }
        if (*(int *)(local_218 + 0x4ac) != 0) {
          FUN_005cb820(*(undefined4 *)(local_218 + 0x4ac),*(undefined4 *)(local_218 + 0x1f8),1);
        }
        *(undefined1 *)(local_218 + 0x7f) = 1;
      }
    }
    cVar1 = FUN_005c84d0(local_218 + 600);
    if (cVar1 != '\0') {
      fVar6 = (float10)FUN_00822d80();
      local_238 = (float)fVar6;
      if ((*(float *)(local_218 + 0x1f0) <= local_238 && local_238 != *(float *)(local_218 + 0x1f0))
         && (*(char *)(local_218 + 0x179) == '\0')) {
        fVar6 = (float10)FUN_00822d80();
        local_2c0 = (float)fVar6;
        *(float *)(local_218 + 0x1f0) = local_2c0 + 4.0;
        fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x1f8),
                                      *(undefined4 *)(local_218 + 600));
        local_240 = (float)fVar6;
        if (local_240 < 90.0) {
          FUN_00437d30("misn0716.wav");
          *(undefined1 *)(local_218 + 0x179) = 1;
        }
      }
    }
  }
  if (((*(char *)(local_218 + 0x6f) == '\0') && (*(char *)(local_218 + 0x58) == '\0')) &&
     (*(char *)(local_218 + 0x57) == '\0')) {
    if ((*(char *)(local_218 + 0x61) != '\0') && (*(char *)(local_218 + 0x65) == '\0')) {
      fVar6 = (float10)FUN_00822d80();
      local_32c = (float)fVar6;
      if ((*(float *)(local_218 + 0x184) <= local_32c && local_32c != *(float *)(local_218 + 0x184))
         || (*(char *)(local_218 + 0x179) != '\0')) {
        fVar6 = (float10)FUN_00822d80();
        local_248 = (float)fVar6;
        *(float *)(local_218 + 0x184) = local_248 + 5.0;
        uVar2 = FUN_005ca520(*(undefined4 *)(local_218 + 0x1f8),0x43480000,2,"svfigh");
        *(undefined4 *)(local_218 + 0x6ec) = uVar2;
        fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x1f8),
                                      *(undefined4 *)(local_218 + 0x20c));
        local_2c8 = (float)fVar6;
        if ((400.0 < local_2c8) && (*(int *)(local_218 + 0x6ec) == 0)) {
          FUN_00437d30("misn0702.wav");
          uVar2 = FUN_005c8250(&DAT_00878c18,1,"jump_cam_spawn",0,0);
          *(undefined4 *)(local_218 + 0x208) = uVar2;
          uVar2 = FUN_005c8080("avfigh",1,*(undefined4 *)(local_218 + 0x20c),0);
          *(undefined4 *)(local_218 + 0x204) = uVar2;
          FUN_005cbc20(*(undefined4 *)(local_218 + 0x204),*(undefined4 *)(local_218 + 0x20c),1);
          fVar6 = (float10)FUN_00822d80();
          local_250 = (float)fVar6;
          *(float *)(local_218 + 0x198) = local_250 + 10.0;
          *(undefined1 *)(local_218 + 0x65) = 1;
        }
      }
    }
    if ((*(char *)(local_218 + 0x65) != '\0') && (*(int *)(local_218 + 0x208) != 0)) {
      FUN_005c9640(*(undefined4 *)(local_218 + 0x208),"Volcano Peak");
    }
    if (*(char *)(local_218 + 0x65) != '\0') {
      fVar6 = (float10)FUN_00822d80();
      local_308 = (float)fVar6;
      if ((*(float *)(local_218 + 0x198) <= local_308 && local_308 != *(float *)(local_218 + 0x198))
         && (*(char *)(local_218 + 0x66) == '\0')) {
        fVar6 = (float10)FUN_00822d80();
        local_258 = (float)fVar6;
        *(float *)(local_218 + 0x1ac) = local_258 + 10.0;
        *(undefined1 *)(local_218 + 0x66) = 1;
      }
    }
    if (*(char *)(local_218 + 0x66) != '\0') {
      fVar6 = (float10)FUN_00822d80();
      local_2d0 = (float)fVar6;
      if ((*(float *)(local_218 + 0x1ac) <= local_2d0 && local_2d0 != *(float *)(local_218 + 0x1ac))
         && (*(char *)(local_218 + 0x17a) == '\0')) {
        fVar6 = (float10)FUN_00822d80();
        local_260 = (float)fVar6;
        *(float *)(local_218 + 0x1ac) = local_260 + 3.0;
        cVar1 = FUN_005c84d0(local_218 + 0x204);
        if (cVar1 != '\0') {
          fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x1f8),
                                        *(undefined4 *)(local_218 + 0x204));
          local_328 = (float)fVar6;
          if (local_328 < 70.0) {
            FUN_005cbc80(*(undefined4 *)(local_218 + 0x204),1);
            FUN_00437d30("misn0718.wav");
            fVar6 = (float10)FUN_00822d80();
            local_268 = (float)fVar6;
            *(float *)(local_218 + 0x1ac) = local_268 + 10.0;
            *(undefined1 *)(local_218 + 0x17a) = 1;
          }
        }
      }
    }
    if (*(char *)(local_218 + 0x17a) != '\0') {
      fVar6 = (float10)FUN_00822d80();
      local_2d8 = (float)fVar6;
      if ((*(float *)(local_218 + 0x1ac) <= local_2d8 && local_2d8 != *(float *)(local_218 + 0x1ac))
         && (*(char *)(local_218 + 0x163) == '\0')) {
        cVar1 = FUN_005c84d0(local_218 + 0x204);
        if (cVar1 != '\0') {
          FUN_00437d30("misn0715.wav");
          FUN_005ccc90(*(undefined4 *)(local_218 + 0x204));
          *(undefined1 *)(local_218 + 0x163) = 1;
        }
      }
    }
  }
  fVar6 = (float10)FUN_00822d80();
  local_270 = (float)fVar6;
  if ((*(float *)(local_218 + 0x1a8) <= local_270 && local_270 != *(float *)(local_218 + 0x1a8)) &&
     (*(char *)(local_218 + 0x58) == '\0')) {
    fVar6 = (float10)FUN_00822d80();
    local_310 = (float)fVar6;
    *(float *)(local_218 + 0x1a8) = local_310 + 5.0;
    if ((*(char *)(local_218 + 0x58) == '\0') && (*(char *)(local_218 + 0x57) == '\0')) {
      fVar6 = (float10)FUN_005c98f0(*(undefined4 *)(local_218 + 0x1f8),
                                    *(undefined4 *)(local_218 + 0x51c),0);
      local_278 = (float)fVar6;
      if (local_278 < 70.0) {
        FUN_00437d30("misn0710.wav");
        FUN_005c95e0(*(undefined4 *)(local_218 + 0x234));
        FUN_005c9640(*(undefined4 *)(local_218 + 0x234),"Radar Array");
        *(undefined1 *)(local_218 + 0x58) = 1;
      }
    }
  }
  if ((*(char *)(local_218 + 0x6f) == '\0') && (*(char *)(local_218 + 0x58) != '\0')) {
    if (*(int *)(local_218 + 0x234) != 0) {
      fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x1f8),
                                    *(undefined4 *)(local_218 + 0x234));
      local_2e0 = (float)fVar6;
      if ((local_2e0 < 170.0) && (*(char *)(local_218 + 0x162) == '\0')) {
        FUN_00437d30("misn0708.wav");
        fVar6 = (float10)FUN_00822d80();
        local_280 = (float)fVar6;
        *(float *)(local_218 + 0x1a0) = local_280 + 6.0;
        *(undefined1 *)(local_218 + 0x162) = 1;
      }
    }
    if (*(char *)(local_218 + 0x162) != '\0') {
      fVar6 = (float10)FUN_00822d80();
      local_334 = (float)fVar6;
      if (*(float *)(local_218 + 0x1a0) <= local_334 && local_334 != *(float *)(local_218 + 0x1a0))
      {
        *(undefined1 *)(local_218 + 0x162) = 0;
      }
    }
    if (*(char *)(local_218 + 0x71) == '\0') {
      FUN_005c95e0(*(undefined4 *)(local_218 + 0x234));
      FUN_005c9640(*(undefined4 *)(local_218 + 0x234),"Radar Array");
      FUN_005cc140(*(undefined4 *)(local_218 + 0x4c8),*(undefined4 *)(local_218 + 0x234),1);
      FUN_005cc140(*(undefined4 *)(local_218 + 0x4cc),*(undefined4 *)(local_218 + 0x234),1);
      *(undefined1 *)(local_218 + 0x71) = 1;
    }
    if (*(char *)(local_218 + 0x59) == '\0') {
      fVar6 = (float10)FUN_00822d80();
      local_288 = (float)fVar6;
      *(float *)(local_218 + 0x180) = local_288 + 20.0;
      *(undefined1 *)(local_218 + 0x59) = 1;
    }
    if (*(char *)(local_218 + 0x59) != '\0') {
      fVar6 = (float10)FUN_00822d80();
      local_2e8 = (float)fVar6;
      if (((*(float *)(local_218 + 0x180) <= local_2e8 && local_2e8 != *(float *)(local_218 + 0x180)
           ) && (*(char *)(local_218 + 0x80) == '\0')) && (*(char *)(local_218 + 0x83) == '\0')) {
        uVar2 = FUN_005c8250("sspilo",2,"hut2_spawn",0,0);
        *(undefined4 *)(local_218 + 0x218) = uVar2;
        uVar2 = FUN_005c8250("sspilo",2,"hut2_spawn",0,0);
        *(undefined4 *)(local_218 + 0x21c) = uVar2;
        uVar2 = FUN_005c8250("sspilo",2,"hut2_spawn",0,0);
        *(undefined4 *)(local_218 + 0x220) = uVar2;
        uVar2 = FUN_005c8250("sspilo",2,"hut1_spawn",0,0);
        *(undefined4 *)(local_218 + 0x224) = uVar2;
        uVar2 = FUN_005c8250("sspilo",2,"hut1_spawn",0,0);
        *(undefined4 *)(local_218 + 0x228) = uVar2;
        if (*(int *)(local_218 + 0x4e4) != *(int *)(local_218 + 0x1f8)) {
          puVar3 = (undefined4 *)FUN_005c8a90(local_3b4,*(undefined4 *)(local_218 + 0x4e4));
          puVar5 = local_154;
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar3 = local_154;
          puVar5 = local_214;
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          FUN_005c83e0(*(undefined4 *)(local_218 + 0x4e4));
          uVar2 = FUN_005c82b0("svturr",2,local_214,0);
          *(undefined4 *)(local_218 + 0x4d0) = uVar2;
          FUN_005cbc80(*(undefined4 *)(local_218 + 0x4d0),1);
        }
        if (*(int *)(local_218 + 0x4e8) != *(int *)(local_218 + 0x1f8)) {
          puVar3 = (undefined4 *)FUN_005c8a90(local_434,*(undefined4 *)(local_218 + 0x4e8));
          puVar5 = local_1d4;
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          puVar3 = local_1d4;
          puVar5 = local_194;
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          FUN_005c83e0(*(undefined4 *)(local_218 + 0x4e8));
          uVar2 = FUN_005c82b0("svturr",2,local_194,0);
          *(undefined4 *)(local_218 + 0x4d4) = uVar2;
          FUN_005cbc80(*(undefined4 *)(local_218 + 0x4d4),1);
        }
        if (*(int *)(local_218 + 0x4d8) != 0) {
          FUN_005cc140(*(undefined4 *)(local_218 + 0x218),*(undefined4 *)(local_218 + 0x4d8),1);
        }
        if (*(int *)(local_218 + 0x4dc) != 0) {
          FUN_005cc140(*(undefined4 *)(local_218 + 0x21c),*(undefined4 *)(local_218 + 0x4dc),1);
        }
        if (*(int *)(local_218 + 0x4e0) != 0) {
          FUN_005cc140(*(undefined4 *)(local_218 + 0x220),*(undefined4 *)(local_218 + 0x4e0),1);
        }
        *(undefined1 *)(local_218 + 0x80) = 1;
      }
    }
    if ((*(char *)(local_218 + 0x59) != '\0') && (*(char *)(local_218 + 0x83) != '\0')) {
      fVar6 = (float10)FUN_00822d80();
      local_290 = (float)fVar6;
      if ((*(float *)(local_218 + 0x180) <= local_290 && local_290 != *(float *)(local_218 + 0x180))
         && (*(char *)(local_218 + 0x80) == '\0')) {
        uVar2 = FUN_005c8250("sspilo",2,"hut2_spawn",0,0);
        *(undefined4 *)(local_218 + 0x218) = uVar2;
        uVar2 = FUN_005c8250("sspilo",2,"hut2_spawn",0,0);
        *(undefined4 *)(local_218 + 0x21c) = uVar2;
        uVar2 = FUN_005c8250("sssold",2,"hut2_spawn",0,0);
        *(undefined4 *)(local_218 + 0x220) = uVar2;
        uVar2 = FUN_005c8250("sspilo",2,"hut1_spawn",0,0);
        *(undefined4 *)(local_218 + 0x224) = uVar2;
        uVar2 = FUN_005c8250("sssold",2,"hut1_spawn",0,0);
        *(undefined4 *)(local_218 + 0x228) = uVar2;
        FUN_005cb820(*(undefined4 *)(local_218 + 0x220),*(undefined4 *)(local_218 + 0x1f8),1);
        FUN_005cb820(*(undefined4 *)(local_218 + 0x228),*(undefined4 *)(local_218 + 0x1f8),1);
        if (*(int *)(local_218 + 0x4d8) != 0) {
          FUN_005cc140(*(undefined4 *)(local_218 + 0x218),*(undefined4 *)(local_218 + 0x4d8),1);
        }
        if (*(int *)(local_218 + 0x4dc) != 0) {
          FUN_005cc140(*(undefined4 *)(local_218 + 0x21c),*(undefined4 *)(local_218 + 0x4dc),1);
        }
        if (*(int *)(local_218 + 0x4e0) != 0) {
          FUN_005cc140(*(undefined4 *)(local_218 + 0x224),*(undefined4 *)(local_218 + 0x4e4),1);
        }
        *(undefined1 *)(local_218 + 0x80) = 1;
      }
    }
    if ((*(char *)(local_218 + 0x80) != '\0') && (*(char *)(local_218 + 0x83) == '\0')) {
      cVar1 = FUN_005c84d0(local_218 + 0x218);
      if ((cVar1 == '\0') && (*(int *)(local_218 + 0x4d8) != 0)) {
        FUN_005cb820(*(undefined4 *)(local_218 + 0x4d8),*(undefined4 *)(local_218 + 0x1f8),1);
      }
      cVar1 = FUN_005c84d0(local_218 + 0x21c);
      if ((cVar1 == '\0') && (*(int *)(local_218 + 0x4dc) != 0)) {
        FUN_005cb820(*(undefined4 *)(local_218 + 0x4dc),*(undefined4 *)(local_218 + 0x1f8),1);
      }
      cVar1 = FUN_005c84d0(local_218 + 0x220);
      if ((cVar1 == '\0') && (*(int *)(local_218 + 0x4e0) != 0)) {
        FUN_005cb820(*(undefined4 *)(local_218 + 0x4e0),*(undefined4 *)(local_218 + 0x1f8),1);
      }
    }
    if ((*(char *)(local_218 + 0x80) != '\0') && (*(char *)(local_218 + 0x83) != '\0')) {
      cVar1 = FUN_005c84d0(local_218 + 0x218);
      if ((cVar1 == '\0') && (*(int *)(local_218 + 0x4d8) != 0)) {
        FUN_005cb9d0(*(undefined4 *)(local_218 + 0x4d8),*(undefined4 *)(local_218 + 0x234),1);
      }
      cVar1 = FUN_005c84d0(local_218 + 0x21c);
      if ((cVar1 == '\0') && (*(int *)(local_218 + 0x4dc) != 0)) {
        FUN_005cb9d0(*(undefined4 *)(local_218 + 0x4dc),*(undefined4 *)(local_218 + 0x234),1);
      }
      cVar1 = FUN_005c84d0(local_218 + 0x224);
      if ((cVar1 == '\0') && (*(int *)(local_218 + 0x4e4) != 0)) {
        FUN_005cc100(*(undefined4 *)(local_218 + 0x4e4),"turret1_spot",1);
      }
    }
    cVar1 = FUN_005c84d0(local_218 + 0x234);
    if (cVar1 != '\0') {
      fVar6 = (float10)FUN_005cced0(*(undefined4 *)(local_218 + 0x234));
      local_318 = (float)fVar6;
      if ((local_318 < 0.5) && (*(char *)(local_218 + 0x164) == '\0')) {
        cVar1 = FUN_005c84d0(local_218 + 0x4a0);
        if (cVar1 != '\0') {
          FUN_005cb9d0(*(undefined4 *)(local_218 + 0x4a0),*(undefined4 *)(local_218 + 0x234),1);
        }
        cVar1 = FUN_005c84d0(local_218 + 0x4b4);
        if (cVar1 != '\0') {
          FUN_005cb9d0(*(undefined4 *)(local_218 + 0x4b4),*(undefined4 *)(local_218 + 0x234),1);
        }
        cVar1 = FUN_005c84d0(local_218 + 0x4c0);
        if (cVar1 != '\0') {
          FUN_005cb9d0(*(undefined4 *)(local_218 + 0x4c0),*(undefined4 *)(local_218 + 0x234),1);
        }
        *(undefined1 *)(local_218 + 0x164) = 1;
      }
    }
  }
  if (*(char *)(local_218 + 0x6f) == '\0') {
    if ((*(char *)(local_218 + 0x58) == '\0') && (*(char *)(local_218 + 0x57) == '\0')) {
      fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x1f8),
                                    *(undefined4 *)(local_218 + 0x508));
      local_298 = (float)fVar6;
      if (local_298 < 160.0) {
        FUN_005c95e0(*(undefined4 *)(local_218 + 0x234));
        FUN_005c9640(*(undefined4 *)(local_218 + 0x234),"Radar Array");
        *(undefined1 *)(local_218 + 0x57) = 1;
      }
    }
    if (*(char *)(local_218 + 0x57) == '\0') {
LAB_0052b676:
      if (*(char *)(local_218 + 0x57) != '\0') {
        cVar1 = FUN_005c8410(*(undefined4 *)(local_218 + 0x1f8),"svfigh");
        if (cVar1 != '\0') goto LAB_0052b6e5;
      }
      if (*(char *)(local_218 + 0x57) != '\0') {
        cVar1 = FUN_005c8410(*(undefined4 *)(local_218 + 0x1f8),"svturr");
        if ((cVar1 != '\0') && (*(char *)(local_218 + 0x81) == '\0')) goto LAB_0052b6e5;
      }
    }
    else {
      cVar1 = FUN_005c8410(*(undefined4 *)(local_218 + 0x1f8),"svtank");
      if (cVar1 == '\0') goto LAB_0052b676;
LAB_0052b6e5:
      *(undefined1 *)(local_218 + 0x81) = 1;
    }
    if ((*(char *)(local_218 + 0x82) == '\0') && (*(char *)(local_218 + 0x57) != '\0')) {
      cVar1 = FUN_005c8720(*(undefined4 *)(local_218 + 0x22c),0x3f733333);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c8720(*(undefined4 *)(local_218 + 0x230),0x3f733333);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c8720(*(undefined4 *)(local_218 + 0x234),0x3f733333);
          if (cVar1 == '\0') {
            cVar1 = FUN_005c8720(*(undefined4 *)(local_218 + 0x238),0x3f733333);
            if (cVar1 == '\0') {
              cVar1 = FUN_005c8720(*(undefined4 *)(local_218 + 0x250),0x3f733333);
              if (cVar1 == '\0') {
                cVar1 = FUN_005c8720(*(undefined4 *)(local_218 + 0x254),0x3f733333);
                if (cVar1 == '\0') {
                  cVar1 = FUN_005c8720(*(undefined4 *)(local_218 + 0x4d8),0x3f733333);
                  if (cVar1 == '\0') {
                    cVar1 = FUN_005c8720(*(undefined4 *)(local_218 + 0x4dc),0x3f733333);
                    if (cVar1 == '\0') {
                      cVar1 = FUN_005c8720(*(undefined4 *)(local_218 + 0x4e0),0x3f733333);
                      if (cVar1 == '\0') {
                        cVar1 = FUN_005c8720(*(undefined4 *)(local_218 + 0x4e4),0x3f733333);
                        if (cVar1 == '\0') {
                          cVar1 = FUN_005c8720(*(undefined4 *)(local_218 + 0x4e8),0x3f733333);
                          if (cVar1 == '\0') goto LAB_0052b910;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      *(undefined1 *)(local_218 + 0x82) = 1;
    }
LAB_0052b910:
    if (((*(char *)(local_218 + 0x82) != '\0') && (*(char *)(local_218 + 0x81) != '\0')) &&
       (*(char *)(local_218 + 0x58) == '\0')) {
      *(undefined1 *)(local_218 + 0x58) = 1;
    }
    if (((*(char *)(local_218 + 0x82) != '\0') && (*(char *)(local_218 + 0x81) == '\0')) &&
       (*(char *)(local_218 + 0x58) == '\0')) {
      *(undefined1 *)(local_218 + 0x58) = 1;
      *(undefined1 *)(local_218 + 0x83) = 1;
    }
  }
  if (*(char *)(local_218 + 0x6f) == '\0') {
    if ((*(char *)(local_218 + 0x58) == '\0') && (*(char *)(local_218 + 0x57) == '\0')) {
      fVar6 = (float10)FUN_005c98f0(*(undefined4 *)(local_218 + 0x284),
                                    *(undefined4 *)(local_218 + 0x51c),0);
      local_2f0 = (float)fVar6;
      if (local_2f0 < 100.0) {
        FUN_00437d30("misn0709.wav");
        *(undefined1 *)(local_218 + 0x58) = 1;
      }
    }
    if ((*(char *)(local_218 + 0x58) == '\0') && (*(char *)(local_218 + 0x57) == '\0')) {
      fVar6 = (float10)FUN_005c98f0(*(undefined4 *)(local_218 + 0x288),
                                    *(undefined4 *)(local_218 + 0x51c),0);
      local_21c = (float)fVar6;
      if (local_21c < 100.0) {
        FUN_00437d30("misn0709.wav");
        *(undefined1 *)(local_218 + 0x58) = 1;
      }
    }
    if ((*(char *)(local_218 + 0x58) == '\0') && (*(char *)(local_218 + 0x57) == '\0')) {
      fVar6 = (float10)FUN_005c98f0(*(undefined4 *)(local_218 + 0x28c),
                                    *(undefined4 *)(local_218 + 0x51c),0);
      local_330 = (float)fVar6;
      if (local_330 < 100.0) {
        FUN_00437d30("misn0709.wav");
        *(undefined1 *)(local_218 + 0x58) = 1;
      }
    }
    if ((*(char *)(local_218 + 0x58) == '\0') && (*(char *)(local_218 + 0x57) == '\0')) {
      fVar6 = (float10)FUN_005c98f0(*(undefined4 *)(local_218 + 0x510),
                                    *(undefined4 *)(local_218 + 0x51c),0);
      local_2a8 = (float)fVar6;
      if (local_2a8 < 100.0) {
        FUN_00437d30("misn0709.wav");
        *(undefined1 *)(local_218 + 0x58) = 1;
      }
    }
    if ((*(char *)(local_218 + 0x58) == '\0') && (*(char *)(local_218 + 0x57) == '\0')) {
      fVar6 = (float10)FUN_005c98f0(*(undefined4 *)(local_218 + 0x514),
                                    *(undefined4 *)(local_218 + 0x51c),0);
      local_2f8 = (float)fVar6;
      if (local_2f8 < 100.0) {
        FUN_00437d30("misn0709.wav");
        *(undefined1 *)(local_218 + 0x58) = 1;
      }
    }
  }
  if (*(char *)(local_218 + 0x6f) != '\0') goto LAB_0052d225;
  if (*(char *)(local_218 + 0x7d) == '\0') {
    cVar1 = FUN_005c84d0(local_218 + 0x4a0);
    if (cVar1 != '\0') {
      cVar1 = FUN_005c84d0(local_218 + 0x49c);
      if ((cVar1 == '\0') && (*(char *)(local_218 + 0x61) != '\0')) {
        cVar1 = FUN_005c84d0(local_218 + 0x464);
        if ((cVar1 != '\0') &&
           (((*(char *)(local_218 + 0x6f) == '\0' && (*(char *)(local_218 + 0x74) == '\0')) &&
            (*(char *)(local_218 + 0x58) == '\0')))) {
          fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x1f8),
                                        *(undefined4 *)(local_218 + 0x4a0));
          local_2b0 = (float)fVar6;
          if ((((local_2b0 < 50.0) && (*(char *)(local_218 + 0x6a) == '\0')) &&
              (*(char *)(local_218 + 0x6b) == '\0')) && (*(char *)(local_218 + 0x6c) == '\0')) {
            FUN_005cc140(*(undefined4 *)(local_218 + 0x4a0),*(undefined4 *)(local_218 + 0x464),1);
            FUN_005c95e0(*(undefined4 *)(local_218 + 0x4a0));
            FUN_005c9640(*(undefined4 *)(local_218 + 0x4a0),"Runner");
            fVar6 = (float10)FUN_00822d80();
            local_220 = (float)fVar6;
            *(float *)(local_218 + 400) = local_220 + 3.0;
            *(undefined1 *)(local_218 + 0x6a) = 1;
          }
        }
      }
    }
    cVar1 = FUN_005c84d0(local_218 + 0x49c);
    if (cVar1 != '\0') {
      cVar1 = FUN_005c84d0(local_218 + 0x4a0);
      if ((cVar1 == '\0') && (*(char *)(local_218 + 0x61) != '\0')) {
        cVar1 = FUN_005c84d0(local_218 + 0x464);
        if ((cVar1 != '\0') &&
           (((*(char *)(local_218 + 0x6f) == '\0' && (*(char *)(local_218 + 0x74) == '\0')) &&
            (*(char *)(local_218 + 0x58) == '\0')))) {
          fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x1f8),
                                        *(undefined4 *)(local_218 + 0x49c));
          local_224 = (float)fVar6;
          if (((local_224 < 50.0) && (*(char *)(local_218 + 0x6a) == '\0')) &&
             ((*(char *)(local_218 + 0x6b) == '\0' && (*(char *)(local_218 + 0x6c) == '\0')))) {
            FUN_005cc140(*(undefined4 *)(local_218 + 0x49c),*(undefined4 *)(local_218 + 0x464),1);
            FUN_005c95e0(*(undefined4 *)(local_218 + 0x49c));
            FUN_005c9640(*(undefined4 *)(local_218 + 0x49c),"Runner");
            fVar6 = (float10)FUN_00822d80();
            local_22c = (float)fVar6;
            *(float *)(local_218 + 400) = local_22c + 3.0;
            *(undefined1 *)(local_218 + 0x6a) = 1;
          }
        }
      }
    }
    cVar1 = FUN_005c84d0(local_218 + 0x4b8);
    if (cVar1 != '\0') {
      cVar1 = FUN_005c84d0(local_218 + 0x4b4);
      if ((cVar1 == '\0') && (*(char *)(local_218 + 0x61) != '\0')) {
        cVar1 = FUN_005c84d0(local_218 + 0x464);
        if ((cVar1 != '\0') &&
           (((*(char *)(local_218 + 0x6f) == '\0' && (*(char *)(local_218 + 0x74) == '\0')) &&
            (*(char *)(local_218 + 0x58) == '\0')))) {
          fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x1f8),
                                        *(undefined4 *)(local_218 + 0x4b8));
          local_234 = (float)fVar6;
          if ((((local_234 < 50.0) && (*(char *)(local_218 + 0x6b) == '\0')) &&
              (*(char *)(local_218 + 0x6a) == '\0')) && (*(char *)(local_218 + 0x6c) == '\0')) {
            FUN_005cc140(*(undefined4 *)(local_218 + 0x4b8),*(undefined4 *)(local_218 + 0x464),1);
            FUN_005c95e0(*(undefined4 *)(local_218 + 0x4b8));
            FUN_005c9640(*(undefined4 *)(local_218 + 0x4b8),"Runner");
            fVar6 = (float10)FUN_00822d80();
            local_23c = (float)fVar6;
            *(float *)(local_218 + 400) = local_23c + 3.0;
            *(undefined1 *)(local_218 + 0x6c) = 1;
          }
        }
      }
    }
    cVar1 = FUN_005c84d0(local_218 + 0x4b4);
    if (cVar1 != '\0') {
      cVar1 = FUN_005c84d0(local_218 + 0x4b8);
      if ((cVar1 == '\0') && (*(char *)(local_218 + 0x61) != '\0')) {
        cVar1 = FUN_005c84d0(local_218 + 0x464);
        if ((cVar1 != '\0') &&
           (((*(char *)(local_218 + 0x6f) == '\0' && (*(char *)(local_218 + 0x74) == '\0')) &&
            (*(char *)(local_218 + 0x58) == '\0')))) {
          fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x1f8),
                                        *(undefined4 *)(local_218 + 0x4b4));
          local_244 = (float)fVar6;
          if (((local_244 < 50.0) && (*(char *)(local_218 + 0x6b) == '\0')) &&
             ((*(char *)(local_218 + 0x6a) == '\0' && (*(char *)(local_218 + 0x6c) == '\0')))) {
            FUN_005cc140(*(undefined4 *)(local_218 + 0x4b4),*(undefined4 *)(local_218 + 0x464),1);
            FUN_005c95e0(*(undefined4 *)(local_218 + 0x4b4));
            FUN_005c9640(*(undefined4 *)(local_218 + 0x4b4),"Runner");
            fVar6 = (float10)FUN_00822d80();
            local_24c = (float)fVar6;
            *(float *)(local_218 + 400) = local_24c + 3.0;
            *(undefined1 *)(local_218 + 0x6c) = 1;
          }
        }
      }
    }
    if ((*(char *)(local_218 + 0x7d) == '\0') && (*(char *)(local_218 + 0x76) == '\0')) {
      if (*(char *)(local_218 + 0x6a) == '\0') {
LAB_0052c2ec:
        if (*(char *)(local_218 + 0x6a) != '\0') {
          fVar6 = (float10)FUN_00822d80();
          local_25c = (float)fVar6;
          if (*(float *)(local_218 + 400) <= local_25c && local_25c != *(float *)(local_218 + 400))
          {
            cVar1 = FUN_005c84d0(local_218 + 0x514);
            if ((cVar1 != '\0') && (*(char *)(local_218 + 0x76) == '\0')) goto LAB_0052c346;
          }
        }
      }
      else {
        fVar6 = (float10)FUN_00822d80();
        local_254 = (float)fVar6;
        if (local_254 < *(float *)(local_218 + 400) || local_254 == *(float *)(local_218 + 400))
        goto LAB_0052c2ec;
        cVar1 = FUN_005c84d0(local_218 + 0x510);
        if ((cVar1 == '\0') || (*(char *)(local_218 + 0x76) != '\0')) goto LAB_0052c2ec;
LAB_0052c346:
        FUN_00437d30("misn0705.wav");
        *(undefined1 *)(local_218 + 0x76) = 1;
      }
      if (*(char *)(local_218 + 0x6b) == '\0') {
LAB_0052c3b7:
        if (*(char *)(local_218 + 0x6b) != '\0') {
          fVar6 = (float10)FUN_00822d80();
          local_26c = (float)fVar6;
          if (*(float *)(local_218 + 400) <= local_26c && local_26c != *(float *)(local_218 + 400))
          {
            cVar1 = FUN_005c84d0(local_218 + 0x514);
            if ((cVar1 != '\0') && (*(char *)(local_218 + 0x76) == '\0')) goto LAB_0052c411;
          }
        }
      }
      else {
        fVar6 = (float10)FUN_00822d80();
        local_264 = (float)fVar6;
        if (local_264 < *(float *)(local_218 + 400) || local_264 == *(float *)(local_218 + 400))
        goto LAB_0052c3b7;
        cVar1 = FUN_005c84d0(local_218 + 0x510);
        if ((cVar1 == '\0') || (*(char *)(local_218 + 0x76) != '\0')) goto LAB_0052c3b7;
LAB_0052c411:
        FUN_00437d30("misn0705.wav");
        *(undefined1 *)(local_218 + 0x76) = 1;
      }
      if (*(char *)(local_218 + 0x6c) == '\0') {
LAB_0052c482:
        if (*(char *)(local_218 + 0x6c) != '\0') {
          fVar6 = (float10)FUN_00822d80();
          local_27c = (float)fVar6;
          if (*(float *)(local_218 + 400) <= local_27c && local_27c != *(float *)(local_218 + 400))
          {
            cVar1 = FUN_005c84d0(local_218 + 0x514);
            if ((cVar1 != '\0') && (*(char *)(local_218 + 0x76) == '\0')) goto LAB_0052c4dc;
          }
        }
      }
      else {
        fVar6 = (float10)FUN_00822d80();
        local_274 = (float)fVar6;
        if (local_274 < *(float *)(local_218 + 400) || local_274 == *(float *)(local_218 + 400))
        goto LAB_0052c482;
        cVar1 = FUN_005c84d0(local_218 + 0x510);
        if ((cVar1 == '\0') || (*(char *)(local_218 + 0x76) != '\0')) goto LAB_0052c482;
LAB_0052c4dc:
        FUN_00437d30("misn0705.wav");
        *(undefined1 *)(local_218 + 0x76) = 1;
      }
    }
    if (*(char *)(local_218 + 0x6a) != '\0') {
      cVar1 = FUN_005c84d0(local_218 + 0x49c);
      if (cVar1 != '\0') {
        *(undefined1 *)(local_218 + 0x77) = 1;
      }
    }
    if (*(char *)(local_218 + 0x6a) != '\0') {
      cVar1 = FUN_005c84d0(local_218 + 0x4a0);
      if (cVar1 != '\0') {
        *(undefined1 *)(local_218 + 0x78) = 1;
      }
    }
    if (*(char *)(local_218 + 0x6b) != '\0') {
      cVar1 = FUN_005c84d0(local_218 + 0x4a8);
      if (cVar1 != '\0') {
        *(undefined1 *)(local_218 + 0x79) = 1;
      }
    }
    if (*(char *)(local_218 + 0x6b) != '\0') {
      cVar1 = FUN_005c84d0(local_218 + 0x4ac);
      if (cVar1 != '\0') {
        *(undefined1 *)(local_218 + 0x7a) = 1;
      }
    }
    if (*(char *)(local_218 + 0x6c) != '\0') {
      cVar1 = FUN_005c84d0(local_218 + 0x4b4);
      if (cVar1 != '\0') {
        *(undefined1 *)(local_218 + 0x7b) = 1;
      }
    }
    if (*(char *)(local_218 + 0x6c) != '\0') {
      cVar1 = FUN_005c84d0(local_218 + 0x4b8);
      if (cVar1 != '\0') {
        *(undefined1 *)(local_218 + 0x7c) = 1;
      }
    }
    if ((*(char *)(local_218 + 0x6a) == '\0') || (*(char *)(local_218 + 0x77) == '\0')) {
LAB_0052c67d:
      if ((*(char *)(local_218 + 0x6a) != '\0') && (*(char *)(local_218 + 0x77) != '\0')) {
        cVar1 = FUN_005c84d0(local_218 + 0x49c);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(local_218 + 0x514);
          if (cVar1 != '\0') goto LAB_0052c6d0;
        }
      }
    }
    else {
      cVar1 = FUN_005c84d0(local_218 + 0x49c);
      if (cVar1 != '\0') goto LAB_0052c67d;
      cVar1 = FUN_005c84d0(local_218 + 0x510);
      if (cVar1 == '\0') goto LAB_0052c67d;
LAB_0052c6d0:
      FUN_00437d30("misn0706.wav");
      *(undefined1 *)(local_218 + 0x6a) = 0;
      *(undefined1 *)(local_218 + 0x77) = 0;
      *(undefined1 *)(local_218 + 0x76) = 0;
    }
    if ((*(char *)(local_218 + 0x6a) == '\0') || (*(char *)(local_218 + 0x78) == '\0')) {
LAB_0052c74e:
      if ((*(char *)(local_218 + 0x6a) != '\0') && (*(char *)(local_218 + 0x78) != '\0')) {
        cVar1 = FUN_005c84d0(local_218 + 0x4a0);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(local_218 + 0x514);
          if (cVar1 != '\0') goto LAB_0052c7a2;
        }
      }
    }
    else {
      cVar1 = FUN_005c84d0(local_218 + 0x4a0);
      if (cVar1 != '\0') goto LAB_0052c74e;
      cVar1 = FUN_005c84d0(local_218 + 0x510);
      if (cVar1 == '\0') goto LAB_0052c74e;
LAB_0052c7a2:
      FUN_00437d30("misn0706.wav");
      *(undefined1 *)(local_218 + 0x6a) = 0;
      *(undefined1 *)(local_218 + 0x78) = 0;
      *(undefined1 *)(local_218 + 0x76) = 0;
    }
    if ((*(char *)(local_218 + 0x6b) == '\0') || (*(char *)(local_218 + 0x79) == '\0')) {
LAB_0052c820:
      if ((*(char *)(local_218 + 0x6b) != '\0') && (*(char *)(local_218 + 0x79) != '\0')) {
        cVar1 = FUN_005c84d0(local_218 + 0x4a8);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(local_218 + 0x514);
          if (cVar1 != '\0') goto LAB_0052c873;
        }
      }
    }
    else {
      cVar1 = FUN_005c84d0(local_218 + 0x4a8);
      if (cVar1 != '\0') goto LAB_0052c820;
      cVar1 = FUN_005c84d0(local_218 + 0x510);
      if (cVar1 == '\0') goto LAB_0052c820;
LAB_0052c873:
      FUN_00437d30("misn0706.wav");
      *(undefined1 *)(local_218 + 0x6b) = 0;
      *(undefined1 *)(local_218 + 0x79) = 0;
      *(undefined1 *)(local_218 + 0x76) = 0;
    }
    if ((*(char *)(local_218 + 0x6b) == '\0') || (*(char *)(local_218 + 0x7a) == '\0')) {
LAB_0052c8f2:
      if ((*(char *)(local_218 + 0x6b) != '\0') && (*(char *)(local_218 + 0x7a) != '\0')) {
        cVar1 = FUN_005c84d0(local_218 + 0x4ac);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(local_218 + 0x514);
          if (cVar1 != '\0') goto LAB_0052c945;
        }
      }
    }
    else {
      cVar1 = FUN_005c84d0(local_218 + 0x4ac);
      if (cVar1 != '\0') goto LAB_0052c8f2;
      cVar1 = FUN_005c84d0(local_218 + 0x510);
      if (cVar1 == '\0') goto LAB_0052c8f2;
LAB_0052c945:
      FUN_00437d30("misn0706.wav");
      *(undefined1 *)(local_218 + 0x6b) = 0;
      *(undefined1 *)(local_218 + 0x7a) = 0;
      *(undefined1 *)(local_218 + 0x76) = 0;
    }
    if ((*(char *)(local_218 + 0x6c) == '\0') || (*(char *)(local_218 + 0x7b) == '\0')) {
LAB_0052c9c3:
      if ((*(char *)(local_218 + 0x6c) != '\0') && (*(char *)(local_218 + 0x7b) != '\0')) {
        cVar1 = FUN_005c84d0(local_218 + 0x4b4);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(local_218 + 0x514);
          if (cVar1 != '\0') goto LAB_0052ca17;
        }
      }
    }
    else {
      cVar1 = FUN_005c84d0(local_218 + 0x4b4);
      if (cVar1 != '\0') goto LAB_0052c9c3;
      cVar1 = FUN_005c84d0(local_218 + 0x510);
      if (cVar1 == '\0') goto LAB_0052c9c3;
LAB_0052ca17:
      FUN_00437d30("misn0706.wav");
      *(undefined1 *)(local_218 + 0x6c) = 0;
      *(undefined1 *)(local_218 + 0x7b) = 0;
      *(undefined1 *)(local_218 + 0x76) = 0;
    }
    if ((*(char *)(local_218 + 0x6c) == '\0') || (*(char *)(local_218 + 0x7c) == '\0')) {
LAB_0052ca95:
      if ((*(char *)(local_218 + 0x6c) != '\0') && (*(char *)(local_218 + 0x7c) != '\0')) {
        cVar1 = FUN_005c84d0(local_218 + 0x4b8);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(local_218 + 0x514);
          if (cVar1 != '\0') goto LAB_0052cae8;
        }
      }
    }
    else {
      cVar1 = FUN_005c84d0(local_218 + 0x4b8);
      if (cVar1 != '\0') goto LAB_0052ca95;
      cVar1 = FUN_005c84d0(local_218 + 0x510);
      if (cVar1 == '\0') goto LAB_0052ca95;
LAB_0052cae8:
      FUN_00437d30("misn0706.wav");
      *(undefined1 *)(local_218 + 0x6c) = 0;
      *(undefined1 *)(local_218 + 0x7c) = 0;
      *(undefined1 *)(local_218 + 0x76) = 0;
    }
  }
  if (((*(char *)(local_218 + 0x77) != '\0') && (*(char *)(local_218 + 0x7d) == '\0')) &&
     (*(char *)(local_218 + 0x58) == '\0')) {
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x49c),
                                  *(undefined4 *)(local_218 + 0x464));
    local_284 = (float)fVar6;
    if ((local_284 < 100.0) && (*(int *)(local_218 + 0x464) != 0)) {
      cVar1 = FUN_005c84d0(local_218 + 0x464);
      if (cVar1 != '\0') {
        FUN_005c9610(*(undefined4 *)(local_218 + 0x49c));
        *(undefined1 *)(local_218 + 0x7d) = 1;
      }
    }
  }
  if (((*(char *)(local_218 + 0x78) != '\0') && (*(char *)(local_218 + 0x7d) == '\0')) &&
     (*(char *)(local_218 + 0x58) == '\0')) {
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x4a0),
                                  *(undefined4 *)(local_218 + 0x464));
    local_28c = (float)fVar6;
    if ((local_28c < 100.0) && (*(int *)(local_218 + 0x464) != 0)) {
      cVar1 = FUN_005c84d0(local_218 + 0x464);
      if (cVar1 != '\0') {
        FUN_005c9610(*(undefined4 *)(local_218 + 0x4a0));
        *(undefined1 *)(local_218 + 0x7d) = 1;
      }
    }
  }
  if (((*(char *)(local_218 + 0x79) != '\0') && (*(char *)(local_218 + 0x7d) == '\0')) &&
     (*(char *)(local_218 + 0x58) == '\0')) {
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x4a8),
                                  *(undefined4 *)(local_218 + 0x464));
    local_294 = (float)fVar6;
    if ((local_294 < 100.0) && (*(int *)(local_218 + 0x464) != 0)) {
      cVar1 = FUN_005c84d0(local_218 + 0x464);
      if (cVar1 != '\0') {
        FUN_005c9610(*(undefined4 *)(local_218 + 0x4a8));
        *(undefined1 *)(local_218 + 0x7d) = 1;
      }
    }
  }
  if (((*(char *)(local_218 + 0x7a) != '\0') && (*(char *)(local_218 + 0x7d) == '\0')) &&
     (*(char *)(local_218 + 0x58) == '\0')) {
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x4ac),
                                  *(undefined4 *)(local_218 + 0x464));
    local_29c = (float)fVar6;
    if ((local_29c < 100.0) && (*(int *)(local_218 + 0x464) != 0)) {
      cVar1 = FUN_005c84d0(local_218 + 0x464);
      if (cVar1 != '\0') {
        FUN_005c9610(*(undefined4 *)(local_218 + 0x4ac));
        *(undefined1 *)(local_218 + 0x7d) = 1;
      }
    }
  }
  if (((*(char *)(local_218 + 0x7b) != '\0') && (*(char *)(local_218 + 0x7d) == '\0')) &&
     (*(char *)(local_218 + 0x58) == '\0')) {
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x4b4),
                                  *(undefined4 *)(local_218 + 0x464));
    local_2a4 = (float)fVar6;
    if ((local_2a4 < 100.0) && (*(int *)(local_218 + 0x464) != 0)) {
      cVar1 = FUN_005c84d0(local_218 + 0x464);
      if (cVar1 != '\0') {
        FUN_005c9610(*(undefined4 *)(local_218 + 0x4b4));
        *(undefined1 *)(local_218 + 0x7d) = 1;
      }
    }
  }
  if (((*(char *)(local_218 + 0x7c) != '\0') && (*(char *)(local_218 + 0x7d) == '\0')) &&
     (*(char *)(local_218 + 0x58) == '\0')) {
    fVar6 = (float10)FUN_005c9780(*(undefined4 *)(local_218 + 0x4b8),
                                  *(undefined4 *)(local_218 + 0x464));
    local_2ac = (float)fVar6;
    if ((local_2ac < 100.0) && (*(int *)(local_218 + 0x464) != 0)) {
      cVar1 = FUN_005c84d0(local_218 + 0x464);
      if (cVar1 != '\0') {
        FUN_005c9610(*(undefined4 *)(local_218 + 0x4b8));
        *(undefined1 *)(local_218 + 0x7d) = 1;
      }
    }
  }
  if (*(char *)(local_218 + 0x7d) == '\0') {
LAB_0052cf9e:
    if (*(char *)(local_218 + 0x7d) != '\0') {
      cVar1 = FUN_005c84d0(local_218 + 0x514);
      if ((cVar1 != '\0') && (*(char *)(local_218 + 0x7e) == '\0')) goto LAB_0052cfd5;
    }
  }
  else {
    cVar1 = FUN_005c84d0(local_218 + 0x510);
    if ((cVar1 == '\0') || (*(char *)(local_218 + 0x7e) != '\0')) goto LAB_0052cf9e;
LAB_0052cfd5:
    FUN_00437d30("misn0707.wav");
    *(undefined1 *)(local_218 + 0x7e) = 1;
  }
  if (*(char *)(local_218 + 0x7d) != '\0') {
    cVar1 = FUN_005c84d0(local_218 + 0x49c);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(local_218 + 0x4a0);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(local_218 + 0x4a4);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(local_218 + 0x464);
          if (cVar1 != '\0') {
            uVar2 = FUN_005c8080("svtank",2,*(undefined4 *)(local_218 + 0x464),0);
            *(undefined4 *)(local_218 + 0x49c) = uVar2;
            uVar2 = FUN_005c8080("svtank",2,*(undefined4 *)(local_218 + 0x464),0);
            *(undefined4 *)(local_218 + 0x4a0) = uVar2;
            FUN_005cc0c0(*(undefined4 *)(local_218 + 0x49c),"patrol_path1",1);
            FUN_005cc0c0(*(undefined4 *)(local_218 + 0x4a0),"patrol_path1",1);
          }
        }
      }
    }
  }
  if (*(char *)(local_218 + 0x7d) != '\0') {
    cVar1 = FUN_005c84d0(local_218 + 0x4b4);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(local_218 + 0x4b8);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(local_218 + 0x4bc);
        if (cVar1 == '\0') {
          cVar1 = FUN_005c84d0(local_218 + 0x464);
          if (cVar1 != '\0') {
            uVar2 = FUN_005c8080("svtank",2,*(undefined4 *)(local_218 + 0x464),0);
            *(undefined4 *)(local_218 + 0x4b4) = uVar2;
            uVar2 = FUN_005c8080("svtank",2,*(undefined4 *)(local_218 + 0x464),0);
            *(undefined4 *)(local_218 + 0x4b8) = uVar2;
            FUN_005cc0c0(*(undefined4 *)(local_218 + 0x4b4),"patrol_path1",1);
            FUN_005cc0c0(*(undefined4 *)(local_218 + 0x4b8),"patrol_path1",1);
          }
        }
      }
    }
  }
LAB_0052d225:
  if (*(char *)(local_218 + 0x6f) == '\0') {
    cVar1 = FUN_005c84d0(local_218 + 0x49c);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(local_218 + 0x4a0);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(local_218 + 0x464);
        if ((cVar1 != '\0') && (*(char *)(local_218 + 0x75) == '\0')) {
          uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_218 + 0x464),0);
          *(undefined4 *)(local_218 + 0x49c) = uVar2;
          uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_218 + 0x464),0);
          *(undefined4 *)(local_218 + 0x4a0) = uVar2;
          FUN_005cc0c0(*(undefined4 *)(local_218 + 0x49c),"patrol_path1",1);
          FUN_005cc0c0(*(undefined4 *)(local_218 + 0x4a0),"patrol_path1",1);
          *(undefined1 *)(local_218 + 0x6a) = 0;
          *(undefined1 *)(local_218 + 0x76) = 0;
          *(undefined1 *)(local_218 + 0x77) = 0;
          *(undefined1 *)(local_218 + 0x78) = 0;
        }
      }
    }
    cVar1 = FUN_005c84d0(local_218 + 0x4b4);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(local_218 + 0x4b8);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(local_218 + 0x464);
        if ((cVar1 != '\0') && (*(char *)(local_218 + 0x75) == '\0')) {
          uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_218 + 0x464),0);
          *(undefined4 *)(local_218 + 0x4b4) = uVar2;
          uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_218 + 0x464),0);
          *(undefined4 *)(local_218 + 0x4b8) = uVar2;
          FUN_005cc0c0(*(undefined4 *)(local_218 + 0x4b4),"patrol_path1",1);
          FUN_005cc0c0(*(undefined4 *)(local_218 + 0x4b8),"patrol_path1",1);
          *(undefined1 *)(local_218 + 0x6c) = 0;
          *(undefined1 *)(local_218 + 0x76) = 0;
          *(undefined1 *)(local_218 + 0x7b) = 0;
          *(undefined1 *)(local_218 + 0x7c) = 0;
        }
      }
    }
    cVar1 = FUN_005c84d0(local_218 + 0x4c0);
    if (cVar1 == '\0') {
      cVar1 = FUN_005c84d0(local_218 + 0x4c4);
      if (cVar1 == '\0') {
        cVar1 = FUN_005c84d0(local_218 + 0x464);
        if (cVar1 != '\0') {
          uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_218 + 0x464),0);
          *(undefined4 *)(local_218 + 0x4c0) = uVar2;
          uVar2 = FUN_005c8080("svfigh",2,*(undefined4 *)(local_218 + 0x464),0);
          *(undefined4 *)(local_218 + 0x4c4) = uVar2;
          FUN_005cc0c0(*(undefined4 *)(local_218 + 0x4c0),"patrol_path2",1);
          FUN_005cc0c0(*(undefined4 *)(local_218 + 0x4c4),"patrol_path2",1);
        }
      }
    }
  }
  cVar1 = FUN_005c84d0(local_218 + 0x234);
  if ((cVar1 == '\0') && (*(char *)(local_218 + 0x6f) == '\0')) {
    uVar2 = FUN_00437d30("misn0714.wav");
    *(undefined4 *)(local_218 + 0x6f0) = uVar2;
    fVar6 = (float10)FUN_00822d80();
    local_2b4 = (float)fVar6;
    *(float *)(local_218 + 0x1e0) = local_2b4 + 10.0;
    fVar6 = (float10)FUN_00822d80();
    local_2bc = (float)fVar6;
    *(float *)(local_218 + 0x1e4) = local_2bc + 7.5;
    *(undefined1 *)(local_218 + 0x6f) = 1;
  }
  if ((*(char *)(local_218 + 0x6f) != '\0') && (*(char *)(local_218 + 0x72) == '\0')) {
    fVar6 = (float10)FUN_00822d80();
    local_2c4 = (float)fVar6;
    if (*(float *)(local_218 + 0x1e4) <= local_2c4 && local_2c4 != *(float *)(local_218 + 0x1e4)) {
      uVar2 = FUN_005c8250("avrec7",1,"recycle_spawn",0,0);
      *(undefined4 *)(local_218 + 0x1fc) = uVar2;
      uVar2 = FUN_005c8250("avmu7",1,"muf_spawn",0,0);
      *(undefined4 *)(local_218 + 0x200) = uVar2;
      FUN_005cb960(*(undefined4 *)(local_218 + 0x1fc),"recycle_path",0);
      FUN_005cb960(*(undefined4 *)(local_218 + 0x200),"muf_path",0);
      uVar2 = FUN_005c8250(&DAT_00878c18,1,"recycle_cam_spawn",0,0);
      *(undefined4 *)(local_218 + 0x26c) = uVar2;
      uVar2 = FUN_005c8250(&DAT_00878c18,1,"recy_cam_spawn",0,0);
      *(undefined4 *)(local_218 + 0x270) = uVar2;
      FUN_005c9640(*(undefined4 *)(local_218 + 0x26c),"Utah Rendezvous");
      FUN_005c9640(*(undefined4 *)(local_218 + 0x270),"CCA BASE");
      FUN_005cada0(1,0x1e);
      FUN_005cacb0(1,0x14);
      FUN_005cada0(2,0x3c);
      FUN_005cacb0(2,0x28);
      FUN_005cb2d0("misn07.aip",2);
      uVar2 = FUN_005c8250("sbtowe",2,"base_tower1_spawn",0,0);
      *(undefined4 *)(local_218 + 0x478) = uVar2;
      FUN_004f6aa0();
      FUN_004f6ab0("misn0701.otf",DAT_009175b0,0x41000000,0);
      FUN_004f6ab0("misn0703.otf",DAT_0091755c,0x41000000,0);
      FUN_004f6ab0("misn0702.otf",DAT_0091755c,0x41000000,0);
      *(undefined1 *)(local_218 + 0x72) = 1;
    }
  }
  if (*(char *)(local_218 + 0x72) != '\0') {
    cVar1 = FUN_005c84d0(local_218 + 0x464);
    if (cVar1 == '\0') {
      *(undefined1 *)(local_218 + 0x70) = 1;
    }
  }
  if ((*(char *)(local_218 + 0x72) != '\0') && (*(char *)(local_218 + 0x55) == '\0')) {
    cVar1 = FUN_005c84d0(local_218 + 0x1fc);
    if (cVar1 != '\0') {
      cVar1 = FUN_005caec0(*(undefined4 *)(local_218 + 0x1fc));
      if (cVar1 != '\0') {
        FUN_004f6aa0();
        FUN_004f6ab0("misn0703.otf",DAT_009175b0,0x41000000,0);
        FUN_004f6ab0("misn0702.otf",DAT_0091755c,0x41000000,0);
        *(undefined1 *)(local_218 + 0x55) = 1;
      }
    }
  }
  cVar1 = FUN_005c84d0(local_218 + 0x1f8);
  if (cVar1 == '\0') {
    cVar1 = FUN_005c8410(*(undefined4 *)(local_218 + 0x1f8),"asuser");
    if (cVar1 != '\0') {
      fVar6 = (float10)FUN_00822d80(0);
      local_2cc = (float)fVar6;
      FUN_0045c0f0(local_2cc + 5.0);
    }
  }
  if (*(char *)(local_218 + 0x72) != '\0') {
    cVar1 = FUN_005c84d0(local_218 + 0x1fc);
    if ((cVar1 == '\0') && (*(char *)(local_218 + 0x171) == '\0')) {
      FUN_00437d30("misn0712.wav");
      if (*(char *)(local_218 + 0x55) == '\0') {
        FUN_004f6aa0();
        FUN_004f6ab0("misn0701.otf",DAT_009175b0,0x41000000,0);
        FUN_004f6ab0("misn0703.otf",DAT_0091757c,0x41000000,0);
        FUN_004f6ab0("misn0702.otf",DAT_0091755c,0x41000000,0);
      }
      fVar6 = (float10)FUN_00822d80("misn07f1.des");
      local_2d4 = (float)fVar6;
      FUN_0045c0f0(local_2d4 + 15.0);
      *(undefined1 *)(local_218 + 0x171) = 1;
    }
  }
  if (*(char *)(local_218 + 0x72) != '\0') {
    cVar1 = FUN_005c84d0(local_218 + 0x464);
    if (cVar1 == '\0') {
      *(undefined1 *)(local_218 + 0x70) = 1;
    }
  }
  if (((*(char *)(local_218 + 0x6f) != '\0') && (*(char *)(local_218 + 0x70) != '\0')) &&
     (*(char *)(local_218 + 0x171) == '\0')) {
    FUN_00437d30("misn0713.wav");
    fVar6 = (float10)FUN_00822d80("misn07w1.des");
    local_2dc = (float)fVar6;
    FUN_0045c110(local_2dc + 15.0);
    *(undefined1 *)(local_218 + 0x171) = 1;
  }
  FUN_0083e885();
  return;
}

