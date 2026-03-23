
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_007aebc0(int param_1)

{
  undefined1 uVar1;
  uint uVar2;
  MaterialManager *this;
  undefined4 uVar3;
  Root *pRVar4;
  RenderSystem *pRVar5;
  undefined4 *puVar6;
  void *pvVar7;
  undefined4 local_e0;
  undefined1 local_d4 [24];
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00860d8b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x178) == 0) {
    if (DAT_009455b0 != 0 || DAT_009455b4 != 0) {
      DAT_0260baac = (int)*(char *)(DAT_0094672c + 0x25);
      DAT_0260baa8 = (uint)*(byte *)(DAT_0094672c + 0x27);
      _DAT_009455b0 = 0;
    }
    uVar2 = FUN_007c3cc0(local_14);
    this = Ogre::MaterialManager::getSingleton();
    Ogre::MaterialManager::setDefaultAnisotropy(this,uVar2);
    if (((*(char *)(param_1 + 0x19e) != '\0') || (*(char *)(param_1 + 0x19c) != '\0')) ||
       (*(char *)(param_1 + 0x1a0) != '\0')) {
      FUN_007d6a70("Updating Window mode via clicking apply\n");
      uVar3 = FUN_007c3d10();
      basic_string<>(uVar3);
      local_8 = 0;
      basic_string<>("Full Screen");
      local_8._0_1_ = 1;
      pRVar4 = Ogre::Root::getSingleton();
      pRVar5 = Ogre::Root::getRenderSystem(pRVar4);
      (**(code **)(*(int *)pRVar5 + 0x10))(local_bc,local_2c);
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
      uVar3 = FUN_007c3d10();
      basic_string<>(uVar3);
      local_8 = 2;
      basic_string<>("Video Mode");
      local_8._0_1_ = 3;
      pRVar4 = Ogre::Root::getSingleton();
      pRVar5 = Ogre::Root::getRenderSystem(pRVar4);
      (**(code **)(*(int *)pRVar5 + 0x10))(local_44,local_74);
      local_8 = CONCAT31(local_8._1_3_,2);
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
      uVar1 = FUN_007c3cc0();
      *(undefined1 *)(DAT_0094672c + 0x26) = uVar1;
      FUN_00683620(1,1);
    }
    if ((*(char *)(param_1 + 0x19f) != '\0') || (*(char *)(param_1 + 0x19d) != '\0')) {
      if (*(char *)(param_1 + 0x19d) != '\0') {
        uVar3 = FUN_007c3d10();
        basic_string<>(uVar3);
        local_8 = 4;
        basic_string<>("Rendering Device");
        local_8._0_1_ = 5;
        pRVar4 = Ogre::Root::getSingleton();
        pRVar5 = Ogre::Root::getRenderSystem(pRVar4);
        (**(code **)(*(int *)pRVar5 + 0x10))(local_a4,local_d4);
        local_8 = CONCAT31(local_8._1_3_,4);
        ~basic_string<>();
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
      uVar3 = FUN_007c3d10();
      basic_string<>(uVar3);
      local_8 = 6;
      basic_string<>(&DAT_00873e08);
      local_8._0_1_ = 7;
      pRVar4 = Ogre::Root::getSingleton();
      pRVar5 = Ogre::Root::getRenderSystem(pRVar4);
      (**(code **)(*(int *)pRVar5 + 0x10))(local_8c,local_5c);
      local_8 = CONCAT31(local_8._1_3_,6);
      ~basic_string<>();
      local_8 = 0xffffffff;
      ~basic_string<>();
      pRVar4 = Ogre::Root::getSingleton();
      Ogre::Root::saveConfig(pRVar4);
      FUN_007c3d60(0xff00);
      FUN_007c3d60(0xff00);
      FUN_007c3d60(0xff00);
    }
    if (*(char *)(param_1 + 0x1a1) != '\0') {
      uVar3 = FUN_007c3cc0();
      puVar6 = (undefined4 *)FUN_004200d0(uVar3);
      DAT_009455ac = *puVar6;
    }
    if (((*(char *)(param_1 + 0x19f) != '\0') || (*(char *)(param_1 + 0x19d) != '\0')) ||
       (*(char *)(param_1 + 0x1a1) != '\0')) {
      pvVar7 = operator_new(0x15c);
      local_8 = 8;
      if (pvVar7 == (void *)0x0) {
        local_e0 = 0;
      }
      else {
        local_e0 = FUN_007c1ef0("Alert",0,0,0x44160000,0x43610000,0x220,0);
      }
      local_8 = 0xffffffff;
      *(undefined4 *)(param_1 + 0x178) = local_e0;
      uVar3 = FUN_0081cb40("options","restart_required");
      FUN_007c2400(uVar3);
      FUN_007c23c0(FUN_007ae860);
      FUN_007d2110(*(undefined4 *)(param_1 + 0x178),0);
    }
    *(undefined1 *)(param_1 + 0x19e) = 0;
    *(undefined1 *)(param_1 + 0x19c) = 0;
    *(undefined1 *)(param_1 + 0x1a0) = 0;
    *(undefined1 *)(param_1 + 0x19f) = 0;
    *(undefined1 *)(param_1 + 0x19d) = 0;
    *(undefined1 *)(param_1 + 0x1a1) = 0;
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

