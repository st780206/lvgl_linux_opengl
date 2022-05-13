DESCRIPTION = "chs camera app for alpine"
SECTION = "applications"
LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

SRC_URI = "file://*"

UPDATE_RCD := "${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'systemd', 'update-rc.d', d)}"

inherit autotools pkgconfig ${UPDATE_RCD}

DEPENDS += "virtual/kernel"
DEPENDS += "virtual/egl"
DEPENDS += "virtual/libgles1"
DEPENDS += "virtual/libgles2"
DEPENDS += "variation"
DEPENDS += "opencv"
#PATCHTOOL = "git"

S = "${WORKDIR}"
INHIBIT_PACKAGE_STRIP = "1"

# for systemd
SYSTEMD_PACKAGES = "${PN}"
SYSTEMD_SERVICE_${PN} = "cameraapp.service"

# for sysvinit
INIT_NAME = "cameraapp"
INITSCRIPT_NAME = "${INIT_NAME}"
INITSCRIPT_PARAMS = "start 20 S . stop 20 0 1 6 ."

EXTRA_OECONF += "KERNEL_DIR=${STAGING_KERNEL_DIR}"
CFLAGS_append = " -I${STAGING_KERNEL_BUILDDIR}/include -I${WORKDIR}/recipe-sysroot/${includedir}/opencv4"

do_install_append() {
	if ${@bb.utils.contains('DISTRO_FEATURES', 'sysvinit', 'true', 'false', d)}; then
		install -d ${D}${sysconfdir}/init.d
		install -m 0755 ${WORKDIR}/cameraapp.init.sh ${D}${sysconfdir}/init.d/${INIT_NAME}
	else
		install -d ${D}/${systemd_unitdir}/system
		install -m 644 ${WORKDIR}/cameraapp.service ${D}/${systemd_unitdir}/system
	fi
}

FILES_${PN} += " \
		${sysconfdir} \
		${@bb.utils.contains('DISTRO_FEATURES', 'systemd', '${systemd_unitdir}', '', d)} \
"


