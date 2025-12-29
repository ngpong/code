FROM centos:7.9.2009

# 基于 centos7 构建，修复了这个版本下的一些遗留的问题
#   o 修复 yum 仓库源已失效的问题
#   o 设置了 yum 的代理
#   o 升级了 glibc 版本
#   o 升级了一些基础工具的版本

RUN sed -i "s/mirror.centos.org/vault.centos.org/g" /etc/yum.repos.d/*.repo && \
  sed -i "s/^#.*baseurl=http/baseurl=http/g" /etc/yum.repos.d/*.repo && \
  sed -i "s/^mirrorlist=http/#mirrorlist=http/g" /etc/yum.repos.d/*.repo && \
  yum clean all && \
  yum -y makecache && \
  yum -y update

# RUN echo -e '\nproxy=http://192.168.31.177:7890' | tee -a /etc/yum.conf
#
# RUN sed -i "s/mirror.centos.org/vault.centos.org/g" /etc/yum.repos.d/*.repo && \
#   sed -i "s/^#.*baseurl=http/baseurl=http/g" /etc/yum.repos.d/*.repo && \
#   sed -i "s/^mirrorlist=http/#mirrorlist=http/g" /etc/yum.repos.d/*.repo
# RUN yum -y update
# # yum clean all && yum -y makecache && 
#
# RUN yum -y install centos-release-scl
# RUN sed -i "s/mirror.centos.org/vault.centos.org/g" /etc/yum.repos.d/*.repo && \
#   sed -i "s/^#.*baseurl=http/baseurl=http/g" /etc/yum.repos.d/*.repo && \
#   sed -i "s/^mirrorlist=http/#mirrorlist=http/g" /etc/yum.repos.d/*.repo
#
# RUN yum -y groupinstall "Development Tools"
# RUN yum -y install epel-release scl-utils scl-utils-build \
#   vim wget \
#   bison python3 bzip2 
#
# WORKDIR /src
#
# RUN wget https://mirrors.aliyun.com/gnu/gcc/gcc-7.4.0/gcc-7.4.0.tar.gz && \
#   tar -zxvf gcc-7.4.0.tar.gz && \
#   mkdir -p gcc-7.4.0/build && \ 
#   rm -rf gcc-7.4.0.tar.gz && \
#   cd gcc-7.4.0 && \
#   ./contrib/download_prerequisites && \
#   cd build && \
#   ../configure --enable-languages=c,c++ --enable-default-pie --disable-multilib --disable-bootstrap --disable-checking --disable-werror --prefix=/usr && \
#   make -j16 && \
#   make install && \
#   cd /src && \
#   rm -rf gcc-7.4.0
#
# # RUN wget https://mirrors.aliyun.com/gnu/make/make-4.3.tar.gz && \
# #   tar -zxvf make-4.3.tar.gz && \
# #   mkdir -p make-4.3/build && \
# #   rm -rf make-4.3.tar.gz && \
# #   cd make-4.3/build && \
# #   ../configure --prefix=/usr && \
# #   make -j16 && \
# #   make install && \
# #   cd /src && \
# #   rm -rf make-4.3
#
# # RUN wget https://mirrors.aliyun.com/gnu/binutils/binutils-2.30.tar.gz && \
# #   tar -zxvf binutils-2.30.tar.gz && \
# #   rm -rf binutils-2.30.tar.gz && \
# #   cd binutils-2.30 && \
# #   ./configure --prefix=/usr && \
# #   make -j16 && \
# #   make install && \
# #   cd /src && \
# #   rm -rf binutils-2.30
#
# # 修复 glibc 在 make install 后出现错误的问题
# #  REF: https://web.archive.org/web/20240716142520/https://sourceware.org/bugzilla/attachment.cgi?id=11157
# #  REF: https://blog.csdn.net/freflying1119/article/details/141937402
# RUN wget https://ftp.gnu.org/gnu/glibc/glibc-2.25.tar.gz && \
#   tar -zxvf glibc-2.25.tar.gz && \
#   mkdir -p glibc-2.25/build && \
#   rm -rf glibc-2.25.tar.gz && \
#   cd glibc-2.25/build && \
#   # cd glibc-2.25 && \
#   # sed -i '126c\\t&& $name ne "nss_test1" && $name ne "nss_test2" && $name ne "nss_nis" && $name ne "nss_nisplus" && $name ne "libgcc_s") {' scripts/test-installation.pl && \
#   # cd build && \
#   ../configure --prefix=/usr --disable-profile --enable-add-ons --with-headers=/usr/include --with-binutils=/usr/bin && \
#   make -j16
#
# # RUN wget https://ftp.gnu.org/gnu/glibc/glibc-2.25.tar.gz && \
# #   tar -zxvf glibc-2.25.tar.gz && \
# #   mkdir -p glibc-2.25/build && \
# #   rm -rf glibc-2.25.tar.gz && \
# #   cd glibc-2.25/build && \
# #   # cd glibc-2.25 && \
# #   # sed -i '126c\\t&& $name ne "nss_test1" && $name ne "nss_test2" && $name ne "nss_nis" && $name ne "nss_nisplus" && $name ne "libgcc_s") {' scripts/test-installation.pl && \
# #   # cd build && \
# #   ../configure --prefix=/usr --disable-profile --enable-add-ons --with-headers=/usr/include --with-binutils=/usr/bin && \
# #   make -j16 && \
# #   make install && \
# #   make localedata/install-locales && \
# #   ldconfig && \
# #   cd /src && \
# #   rm -rf glibc-2.25
#
# WORKDIR /src
