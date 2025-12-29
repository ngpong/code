FROM centos:8.4.2105

RUN echo -e '\nproxy=http://192.168.31.177:7890' | tee -a /etc/yum.conf

RUN sed -i "s/mirror.centos.org/vault.centos.org/g" /etc/yum.repos.d/*.repo && \
  sed -i "s/^#.*baseurl=http/baseurl=http/g" /etc/yum.repos.d/*.repo && \
  sed -i "s/^mirrorlist=http/#mirrorlist=http/g" /etc/yum.repos.d/*.repo && \
  yum clean all && \
  yum -y makecache && \
  yum -y update

RUN yum -y groupinstall "Development Tools"
RUN yum install -y epel-release vim wget bzip2 \
  mc which dos2unix \
  redhat-lsb-core python2 python2-pip \
  mariadb-devel python2-devel \
  sqlite-devel readline-devel \
  gdbm-devel bzip2-devel \
  ncurses-devel binutils-devel
RUN ln -s /usr/bin/python2 /usr/bin/python && \
  pip2 install scons && \
  pip2 install sqlobject

WORKDIR /src
