project('Yugimeme_Interface', 'cpp')

EXECUTABLE_NAME = 'yugimemegui'

gtkmm_dep = dependency('gtkmm-4.0', version: '>= 4.16.0')
exe_file = executable(EXECUTABLE_NAME, 'main.cpp', 'mainWindow.cpp', 
  dependencies: gtkmm_dep,
)

