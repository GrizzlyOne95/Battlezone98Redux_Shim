
/* Library Function - Multiple Matches With Same Base Name
    class std::error_code __cdecl std::make_error_code(enum std::io_errc)
    class std::error_code __cdecl std::make_error_code(enum std::io_errc::io_errc)
   
   Library: Visual Studio */

undefined4 make_error_code(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = FUN_006abbb0();
  FUN_00416430(param_2,uVar1);
  return param_1;
}

