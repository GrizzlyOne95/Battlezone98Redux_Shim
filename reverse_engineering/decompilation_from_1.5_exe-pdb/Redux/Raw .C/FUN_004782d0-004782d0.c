
void __fastcall FUN_004782d0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  float10 fVar3;
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  float local_24;
  float local_20;
  int local_1c;
  int local_18;
  float local_14;
  undefined1 local_10 [4];
  int *local_c;
  int local_8;
  
  local_8 = param_1;
  uVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x24));
  *(undefined4 *)(local_8 + 0x18) = uVar2;
  if (*(int *)(local_8 + 0x18) == 0) {
    *(undefined4 *)(local_8 + 0xc) = 0xd;
  }
  else {
    uVar2 = (**(code **)(*(int *)(*(int *)(local_8 + 0x18) + 0x18) + 0xc))();
    uVar2 = (**(code **)(*(int *)(*(int *)(local_8 + 0x10) + 0x18) + 0xc))(uVar2);
    fVar3 = (float10)FUN_00462010(uVar2);
    local_24 = (float)fVar3;
    if (*(float *)(local_8 + 0x134) <= local_24) {
      local_18 = 0;
      local_20 = 1e+30;
      local_1c = *(int *)(local_8 + 0x104) + 8;
      FUN_0042d8c0(local_10);
      while( true ) {
        uVar2 = FID_conflict_begin(local_2c);
        cVar1 = FUN_00420f10(uVar2);
        if (cVar1 == '\0') break;
        local_c = (int *)FUN_0042de50();
        if ((*local_c != *(int *)(local_8 + 0x10)) &&
           ((*(int *)(local_c[1] + 8) == 0xb || (*(int *)(local_c[1] + 0xc) == 0xb)))) {
          uVar2 = (**(code **)(*(int *)(*local_c + 0x18) + 0xc))();
          uVar2 = (**(code **)(*(int *)(*(int *)(local_8 + 0x10) + 0x18) + 0xc))(uVar2);
          fVar3 = (float10)FUN_00462010(uVar2);
          local_14 = (float)fVar3;
          if ((local_14 <= 22500.0) && (local_14 <= local_20)) {
            local_18 = *local_c;
            local_20 = local_14;
          }
        }
        FUN_00438c10(local_28,0);
      }
      if (local_18 == 0) {
        *(undefined4 *)(local_8 + 0x14) = *(undefined4 *)(local_8 + 0x24);
        *(undefined4 *)(local_8 + 0xc) = 0xb;
      }
      else {
        uVar2 = FUN_00462380();
        *(undefined4 *)(local_8 + 0x14) = uVar2;
        *(undefined4 *)(local_8 + 0xc) = 4;
      }
    }
    else {
      *(undefined4 *)(local_8 + 0x14) = *(undefined4 *)(local_8 + 0x24);
      *(undefined4 *)(local_8 + 0xc) = 2;
    }
  }
  return;
}

