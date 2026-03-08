include(FetchContent)

FetchContent_Declare(
        cglm
        GIT_REPOSITORY https://github.com/recp/cglm.git
        GIT_TAG v0.9.6
)
set(CGLM_SHARED OFF)
set(CGLM_STATIC ON)
FetchContent_MakeAvailable(cglm)