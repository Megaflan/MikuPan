include(FetchContent)

FetchContent_Declare(
        sdl3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.26
)

FetchContent_MakeAvailable(sdl3)