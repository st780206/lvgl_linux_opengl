#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# Check autoconf version
AC_PREREQ([2.69])

# Init autoconf (PROJECT_NAME / PROJECT_VERSION / DEVELOPER E-MAIL)
AC_INIT([cameraapp], [1.0.0], [jjongspi@telechips.com])

AC_CONFIG_HEADERS([config.h])

# Init automake
AM_INIT_AUTOMAKE([foreign subdir-objects])

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX

# Checks for libraries.
AC_CHECK_LIB([pthread], [pthread_join], , )

# Checks for header files.
#AC_CHECK_HEADERS([fcntl.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MMAP
AC_CHECK_FUNCS([munmap])

#
# Set kernel path
# ===============
# KERNEL_DIR
#
AC_ARG_VAR(KERNEL_DIR, "Set kernel header path")
AC_SUBST([KERNEL_DIR])

#
# Set machine & board type
# ========================
# MACH_TYPE: if tcc893x, tcc896x, tcc897x then HDMI_V1.4
# BOARD_TYPE: if lcnv2 then -DNO_HPD_CEC_EDID
#
#AC_SUBST([ARCH], [arm])
#AC_SUBST([MACH], [tcc803x])

# Declare the output files to be created
AC_CONFIG_FILES([Makefile project/Makefile])

# Declare the end of autoconf
AC_OUTPUT

