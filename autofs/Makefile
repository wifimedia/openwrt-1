#
# Author: Zhifeng Gu <guzhifeng1979@hotmail.com> 
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
#

include $(TOPDIR)/rules.mk

PKG_NAME:=autofs
PKG_VERSION:=5.1.1
PKG_RELEASE:=3

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=http://www.kernel.org/pub/linux/daemons/autofs/v5
# PKG_MD5SUM:=a1d262cb6ebef0c2dd0fe22232fb3d5a
PKG_INSTALL:=1
PKG_FIXUP:=autoreconf
PKG_REMOVE_FILES:=

AUTOFS_MODS := parse_sun.so \
	mount_nfs4.so mount_nfs.so mount_generic.so mount_changer.so mount_bind.so mount_autofs.so mount_afs.so \
	lookup_userhome.so lookup_program.so lookup_multi.so lookup_hosts.so lookup_files.so lookup_file.so lookup_dir.so

AUTOFS_EXT2_MODS := mount_ext2.so mount_ext3.so mount_ext4.so

include $(INCLUDE_DIR)/package.mk

define Package/autofs5/common
  SECTION:=utils
  CATEGORY:=Utilities
  SUBMENU:=Filesystem
  TITLE:=Autofs Userspace Daemon
  MAINTAINER:=Zhifeng Gu <guzhifeng1979@hotmail.com>
  URL:=http://www.kernel.org/pub/linux/daemons/autofs/
endef

define Package/autofs5
  $(call Package/autofs5/common)
  DEPENDS+= +kmod-fs-autofs4 +libpthread +librpc +blkid
endef

define Package/autofs5/description
  Autofs controls the operation of the automount daemons. The
  automount daemons automatically mount filesystems when they
  are used and unmount them after a period of inactivity. This
  is done based on a set of pre-configured maps.

  The kernel automounter implements an almost complete SunOS
  style automounter under Linux. A recent version of the kernel
  autofs4 module (builtin or separate) is required.
endef


define Package/autofs5-mount-ext2
  $(call Package/autofs5/common)
  DEPENDS+= +autofs5 +e2fsprogs
endef

define Package/autofs5-mount-ext2/description
  This module enables fsck when mounting ext2/3/4 filesystems.
endef

define Package/autofs5/conffiles
/etc/autofs.conf
/etc/auto.master
/etc/auto.misc
/etc/auto.net
/etc/auto.smb
endef

CONFIGURE_ARGS +=	--with-openldap=no \
			--with-sasl=no \
			--with-fifodir=/var/run \
			ac_cv_path_UMOUNT=/bin/umount \
			ac_cv_path_MOUNT=/bin/mount \
			ac_cv_path_E2FSCK=/usr/sbin/e2fsck \
			ac_cv_path_E3FSCK=/usr/sbin/e2fsck \
			ac_cv_path_E4FSCK=/usr/sbin/e2fsck \
			--with-flagdir=/var/run

# 			--with-confdir=/etc/autofs/conf.d \
#			--with-mapdir=/etc/autofs \

define Package/autofs5/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/automount $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/usr/lib/autofs
	for MOD in $(AUTOFS_MODS); do \
		$(CP) $(PKG_INSTALL_DIR)/usr/lib/autofs/$$$$MOD $(1)/usr/lib/autofs/; \
	done
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/autofs.init $(1)/etc/init.d/autofs
	$(INSTALL_DIR) $(1)/etc
	$(CP) $(PKG_INSTALL_DIR)/etc/auto.* $(1)/etc/
	$(CP) $(PKG_INSTALL_DIR)/etc/autofs.conf $(1)/etc/
	$(INSTALL_DIR) $(1)/etc/hotplug.d/block
	$(INSTALL_DATA) ./files/50-autofs $(1)/etc/hotplug.d/block
#	$(INSTALL_BIN) ./files/direct.fstab $(1)/lib/functions/autofs
#	ln -sf /tmp/auto.master $(1)/etc/
endef

define Package/autofs5-mount-ext2/install
	$(INSTALL_DIR) $(1)/usr/lib/autofs
	for MOD in $(AUTOFS_EXT2_MODS); do \
		$(CP) $(PKG_INSTALL_DIR)/usr/lib/autofs/$$$$MOD $(1)/usr/lib/autofs/; \
	done
endef

$(eval $(call BuildPackage,autofs5))
$(eval $(call BuildPackage,autofs5-mount-ext2))
