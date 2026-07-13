
void FUN_00466290(float param_1,float param_2,float param_3,float param_4,undefined4 param_5)

{
  char cVar1;
  char cVar2;
  ushort uVar3;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;
  double local_2c;
  undefined8 local_24;
  double local_1c;
  float local_14;
  undefined4 local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  cVar1 = FUN_0048fca0(param_1,param_2);
  cVar2 = FUN_0048fca0(param_3,param_4);
  if (cVar1 == cVar2) {
    DAT_00915566 = FUN_0048fbe0(param_3,param_4);
    DAT_008e7730 = 0xff;
    local_30 = FUN_00591670(DAT_00915566);
    if ((local_30 != 6) && (local_30 != 5)) {
      DAT_009173b0 = FUN_0048fc40(param_3,param_4);
      FUN_005e0bc0(param_5);
      uVar3 = FUN_00462590();
      DAT_009173b4 = ~uVar3;
      local_2c = (double)param_3;
      local_24 = 0;
      local_1c = (double)param_4;
      local_14 = param_1 - param_3;
      local_10 = 0;
      local_c = param_2 - param_4;
      local_38 = 0x3f800000;
      local_34 = FUN_00784dd0(local_2c,0,0,local_1c,local_14,0,local_c,FUN_0048fd00,&local_38);
    }
  }
  FUN_0083e885();
  return;
}

