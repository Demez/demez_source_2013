
# "/media/demez/Shitdows/Program Files (x86)/Steam/steamapps/common/Source SDK Base 2013 Multiplayer/hl2.sh" -sw -noborder -w 1920 -h 1080 -game "%GameDir%"



host_library_paths=/home/demez/.steam/steam/ubuntu12_32/steam-runtime

PATH_GAME=$(cd "${0%/*}" && echo $PWD)
PATH_ENGINE="/media/demez/Shitdows/Program Files (x86)/Steam/steamapps/common/Source SDK Base 2013 Multiplayer"

steam_runtime_library_paths="$host_library_paths$STEAM_RUNTIME/i386/lib/i386-linux-gnu:$STEAM_RUNTIME/i386/lib:$STEAM_RUNTIME/i386/usr/lib/i386-linux-gnu:$STEAM_RUNTIME/i386/usr/lib:$STEAM_RUNTIME/amd64/lib/x86_64-linux-gnu:$STEAM_RUNTIME/amd64/lib:$STEAM_RUNTIME/amd64/usr/lib/x86_64-linux-gnu:$STEAM_RUNTIME/amd64/usr/lib"

export LD_LIBRARY_PATH="$steam_runtime_library_paths:${LD_LIBRARY_PATH-}"

export LD_LIBRARY_PATH="${PATH_ENGINE}"/bin:${LD_LIBRARY_PATH}

ulimit -n 2048

# enable nVidia threaded optimizations
export __GL_THREADED_OPTIMIZATIONS=1

export ENABLE_PATHMATCH=1

export LD_LIBRARY_PATH="${PATH_ENGINE}/bin:/home/demez/.local/share/Steam/ubuntu12_32/steam-runtime/pinned_libs_32:/home/demez/.local/share/Steam/ubuntu12_32/steam-runtime/pinned_libs_64:/usr/lib/x86_64-linux-gnu/libfakeroot:/lib/i386-linux-gnu:/usr/lib/i386-linux-gnu:/usr/local/lib:/lib/x86_64-linux-gnu:/usr/lib/x86_64-linux-gnu:/lib32:/usr/lib32:/libx32:/usr/libx32:/lib:/usr/lib:/usr/lib/i386-linux-gnu/sse2:/home/demez/.local/share/Steam/ubuntu12_32/steam-runtime/i386/lib/i386-linux-gnu:/home/demez/.local/share/Steam/ubuntu12_32/steam-runtime/i386/lib:/home/demez/.local/share/Steam/ubuntu12_32/steam-runtime/i386/usr/lib/i386-linux-gnu:/home/demez/.local/share/Steam/ubuntu12_32/steam-runtime/i386/usr/lib:/home/demez/.local/share/Steam/ubuntu12_32/steam-runtime/amd64/lib/x86_64-linux-gnu:/home/demez/.local/share/Steam/ubuntu12_32/steam-runtime/amd64/lib:/home/demez/.local/share/Steam/ubuntu12_32/steam-runtime/amd64/usr/lib/x86_64-linux-gnu:/home/demez/.local/share/Steam/ubuntu12_32/steam-runtime/amd64/usr/lib:"

cd "${PATH_ENGINE}"

"${PATH_ENGINE}"/hl2_linux "$@" -sw -noborder -w 1920 -h 1080 -dev -game "${PATH_GAME}"