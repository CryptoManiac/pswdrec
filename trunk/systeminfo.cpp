#include <sys/utsname.h>

#include "systeminfo.h"
#include <QFile>

SystemInfo::SystemInfo() : QObject() {
}

QString getOS() {

    QString os_str_ = "Unknown";

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
        if ( QFile::exists(osInfo[i].file) ) {
            char buffer[128];

            QFile f( osInfo[i].file );
            f.open( QIODevice::ReadOnly );
            f.readLine( buffer, 128 );
            QString desc(buffer);

            desc = desc.trimmed();

            switch (osInfo[i].flags) {
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
    return os_str_;
}
QString localHostName() {
    struct utsname u;
    uname(&u);
    QString hostName;
    hostName.sprintf("%s", u.nodename);
    return hostName;
}

QString kernelVersion() {
    struct utsname u;
    uname(&u);
    QString kernel;
    kernel = u.release;
    return kernel;
}

QDomDocument SystemInfo::collect() {
    QDomDocument doc;
    QDomElement root = doc.createElement("System info");
    doc.appendChild(root);


    QDomElement tag = doc.createElement("Distro");
    root.appendChild(tag);
    QDomText t = doc.createTextNode(getOS());
    tag.appendChild(t);


    tag = doc.createElement("Kernel version");
    root.appendChild(tag);
    t = doc.createTextNode(kernelVersion());
    tag.appendChild(t);

    tag = doc.createElement("Host name");
    root.appendChild(tag);
    t = doc.createTextNode(localHostName());
    tag.appendChild(t);

    return doc;
}

SystemInfo* SystemInfo::instance() {
    if (!instance_)
        instance_ = new SystemInfo();
    return instance_;
}

SystemInfo* SystemInfo::instance_ = NULL;
