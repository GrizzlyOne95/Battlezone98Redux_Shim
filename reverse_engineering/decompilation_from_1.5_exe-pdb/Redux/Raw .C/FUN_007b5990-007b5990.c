
undefined4 * __fastcall FUN_007b5990(undefined4 *param_1)

{
  char cVar1;
  byte bVar2;
  void *pvVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  bool bVar7;
  int iVar8;
  undefined4 local_74;
  int *local_70;
  int *local_64;
  uint local_54;
  undefined4 local_4c;
  undefined4 local_48;
  int *local_44;
  char *local_3c;
  byte *local_38;
  char *local_34;
  byte *local_2c;
  int local_24;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008612f0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007d0fa0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = cUI_OptionsJoystick::vftable;
  local_3c = &DAT_008e90a0 + *(int *)(DAT_0094672c + 0x34) * 0x140;
  local_34 = &DAT_008ead70;
  do {
    cVar1 = *local_3c;
    *local_34 = cVar1;
    local_3c = local_3c + 1;
    local_34 = local_34 + 1;
  } while (cVar1 != '\0');
  DAT_009455c0 = param_1;
  pvVar3 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (pvVar3 == (void *)0x0) {
    local_74 = 0;
  }
  else {
    local_74 = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8._0_1_ = 0;
  FUN_007d3f20(1);
  FUN_007d2870("poptions_center.png");
  FUN_007d2110(local_74,0);
  uVar4 = FUN_0081cb40("missions",&DAT_008714b0);
  uVar5 = FUN_0081cb40("joystick","select");
  uVar6 = FUN_0081cb40("joystick","sensitivity");
  pvVar3 = operator_new(0x1ec);
  local_8._0_1_ = 2;
  if (pvVar3 == (void *)0x0) {
    local_70 = (int *)0x0;
  }
  else {
    local_70 = (int *)FUN_007c2480(&DAT_00877f98,0,0,0x43ab0000,0x429a0000,0x20,0,0x41e00000,0);
  }
  local_8._0_1_ = 0;
  FUN_007d2870("topcorner.png");
  (**(code **)(*local_70 + 0x40))("topcrnhv.png");
  (**(code **)(*local_70 + 0x3c))("topcrnck.png");
  FUN_007c2950(uVar4);
  FUN_007c23e0(FUN_007b58c0);
  FUN_007d2110(local_70,0);
  pvVar3 = operator_new(0x930);
  local_8._0_1_ = 3;
  if (pvVar3 == (void *)0x0) {
    local_44 = (int *)0x0;
  }
  else {
    local_44 = (int *)FUN_007cc390("Select",0x43ca8000,0x42f80000,0x441d8000,0x422c0000,0x9020,
                                   local_74,0);
  }
  local_8._0_1_ = 0;
  (**(code **)(*local_44 + 0x3c))(uVar5);
  FUN_007d2110(local_44,0);
  pvVar3 = operator_new(0x180);
  local_8._0_1_ = 4;
  if (pvVar3 == (void *)0x0) {
    local_4c = 0;
  }
  else {
    local_4c = FUN_007c9de0("Joystick_List",0x43ca8000,0x43610000,0x441d8000,0x43e10000,FUN_007b58a0
                            ,FUN_007b58b0,0,local_74,0xff00ff00,0x3f800000);
  }
  local_8._0_1_ = 0;
  param_1[0x51] = local_4c;
  DAT_009455bc = param_1[0x51];
  local_24 = 0;
  do {
    if (0xe < local_24) {
      FUN_007cb3e0(FUN_007b58d0);
      FUN_007d2110(param_1[0x51],0);
      pvVar3 = operator_new(0x930);
      local_8._0_1_ = 5;
      if (pvVar3 == (void *)0x0) {
        local_64 = (int *)0x0;
      }
      else {
        local_64 = (int *)FUN_007cc390("Sensitivity",0x43ca8000,0x442b8000,0x438c0000,0x429e0000,
                                       0x8020,local_74,0);
      }
      local_8._0_1_ = 0;
      (**(code **)(*local_64 + 0x3c))(uVar6);
      FUN_007cc6b0(0x3f59999a);
      FUN_007d2110(local_64,0);
      pvVar3 = operator_new(0x164);
      local_8._0_1_ = 6;
      if (pvVar3 == (void *)0x0) {
        local_48 = 0;
      }
      else {
        local_48 = FUN_007cbd60("JoystickSlider",0x442b4000,0x442b8000,0x43ca8000,0x429e0000,0x20,
                                local_74);
      }
      local_8 = (uint)local_8._1_3_ << 8;
      param_1[0x52] = local_48;
      FUN_007cc2d0((float)*(int *)(DAT_0094672c + 0x3c));
      FUN_007cc340(FUN_007b58e0);
      FUN_007d2110(param_1[0x52],0);
      ExceptionList = local_10;
      return param_1;
    }
    uVar5 = 0;
    iVar8 = local_24;
    uVar4 = FUN_0081cb40("joystick",&DAT_008e90a0 + local_24 * 0x140,local_24,0);
    FUN_007cabf0(uVar4,iVar8,uVar5);
    local_38 = &DAT_008ead70;
    local_2c = &DAT_008e90a0 + local_24 * 0x140;
    do {
      bVar2 = *local_2c;
      bVar7 = bVar2 < *local_38;
      if (bVar2 != *local_38) {
LAB_007b5e3a:
        local_54 = -(uint)bVar7 | 1;
        goto LAB_007b5e42;
      }
      if (bVar2 == 0) break;
      bVar2 = local_2c[1];
      bVar7 = bVar2 < local_38[1];
      if (bVar2 != local_38[1]) goto LAB_007b5e3a;
      local_2c = local_2c + 2;
      local_38 = local_38 + 2;
    } while (bVar2 != 0);
    local_54 = 0;
LAB_007b5e42:
    if (local_54 == 0) {
      FUN_007cafa0(local_24);
    }
    local_24 = local_24 + 1;
  } while( true );
}

