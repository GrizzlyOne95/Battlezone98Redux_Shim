
void __thiscall
FUN_00499ab0(undefined4 param_1,undefined4 param_2,float param_3,int param_4,undefined4 param_5)

{
  float local_20;
  undefined8 local_1c;
  undefined1 local_14 [12];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (param_4 == 0) {
    local_1c = FUN_00497780(param_2,DAT_00917594,&local_20,param_1);
  }
  else {
    FUN_00820180(local_14,param_2,1,param_4);
    local_1c = FUN_00497780(local_14,DAT_00917594,&local_20,param_1);
  }
  FUN_0068ad00(DAT_00917580,local_1c,(int)(local_20 * param_3),0x10,param_5,0);
  FUN_0083e885();
  return;
}

