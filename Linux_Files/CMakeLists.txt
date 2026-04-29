cmake_minimum_required(VERSION 3.10)
project(SemaforoLinux C)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(semaforo_exe main.c rsc_table.c)

target_link_libraries(semaforo_exe metal open_amp)

