
undefined4 FUN_00837fd1(undefined4 param_1)

{
  code *pcVar1;
  int iVar2;
  
  FUN_0082c058(param_1,"_LOADLIB");
  FUN_0082cc15(param_1,FUN_00837e65,0);
  FUN_0082d102(param_1,0xfffffffe,&DAT_0087d000);
  FUN_0082c2f0(param_1,"package",&PTR_s_loadlib_0086fed0);
  FUN_0082cdd2(param_1,0xffffffff);
  FUN_0082cfd8(param_1,0xffffd8ef);
  FUN_0082c68b(param_1,4,0);
  iVar2 = 0;
  pcVar1 = FUN_008379d8;
  while (pcVar1 != (code *)0x0) {
    FUN_0082cc15(param_1,pcVar1,0);
    iVar2 = iVar2 + 1;
    FUN_0082cf37(param_1,0xfffffffe,iVar2);
    pcVar1 = (code *)(&PTR_FUN_0086ff00)[iVar2];
  }
  FUN_0082d102(param_1,0xfffffffe,"loaders");
  FUN_008382b3(param_1,&DAT_0087a548,"LUA_PATH",
               ".\\?.lua;!\\lua\\?.lua;!\\lua\\?\\init.lua;!\\?.lua;!\\?\\init.lua");
  FUN_008382b3(param_1,"cpath","LUA_CPATH",".\\?.dll;!\\?.dll;!\\loadall.dll");
  FUN_0082cd08(param_1,"\\\n;\n?\n!\n-",9);
  FUN_0082d102(param_1,0xfffffffe,"config");
  FUN_0082bc6c(param_1,0xffffd8f0,"_LOADED",2);
  FUN_0082d102(param_1,0xfffffffe,"loaded");
  FUN_0082c68b(param_1,0,0);
  FUN_0082d102(param_1,0xfffffffe,"preload");
  FUN_0082cdd2(param_1,0xffffd8ee);
  FUN_0082c2f0(param_1,0,&PTR_s_module_0086fee8);
  FUN_0082d226(param_1,0xfffffffe);
  return 1;
}

