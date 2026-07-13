/*
 * Entry: 00445d9c
 * Name: Misns7Mission::Setup
 * Namespace: Misns7Mission
 * Signature: void Setup(Misns7Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns7Mission::Setup(Misns7Mission *this)

{
  int iVar1;
  
  (this->field19_0x264)._s_0.stuff = 10;
  (this->field19_0x264)._s_0.stuff2 = 0;
  (this->field19_0x264)._s_0.stuff4 = 10;
  (this->field19_0x264)._s_0.scrap = 0;
  (this->field16_0x40)._s_0.main_on = true;
  (this->field16_0x40)._s_0.maint_on = true;
  (this->field16_0x40)._s_0.camera_off_supply = false;
  iVar1 = GetHandle("svapc");
  (this->field18_0x130)._s_0.apc = iVar1;
  iVar1 = GetHandle("avrecycle");
  (this->field18_0x130)._s_0.avrecycle = iVar1;
  iVar1 = GetHandle("jail");
  (this->field18_0x130)._s_0.jail = iVar1;
  iVar1 = GetHandle("supply");
  (this->field18_0x130)._s_0.supply = iVar1;
  iVar1 = GetHandle("geyser1");
  (this->field18_0x130)._s_0.geyser1 = iVar1;
  iVar1 = GetHandle("geyser2");
  (this->field18_0x130)._s_0.geyser2 = iVar1;
  iVar1 = GetHandle("geyser3");
  (this->field18_0x130)._s_0.geyser3 = iVar1;
  iVar1 = GetHandle("boxes");
  (this->field18_0x130)._s_0.boxes = iVar1;
  iVar1 = GetHandle("getum_started");
  (this->field18_0x130)._s_0.fed_up_scrap = iVar1;
  iVar1 = GetHandle("svsilo");
  (this->field18_0x130)._s_0.svsilo = iVar1;
  iVar1 = GetHandle("guntower1");
  (this->field18_0x130)._s_0.guntower1 = iVar1;
  iVar1 = GetHandle("guntower2");
  (this->field18_0x130)._s_0.guntower2 = iVar1;
  iVar1 = GetHandle("field_geyser1");
  (this->field18_0x130)._s_0.field_geyser1 = iVar1;
  iVar1 = GetHandle("avsilo");
  (this->field18_0x130)._s_0.avsilo = iVar1;
  iVar1 = GetHandle("hanger");
  (this->field18_0x130)._s_0.hanger = iVar1;
  iVar1 = GetHandle("rig");
  (this->field18_0x130)._s_0.avrig = iVar1;
  iVar1 = GetHandle("wind_power1");
  (this->field18_0x130)._s_0.main_power = iVar1;
  iVar1 = GetHandle("con_geyser");
  (this->field18_0x130)._s_0.con_geyser = iVar1;
  iVar1 = GetHandle("bturret1");
  (this->field18_0x130)._s_0.bturret1 = iVar1;
  iVar1 = GetHandle("bturret2");
  (this->field18_0x130)._s_0.bturret2 = iVar1;
  iVar1 = GetHandle("svrecycle");
  (this->field18_0x130)._s_0.svrecycle = iVar1;
  iVar1 = GetHandle("svmuf");
  (this->field18_0x130)._s_0.svmuf = iVar1;
  iVar1 = GetHandle("main_tower");
  (this->field18_0x130)._s_0.avmuf = 0;
  (this->field18_0x130)._s_0.bturret3 = 0;
  (this->field18_0x130)._s_0.bturret4 = 0;
  (this->field18_0x130)._s_0.bvrig = 0;
  (this->field18_0x130)._s_0.bvrecycle = 0;
  (this->field18_0x130)._s_0.main_tower = iVar1;
  return;
}
