
env = Environment( tools=["mingw"] )
env.Append(CPPPATH=["C:/MinGW/include/SDL", "../project_G/include", "./include"])
env.Append(LIBPATH=["../project_G"])
env.Append(CPPDEFINES = {"_GNU_SOURCE":"1", "_REENTRANT":""})
env.Append(LIBS=['mingw32', 'projectg', 'SDLmain', 'SDL', 'SDL_image', 'SDL_ttf'])
env.Append(CCFLAGS=['-Wall', '-Werror', '-O0', '-g'])
env.Append(LINKFLAGS='-mwindows')

SOURCES = [
        'src/block.cc',          \
		'src/figure.cc',          \
		'src/figure_factory.cc',          \
		'src/sdl_app.cc',          \
		'src/tetris_game.cc',          \
		'src/tetris_ui.cc',          \
		'src/world.cc'          \
		]

TARGET = "a.exe"
env.Clean(TARGET, ["stderr.txt","stdout.txt"])
env.Program(TARGET, SOURCES)
Default(TARGET)
