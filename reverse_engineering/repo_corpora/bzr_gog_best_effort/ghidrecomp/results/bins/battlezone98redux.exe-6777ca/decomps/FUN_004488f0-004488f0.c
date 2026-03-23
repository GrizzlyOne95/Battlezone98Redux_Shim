
undefined4 * __thiscall FUN_004488f0(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = FUN_0083e820(param_3);
  puVar2 = (undefined4 *)FUN_00416430(param_2,uVar1);
  FUN_004486f0(*puVar2,puVar2[1],param_3);
  *param_1 = boost::thread_exception::vftable;
  return param_1;
}

