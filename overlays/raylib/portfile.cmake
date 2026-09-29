vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO raysan5/raylib
    REF 6ecf21f700642c797dd0f2f3d4b1f2c91b71711d
    SHA512 b1fa016246392efcef3bb58b0be6eafbe067bb8a69546fd06fa95c138de1c6686cffbe16cd7ab13d189c31051df62766d95432a866caa7fb2775434acda5ae43
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        -DBUILD_EXAMPLES=OFF
        -DBUILD_GAMES=OFF
        -DBUILD_SHARED_LIBS=OFF
        -DUSE_EXTERNAL_GLFW=OFF
        -DCUSTOMIZE_BUILD=OFF
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup(CONFIG_PATH lib/cmake/raylib)
vcpkg_fixup_pkgconfig()

file(REMOVE_RECURSE
    "${CURRENT_PACKAGES_DIR}/debug/include"
    "${CURRENT_PACKAGES_DIR}/debug/share"
)

vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE")