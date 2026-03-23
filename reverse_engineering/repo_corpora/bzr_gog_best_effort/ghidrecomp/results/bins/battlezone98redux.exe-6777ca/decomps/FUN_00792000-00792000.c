
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void __fastcall FUN_00792000(undefined4 *param_1)

{
  byte bVar1;
  char cVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  int iVar4;
  void *pvVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  bool bVar10;
  undefined4 uStack_1f4ac;
  int *piStack_1f4a0;
  int *piStack_1f49c;
  int *piStack_1f498;
  int *piStack_1f490;
  uint uStack_1f48c;
  int *piStack_1f488;
  byte *pbStack_1f480;
  byte *pbStack_1f478;
  byte *pbStack_1f474;
  byte *pbStack_1f470;
  byte *pbStack_1f46c;
  byte *pbStack_1f464;
  undefined1 auStack_1f444 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_1f42c [24];
  byte abStack_1f414 [128004];
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085ef4b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007d0fa0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = cUI_MissionFailed::vftable;
  DAT_0091830c = 1;
  DAT_00945540 = param_1;
  FUN_007d3f20(0);
  pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_00482850();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(abStack_1f42c,pbVar3)
  ;
  local_8 = CONCAT31(local_8._1_3_,1);
  cVar2 = FUN_00427310(abStack_1f42c,&DAT_0094ffe0);
  if (cVar2 == '\0') {
    cVar2 = FUN_00427310(abStack_1f42c,&DAT_0094fea8);
    if (cVar2 == '\0') {
      FUN_007d2870("failed.png");
    }
    else {
      iVar4 = FUN_00417c70();
      if (iVar4 == 0) {
        FUN_007d2870("svtdeath.png");
      }
      else {
        FUN_007d2870("svtlose.png");
      }
    }
  }
  else {
    iVar4 = FUN_00417c70();
    if (iVar4 == 0) {
      FUN_007d2870("death.png");
    }
    else {
      FUN_007d2870("failed.png");
    }
  }
  pvVar5 = operator_new(0x144);
  local_8._0_1_ = 2;
  if (pvVar5 == (void *)0x0) {
    uStack_1f4ac = 0;
  }
  else {
    uStack_1f4ac = FUN_007d1cc0("temp overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 1;
  FUN_007d2110(uStack_1f4ac,0);
  uVar6 = FUN_0081cb40("fail_mission","message");
  uVar7 = FUN_0081cb40("fail_mission","load_game");
  uVar8 = FUN_0081cb40("fail_mission","replay_mission");
  uVar9 = FUN_0081cb40("missions","main_menu");
  pvVar5 = operator_new(0x1ec);
  local_8._0_1_ = 3;
  if (pvVar5 == (void *)0x0) {
    piStack_1f4a0 = (int *)0x0;
  }
  else {
    piStack_1f4a0 = (int *)FUN_007c2480("MainMenu",0,0,0x43ab0000,0x429a0000,0x20,0,0x41a00000,0);
  }
  local_8._0_1_ = 1;
  FUN_007d2870("topcorner.png");
  (**(code **)(*piStack_1f4a0 + 0x40))("topcrnhv.png");
  (**(code **)(*piStack_1f4a0 + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar9);
  FUN_007c23e0(FUN_00791f40);
  FUN_007d2110(piStack_1f4a0,0);
  pvVar5 = operator_new(0x1ec);
  local_8._0_1_ = 4;
  if (pvVar5 == (void *)0x0) {
    piStack_1f490 = (int *)0x0;
  }
  else {
    piStack_1f490 = (int *)FUN_007c2480("Restart",0,0,0x43ab0000,0x429a0000,0xa2,0,0xc2200000,0);
  }
  local_8._0_1_ = 1;
  FUN_007d2870("topcorner.png");
  (**(code **)(*piStack_1f490 + 0x40))("topcrnhv.png");
  (**(code **)(*piStack_1f490 + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar8);
  FUN_007c23e0(FUN_00791f20);
  FUN_007c30e0(0x3f666666);
  FUN_007d2110(piStack_1f490,0);
  pvVar5 = operator_new(0x1ec);
  local_8._0_1_ = 5;
  if (pvVar5 == (void *)0x0) {
    piStack_1f498 = (int *)0x0;
  }
  else {
    piStack_1f498 =
         (int *)FUN_007c2480(&DAT_0087d1e8,0,0x447ac000,0x43ab0000,0x429a0000,0xa6,0,0xc2200000,0);
  }
  local_8._0_1_ = 1;
  FUN_007d2870("topcorner.png");
  (**(code **)(*piStack_1f498 + 0x40))("topcrnhv.png");
  (**(code **)(*piStack_1f498 + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar7);
  FUN_007c23e0(FUN_00791f30);
  FUN_007d2110(piStack_1f498,0);
  pvVar5 = operator_new(0x930);
  local_8._0_1_ = 6;
  if (pvVar5 == (void *)0x0) {
    piStack_1f488 = (int *)0x0;
  }
  else {
    piStack_1f488 =
         (int *)FUN_007cc390("MISSION FAILED",0x430e0000,0x43710000,0x44908000,0x41e00000,0x9020,
                             uStack_1f4ac,0);
  }
  local_8._0_1_ = 1;
  (**(code **)(*piStack_1f488 + 0x3c))(uVar6);
  FUN_007d2110(piStack_1f488,0);
  BadAllocException(auStack_1f444);
  local_8._0_1_ = 7;
  uVar6 = FUN_0041f870(abStack_1f414);
  FUN_004889c0(uVar6);
  local_8 = CONCAT31(local_8._1_3_,1);
  ~basic_string<>();
  pbStack_1f46c = (byte *)0x876e74;
  pbStack_1f464 = abStack_1f414;
  do {
    bVar1 = *pbStack_1f464;
    bVar10 = bVar1 < *pbStack_1f46c;
    if (bVar1 != *pbStack_1f46c) {
LAB_00792790:
      uStack_1f48c = -(uint)bVar10 | 1;
      goto LAB_0079279b;
    }
    if (bVar1 == 0) break;
    bVar1 = pbStack_1f464[1];
    bVar10 = bVar1 < pbStack_1f46c[1];
    if (bVar1 != pbStack_1f46c[1]) goto LAB_00792790;
    pbStack_1f464 = pbStack_1f464 + 2;
    pbStack_1f46c = pbStack_1f46c + 2;
  } while (bVar1 != 0);
  uStack_1f48c = 0;
LAB_0079279b:
  if (uStack_1f48c == 0) {
    iVar4 = FUN_00417c70();
    if (iVar4 == 0) {
      pbStack_1f480 = (byte *)FUN_0081cb40("fail_mission","killed");
      pbStack_1f474 = abStack_1f414;
      do {
        bVar1 = *pbStack_1f480;
        *pbStack_1f474 = bVar1;
        pbStack_1f480 = pbStack_1f480 + 1;
        pbStack_1f474 = pbStack_1f474 + 1;
      } while (bVar1 != 0);
    }
    else {
      pbStack_1f478 = (byte *)FUN_0081cb40("fail_mission","failed");
      pbStack_1f470 = abStack_1f414;
      do {
        bVar1 = *pbStack_1f478;
        *pbStack_1f470 = bVar1;
        pbStack_1f478 = pbStack_1f478 + 1;
        pbStack_1f470 = pbStack_1f470 + 1;
      } while (bVar1 != 0);
    }
  }
  pvVar5 = operator_new(0x294c);
  local_8._0_1_ = 8;
  if (pvVar5 == (void *)0x0) {
    piStack_1f49c = (int *)0x0;
  }
  else {
    piStack_1f49c =
         (int *)FUN_007ccb70("MISSION TEXT",0x430e0000,0x43b98000,0x44908000,0x43fe8000,0x20,
                             uStack_1f4ac);
  }
  local_8 = CONCAT31(local_8._1_3_,1);
  iVar4 = FUN_004344a0();
  if (iVar4 == 2) {
    FUN_007cce50(0x3f800000);
  }
  (**(code **)(*piStack_1f49c + 0x3c))(abStack_1f414,3);
  FUN_007d2110(piStack_1f49c,0);
  local_8 = local_8 & 0xffffff00;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

