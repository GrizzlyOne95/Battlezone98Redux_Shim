
/* Library Function - Multiple Matches With Same Base Name
    bool __cdecl _Bitmask_includes(enum __std_fs_file_attr,enum __std_fs_file_attr)
    bool __cdecl _Bitmask_includes(enum __std_fs_stats_flags,enum __std_fs_stats_flags)
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
   Studio 2019 Release */

bool __thiscall Bitmask_includes(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_005cc020(param_2,param_3,param_1);
  return iVar1 != 0;
}

