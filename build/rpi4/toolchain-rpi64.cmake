set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# مسیر sysroot ARM
set(CMAKE_SYSROOT /home/asus/proj/qt/rpi4_sysroot)
set(CMAKE_STAGING_PREFIX /home/asus/proj/qt/rpi4_sysroot)

set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc-12)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++-12)

# نحوه جستجو
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)   # ابزار میزبان روی x86_64
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)   # کتابخانه‌ها داخل sysroot
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)   # هدرها داخل sysroot
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)   # پکیج‌ها داخل sysroot
set(OPENGL_gl_LIBRARY ${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/libGL.so)
set(OPENGL_opengl_LIBRARY ${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/libGL.so)
# Qt ARM
set(Qt6_DIR /home/asus/proj/qt/rpi4_sysroot/usr/lib/aarch64-linux-gnu/cmake/Qt6)

# Qt ابزار میزبان x86_64
set(Qt6CoreTools_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt6CoreTools)
set(Qt6WidgetsTools_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt6WidgetsTools)
set(Qt6GuiTools_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt6GuiTools)

# PATH برای ابزار میزبان
set(ENV{PATH} "/usr/lib/x86_64-linux-gnu/qt6/bin:$ENV{PATH}")
add_compile_definitions(_XOPEN_SOURCE=700)
add_compile_definitions(L_tmpnam=20)
