
void FUN_00621b90(uint param_1,char *param_2)

{
  byte bVar1;
  UINT UVar2;
  MMRESULT MVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  void *pvVar6;
  void *pvVar7;
  uint *puVar8;
  int iVar9;
  bool bVar10;
  uint local_1c4;
  byte *local_1bc;
  byte *local_1b8;
  UINT local_1a0;
  tagJOYCAPSA local_19c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((-1 < (int)param_1) && (UVar2 = joyGetNumDevs(), param_1 < UVar2)) {
    memset(&local_19c,0,0x194);
    MVar3 = joyGetDevCapsA(param_1,&local_19c,0x194);
    if (MVar3 == 0) {
      puVar4 = calloc(6,4);
      *(undefined4 **)(param_2 + 0x60) = puVar4;
      puVar5 = calloc(6,4);
      *(undefined4 **)(param_2 + 100) = puVar5;
      pvVar6 = calloc(0x30,4);
      *(void **)(param_2 + 0x68) = pvVar6;
      pvVar7 = calloc(0x30,4);
      *(void **)(param_2 + 0x6c) = pvVar7;
      if ((((puVar4 != (undefined4 *)0x0) && (puVar5 != (undefined4 *)0x0)) &&
          (pvVar6 != (void *)0x0)) &&
         ((pvVar7 != (void *)0x0 && (puVar8 = calloc(1,0xf0), puVar8 != (uint *)0x0)))) {
        *puVar8 = param_1;
        *(uint **)(param_2 + 0x70) = puVar8;
        iVar9 = FUN_00623620(param_1,local_19c.szRegKey,param_2 + 0xc,0x40);
        if (iVar9 == 0) {
          sprintf(param_2 + 0xc,"Joystick %d",param_1 + 1);
        }
        sprintf(param_2,"joystick%d",param_1 + 1);
        FUN_00623810(param_2,&local_19c);
        *puVar4 = s_Horizontal_Position_008ec114;
        *puVar5 = s_HorizPos_008ec09c;
        puVar4[1] = s_Vertical_Position_008ec100;
        puVar5[1] = s_VertPos_008ec248;
        local_1a0 = 2;
        if ((local_19c.wCaps & 1) != 0) {
          local_1b8 = (byte *)0x88d1dc;
          local_1bc = (byte *)(param_2 + 0x4c);
          do {
            bVar1 = *local_1bc;
            bVar10 = bVar1 < *local_1b8;
            if (bVar1 != *local_1b8) {
LAB_00621e2d:
              local_1c4 = -(uint)bVar10 | 1;
              goto LAB_00621e38;
            }
            if (bVar1 == 0) break;
            bVar1 = local_1bc[1];
            bVar10 = bVar1 < local_1b8[1];
            if (bVar1 != local_1b8[1]) goto LAB_00621e2d;
            local_1bc = local_1bc + 2;
            local_1b8 = local_1b8 + 2;
          } while (bVar1 != 0);
          local_1c4 = 0;
LAB_00621e38:
          if (local_1c4 == 0) {
            puVar4[2] = s_Left_Right_Head_Roll_008ebfc8;
            puVar5[2] = s_HeadRoll_008ec034;
            local_1a0 = 3;
          }
          else {
            puVar4[2] = s_Throttle_Position_008ec00c;
            puVar5[2] = s_Throttle_008ec250;
            local_1a0 = 3;
          }
        }
        if ((local_19c.wCaps & 2) != 0) {
          puVar4[local_1a0] = s_Rudder_Position_008ec1ac;
          puVar5[local_1a0] = s_Rudder_008ec150;
          local_1a0 = local_1a0 + 1;
        }
        if ((local_19c.wCaps & 4) != 0) {
          puVar4[local_1a0] = s_U_Slider_Movement_008ec1dc;
          puVar5[local_1a0] = s_USlider_008ec1f0;
          local_1a0 = local_1a0 + 1;
        }
        if ((local_19c.wCaps & 8) != 0) {
          puVar4[local_1a0] = s_V_Slider_Movement_008ec158;
          puVar5[local_1a0] = s_VSlider_008ec0d8;
          local_1a0 = local_1a0 + 1;
        }
        *(UINT *)(param_2 + 0x58) = local_1a0;
        for (local_1a0 = 0; (int)local_1a0 < (int)local_19c.wNumButtons; local_1a0 = local_1a0 + 1)
        {
          *(undefined **)((int)pvVar6 + local_1a0 * 4) = &DAT_02a17210 + local_1a0 * 0xb;
          *(undefined **)((int)pvVar7 + local_1a0 * 4) = &DAT_02a144b0 + local_1a0 * 0xb;
        }
        local_1a0 = local_19c.wNumButtons;
        if ((local_19c.wCaps & 0x10) != 0) {
          *(char **)((int)pvVar6 + local_19c.wNumButtons * 4) = s_Hat_Up_008ec23c;
          *(char **)((int)pvVar7 + local_19c.wNumButtons * 4) = s_HatUp_008ec088;
          *(char **)((int)pvVar6 + (local_19c.wNumButtons + 1) * 4) = s_Hat_Right_008ec190;
          *(char **)((int)pvVar7 + (local_19c.wNumButtons + 1) * 4) = s_HatRight_008ec054;
          *(char **)((int)pvVar6 + (local_19c.wNumButtons + 2) * 4) = s_Hat_Down_008ec210;
          *(char **)((int)pvVar7 + (local_19c.wNumButtons + 2) * 4) = s_HatDown_008ec04c;
          *(char **)((int)pvVar6 + (local_19c.wNumButtons + 3) * 4) = s_Hat_Left_008ec040;
          *(char **)((int)pvVar7 + (local_19c.wNumButtons + 3) * 4) = s_HatLeft_008ec16c;
          local_1a0 = local_19c.wNumButtons + 4;
        }
        *(char **)((int)pvVar6 + local_1a0 * 4) = s_Horizontal_Negative_008ec128;
        *(char **)((int)pvVar7 + local_1a0 * 4) = s_HorizNeg_008ec230;
        *(char **)((int)pvVar6 + (local_1a0 + 1) * 4) = s_Horizontal_Positive_008ec074;
        *(char **)((int)pvVar7 + (local_1a0 + 1) * 4) = s_HorizPos_008ec0cc;
        *(char **)((int)pvVar6 + (local_1a0 + 2) * 4) = s_Vertical_Negative_008ec0b8;
        *(char **)((int)pvVar7 + (local_1a0 + 2) * 4) = s_VertNeg_008ec188;
        *(char **)((int)pvVar6 + (local_1a0 + 3) * 4) = s_Vertical_Positive_008ec020;
        *(char **)((int)pvVar7 + (local_1a0 + 3) * 4) = s_VertPos_008ec06c;
        UVar2 = local_1a0 + 4;
        if ((local_19c.wCaps & 1) != 0) {
          *(char **)((int)pvVar6 + UVar2 * 4) = s_Throttle_Negative_008ec1c8;
          *(char **)((int)pvVar7 + UVar2 * 4) = s_ThrottleNeg_008ec0e0;
          *(char **)((int)pvVar6 + (local_1a0 + 5) * 4) = s_Throttle_Positive_008ec174;
          *(char **)((int)pvVar7 + (local_1a0 + 5) * 4) = s_ThrottlePos_008ec090;
          UVar2 = local_1a0 + 6;
        }
        local_1a0 = UVar2;
        if ((local_19c.wCaps & 2) != 0) {
          *(char **)((int)pvVar6 + local_1a0 * 4) = s_Rudder_Negative_008ec19c;
          *(char **)((int)pvVar7 + local_1a0 * 4) = s_RudderNeg_008ec1bc;
          *(char **)((int)pvVar6 + (local_1a0 + 1) * 4) = s_Rudder_Positive_008ec0a8;
          *(char **)((int)pvVar7 + (local_1a0 + 1) * 4) = s_RudderPos_008ec060;
          local_1a0 = local_1a0 + 2;
        }
        if ((local_19c.wCaps & 4) != 0) {
          *(char **)((int)pvVar6 + local_1a0 * 4) = s_U_Slider_Negative_008ec13c;
          *(char **)((int)pvVar7 + local_1a0 * 4) = s_USliderNeg_008ebfe0;
          *(char **)((int)pvVar6 + (local_1a0 + 1) * 4) = s_U_Slider_Positive_008ebff8;
          *(char **)((int)pvVar7 + (local_1a0 + 1) * 4) = s_USliderPos_008ebfec;
          local_1a0 = local_1a0 + 2;
        }
        if ((local_19c.wCaps & 8) != 0) {
          *(char **)((int)pvVar6 + local_1a0 * 4) = s_V_Slider_Negative_008ec0ec;
          *(char **)((int)pvVar7 + local_1a0 * 4) = s_VSliderNeg_008ec1f8;
          *(char **)((int)pvVar6 + (local_1a0 + 1) * 4) = s_V_Slider_Positive_008ec21c;
          *(char **)((int)pvVar7 + (local_1a0 + 1) * 4) = s_VSliderPos_008ec204;
          local_1a0 = local_1a0 + 2;
        }
        *(UINT *)(param_2 + 0x5c) = local_1a0;
      }
    }
  }
  FUN_0083e885();
  return;
}

