Name:		signing-milter
Version:	20110301
%define		debian_version %{version}01
Release:	1.1
Summary:	Sign email via milter protocol
License:	GNU GPL version 2
Group:		Productivity/Networking/Email/Utilities
Url:		http://andreasschulze.de/signing-milter
Source:		http://andreasschulze.de/signing-milter/signing-milter_%{debian_version}.tar.gz
BuildRoot:	%{_tmppath}/%{name}
BuildRequires:	pwdutils, sendmail-devel >= 8.14, tinycdb-devel >= 0.77
%if 0%{?sles_version} == 9
%define		openssl_version 0.9.8o
Source2:	http://www.openssl.org/source/openssl-%{openssl_version}.tar.gz
%else
BuildRequires:	openssl-devel
%endif
Requires:	cron

%description
signing-milter  uses  the  milter  interface, originally distributed as
part of version 8.11 of sendmail(8), to  provide  signing  service  for
mail transiting a milter-aware MTA.

%prep
%setup -n %{name}-%{debian_version}

%build
%if 0%{?sles_version} == 9
# SSL selber bauen
gzip -cd %{S:2} | tar xf -
cd openssl-%{openssl_version}
./config threads no-rc5 no-idea no-zlib --prefix=/usr
make depend
make
make INSTALL_PREFIX=`pwd`/../openssl-%{openssl_version}-inst/ install
SSL_INCDIR="`pwd`/../openssl-%{openssl_version}-inst/usr/include/"
SSL_LIBDIR="`pwd`/../openssl-%{openssl_version}-inst/usr/lib/"
export SSL_INCDIR SSL_LIBDIR
cd ..
%endif

make

%install
make DESTDIR=%{buildroot} install

%pre
getent group signing-milter 2>/dev/null || {
  groupadd -o -g 30053 signing-milter || :
}
getent passwd signing-milter 2>/dev/null || {
  useradd -o -u 30053 -g signing-milter -c "signing-milter" -d /etc/signing-milter -s /bin/false signing-milter || :
  chage --lastday -1 --mindays -1 --maxdays -1 --warndays -1 --inactive -1 --expiredate -1 signing-milter || :
}

%post
if [ ! -L /etc/service/signing-milter ]; then
    echo " - richte signing-milter ein ( starte aber noch nicht )"
    touch /var/lib/supervise/signing-milter/down
    ln -s ../../var/lib/supervise/signing-milter /etc/service/ || :
else 
    echo "- starte signing-milter neu"
    /usr/bin/svc -t /var/lib/supervise/signing-milter || :
fi

%files
%defattr(-,root,root)
%doc INSTALL README debian/changelog debian/copyright
%config %{_sysconfdir}/cron.daily/signing-milter
%config %{_sysconfdir}/cron.hourly/signing-milter
%config(noreplace) %{_sysconfdir}/default/signing-milter
%attr(0750,root,signing-milter) %dir %{_sysconfdir}/signing-milter/
%{_sbindir}/signing-milter
%{_mandir}/man8/signing-milter.8*
%dir %{_prefix}/share/signing-milter/
%{_prefix}/share/signing-milter/run_signing-milter
%dir /var/lib/supervise/signing-milter/
/var/lib/supervise/signing-milter/run

%changelog
* Sun Aug 22 2010 <signing-milter@andreasschulze.de> - 20100822
- komplettes Changelog nur unter
  /usr/share/doc/packages/signing-milter/changelog
