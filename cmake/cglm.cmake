include(FetchContent)

FetchContent_Declare(
        cglm
        GIT_REPOSITORY https://github.com/recp/cglm.git
        GIT_TAG v0.9.6
)

FetchContent_MakeAvailable(cglm)