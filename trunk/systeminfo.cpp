#include <QFileInfo>
#include <sys/utsname.h>

#include "systeminfo.h"

#include <QDebug>

SystemInfo::SystemInfo() : QObject()
{

        os_str_ = "Unknown";
	
	// Detect

	struct utsname u;
	uname(&u);
        os_str_ = u.sysname;

	// get description about os
	enum LinuxName {
		LinuxNone = 0,

		LinuxMandrake,
		LinuxDebian,
		LinuxRedHat,
		LinuxGentoo,
		LinuxSlackware,
		LinuxSuSE,
		LinuxConectiva,
		LinuxCaldera,
		LinuxLFS,

		LinuxASP, // Russian Linux distros
		LinuxALT,

		LinuxPLD, // Polish Linux distros
		LinuxAurox,
		LinuxArch
	};

	enum OsFlags {
		OsUseName = 0,
		OsUseFile,
		OsAppendFile
	};

	struct OsInfo {
		LinuxName id;
		OsFlags flags;
		QString file;
		QString name;
	} osInfo[] = {
		{ LinuxMandrake,	OsUseFile,	"/etc/mandrake-release",	"Mandrake Linux"	},
		{ LinuxDebian,		OsAppendFile,	"/etc/debian_version",		"Debian GNU/Linux"	},
		{ LinuxGentoo,		OsUseFile,	"/etc/gentoo-release",		"Gentoo Linux"		},
		{ LinuxSlackware,	OsAppendFile,	"/etc/slackware-version",	"Slackware Linux"	},
		{ LinuxPLD,		OsUseFile,	"/etc/pld-release",		"PLD Linux"		},
		{ LinuxAurox,		OsUseName,	"/etc/aurox-release",		"Aurox Linux"		},
		{ LinuxArch,		OsUseFile,	"/etc/arch-release",		"Arch Linux"		},
		{ LinuxLFS,		OsAppendFile,	"/etc/lfs-release",		"LFS Linux"		},

		// untested
		{ LinuxSuSE,		OsUseFile,	"/etc/SuSE-release",		"SuSE Linux"		},
		{ LinuxConectiva,	OsUseFile,	"/etc/conectiva-release",	"Conectiva Linux"	},
		{ LinuxCaldera,		OsUseFile,	"/etc/.installed",		"Caldera Linux"		},

		// many distros use the /etc/redhat-release for compatibility, so RedHat will be the last :)
		{ LinuxRedHat,		OsUseFile,	"/etc/redhat-release",		"RedHat Linux"		},

		{ LinuxNone,		OsUseName,	"",				""			}
	};

	for (int i = 0; osInfo[i].id != LinuxNone; i++) {
		QFileInfo fi( osInfo[i].file );
		if ( fi.exists() ) {
			char buffer[128];

			QFile f( osInfo[i].file );
			f.open( QIODevice::ReadOnly );
			f.readLine( buffer, 128 );
			QString desc(buffer);

                        desc = desc.trimmed ();

			switch ( osInfo[i].flags ) {
				case OsUseFile:
					os_str_ = desc;
					break;
				case OsUseName:
					os_str_ = osInfo[i].name;
					break;
				case OsAppendFile:
					os_str_ = osInfo[i].name + " (" + desc + ")";
					break;
			}

			break;
		}
	}
}

QString SystemInfo::localHostName_()
{
        struct utsname u;
        uname(&u);
        QString hostName;
        hostName.sprintf("%s", u.nodename);
        return hostName;
}

QString SystemInfo::kernelVersion()
{
        struct utsname u;
        uname(&u);
        QString kernel;
        kernel = u.release;
        return kernel;
}

SystemInfo* SystemInfo::instance()
{
	if (!instance_) 
		instance_ = new SystemInfo();
	return instance_;
}

SystemInfo* SystemInfo::instance_ = NULL;
