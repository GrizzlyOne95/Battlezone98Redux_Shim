
undefined4 FUN_00663de0(undefined4 param_1,int *param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  uVar2 = (**(code **)(*param_2 + 4))("Direct3D9 Rendering Subsystem",0);
  cVar1 = FUN_00427270(uVar2);
  if (cVar1 == '\0') {
    uVar2 = (**(code **)(*param_2 + 4))("Direct3D11 Rendering Subsystem");
    cVar1 = FUN_00427270(uVar2);
    if (cVar1 == '\0') {
      uVar2 = (**(code **)(*param_2 + 4))("OpenGL Rendering Subsystem");
      cVar1 = FUN_00427270(uVar2);
      if (cVar1 == '\0') {
        basic_string<>(&DAT_008a1ad8);
      }
      else {
        basic_string<>(&DAT_0089202c);
      }
    }
    else {
      basic_string<>(" DX11");
    }
  }
  else {
    basic_string<>(&DAT_008a1ad8);
  }
  return param_1;
}

