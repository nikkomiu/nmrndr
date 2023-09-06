nm_build(
    PKG_NAME Core
    PKG_TYPE STATIC
    PUBLIC_LINK_LIBRARIES
        NMM

    PRIVATE_LINK_LIBRARIES
        # TODO: split into separate package for window based rendering
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2-static>,SDL2::SDL2-static,SDL2::SDL2>
)
