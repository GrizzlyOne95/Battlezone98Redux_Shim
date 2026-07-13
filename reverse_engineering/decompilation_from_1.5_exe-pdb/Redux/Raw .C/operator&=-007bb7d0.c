
/* Library Function - Multiple Matches With Same Base Name
    enum __std_fs_copy_options & __cdecl operator&=(enum __std_fs_copy_options &,enum
   __std_fs_copy_options)
    enum __std_fs_stats_flags & __cdecl operator&=(enum __std_fs_stats_flags &,enum
   __std_fs_stats_flags)
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
   Studio 2019 Release */

undefined4 * operator&=(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = operator&(*param_1,param_2);
  *param_1 = uVar1;
  return param_1;
}

