
/* Library Function - Multiple Matches With Same Base Name
    enum __std_fs_copy_options __cdecl operator&(enum __std_fs_copy_options,enum
   __std_fs_copy_options)
    enum __std_fs_stats_flags __cdecl operator&(enum __std_fs_stats_flags,enum __std_fs_stats_flags)
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
   Studio 2019 Release */

uint operator&(uint param_1,uint param_2)

{
  return param_1 & param_2;
}

