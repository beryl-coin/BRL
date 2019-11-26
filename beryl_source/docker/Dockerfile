FROM debian:stretch
LABEL maintainer="Beryl Developers <dev@beryl.org>"
LABEL description="Dockerised BerylCore, built from Travis"

RUN apt-get update && apt-get -y upgrade && apt-get clean && rm -fr /var/cache/apt/*

COPY bin/* /usr/bin/
