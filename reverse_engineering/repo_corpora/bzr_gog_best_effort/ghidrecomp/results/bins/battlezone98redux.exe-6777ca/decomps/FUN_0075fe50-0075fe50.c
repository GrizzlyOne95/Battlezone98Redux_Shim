
/* WARNING: Removing unreachable block (ram,0x0075fe7e) */

undefined4 __thiscall FUN_0075fe50(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined8 uVar2;
  
  uVar2 = __allmul(param_2,param_3,1000,0);
  puVar1 = (undefined4 *)FUN_006c9a90(uVar2);
  FUN_006b2940(*puVar1,puVar1[1]);
  return param_1;
}

